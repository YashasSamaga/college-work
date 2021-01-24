#include "CodeGen/IRGenerator.h"

#include "AST/types.h"
#include "AST/operators.h"
#include "AST/tree.h"

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstrTypes.h"

#include <iostream>

using namespace llvm;
using namespace codegen;

static AllocaInst *CreateEntryBlockAlloca(Function* func, Type* type, const std::string& id) {
  IRBuilder<> TmpB(&func->getEntryBlock(), func->getEntryBlock().begin());
  return TmpB.CreateAlloca(type, 0, id.c_str());
}

IRGenerator::IRGenerator(std::string_view mname)
    : context(std::make_unique<LLVMContext>()),
      module(std::make_unique<Module>(mname.data(), *context)),
      builder(std::make_unique<IRBuilder<>>(*context))
{

}

void IRGenerator::dump(std::string& str) {
    raw_string_ostream os(str);        
    module->print(os, nullptr);
}

void IRGenerator::visit(const ast::TranslationUnit& node) {
    for (auto& child : node.getGlobalDeclarations())
        child->accept(*this);
}

void IRGenerator::visit(const ast::FormalParameter& param) { ASSERT(0); /* unused */ }

void IRGenerator::visit(const ast::Prototype& proto) {
    // proto.isExternal() TODO

    const auto& id = proto.getID().str();

    std::vector<std::string> argNames;
    for (const auto& param : proto.getFormals())
        argNames.push_back(param->getID());

    Function* func = module->getFunction(id);
    if (func) {
        /* function has been declared before; let's set arg names to match the names used in the latest definition */
        int i = 0;
        for (auto& arg : func->args())
            arg.setName(argNames[i++]);
        exchange_v = func;
        return;
    }

    auto* retType = getLLVMType(proto.getReturnType());

    std::vector<Type*> argTypes;
    for (const auto& param : proto.getFormals())
        argTypes.push_back(getLLVMType(param->getType()));

    FunctionType* funcType  = FunctionType::get(retType, argTypes, false);
    func = Function::Create(funcType, Function::ExternalLinkage, id, *module);
    
    {
        int i = 0;
        for (auto& arg : func->args())
            arg.setName(argNames[i++]);
    }

    exchange_v = func;
}

void IRGenerator::visit(const ast::FunctionDeclaration& decl) {
    decl.getPrototype()->accept(*this);
    // exchange_v has Function* representing the declaration
}

void IRGenerator::visit(const ast::FunctionDefinition& decl) {
    const auto& proto = decl.getPrototype();
    proto->accept(*this);

    Function* curFunc = std::get<Function*>(exchange_v);
    ASSERT(curFunc);
    ASSERT(curFunc->empty());

    BasicBlock* BB = BasicBlock::Create(*context, "entry", curFunc);
    builder->SetInsertPoint(BB);

    ScopeEnter fscope(table);
    {
        const auto& formals = proto->getFormals();

        int i = 0;
        for (auto& arg : curFunc->args()) {
            const auto& id = arg.getName();
            AllocaInst* alloca = CreateEntryBlockAlloca(curFunc, getLLVMType(formals[i]->getType()), id);
            builder->CreateStore(&arg, alloca);
            table.addAlloca(id, alloca);
            i++;
        }
    }

    decl.getBody()->accept(*this);

    // make a backup return in case body doesn't
    const auto& retType = proto->getReturnType();
    if (retType.base == ast::BaseType::Void) {
        builder->CreateRetVoid();   
    } else {
        if (retType.base == ast::BaseType::Float) {
            builder->CreateRet(ConstantFP::get(Type::getFloatTy(*context), 0.0));
        } else {
            builder->CreateRet(ConstantInt::get(getLLVMType(retType), 0));
        }
    }
    verifyFunction(*curFunc);
    exchange_v = curFunc;
}

void IRGenerator::visit(const ast::VariableDeclarationList& node) {
    for (auto& var : node.getVariableDeclarations())
        var->accept(*this);
}

void IRGenerator::visit(const ast::VariableDeclaration& node) {
    auto& id = node.getID().str();

    if (table.numScopes()) {
        /* local */
        Function* curFunc = builder->GetInsertBlock()->getParent();
        AllocaInst* alloca = CreateEntryBlockAlloca(curFunc, getLLVMType(node.getType()), id);

        auto initExpr = node.getInitExpr();
        if (initExpr) {
            initExpr->accept(*this);
            ASSERT(std::holds_alternative<Value*>(exchange_v));
            builder->CreateStore(std::get<Value*>(exchange_v), alloca);
        }

        table.addAlloca(id, alloca);
    } else {
        module->getOrInsertGlobal(id, getLLVMType(node.getType()));
        
        auto initExpr = node.getInitExpr();
        if (initExpr) {
            initExpr->accept(*this);
            ASSERT(std::holds_alternative<Value*>(exchange_v));
            Value* initVal = std::get<Value*>(exchange_v);

            GlobalVariable* var = module->getNamedGlobal(id);
            var->setInitializer(static_cast<Constant*>(initVal));
        }
    }
}

void IRGenerator::visit(const ast::CompoundStatement& cstmt) {
    ScopeEnter cscope(table);
    for (auto& stmt : cstmt.getStatementList())
        stmt->accept(*this);
}

void IRGenerator::visit(const ast::ExpressionStatement& stmt) {
    stmt.getExpr()->accept(*this);
}

void IRGenerator::visit(const ast::EmptyStatement&) { }

void IRGenerator::visit(const ast::IfStatement& stmt) {
    stmt.getCondExpr()->accept(*this);
    ASSERT(std::holds_alternative<Value*>(exchange_v));
    Value* condValue = std::get<Value*>(exchange_v);
    ASSERT(condValue->getType()->isIntegerTy(1));

    Value* condResult = builder->CreateICmpNE(condValue, ConstantInt::getFalse(*context));

    Function* curFunc = builder->GetInsertBlock()->getParent();
    BasicBlock* thenBB = BasicBlock::Create(*context, "then", curFunc);
    BasicBlock* mergeBB = BasicBlock::Create(*context, "ifmerge");

    const auto& ifBody = stmt.getIfBody();
    const auto& elseBody = stmt.getElseBody();
    if (elseBody) {
        BasicBlock* elseBB = BasicBlock::Create(*context, "else");
        builder->CreateCondBr(condResult, thenBB, elseBB);

        builder->SetInsertPoint(thenBB);
        stmt.getIfBody()->accept(*this);
        builder->CreateBr(mergeBB);

        curFunc->getBasicBlockList().push_back(elseBB);
        builder->SetInsertPoint(elseBB);
        stmt.getElseBody()->accept(*this);
        builder->CreateBr(mergeBB);
    } else {
        builder->CreateCondBr(condResult, thenBB, mergeBB);

        builder->SetInsertPoint(thenBB);
        stmt.getIfBody()->accept(*this);
        builder->CreateBr(mergeBB);
    }
    
    curFunc->getBasicBlockList().push_back(mergeBB);
    builder->SetInsertPoint(mergeBB);
}

void IRGenerator::visit(const ast::ForStatement& stmt) {
    ScopeEnter forscope(table);
    stmt.getInitStmt()->accept(*this);

    Function* curFunc = builder->GetInsertBlock()->getParent();
    BasicBlock* condBB = BasicBlock::Create(*context, "loopcond", curFunc);
    BasicBlock* bodyBB = BasicBlock::Create(*context, "loopbody");
    BasicBlock* mergeBB = BasicBlock::Create(*context, "loopmerge");
    
    builder->CreateBr(condBB);
    builder->SetInsertPoint(condBB);

    stmt.getCondStmt()->accept(*this); /* expression statement; value from expr will be forwarded */
    ASSERT(std::holds_alternative<Value*>(exchange_v));
    Value* condValue = std::get<Value*>(exchange_v);
    Value* condResult = builder->CreateICmpNE(condValue, ConstantInt::getFalse(*context));
    builder->CreateCondBr(condResult, bodyBB, mergeBB);

    curFunc->getBasicBlockList().push_back(bodyBB);
    builder->SetInsertPoint(bodyBB);
    stmt.getBody()->accept(*this);
    if (stmt.getIterExpr())
        stmt.getIterExpr()->accept(*this);
    builder->CreateBr(condBB);

    curFunc->getBasicBlockList().push_back(mergeBB);
    builder->SetInsertPoint(mergeBB);        
}

void IRGenerator::visit(const ast::WhileStatement& stmt) {
    Function* curFunc = builder->GetInsertBlock()->getParent();

    BasicBlock* condBB = BasicBlock::Create(*context, "loopcond", curFunc);
    BasicBlock* bodyBB = BasicBlock::Create(*context, "loopbody");
    BasicBlock* mergeBB = BasicBlock::Create(*context, "loopmerge");
    
    builder->CreateBr(condBB);
    builder->SetInsertPoint(condBB);

    stmt.getCondExpr()->accept(*this);
    ASSERT(std::holds_alternative<Value*>(exchange_v));
    Value* condValue = std::get<Value*>(exchange_v);
    Value* condResult = builder->CreateICmpNE(condValue, ConstantInt::getFalse(*context));
    builder->CreateCondBr(condResult, bodyBB, mergeBB);

    curFunc->getBasicBlockList().push_back(bodyBB);
    builder->SetInsertPoint(bodyBB);
    stmt.getBody()->accept(*this);
    builder->CreateBr(condBB);

    curFunc->getBasicBlockList().push_back(mergeBB);
    builder->SetInsertPoint(mergeBB);
}

void IRGenerator::visit(const ast::ReturnStatement& stmt) {
    Function* curFunc = builder->GetInsertBlock()->getParent();
    BasicBlock* retBB = BasicBlock::Create(*context, "noret", curFunc);

    if (stmt.getExpr()) {
        stmt.getExpr()->accept(*this);
        ASSERT(std::holds_alternative<Value*>(exchange_v));
        Value* retval = std::get<Value*>(exchange_v);
        exchange_v = builder->CreateRet(retval);
    } else {
        builder->CreateRetVoid();
    }
    builder->SetInsertPoint(retBB);
}

void IRGenerator::visit(const ast::ContinueStatement& stmt) { /* TODO */ }

void IRGenerator::visit(const ast::BreakStatement& stmt) { /* TODO */ }

void IRGenerator::visit(const ast::ExpressionList& exprlist) {
    for (const auto& expr : exprlist.getExprs())
        expr->accept(*this);
    // forward last exchange_v
}

void IRGenerator::visit(const ast::TernaryOpExpression& node) {
    ASSERT(node.getOp() == ast::TernaryOp::Conditional);

    node.getLHS()->accept(*this);
    ASSERT(std::holds_alternative<Value*>(exchange_v));
    Value* condValue = std::get<Value*>(exchange_v);

    Value* condResult = builder->CreateICmpNE(condValue, ConstantInt::getFalse(*context));

    Function* curFunc = builder->GetInsertBlock()->getParent();
    BasicBlock* thenBB = BasicBlock::Create(*context, "ttrue", curFunc);
    BasicBlock* elseBB = BasicBlock::Create(*context, "tfalse");
    BasicBlock* mergeBB = BasicBlock::Create(*context, "tmerge");

    builder->CreateCondBr(condResult, thenBB, elseBB);

    builder->SetInsertPoint(thenBB);
    node.getMiddle()->accept(*this);
    ASSERT(std::holds_alternative<Value*>(exchange_v));
    Value* trueValue = std::get<Value*>(exchange_v);
    builder->CreateBr(mergeBB);
    thenBB = builder->GetInsertBlock();

    curFunc->getBasicBlockList().push_back(elseBB);
    builder->SetInsertPoint(elseBB);
    node.getRHS()->accept(*this);
    ASSERT(std::holds_alternative<Value*>(exchange_v));
    Value* falseValue = std::get<Value*>(exchange_v);
    builder->CreateBr(mergeBB);
    elseBB = builder->GetInsertBlock();

    curFunc->getBasicBlockList().push_back(mergeBB);
    builder->SetInsertPoint(mergeBB);

    PHINode* phi = builder->CreatePHI(getLLVMType(node.getType()), 2, "iftmp");
    phi->addIncoming(trueValue, thenBB);
    phi->addIncoming(falseValue, elseBB);
    exchange_v = phi;
}

void IRGenerator::visit(const ast::BinaryOpExpression& node) {
    node.getLHS()->accept(*this);
    auto lhs = std::get<Value*>(exchange_v);
    auto lhsType = lhs->getType();
    Value* value, *ptr;
    if (std::holds_alternative<Value*>(exchange_addr))
        ptr = std::get<Value*>(exchange_addr);

    node.getRHS()->accept(*this);
    auto rhs = std::get<Value*>(exchange_v);
    auto rhsType = rhs->getType();

    if (lhsType->isFloatTy()) {
        ASSERT(rhsType->isFloatTy()); // AST invariant
    
        switch(node.getOp()) {
            case ast::BinaryOp::Mul: value = builder->CreateFMul(lhs, rhs); break;
            case ast::BinaryOp::Div: value = builder->CreateFDiv(lhs, rhs); break;
            case ast::BinaryOp::Rem: value = nullptr; ASSERT(0); break; // undefined
            case ast::BinaryOp::Add: value = builder->CreateFAdd(lhs, rhs); break;
            case ast::BinaryOp::Sub: value = builder->CreateFSub(lhs, rhs); break;
            case ast::BinaryOp::LessThan: value = builder->CreateFCmp(CmpInst::Predicate::FCMP_OLT, lhs, rhs); break;
            case ast::BinaryOp::GreaterThan: value = builder->CreateFCmp(CmpInst::Predicate::FCMP_OGT, lhs, rhs); break;
            case ast::BinaryOp::LessThanEqual: value = builder->CreateFCmp(CmpInst::Predicate::FCMP_OLE, lhs, rhs); break;
            case ast::BinaryOp::GreaterThanEqual: value = builder->CreateFCmp(CmpInst::Predicate::FCMP_OGE, lhs, rhs); break;
            case ast::BinaryOp::Equal: value = builder->CreateFCmp(CmpInst::Predicate::FCMP_OEQ, lhs, rhs); break;
            case ast::BinaryOp::NotEqual: value = builder->CreateFCmp(CmpInst::Predicate::FCMP_ONE, lhs, rhs); break;
            case ast::BinaryOp::LogicalAnd: value = nullptr; ASSERT(0); break; // undefined
            case ast::BinaryOp::LogicalOr: value = nullptr; ASSERT(0); break; // undefined
            case ast::BinaryOp::Assign:
                value = rhs;
                builder->CreateStore(value, ptr);
                break;
            case ast::BinaryOp::MulAssign:
                value = builder->CreateFMul(lhs, rhs);
                builder->CreateStore(value, ptr);
                break;
            case ast::BinaryOp::DivAssign:
                value = builder->CreateFDiv(lhs, rhs);
                builder->CreateStore(value, ptr);
                break;
            case ast::BinaryOp::RemAssign:
                ASSERT(0);
                break;
            case ast::BinaryOp::AddAssign:
                value = builder->CreateFAdd(lhs, rhs);
                builder->CreateStore(value, ptr);
                break;
            case ast::BinaryOp::SubAssign:
                value = builder->CreateFSub(lhs, rhs);
                builder->CreateStore(value, ptr);
                break;
        }
    } else if (lhsType->isIntegerTy()) {
        ASSERT(rhsType->isIntegerTy()); // AST invariant

        // TODO unsigned support
        switch(node.getOp()) {
            case ast::BinaryOp::Mul: value = builder->CreateMul(lhs, rhs); break;
            case ast::BinaryOp::Div: value = builder->CreateSDiv(lhs, rhs); break;
            case ast::BinaryOp::Rem: value = builder->CreateSRem(lhs, rhs); break;
            case ast::BinaryOp::Add: value = builder->CreateAdd(lhs, rhs); break;
            case ast::BinaryOp::Sub: value = builder->CreateSub(lhs, rhs); break;
            case ast::BinaryOp::LessThan: value = builder->CreateICmp(CmpInst::Predicate::ICMP_SLT, lhs, rhs); break;
            case ast::BinaryOp::GreaterThan: value = builder->CreateICmp(CmpInst::Predicate::ICMP_SGT, lhs, rhs); break;
            case ast::BinaryOp::LessThanEqual: value = builder->CreateICmp(CmpInst::Predicate::ICMP_SLE, lhs, rhs); break;
            case ast::BinaryOp::GreaterThanEqual: value = builder->CreateICmp(CmpInst::Predicate::ICMP_SGE, lhs, rhs); break;
            case ast::BinaryOp::Equal: value = builder->CreateICmp(CmpInst::Predicate::ICMP_EQ, lhs, rhs); break;
            case ast::BinaryOp::NotEqual: value = builder->CreateICmp(CmpInst::Predicate::ICMP_NE, lhs, rhs); break;
            case ast::BinaryOp::LogicalAnd:
                ASSERT(lhsType->isIntegerTy(1) && rhsType->isIntegerTy(1));
                value = builder->CreateAnd(lhs, rhs);
                break;
            case ast::BinaryOp::LogicalOr: return;
                ASSERT(lhsType->isIntegerTy(1) && rhsType->isIntegerTy(1));
                value = builder->CreateOr(lhs, rhs);
            case ast::BinaryOp::Assign:
                value = rhs;
                builder->CreateStore(value, ptr);
                break;
            case ast::BinaryOp::MulAssign:
                value = builder->CreateMul(lhs, rhs);
                builder->CreateStore(value, ptr);
                break;
            case ast::BinaryOp::DivAssign:
                value = builder->CreateSDiv(lhs, rhs);
                builder->CreateStore(value, ptr);
                break;
            case ast::BinaryOp::RemAssign:
                value = builder->CreateSRem(lhs, rhs);
                builder->CreateStore(value, ptr);
                break;
            case ast::BinaryOp::AddAssign:
                value = builder->CreateAdd(lhs, rhs);
                builder->CreateStore(value, ptr);
                break;
            case ast::BinaryOp::SubAssign:
                value = builder->CreateSub(lhs, rhs);
                builder->CreateStore(value, ptr);
                break;
        }
    }
    exchange_v = value;
}

void IRGenerator::visit(const ast::PrefixUnaryOpExpression& node) {
    Value* result;
    if (const auto& idexpr = std::dynamic_pointer_cast<ast::IDExpression>(node.getExpr())) {
        /* load and use */
        idexpr->accept(*this);
        Value* loaded = std::get<Value*>(exchange_v);
        Value* ptr = std::get<Value*>(exchange_addr);
        switch(node.getOp()) {
            case ast::UnaryOp::Increment: result = builder->CreateAdd(loaded, builder->getInt32(1)); break;
            case ast::UnaryOp::Decrement: result = builder->CreateSub(loaded, builder->getInt32(1)); break;
            case ast::UnaryOp::Plus: result = nullptr; ASSERT(0); break;
            case ast::UnaryOp::Minus: result = builder->CreateNeg(loaded); break;
            case ast::UnaryOp::LogicalNot: result = builder->CreateNot(loaded); break;
        }
        builder->CreateStore(result, ptr);
    } else if (const auto& subscriptExpr = std::dynamic_pointer_cast<ast::ArraySubscriptExpression>(node.getExpr())) {    
        subscriptExpr->accept(*this);
        Value* loaded = std::get<Value*>(exchange_v);
        Value* ptr = std::get<Value*>(exchange_addr);
        switch(node.getOp()) {
            case ast::UnaryOp::Increment: result = builder->CreateAdd(loaded, builder->getInt32(1)); break;
            case ast::UnaryOp::Decrement: result = builder->CreateSub(loaded, builder->getInt32(1)); break;
            case ast::UnaryOp::Plus: result = nullptr; ASSERT(0); break;
            case ast::UnaryOp::Minus: result = builder->CreateNeg(loaded); break;
            case ast::UnaryOp::LogicalNot: result = builder->CreateNot(loaded); break;
        }
        builder->CreateStore(result, ptr);
    } else {
        /* directly use value */
        node.getExpr()->accept(*this);
        ASSERT(std::holds_alternative<Value*>(exchange_v));
        Value* value = std::get<Value*>(exchange_v);

        switch(node.getOp()) {
            case ast::UnaryOp::Increment: ASSERT(0); break;
            case ast::UnaryOp::Decrement: ASSERT(0); break;
            case ast::UnaryOp::Plus: result = nullptr; ASSERT(0); break;
            case ast::UnaryOp::Minus: result = builder->CreateNeg(value); break;
            case ast::UnaryOp::LogicalNot: result = builder->CreateNot(value); break;
        }
    }
    exchange_v = result;
}

void IRGenerator::visit(const ast::PostfixUnaryOpExpression& node) {
    node.getExpr()->accept(*this);
    Value* loaded = std::get<Value*>(exchange_v);
    Value* ptr = std::get<Value*>(exchange_addr);

    Type* loadedType = loaded->getType();
    
    Value* result = nullptr, *const1;
    if (loadedType->isFloatTy()) {
        const1 = ConstantFP::get(loadedType, 1.0);
        switch(node.getOp()) {
            case ast::UnaryOp::Increment: result = builder->CreateFAdd(loaded, const1); break;
            case ast::UnaryOp::Decrement: result = builder->CreateFSub(loaded, const1); break;
        }
    } else {
        const1 = ConstantInt::get(loadedType, 1);
        switch(node.getOp()) {
            case ast::UnaryOp::Increment: result = builder->CreateAdd(loaded, const1); break;
            case ast::UnaryOp::Decrement: result = builder->CreateSub(loaded, const1); break;
        }
    }

    builder->CreateStore(result, ptr);
    result = loaded; // return old value
    exchange_v = result;
}

void IRGenerator::visit(const ast::ArraySubscriptExpression& expr) {
    expr.getLocationExpr()->accept(*this);
    ASSERT(std::holds_alternative<Value*>(exchange_addr));
    Value* ptr = std::get<Value*>(exchange_addr);

    expr.getSubscriptExpr()->accept(*this);
    ASSERT(std::holds_alternative<Value*>(exchange_v));
    Value* idx[1];
    idx[0] = std::get<Value*>(exchange_v);

    Value* addr = builder->CreateGEP(ptr, ArrayRef<Value*>(idx, 1));
    exchange_v = exchange_addr = addr;
    if (!expr.getType().isArray())
        exchange_v = builder->CreateLoad(addr);
}

void IRGenerator::visit(const ast::CallExpression& callexpr) {
    const auto& idexpr = std::dynamic_pointer_cast<ast::IDExpression>(callexpr.getCallee());
    Function *callee = module->getFunction(idexpr->getID().str());
    ASSERT(callee);

    std::vector<Value*> args;
    for (const auto& arg : callexpr.getArgs()) {
        arg->accept(*this);
        if (arg->getType().isArray()) {
            ASSERT(std::holds_alternative<Value*>(exchange_addr));
            args.push_back(std::get<Value*>(exchange_addr));
        } else {
            ASSERT(std::holds_alternative<Value*>(exchange_v));
            args.push_back(std::get<Value*>(exchange_v));
        }
    }
    exchange_v = builder->CreateCall(callee, args);
}

void IRGenerator::visit(const ast::CastExpression& cexpr) {
    const auto& expr = cexpr.getExpr();
    expr->accept(*this);
    ASSERT(std::holds_alternative<Value*>(exchange_v));
    Value* value = std::get<Value*>(exchange_v);

    const auto& sourceType = expr->getType();
    const auto& targetType = cexpr.getType();

    Type* source = value->getType();
    Type* target = getLLVMType(targetType);

    if (source == target) {
        exchange_v = value;
        return;
    }

    if (source->isIntegerTy() && target->isIntegerTy(1)) {
        exchange_v = builder->CreateICmpNE(value, ConstantInt::get(source, 0));
    } else if (source->isFloatTy() && target->isIntegerTy(1)) { 
        exchange_v = builder->CreateFCmpONE(value, ConstantFP::get(Type::getFloatTy(*context), 0.0));
    } else if (source->isIntegerTy() && target->isFloatTy()) {
        if (sourceType.isSigned())
            exchange_v = builder->CreateSIToFP(value, target);
        else
            exchange_v = builder->CreateUIToFP(value, target);
    } else if (source->isIntegerTy(1) && target->isIntegerTy()) {
        exchange_v = builder->CreateCast(CastInst::ZExt, value, target);
    } else if (source->isIntegerTy() && target->isIntegerTy()) {
        auto extType = cexpr.getType().isSigned() ? CastInst::SExt : CastInst::ZExt;
        exchange_v = builder->CreateCast(extType, value, target);
    } else if (source->isFloatTy() && target->isIntegerTy()) {
        if (targetType.isSigned())
            exchange_v = builder->CreateFPToSI(value, target);
        else
            exchange_v = builder->CreateFPToUI(value, target);
    } else {
        ASSERT(0);
    }
}

void IRGenerator::visit(const ast::IDExpression& idexpr) {
    const auto& id = idexpr.getID();
    if (!idexpr.getType().isArray())
        exchange_v = loadValue(id);
    exchange_addr = loadAddress(id);
}

void IRGenerator::visit(const ast::BooleanLiteral& blit) {
    Type* i1 = Type::getInt1Ty(*context); 
    exchange_v = ConstantInt::get(i1, blit.getValue(), false);
}

void IRGenerator::visit(const ast::CharacterLiteral& clit) {
    Type* i8 = Type::getInt8Ty(*context); 
    exchange_v = ConstantInt::get(i8, clit.getValue(), true);
}

void IRGenerator::visit(const ast::IntegerLiteral& ilit) {
    Type* i32 = Type::getInt32Ty(*context); 
    exchange_v = ConstantInt::get(i32, ilit.getValue(), true);
}

void IRGenerator::visit(const ast::FloatLiteral& flit) {
    Type* f32 = Type::getFloatTy(*context);
    exchange_v = ConstantFP::get(f32, flit.getValue());
}

void IRGenerator::visit(const ast::StringLiteral& slit) {
    auto* i8 = Type::getInt8Ty(*context);
    const auto& str = slit.getValue();
    std::vector<llvm::Constant*> chars(str.size());
    for(int i = 0; i < str.size(); i++)
        chars[i] = ConstantInt::get(i8, str[i]);
    exchange_v = ConstantArray::get(ArrayType::get(i8, chars.size()), chars);
}

void IRGenerator::visit(const ast::ArrayLiteral&) { ASSERT(0); }

Type* IRGenerator::getLLVMBaseType(ast::BaseType type) {
   switch(type) {
        case ast::BaseType::Void: return Type::getVoidTy(*context);
        case ast::BaseType::Bool: return Type::getInt1Ty(*context);
        case ast::BaseType::Char: return Type::getInt8Ty(*context);
        case ast::BaseType::Int: return Type::getInt32Ty(*context);
        case ast::BaseType::Float: return Type::getFloatTy(*context);
    };
    ASSERT(0);
    return nullptr;
}

ArrayType* IRGenerator::getLLVMArrayType(Type* base, const std::vector<std::size_t>& dims) {
    ASSERT(!dims.empty());
    ArrayType* arrayType = ArrayType::get(base, dims[0]);
    for (int i = 1; i < dims.size(); i++)
        arrayType = ArrayType::get(arrayType, dims[i]);
    return arrayType;
}

Type* IRGenerator::getLLVMType(const ast::Type& type) {
    auto* base = getLLVMBaseType(type.base);
    if (!type.dimensions.empty())
        return getLLVMArrayType(base, type.dimensions);
    return base;
}

Value* IRGenerator::loadAddress(const std::string& id) {
    if (table.exists(id)) {
        /* local variable */
        return table.lookup(id);
    } else {
        /* global variable */
        return module->getNamedGlobal(id);
    }
}

Value* IRGenerator::loadValue(const std::string& id) {
    if (table.exists(id)) {
        /* local variable */
        return builder->CreateLoad(table.lookup(id), id.c_str());
    } else {
        /* global variable */
        GlobalVariable* var = module->getNamedGlobal(id);
        return builder->CreateLoad(var);
    }
}

StoreInst* IRGenerator::storeValue(const std::string& id, Value* value) {
    if (table.exists(id)) {
        /* local variable */
        return builder->CreateStore(value, table.lookup(id));
    } else {
        /* global variable */
        GlobalVariable* var = module->getNamedGlobal(id);
        return builder->CreateStore(value, var);
    }
}