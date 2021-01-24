#include "AST/tree.h"
#include "ExprVisitor.h"

#include "assertions.h"

#include <iostream>
#include <vector>
#include <numeric>

class ExprBuildASTVisitor : public ExprVisitor {
public:
    antlrcpp::Any visitTranslationUnit(ExprParser::TranslationUnitContext *context) override;
    antlrcpp::Any visitDeclaration(ExprParser::DeclarationContext *context) override;
    antlrcpp::Any visitVariableDeclaration(ExprParser::VariableDeclarationContext *context) override;
    antlrcpp::Any visitInitDeclarator(ExprParser::InitDeclaratorContext *context) override;
    antlrcpp::Any visitInitializer(ExprParser::InitializerContext *context) override;
    antlrcpp::Any visitFunctionDeclaration(ExprParser::FunctionDeclarationContext *context) override;
    antlrcpp::Any visitFunctionDefinition(ExprParser::FunctionDefinitionContext *context) override;
    antlrcpp::Any visitFunctionPrototype(ExprParser::FunctionPrototypeContext *context) override;
    antlrcpp::Any visitFormalParameterList(ExprParser::FormalParameterListContext *context) override;
    antlrcpp::Any visitFormalParameter(ExprParser::FormalParameterContext *context) override;
    antlrcpp::Any visitArrayDimensionList(ExprParser::ArrayDimensionListContext *context) override;
    antlrcpp::Any visitArrayDimExpr(ExprParser::ArrayDimExprContext *context) override;
    antlrcpp::Any visitEmptyStatementStat(ExprParser::EmptyStatementStatContext *context) override;
    antlrcpp::Any visitPassStatement(ExprParser::PassStatementContext *context) override;
    antlrcpp::Any visitReturnStatementStat(ExprParser::ReturnStatementStatContext *context) override;
    antlrcpp::Any visitContinueStatementStat(ExprParser::ContinueStatementStatContext *context) override;
    antlrcpp::Any visitBreakStatementStat(ExprParser::BreakStatementStatContext *context) override;
    antlrcpp::Any visitVarDeclarationStatement(ExprParser::VarDeclarationStatementContext *context) override;
    antlrcpp::Any visitCompoundStatement(ExprParser::CompoundStatementContext *context) override;
    antlrcpp::Any visitExpressionStatement(ExprParser::ExpressionStatementContext *context) override;
    antlrcpp::Any visitIfOnlyStatement(ExprParser::IfOnlyStatementContext *context) override;
    antlrcpp::Any visitIfElseStatement(ExprParser::IfElseStatementContext *context) override;
    antlrcpp::Any visitForStatement(ExprParser::ForStatementContext *context) override;
    antlrcpp::Any visitForInitStatement(ExprParser::ForInitStatementContext *context) override;
    antlrcpp::Any visitWhileStatement(ExprParser::WhileStatementContext *context) override;
    antlrcpp::Any visitIdExpression(ExprParser::IdExpressionContext *context) override;
    antlrcpp::Any visitIdentPrimaryExpr(ExprParser::IdentPrimaryExprContext *context) override;
    antlrcpp::Any visitLiteralPrimaryExpr(ExprParser::LiteralPrimaryExprContext *context) override;
    antlrcpp::Any visitParenPrimaryExpr(ExprParser::ParenPrimaryExprContext *context) override;
    antlrcpp::Any visitFallbackPostfixExpression(ExprParser::FallbackPostfixExpressionContext *context) override ;
    antlrcpp::Any visitArraySubscriptExpression(ExprParser::ArraySubscriptExpressionContext *context) override;
    antlrcpp::Any visitCallExpression(ExprParser::CallExpressionContext *context) override;
    antlrcpp::Any visitCastExpression(ExprParser::CastExpressionContext *context) override;
    antlrcpp::Any visitDoPostfixExpression(ExprParser::DoPostfixExpressionContext *context) override;
    antlrcpp::Any visitFallbackPrefixExpression(ExprParser::FallbackPrefixExpressionContext *context) override;
    antlrcpp::Any visitDoPrefixExpression(ExprParser::DoPrefixExpressionContext *context) override;
    antlrcpp::Any visitFallbackMultiplicativeExpression(ExprParser::FallbackMultiplicativeExpressionContext *context) override;
    antlrcpp::Any visitDoMultiplicativeExpression(ExprParser::DoMultiplicativeExpressionContext *context) override;
    antlrcpp::Any visitFallbackAdditiveExpression(ExprParser::FallbackAdditiveExpressionContext *context) override;
    antlrcpp::Any visitDoAdditiveExpression(ExprParser::DoAdditiveExpressionContext *context) override;
    antlrcpp::Any visitFallbackRelationalExpression(ExprParser::FallbackRelationalExpressionContext *context) override;
    antlrcpp::Any visitDoRelationalExpression(ExprParser::DoRelationalExpressionContext *context) override;
    antlrcpp::Any visitFallbackEqualityExpression(ExprParser::FallbackEqualityExpressionContext *context) override;
    antlrcpp::Any visitDoEqualityExpression(ExprParser::DoEqualityExpressionContext *context) override;
    antlrcpp::Any visitFallbackLogicalAndExpression(ExprParser::FallbackLogicalAndExpressionContext *context) override;
    antlrcpp::Any visitDoLogicalAndExpression(ExprParser::DoLogicalAndExpressionContext *context) override;
    antlrcpp::Any visitFallbackLogicalOrExpression(ExprParser::FallbackLogicalOrExpressionContext *context) override;
    antlrcpp::Any visitDoLogicalOrExpression(ExprParser::DoLogicalOrExpressionContext *context) override;
    antlrcpp::Any visitFallbackConditionalExpression(ExprParser::FallbackConditionalExpressionContext *context) override;
    antlrcpp::Any visitDoConditionalExpression(ExprParser::DoConditionalExpressionContext *context) override;
    antlrcpp::Any visitFallbackAssigmentExpression(ExprParser::FallbackAssigmentExpressionContext *context) override;
    antlrcpp::Any visitDoAssignmentExpression(ExprParser::DoAssignmentExpressionContext *context) override;
    antlrcpp::Any visitFallbackExpr(ExprParser::FallbackExprContext *context) override;
    antlrcpp::Any visitDoExpressionList(ExprParser::DoExpressionListContext *context) override;
    antlrcpp::Any visitConstantExpression(ExprParser::ConstantExpressionContext *context) override;
    antlrcpp::Any visitType(ExprParser::TypeContext *context) override;
    antlrcpp::Any visitTypemodifier(ExprParser::TypemodifierContext *context) override;
    antlrcpp::Any visitType_name(ExprParser::Type_nameContext *context) override;
    antlrcpp::Any visitLiteral(ExprParser::LiteralContext *context) override;
    antlrcpp::Any visitBoolLiteral(ExprParser::BoolLiteralContext *context) override;
    antlrcpp::Any visitCharLiteral(ExprParser::CharLiteralContext *context) override;
    antlrcpp::Any visitIntegerLiteral(ExprParser::IntegerLiteralContext *context) override;
    antlrcpp::Any visitFloatLiteral(ExprParser::FloatLiteralContext *context) override;
    antlrcpp::Any visitStringLiteral(ExprParser::StringLiteralContext *context) override;
    antlrcpp::Any visitArrayLiteral(ExprParser::ArrayLiteralContext *context) override;
    antlrcpp::Any visitArrayLiteralList(ExprParser::ArrayLiteralListContext *context) override;
};