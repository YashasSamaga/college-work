
// Generated from Expr.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "ExprParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ExprParser.
 */
class  ExprVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ExprParser.
   */
    virtual antlrcpp::Any visitTranslationUnit(ExprParser::TranslationUnitContext *context) = 0;

    virtual antlrcpp::Any visitDeclaration(ExprParser::DeclarationContext *context) = 0;

    virtual antlrcpp::Any visitVariableDeclaration(ExprParser::VariableDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitInitDeclarator(ExprParser::InitDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitInitializer(ExprParser::InitializerContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDeclaration(ExprParser::FunctionDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDefinition(ExprParser::FunctionDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitFunctionPrototype(ExprParser::FunctionPrototypeContext *context) = 0;

    virtual antlrcpp::Any visitFormalParameterList(ExprParser::FormalParameterListContext *context) = 0;

    virtual antlrcpp::Any visitFormalParameter(ExprParser::FormalParameterContext *context) = 0;

    virtual antlrcpp::Any visitArrayDimensionList(ExprParser::ArrayDimensionListContext *context) = 0;

    virtual antlrcpp::Any visitArrayDimExpr(ExprParser::ArrayDimExprContext *context) = 0;

    virtual antlrcpp::Any visitPassStatement(ExprParser::PassStatementContext *context) = 0;

    virtual antlrcpp::Any visitEmptyStatementStat(ExprParser::EmptyStatementStatContext *context) = 0;

    virtual antlrcpp::Any visitReturnStatementStat(ExprParser::ReturnStatementStatContext *context) = 0;

    virtual antlrcpp::Any visitContinueStatementStat(ExprParser::ContinueStatementStatContext *context) = 0;

    virtual antlrcpp::Any visitBreakStatementStat(ExprParser::BreakStatementStatContext *context) = 0;

    virtual antlrcpp::Any visitVarDeclarationStatement(ExprParser::VarDeclarationStatementContext *context) = 0;

    virtual antlrcpp::Any visitCompoundStatement(ExprParser::CompoundStatementContext *context) = 0;

    virtual antlrcpp::Any visitExpressionStatement(ExprParser::ExpressionStatementContext *context) = 0;

    virtual antlrcpp::Any visitIfOnlyStatement(ExprParser::IfOnlyStatementContext *context) = 0;

    virtual antlrcpp::Any visitIfElseStatement(ExprParser::IfElseStatementContext *context) = 0;

    virtual antlrcpp::Any visitForStatement(ExprParser::ForStatementContext *context) = 0;

    virtual antlrcpp::Any visitForInitStatement(ExprParser::ForInitStatementContext *context) = 0;

    virtual antlrcpp::Any visitWhileStatement(ExprParser::WhileStatementContext *context) = 0;

    virtual antlrcpp::Any visitIdExpression(ExprParser::IdExpressionContext *context) = 0;

    virtual antlrcpp::Any visitIdentPrimaryExpr(ExprParser::IdentPrimaryExprContext *context) = 0;

    virtual antlrcpp::Any visitLiteralPrimaryExpr(ExprParser::LiteralPrimaryExprContext *context) = 0;

    virtual antlrcpp::Any visitParenPrimaryExpr(ExprParser::ParenPrimaryExprContext *context) = 0;

    virtual antlrcpp::Any visitCastExpression(ExprParser::CastExpressionContext *context) = 0;

    virtual antlrcpp::Any visitCallExpression(ExprParser::CallExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDoPostfixExpression(ExprParser::DoPostfixExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFallbackPostfixExpression(ExprParser::FallbackPostfixExpressionContext *context) = 0;

    virtual antlrcpp::Any visitArraySubscriptExpression(ExprParser::ArraySubscriptExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFallbackPrefixExpression(ExprParser::FallbackPrefixExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDoPrefixExpression(ExprParser::DoPrefixExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDoMultiplicativeExpression(ExprParser::DoMultiplicativeExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFallbackMultiplicativeExpression(ExprParser::FallbackMultiplicativeExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDoAdditiveExpression(ExprParser::DoAdditiveExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFallbackAdditiveExpression(ExprParser::FallbackAdditiveExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFallbackRelationalExpression(ExprParser::FallbackRelationalExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDoRelationalExpression(ExprParser::DoRelationalExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDoEqualityExpression(ExprParser::DoEqualityExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFallbackEqualityExpression(ExprParser::FallbackEqualityExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDoLogicalAndExpression(ExprParser::DoLogicalAndExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFallbackLogicalAndExpression(ExprParser::FallbackLogicalAndExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDoLogicalOrExpression(ExprParser::DoLogicalOrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFallbackLogicalOrExpression(ExprParser::FallbackLogicalOrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFallbackConditionalExpression(ExprParser::FallbackConditionalExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDoConditionalExpression(ExprParser::DoConditionalExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFallbackAssigmentExpression(ExprParser::FallbackAssigmentExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDoAssignmentExpression(ExprParser::DoAssignmentExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFallbackExpr(ExprParser::FallbackExprContext *context) = 0;

    virtual antlrcpp::Any visitDoExpressionList(ExprParser::DoExpressionListContext *context) = 0;

    virtual antlrcpp::Any visitConstantExpression(ExprParser::ConstantExpressionContext *context) = 0;

    virtual antlrcpp::Any visitType(ExprParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitTypemodifier(ExprParser::TypemodifierContext *context) = 0;

    virtual antlrcpp::Any visitType_name(ExprParser::Type_nameContext *context) = 0;

    virtual antlrcpp::Any visitLiteral(ExprParser::LiteralContext *context) = 0;

    virtual antlrcpp::Any visitBoolLiteral(ExprParser::BoolLiteralContext *context) = 0;

    virtual antlrcpp::Any visitCharLiteral(ExprParser::CharLiteralContext *context) = 0;

    virtual antlrcpp::Any visitIntegerLiteral(ExprParser::IntegerLiteralContext *context) = 0;

    virtual antlrcpp::Any visitFloatLiteral(ExprParser::FloatLiteralContext *context) = 0;

    virtual antlrcpp::Any visitStringLiteral(ExprParser::StringLiteralContext *context) = 0;

    virtual antlrcpp::Any visitArrayLiteral(ExprParser::ArrayLiteralContext *context) = 0;

    virtual antlrcpp::Any visitArrayLiteralList(ExprParser::ArrayLiteralListContext *context) = 0;


};

