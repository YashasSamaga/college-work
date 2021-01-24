#include "AST/Passes/TypeInference.h"

#include "AST/types.h"
#include "AST/operators.h"
#include "AST/tree.h"
#include "AST/identifier.h"
#include "AST/SymbolTable.h"
#include "AST/build_utils.h"

#include <iostream>

using ast::LookupMode;
using ast::SymbolType;
using ast::ScopeEnter;
using ast::ScopeType;

template <class T>
void finalizeArrayType(T& param, bool paramOrVar) {
    const auto& dimExprs = param.getDimExprs();
    if (!dimExprs.empty()) {
        std::vector<std::size_t> dims;
        for (auto& expr : dimExprs) {
            int size = 0;
            if (expr) {
                if (auto p = std::dynamic_pointer_cast<ast::IntegerLiteral>(expr)) {
                    size = p->getValue();
                    if (size <= 0) {
                        std::cout << "error: array size must evaluate to a positive integer (assuming zero)";
                        size = 0;
                    }
                } else {
                    std::cout << "error: array dimensions must an constexpr integer expression (assuming zero)";
                }
            } else {
                // size deduction
                if (!paramOrVar)
                    std::cout << "error: size deduction is not supported yet" << std::endl;
            }
            dims.push_back(size);
        }

        auto type = param.getType();
        type.dimensions = std::move(dims);
        param.setType(type);
    }
}

bool arePrototypesCompatible(const ast::Prototype& first, const ast::Prototype& second) {
    if (first.getReturnType() != second.getReturnType())
        return false;

    if (first.getID() != second.getID())
        return false;
    
    const auto& formalsFirst = first.getFormals(),
                formalsSecond = second.getFormals();
    if (formalsFirst.size() != formalsSecond.size())
        return false;
    
    for (int i = 0; i < formalsFirst.size(); i++) {
        if (formalsFirst[i]->getType() != formalsSecond[i]->getType())
            return false;
    }

    return true;
}

TypeInference::TypeInference() : currentFunction(nullptr) { }

void TypeInference::visit(ast::TranslationUnit& node) {
    symtab = ast::SymbolTable(); // create global scope
    for (auto& child : node.getGlobalDeclarations())
        child->accept(*this);
}

void TypeInference::visit(ast::FormalParameter& param) {
    finalizeArrayType(param, true);
    if (param.getID()) { /* we ignore nameless parameters */
        if (symtab.exists(param.getID(), LookupMode::CurrentScope)) {
            std::cout << "error: a formal parameter with id \"" << param.getID() << "\" already defined (ignoring the second declaration)" << std::endl;
            return;
        }
        symtab.emplaceSymbol(param.getID(), SymbolType::FormalParameter, param);
    }
}

void TypeInference::visit(ast::Prototype& proto) {
    if (proto.getReturnType().isArray())
        std::cout << "error: returning arrays is not allowed\n";

    for (auto& param : proto.getFormals())
        param->accept(*this);
}

void TypeInference::visit(ast::FunctionDeclaration& decl) {
    auto proto = decl.getPrototype();
    const auto& fname = proto->getID();

    if (symtab.numScopes() > 1) {
        std::cout << "error: attempting to declare a function \"" << fname << "\" in non-global scope; ignoring declaration\n";
        return;
    }

    {
        ScopeEnter fake(ScopeType::Function, symtab);
        proto->accept(*this);
        // process formal parameters and release scope
    }

    auto prevs = symtab.lookupAll(fname, LookupMode::Global);
    for (auto sym : prevs) {
        switch (sym->getType()) {
            case SymbolType::FunctionDeclaration:
            {
                auto& proto2 = sym->getNodeAs<ast::FunctionDeclaration>().getPrototype();
                if (!arePrototypesCompatible(*proto, *proto2)) {
                    std::cout << "error: prototype for \"" << fname << "\" does not match a previous declaration/definition; ignoring declaration\n";
                    return;
                }
                break;
            }
            case SymbolType::FunctionDefinition:
            {
                auto& proto2 = sym->getNodeAs<ast::FunctionDeclaration>().getPrototype();
                if (!arePrototypesCompatible(*proto, *proto2)) {
                    std::cout << "error: prototype for \"" << fname << "\" does not match a previous declaration/definition; ignoring declaration\n";
                    return;
                }
                break;
            }
            case SymbolType::FormalParameter: ASSERT(0); return;
            case SymbolType::Variable:
                std::cout << "error: forward function declaration uses id \"" << fname << " which is already in use by a global variable; ignoring declaration\"\n";
                return;
        }
    }

    symtab.emplaceSymbol(fname, SymbolType::FunctionDeclaration, decl);
}

void TypeInference::visit(ast::FunctionDefinition& decl) {
    auto proto = decl.getPrototype();
    const auto& fname = proto->getID();
    
    if (proto->isExternal()) {
        std::cout << "error: 'extern' function \"" << fname << "\" cannot have a definition\n";
        return;        
    }

    if (symtab.numScopes() > 1) {
        std::cout << "error: attempting to define a function \"" << fname << "\" in non-global scope; ignoring declaration\n";
        return;
    }

    auto prevs = symtab.lookupAll(fname, LookupMode::Global);
    for (auto sym : prevs) {
        switch (sym->getType()) {
            case SymbolType::FunctionDeclaration:
            {
                auto& proto2 = sym->getNodeAs<ast::FunctionDeclaration>().getPrototype();
                if (!arePrototypesCompatible(*proto, *proto2)) {
                    std::cout << "error: prototype for \"" << fname << "\" does not match a previous declaration; ignoring declaration\n";
                    return;
                }
                break;
            }
            case SymbolType::FunctionDefinition:
                std::cout << "error: redefinition of function \"" << fname << "\"; ignoring new definition\n";
                return;
            case SymbolType::FormalParameter: ASSERT(0); return;
            case SymbolType::Variable:
                std::cout << "error: function definition uses id \"" << fname << " which is already in use by a global variable; ignoring definition\"\n";
                return;
        }
    }

    symtab.emplaceSymbol(fname, SymbolType::FunctionDefinition, decl);
    {
        ScopeEnter funcParamScope(ScopeType::Function, symtab);
        decl.getPrototype()->accept(*this);

        currentFunction = &decl;
        try {
            decl.getBody()->accept(*this); // will introduce a new scope downstream
        } catch(...) {
            currentFunction = nullptr;
            throw;
        }
    }
}

void TypeInference::visit(ast::VariableDeclarationList& node) {
    auto varDecls = node.getVariableDeclarations();
    for (int i = 0; i < varDecls.size(); i++)
        varDecls[i]->accept(*this);
}

void TypeInference::visit(ast::VariableDeclaration& var) {
    finalizeArrayType(var, false);

    const auto& id = var.getID();
    if (symtab.exists(id, LookupMode::CurrentScope)) {
        std::cout << "error: variable \"" << static_cast<std::string_view>(id) << "\" already defined" << std::endl;
        return;
    }
    symtab.emplaceSymbol(id, SymbolType::Variable, var);

    if (auto& initExpr = var.getInitExpr()) {
        initExpr->accept(*this);

        const auto& varType = var.getType();
        const auto& initType = initExpr->getType();

        if (!ast::isConvertibleOrSame(varType, initType)) {
            std::cout << "error: initializer type does not agree with variable type\n";
            return;
        }

        if (ast::isImplicitConversionRequired(varType, initType)) {
            auto newInitExpr = make_shared_expr<ast::CastExpression>(var.getType(), initExpr); // implicit conversion
            var.setInitExpr(newInitExpr);
        }
    }
}

void TypeInference::visit(ast::CompoundStatement& cstmt) {
    ScopeEnter compoundScope(ScopeType::Compound, symtab);
    for (auto& stmt : cstmt.getStatementList())
        stmt->accept(*this);
}

void TypeInference::visit(ast::ExpressionStatement& stmt) {
    stmt.getExpr()->accept(*this);
}

void TypeInference::visit(ast::EmptyStatement&) { }

void TypeInference::visit(ast::IfStatement& stmt) {
    auto& condExpr = stmt.getCondExpr();
    condExpr->accept(*this);
    
    const auto& condType = condExpr->getType();
    const auto& requiredType = ast::Type(ast::BaseType::Bool);

    if (!ast::isConvertibleOrSame(condType, requiredType)) {
        std::cout << "error: if condition is not convertible to bool\n";
        return;
    }

    if (ast::isImplicitConversionRequired(condType, requiredType)) {
        auto newCondExpr = make_shared_expr<ast::CastExpression>(requiredType, condExpr); // implicit conversion
        stmt.setCondExpr(newCondExpr);
    }
    
    stmt.getIfBody()->accept(*this);
    if (stmt.getElseBody())
        stmt.getElseBody()->accept(*this);
}

void TypeInference::visit(ast::ForStatement& stmt) {
    ScopeEnter forScope(ScopeType::For, symtab);

    stmt.getInitStmt()->accept(*this);
    
    auto& condStmt = stmt.getCondStmt();
    condStmt->accept(*this);

    if (auto exprStmt = std::dynamic_pointer_cast<ast::ExpressionStatement>(condStmt)) {
        auto& condExpr = exprStmt->getExpr();

        const auto& condType = condExpr->getType();
        const auto& requiredType = ast::Type(ast::BaseType::Bool);

        if (!ast::isConvertibleOrSame(condType, requiredType)) {
            std::cout << "error: for condition is not convertible to bool\n";
            return;
        }

        if (ast::isImplicitConversionRequired(condType, requiredType)) {
            auto newCondExpr = make_shared_expr<ast::CastExpression>(requiredType, condExpr); // implicit conversion
            exprStmt->setExpr(newCondExpr);
        }
    } else if (auto emptyStmt = std::dynamic_pointer_cast<ast::EmptyStatement>(condStmt)) {
        auto trueLiteral = make_shared_stmt<ast::ExpressionStatement>(make_shared_expr<ast::BooleanLiteral>(true));
        stmt.setCondStmt(trueLiteral);
        trueLiteral->accept(*this);
    } else {
        ASSERT(0);
    }

    if (stmt.getIterExpr())
        stmt.getIterExpr()->accept(*this);
    stmt.getBody()->accept(*this);
}

void TypeInference::visit(ast::WhileStatement& stmt) {
    auto& condExpr = stmt.getCondExpr();
    condExpr->accept(*this);

    const auto& condType = condExpr->getType();
    const auto& requiredType = ast::Type(ast::BaseType::Bool);

    if (!ast::isConvertibleOrSame(condType, requiredType)) {
        std::cout << "error: while condition is not convertible to bool\n";
        return;
    }

    if (ast::isImplicitConversionRequired(condType, requiredType)) {
        auto newCondExpr = make_shared_expr<ast::CastExpression>(requiredType, condExpr); // implicit conversion
        stmt.setCondExpr(newCondExpr);
    }
    
    stmt.getBody()->accept(*this);
}

void TypeInference::visit(ast::ReturnStatement& stmt) {
    ASSERT(currentFunction);
    auto& retExpr = stmt.getExpr();
    auto& expectedReturnType = currentFunction->getPrototype()->getReturnType();
    if (retExpr) {
        retExpr->accept(*this);

        const auto& retType = retExpr->getType();
        if (!ast::isConvertibleOrSame(retType, expectedReturnType)) {
            std::cout << "error: return type does not match with function signature\n";
            return;
        }

        if (ast::isImplicitConversionRequired(retType, expectedReturnType)) {
            auto newReturnExpr = make_shared_expr<ast::CastExpression>(expectedReturnType, retExpr); // implicit conversion
            stmt.setExpr(newReturnExpr);
        }
    } else {
        if (expectedReturnType.base != ast::BaseType::Void)
            std::cout << "error: function expects a value to be returned\n";
    }
}

void TypeInference::visit(ast::ContinueStatement& stmt) { }
void TypeInference::visit(ast::BreakStatement& stmt) { }

void TypeInference::visit(ast::ExpressionList& exprlist) {
    auto exprs = exprlist.getExprs();
    for (auto& expr : exprs)
        expr->accept(*this);
    exprlist.setType(exprs.back()->getType());
}

void TypeInference::visit(ast::TernaryOpExpression& node) {
    ASSERT(node.getOp() == ast::TernaryOp::Conditional); // only ternary op supported currently

    const auto& lhs = node.getLHS();
    lhs->accept(*this);

    const auto& mid = node.getMiddle();
    mid->accept(*this);

    const auto& rhs = node.getRHS();
    rhs->accept(*this);

    // lhs = cond, middle = true branch, rhs = false branch
    if (mid->getType() != rhs->getType()) {
        std::cout << "error: types of true and false branch of ternary operator do not match (assuming true branch type)\n";
    }

    node.setType(mid->getType());
}

void TypeInference::visit(ast::BinaryOpExpression& node) {
    const auto& lhs = node.getLHS();
    lhs->accept(*this);
    const auto& lhsType = lhs->getType();

    const auto& rhs = node.getRHS();
    rhs->accept(*this);
    const auto& rhsType = rhs->getType();

    auto op = node.getOp();
    switch(op) {
        case ast::BinaryOp::Assign:
        case ast::BinaryOp::MulAssign:
        case ast::BinaryOp::DivAssign:
        case ast::BinaryOp::RemAssign:
        case ast::BinaryOp::AddAssign:
        case ast::BinaryOp::SubAssign:
            if (lhsType.qualifiers.count(ast::TypeQualifier::Const))
                std::cout << "error: assignment to a const qualified location\n";
    }

    if (!ast::areCompatibleTypes(op, lhsType, rhsType)) {
        std::cout << "error: invalid binary operation\n";
        return;
    }

    auto promotedType = ast::GetCombinedType(op, lhsType, rhsType);

    if (ast::isImplicitConversionRequired(lhsType, promotedType)) {
        auto newExpr = make_shared_expr<ast::CastExpression>(promotedType, lhs); // implicit conversion
        node.setLHS(newExpr);
    }

    if (ast::isImplicitConversionRequired(rhsType, promotedType)) {
        auto newExpr = make_shared_expr<ast::CastExpression>(promotedType, rhs); // implicit conversion
        node.setRHS(newExpr);
    }

    node.setType(promotedType);
}

void TypeInference::visit(ast::PrefixUnaryOpExpression& node) {
    auto& expr = node.getExpr();
    expr->accept(*this);
    node.setType(expr->getType());
}

void TypeInference::visit(ast::PostfixUnaryOpExpression& node) {
    auto& expr = node.getExpr();
    expr->accept(*this);
    node.setType(expr->getType());
}

void TypeInference::visit(ast::ArraySubscriptExpression& expr) {
    auto locationExpr = expr.getLocationExpr();
    locationExpr->accept(*this);

    expr.getSubscriptExpr()->accept(*this);

    auto arrType = locationExpr->getType();
    if (arrType.dimensions.empty()) {
        std::cout << "error: indexing non-arrays is not allowed\n";
        return;
    }

    arrType.dimensions.erase(arrType.dimensions.begin());
    expr.setType(arrType);
}

void TypeInference::visit(ast::CallExpression& callexpr) {
    callexpr.setType(ast::Type(ast::BaseType::Void)); // default error type

    auto func_b = callexpr.getCallee();
    auto func = std::dynamic_pointer_cast<ast::IDExpression>(func_b);
    const auto& id = func->getID();

    std::shared_ptr<ast::Prototype> proto;
    if (auto sym = symtab.lookup(id, LookupMode::BottomUp)) {
        switch (sym->getType()) {
            case SymbolType::FunctionDeclaration:
            {
                proto = sym->getNodeAs<ast::FunctionDeclaration>().getPrototype();
                func->setRefSymbol(*sym);
                callexpr.setType(proto->getReturnType());
                break;
            }
            case SymbolType::FunctionDefinition:
            {
                proto = sym->getNodeAs<ast::FunctionDefinition>().getPrototype();
                func->setRefSymbol(*sym);
                callexpr.setType(proto->getReturnType());
                break;
            }
            case SymbolType::FormalParameter:
            case SymbolType::Variable:
                std::cout << "error: variable \"" << id << "\" cannot be called as a function\n";
                return;
        }
    } else {
        std::cout << "error: undeclared use of identifier\"" << id << "\"\n";
        return;
    }

    auto& formals = proto->getFormals();
    auto args = callexpr.getArgs();
    if (formals.size() != args.size()) {
        std::cout << "error: number of arguments do not match requirements\n";
        return;
    }

    for (int i = 0; i < args.size(); i++) {
        args[i]->accept(*this);
        
        auto& argType = args[i]->getType();
        auto& formalType = formals[i]->getType();

        if (!ast::isConvertibleOrSame(argType, formalType)) {
            std::cout << "error: argument type does not match with formal parameter\n";
            return;
        }

        if (ast::isImplicitConversionRequired(argType, formalType))
            args[i] = make_shared_expr<ast::CastExpression>(formalType, args[i]); // implicit conversion
    }
    callexpr.setArgs(args);
}

void TypeInference::visit(ast::CastExpression& expr) { expr.getExpr()->accept(*this); }

void TypeInference::visit(ast::IDExpression& expr) {
    const auto& id = expr.getID();
    if (auto sym = symtab.lookup(id, LookupMode::BottomUp)) {
        switch (sym->getType()) {
            case SymbolType::FunctionDeclaration:
            case SymbolType::FunctionDefinition:
                std::cout << "error: function \"" << id << "\" cannot be used as values\n";
                return;
            case SymbolType::FormalParameter:
            {
                const auto& var = sym->getNodeAs<ast::FormalParameter>();
                expr.setRefSymbol(*sym);
                expr.setType(var.getType());
                return;     
            }
            case SymbolType::Variable:
            {
                const auto& var = sym->getNodeAs<ast::VariableDeclaration>();
                expr.setRefSymbol(*sym);
                expr.setType(var.getType());
                return;     
            }       
        }
    } else {
        std::cout << "error: undeclared use of identifier\"" << id << "\"\n";
        return;
    }
    ASSERT(0);
}

void TypeInference::visit(ast::BooleanLiteral& blit) { }
void TypeInference::visit(ast::CharacterLiteral& clit) { }
void TypeInference::visit(ast::IntegerLiteral& ilit) { }
void TypeInference::visit(ast::FloatLiteral& flit) { }

void TypeInference::visit(ast::StringLiteral& slit) { }
void TypeInference::visit(ast::ArrayLiteral&) { }