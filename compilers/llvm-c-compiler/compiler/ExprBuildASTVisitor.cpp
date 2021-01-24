#include "ExprBuildASTVisitor.h"
#include "ExprLexer.h"

#include "AST/build_utils.h"
#include "assertions.h"

#include <iostream>
#include <vector>
#include <numeric>
#include <memory>
#include <unordered_map>

// returns the casted pointer of type To from a pointer of type From
template <class To, class From = ast::ASTBase>
std::shared_ptr<To> get_derived(antlrcpp::Any any) {
    std::shared_ptr<From> bptr = any;
    return std::dynamic_pointer_cast<To>(bptr);
}

antlrcpp::Any ExprBuildASTVisitor::visitTranslationUnit(ExprParser::TranslationUnitContext *context) {
    auto tu = std::make_shared<ast::TranslationUnit>();
    for (auto decl : context->declaration()) {
        std::shared_ptr<ast::ASTBase> d = visit(decl);
        ASSERT(d);
        tu->add(std::move(d));
    }
    return tu;
}

antlrcpp::Any ExprBuildASTVisitor::visitDeclaration(ExprParser::DeclarationContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitVariableDeclaration(ExprParser::VariableDeclarationContext *context) {
    ast::Type type = visit(context->type());
    std::vector<std::shared_ptr<ast::VariableDeclaration>> declarations;
    for (auto decl : context->initDeclarator()) {
        using declorTuple = std::tuple<ast::Identifier, std::vector<std::shared_ptr<ast::ExpressionBase>>, std::shared_ptr<ast::ExpressionBase>>;
        auto [id, dims, init] = visit(decl).as<declorTuple>();
        auto varDecl = std::make_shared<ast::VariableDeclaration>(std::move(id), type, std::move(dims), std::move(init));
        declarations.push_back(varDecl);
    }
    return make_shared_ast<ast::VariableDeclarationList>(declarations);
}

antlrcpp::Any ExprBuildASTVisitor::visitInitDeclarator(ExprParser::InitDeclaratorContext *context) {
    auto id = ast::Identifier(context->IDENT()->getText());
    ASSERT(id);

    auto arrayDimensionList_c = context->arrayDimensionList();
    std::vector<std::shared_ptr<ast::ExpressionBase>> arrayDimensionList;
    if (arrayDimensionList_c)
        arrayDimensionList = visit(arrayDimensionList_c).as<std::vector<std::shared_ptr<ast::ExpressionBase>>>();
    
    auto initializer_c = context->initializer();
    std::shared_ptr<ast::ExpressionBase> initializer;
    if (initializer_c) {
        std::shared_ptr<ast::ASTBase> astNode = visit(initializer_c);
        initializer = std::dynamic_pointer_cast<ast::ExpressionBase>(astNode);
        ASSERT(initializer);
    }

    return std::tuple(id, arrayDimensionList, initializer);
}

antlrcpp::Any ExprBuildASTVisitor::visitInitializer(ExprParser::InitializerContext *context) {
    ASSERT(context->children.size() == 2);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitFunctionDeclaration(ExprParser::FunctionDeclarationContext *context) {
    auto prototype = get_derived<ast::Prototype>(visit(context->functionPrototype()));
    return make_shared_ast<ast::FunctionDeclaration>(prototype);
}

antlrcpp::Any ExprBuildASTVisitor::visitFunctionDefinition(ExprParser::FunctionDefinitionContext *context) {
    std::shared_ptr<ast::ASTBase> prototype = visit(context->functionPrototype());

    std::shared_ptr<ast::ASTBase> stmt = visit(context->compoundStatement());
    auto bodyCompoundStmt = std::dynamic_pointer_cast<ast::StatementBase>(stmt);
    
    return make_shared_ast<ast::FunctionDefinition>(std::dynamic_pointer_cast<ast::Prototype>(prototype),
                                                    std::dynamic_pointer_cast<ast::CompoundStatement>(bodyCompoundStmt));
}

antlrcpp::Any ExprBuildASTVisitor::visitFunctionPrototype(ExprParser::FunctionPrototypeContext *context) {

    bool external = (context->EXTERN() != nullptr);

    ast::Type type = visit(context->type());

    std::vector<std::shared_ptr<ast::FormalParameter>> formalParameterList;
    auto formalParameterList_c = context->formalParameterList();
    if (formalParameterList_c)
        formalParameterList = visit(context->formalParameterList()).as<std::vector<std::shared_ptr<ast::FormalParameter>>>();
    
    auto id = ast::Identifier(context->IDENT()->getText());
    
    return make_shared_ast<ast::Prototype>(type, id, formalParameterList, external);

}

antlrcpp::Any ExprBuildASTVisitor::visitFormalParameterList(ExprParser::FormalParameterListContext *context) {
    std::vector<std::shared_ptr<ast::FormalParameter>> params;
    for (auto param : context->formalParameter())
        params.push_back(get_derived<ast::FormalParameter>(visit(param)));
    return params;
}

antlrcpp::Any ExprBuildASTVisitor::visitFormalParameter(ExprParser::FormalParameterContext *context) {
    auto type = visit(context->type());
    auto id = context->IDENT();
    auto arrayDimensionList_c = context->arrayDimensionList();
    std::vector<std::shared_ptr<ast::ExpressionBase>> arrayDimensionList;
    if (arrayDimensionList_c)
        arrayDimensionList = visit(arrayDimensionList_c).as<std::vector<std::shared_ptr<ast::ExpressionBase>>>();    
    return make_shared_ast<ast::FormalParameter>(id ? id->getText() : "", type, std::move(arrayDimensionList));
}

antlrcpp::Any ExprBuildASTVisitor::visitArrayDimensionList(ExprParser::ArrayDimensionListContext *context) {
    std::vector<std::shared_ptr<ast::ExpressionBase>> exprs;
    for (auto dimExpr : context->arrayDimExpr()) {
        if (dimExpr) {
            std::shared_ptr<ast::ASTBase> astNode = visit(dimExpr);
            auto exprNode = std::dynamic_pointer_cast<ast::ExpressionBase>(astNode);
            exprs.push_back(exprNode);
        }
        else
            exprs.push_back(nullptr);
    }
    return exprs;        
}

antlrcpp::Any ExprBuildASTVisitor::visitArrayDimExpr(ExprParser::ArrayDimExprContext *context) {
    auto constExpr = context->constantExpression();
    if (constExpr)
        return visit(constExpr);
    return std::shared_ptr<ast::ASTBase>(nullptr);
}

antlrcpp::Any ExprBuildASTVisitor::visitEmptyStatementStat(ExprParser::EmptyStatementStatContext *context) {
    return make_shared_ast<ast::EmptyStatement>();
}

antlrcpp::Any ExprBuildASTVisitor::visitPassStatement(ExprParser::PassStatementContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitReturnStatementStat(ExprParser::ReturnStatementStatContext *context) {
    std::shared_ptr<ast::ASTBase> expr = visit(context->expr());
    return make_shared_ast<ast::ReturnStatement>(std::dynamic_pointer_cast<ast::ExpressionBase>(expr));
}

antlrcpp::Any ExprBuildASTVisitor::visitContinueStatementStat(ExprParser::ContinueStatementStatContext *context) {
    return make_shared_ast<ast::ContinueStatement>();
}

antlrcpp::Any ExprBuildASTVisitor::visitBreakStatementStat(ExprParser::BreakStatementStatContext *context) {
    return make_shared_ast<ast::BreakStatement>();
}

antlrcpp::Any ExprBuildASTVisitor::visitVarDeclarationStatement(ExprParser::VarDeclarationStatementContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitCompoundStatement(ExprParser::CompoundStatementContext *context) {
    std::vector<std::shared_ptr<ast::StatementBase>> statements;
    for (auto stmt : context->statement())
        statements.push_back(get_derived<ast::StatementBase>(visit(stmt)));
    return make_shared_ast<ast::CompoundStatement>(statements);
}

antlrcpp::Any ExprBuildASTVisitor::visitExpressionStatement(ExprParser::ExpressionStatementContext *context) {
    std::shared_ptr<ast::ExpressionBase> expr;
    if (context->expr())
        expr = get_derived<ast::ExpressionBase>(visit(context->expr()));
    if (!expr)
        return make_shared_ast<ast::EmptyStatement>();
    return make_shared_ast<ast::ExpressionStatement>(expr);
}

antlrcpp::Any ExprBuildASTVisitor::visitIfOnlyStatement(ExprParser::IfOnlyStatementContext *context) {
    std::shared_ptr<ast::ASTBase> condExpr = visit(context->expr()),
                                  bodyStmt = visit(context->statement());
    return make_shared_ast<ast::IfStatement>(std::dynamic_pointer_cast<ast::ExpressionBase>(condExpr),
                                            std::dynamic_pointer_cast<ast::StatementBase>(bodyStmt));
}

antlrcpp::Any ExprBuildASTVisitor::visitIfElseStatement(ExprParser::IfElseStatementContext *context) {
    std::shared_ptr<ast::ASTBase> condExpr = visit(context->expr()),
                                  ifBodyStmt = visit(context->statement(0)),
                                  elseBodyStmt = visit(context->statement(1));
    return make_shared_ast<ast::IfStatement>(std::dynamic_pointer_cast<ast::ExpressionBase>(condExpr),
                                            std::dynamic_pointer_cast<ast::StatementBase>(ifBodyStmt),
                                            std::dynamic_pointer_cast<ast::StatementBase>(elseBodyStmt));
}

antlrcpp::Any ExprBuildASTVisitor::visitForStatement(ExprParser::ForStatementContext *context) {
    std::shared_ptr<ast::ASTBase> initStmt = visit(context->forInitStatement()),
                                  condStmt = visit(context->expressionStatement()),
                                  iterExpr,
                                  bodyStmt = visit(context->statement());
    if (context->expr())
        iterExpr = visit(context->expr());
    return make_shared_ast<ast::ForStatement>(std::dynamic_pointer_cast<ast::StatementBase>(initStmt), // not strictly a statement since decls are allowed
                                              std::dynamic_pointer_cast<ast::StatementBase>(condStmt),
                                              std::dynamic_pointer_cast<ast::ExpressionBase>(iterExpr),
                                              std::dynamic_pointer_cast<ast::StatementBase>(bodyStmt));
}

antlrcpp::Any ExprBuildASTVisitor::visitForInitStatement(ExprParser::ForInitStatementContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitWhileStatement(ExprParser::WhileStatementContext *context) {
    std::shared_ptr<ast::ASTBase> condExpr = visit(context->expr()),
                                    bodyStmt = visit(context->statement());
    return make_shared_ast<ast::WhileStatement>(std::dynamic_pointer_cast<ast::ExpressionBase>(condExpr),
                                                std::dynamic_pointer_cast<ast::StatementBase>(bodyStmt));;
}

antlrcpp::Any ExprBuildASTVisitor::visitIdExpression(ExprParser::IdExpressionContext *context) {
    return make_shared_ast<ast::IDExpression>(context->IDENT()->getText());
}

antlrcpp::Any ExprBuildASTVisitor::visitIdentPrimaryExpr(ExprParser::IdentPrimaryExprContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitLiteralPrimaryExpr(ExprParser::LiteralPrimaryExprContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitParenPrimaryExpr(ExprParser::ParenPrimaryExprContext *context) {
    ASSERT(context->children.size() == 3);
    return visit(context->expr());
}

antlrcpp::Any ExprBuildASTVisitor::visitFallbackPostfixExpression(ExprParser::FallbackPostfixExpressionContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitArraySubscriptExpression(ExprParser::ArraySubscriptExpressionContext *context) {
    std::shared_ptr<ast::ASTBase> locationExpr = visit(context->postfixExpression()),
                                  subscriptExpr = visit(context->expr());
    return make_shared_ast<ast::ArraySubscriptExpression>(std::dynamic_pointer_cast<ast::ExpressionBase>(locationExpr),
                                                          std::dynamic_pointer_cast<ast::ExpressionBase>(subscriptExpr));
}

antlrcpp::Any ExprBuildASTVisitor::visitCallExpression(ExprParser::CallExpressionContext *context) {
    std::shared_ptr<ast::ASTBase> fexpr = visit(context->postfixExpression());
    std::vector<std::shared_ptr<ast::ExpressionBase>> args;

    if (context->expr())
    {
        std::shared_ptr<ast::ASTBase> argsExpr = visit(context->expr());
        auto argsExprList = std::dynamic_pointer_cast<ast::ExpressionList>(argsExpr);
        if (argsExprList)
            args = argsExprList->getExprs();
        else
            args.push_back(std::dynamic_pointer_cast<ast::ExpressionBase>(argsExpr));
    }
    
    return make_shared_ast<ast::CallExpression>(std::dynamic_pointer_cast<ast::ExpressionBase>(fexpr), std::move(args));
}

antlrcpp::Any ExprBuildASTVisitor::visitCastExpression(ExprParser::CastExpressionContext *context) {
    ast::Type type = visit(context->type());
    std::shared_ptr<ast::ASTBase> expr = visit(context->expr());
    return make_shared_ast<ast::CastExpression>(type, std::dynamic_pointer_cast<ast::ExpressionBase>(expr));
}

antlrcpp::Any ExprBuildASTVisitor::visitDoPostfixExpression(ExprParser::DoPostfixExpressionContext *context) {
    auto op = ast::getUnaryOpFromText(context->op->getText()).value();
    std::shared_ptr<ast::ASTBase> expr = visit(context->postfixExpression());
    return make_shared_ast<ast::PostfixUnaryOpExpression>(op, std::dynamic_pointer_cast<ast::ExpressionBase>(expr));
}

antlrcpp::Any ExprBuildASTVisitor::visitFallbackPrefixExpression(ExprParser::FallbackPrefixExpressionContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitDoPrefixExpression(ExprParser::DoPrefixExpressionContext *context) {
    auto op = ast::getUnaryOpFromText(context->op->getText()).value();
    std::shared_ptr<ast::ASTBase> expr = visit(context->prefixExpression()).as<std::shared_ptr<ast::ASTBase>>();
    return make_shared_ast<ast::PrefixUnaryOpExpression>(op, std::dynamic_pointer_cast<ast::ExpressionBase>(expr));
}

antlrcpp::Any ExprBuildASTVisitor::visitFallbackMultiplicativeExpression(ExprParser::FallbackMultiplicativeExpressionContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitDoMultiplicativeExpression(ExprParser::DoMultiplicativeExpressionContext *context)  {
    auto op = ast::getBinaryOpFromText(context->op->getText()).value();
    std::shared_ptr<ast::ASTBase> lhs = visit(context->multiplicativeExpression()),
                                    rhs = visit(context->prefixExpression());
    return make_shared_ast<ast::BinaryOpExpression>(op,
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(lhs),
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(rhs));
}

antlrcpp::Any ExprBuildASTVisitor::visitFallbackAdditiveExpression(ExprParser::FallbackAdditiveExpressionContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitDoAdditiveExpression(ExprParser::DoAdditiveExpressionContext *context)  {
    auto op = ast::getBinaryOpFromText(context->op->getText()).value();
    std::shared_ptr<ast::ASTBase> lhs = visit(context->additiveExpression()),
                                    rhs = visit(context->multiplicativeExpression());
    return make_shared_ast<ast::BinaryOpExpression>(op,
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(lhs),
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(rhs));
}

antlrcpp::Any ExprBuildASTVisitor::visitFallbackRelationalExpression(ExprParser::FallbackRelationalExpressionContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitDoRelationalExpression(ExprParser::DoRelationalExpressionContext *context) {
    auto op = ast::getBinaryOpFromText(context->op->getText()).value();
    std::shared_ptr<ast::ASTBase> lhs = visit(context->relationalExpression()),
                                    rhs = visit(context->additiveExpression());
    return make_shared_ast<ast::BinaryOpExpression>(op,
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(lhs),
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(rhs));
}

antlrcpp::Any ExprBuildASTVisitor::visitFallbackEqualityExpression(ExprParser::FallbackEqualityExpressionContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitDoEqualityExpression(ExprParser::DoEqualityExpressionContext *context) {
    auto op = ast::getBinaryOpFromText(context->op->getText()).value();
    std::shared_ptr<ast::ASTBase> lhs = visit(context->equalityExpression()),
                                  rhs = visit(context->relationalExpression());
    return make_shared_ast<ast::BinaryOpExpression>(op,
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(lhs),
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(rhs));
}

antlrcpp::Any ExprBuildASTVisitor::visitFallbackLogicalAndExpression(ExprParser::FallbackLogicalAndExpressionContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitDoLogicalAndExpression(ExprParser::DoLogicalAndExpressionContext *context) {
    std::shared_ptr<ast::ASTBase> lhs = visit(context->logicalAndExpression()),
                                  rhs = visit(context->equalityExpression());
    return make_shared_ast<ast::BinaryOpExpression>(ast::BinaryOp::LogicalAnd,
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(lhs),
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(rhs));
}

antlrcpp::Any ExprBuildASTVisitor::visitFallbackLogicalOrExpression(ExprParser::FallbackLogicalOrExpressionContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitDoLogicalOrExpression(ExprParser::DoLogicalOrExpressionContext *context) {
    std::shared_ptr<ast::ASTBase> lhs = visit(context->logicalOrExpression()),
                                    rhs = visit(context->logicalAndExpression());
    return make_shared_ast<ast::BinaryOpExpression>(ast::BinaryOp::LogicalOr,
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(lhs),
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(rhs));
}

antlrcpp::Any ExprBuildASTVisitor::visitFallbackConditionalExpression(ExprParser::FallbackConditionalExpressionContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitDoConditionalExpression(ExprParser::DoConditionalExpressionContext *context) {
    std::shared_ptr<ast::ASTBase> lhs = visit(context->logicalOrExpression()),
                                  middle = visit(context->expr()),
                                  rhs = visit(context->conditionalExpression());
    return make_shared_ast<ast::TernaryOpExpression>(ast::TernaryOp::Conditional,
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(lhs),
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(middle),
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(rhs));
}

antlrcpp::Any ExprBuildASTVisitor::visitFallbackAssigmentExpression(ExprParser::FallbackAssigmentExpressionContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitDoAssignmentExpression(ExprParser::DoAssignmentExpressionContext *context) {
    auto op = ast::getBinaryOpFromText(context->op->getText()).value();
    std::shared_ptr<ast::ASTBase> lhs = visit(context->prefixExpression()),
                                  rhs = visit(context->assignmentExpression());
    return make_shared_ast<ast::BinaryOpExpression>(op,
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(lhs),
                                                    std::dynamic_pointer_cast<ast::ExpressionBase>(rhs));
}

antlrcpp::Any ExprBuildASTVisitor::visitFallbackExpr(ExprParser::FallbackExprContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context);
}

antlrcpp::Any ExprBuildASTVisitor::visitDoExpressionList(ExprParser::DoExpressionListContext *context) {
    std::vector<std::shared_ptr<ast::ExpressionBase>> exprs;
    for (auto expr : context->assignmentExpression())
        exprs.push_back(get_derived<ast::ExpressionBase>(visit(expr)));
    return make_shared_ast<ast::ExpressionList>(exprs);
}

antlrcpp::Any ExprBuildASTVisitor::visitConstantExpression(ExprParser::ConstantExpressionContext *context) {
    ASSERT(context->children.size() == 1);
    return visit(context->conditionalExpression());
}

antlrcpp::Any ExprBuildASTVisitor::visitType(ExprParser::TypeContext *context) {
    ast::Type type;
    auto modifier = context->typemodifier();
    if (modifier != nullptr)
    {
        ast::TypeModifier m = visit(modifier);
        type.modifiers.insert(m);
    }
    type.base = visit(context->type_name());
    return type;
}

antlrcpp::Any ExprBuildASTVisitor::visitTypemodifier(ExprParser::TypemodifierContext *context) {
    using ast::TypeModifier;
    TypeModifier modifier;
    switch (context->modifier->getType())
    {
        case ExprLexer::SIGNED: modifier = TypeModifier::Signed; break;
        case ExprLexer::UNSIGNED: modifier = TypeModifier::Unsigned; break;
        default: { ASSERT(0 && "unknown modifier"); }
    }
    return modifier;
}

antlrcpp::Any ExprBuildASTVisitor::visitType_name(ExprParser::Type_nameContext *context) {
    using ast::BaseType;
    BaseType type;
    switch (context->name->getType())
    {
        case ExprLexer::VOID: type = BaseType::Void; break;
        case ExprLexer::BOOL: type = BaseType::Bool; break;
        case ExprLexer::CHAR: type = BaseType::Char; break;
        case ExprLexer::INT: type = BaseType::Int; break;
        case ExprLexer::FLOAT: type = BaseType::Float; break;
        default: { ASSERT(0 && "unknown type"); }
    }
    return type;
}

antlrcpp::Any ExprBuildASTVisitor::visitLiteral(ExprParser::LiteralContext *context) {
    ASSERT(context->children.size() == 1);
    return visitChildren(context); // forward only child to parent
}

antlrcpp::Any ExprBuildASTVisitor::visitBoolLiteral(ExprParser::BoolLiteralContext *context) {
    return make_shared_ast<ast::BooleanLiteral>(context->value->getType() == ExprLexer::TRUE ? true : false);
}

antlrcpp::Any ExprBuildASTVisitor::visitCharLiteral(ExprParser::CharLiteralContext *context) {
    auto str = context->CHARACTER_LITERAL()->getText();
    return make_shared_ast<ast::CharacterLiteral>(str[1]);
}

antlrcpp::Any ExprBuildASTVisitor::visitIntegerLiteral(ExprParser::IntegerLiteralContext *context) {
    return make_shared_ast<ast::IntegerLiteral>(std::stoi(context->INTEGER_LITERAL()->getText()));
}

antlrcpp::Any ExprBuildASTVisitor::visitFloatLiteral(ExprParser::FloatLiteralContext *context) {
    return make_shared_ast<ast::FloatLiteral>(std::stof(context->FLOAT_LITERAL()->getText()));
}

antlrcpp::Any ExprBuildASTVisitor::visitStringLiteral(ExprParser::StringLiteralContext *context) {
    auto strings = context->STRING_LITERAL();
    ASSERT(strings.size() == 1); // TODO compile-time string concatenation
    // auto str = std::accumulate(std::begin(strings), std::end(strings), std::string(), [](const auto& current, const auto& next) {
    //     return current + next->getText();
    // });
    return make_shared_ast<ast::StringLiteral>(strings[0]->getText());
}

antlrcpp::Any ExprBuildASTVisitor::visitArrayLiteral(ExprParser::ArrayLiteralContext *context) {
    return nullptr; // TODO
}

antlrcpp::Any ExprBuildASTVisitor::visitArrayLiteralList(ExprParser::ArrayLiteralListContext *context) {
    return nullptr; // TODO
}