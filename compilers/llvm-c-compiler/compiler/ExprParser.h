
// Generated from Expr.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  ExprParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    EXTERN = 33, IF = 34, ELSE = 35, FOR = 36, WHILE = 37, CONTINUE = 38, 
    BREAK = 39, RETURN = 40, SIGNED = 41, UNSIGNED = 42, INT = 43, CHAR = 44, 
    BOOL = 45, FLOAT = 46, VOID = 47, STATIC_CAST = 48, TRUE = 49, FALSE = 50, 
    IDENT = 51, COMMENT = 52, NS = 53, FLOAT_LITERAL = 54, INTEGER_LITERAL = 55, 
    CHARACTER_LITERAL = 56, STRING_LITERAL = 57
  };

  enum {
    RuleTranslationUnit = 0, RuleDeclaration = 1, RuleVariableDeclaration = 2, 
    RuleInitDeclarator = 3, RuleInitializer = 4, RuleFunctionDeclaration = 5, 
    RuleFunctionDefinition = 6, RuleFunctionPrototype = 7, RuleFormalParameterList = 8, 
    RuleFormalParameter = 9, RuleArrayDimensionList = 10, RuleArrayDimExpr = 11, 
    RuleStatement = 12, RuleCompoundStatement = 13, RuleExpressionStatement = 14, 
    RuleIfStatement = 15, RuleForStatement = 16, RuleForInitStatement = 17, 
    RuleWhileStatement = 18, RuleIdExpression = 19, RulePrimaryExpression = 20, 
    RulePostfixExpression = 21, RulePrefixExpression = 22, RuleMultiplicativeExpression = 23, 
    RuleAdditiveExpression = 24, RuleRelationalExpression = 25, RuleEqualityExpression = 26, 
    RuleLogicalAndExpression = 27, RuleLogicalOrExpression = 28, RuleConditionalExpression = 29, 
    RuleAssignmentExpression = 30, RuleExpr = 31, RuleConstantExpression = 32, 
    RuleType = 33, RuleTypemodifier = 34, RuleType_name = 35, RuleLiteral = 36, 
    RuleBoolLiteral = 37, RuleCharLiteral = 38, RuleIntegerLiteral = 39, 
    RuleFloatLiteral = 40, RuleStringLiteral = 41, RuleArrayLiteral = 42, 
    RuleArrayLiteralList = 43
  };

  ExprParser(antlr4::TokenStream *input);
  ~ExprParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class TranslationUnitContext;
  class DeclarationContext;
  class VariableDeclarationContext;
  class InitDeclaratorContext;
  class InitializerContext;
  class FunctionDeclarationContext;
  class FunctionDefinitionContext;
  class FunctionPrototypeContext;
  class FormalParameterListContext;
  class FormalParameterContext;
  class ArrayDimensionListContext;
  class ArrayDimExprContext;
  class StatementContext;
  class CompoundStatementContext;
  class ExpressionStatementContext;
  class IfStatementContext;
  class ForStatementContext;
  class ForInitStatementContext;
  class WhileStatementContext;
  class IdExpressionContext;
  class PrimaryExpressionContext;
  class PostfixExpressionContext;
  class PrefixExpressionContext;
  class MultiplicativeExpressionContext;
  class AdditiveExpressionContext;
  class RelationalExpressionContext;
  class EqualityExpressionContext;
  class LogicalAndExpressionContext;
  class LogicalOrExpressionContext;
  class ConditionalExpressionContext;
  class AssignmentExpressionContext;
  class ExprContext;
  class ConstantExpressionContext;
  class TypeContext;
  class TypemodifierContext;
  class Type_nameContext;
  class LiteralContext;
  class BoolLiteralContext;
  class CharLiteralContext;
  class IntegerLiteralContext;
  class FloatLiteralContext;
  class StringLiteralContext;
  class ArrayLiteralContext;
  class ArrayLiteralListContext; 

  class  TranslationUnitContext : public antlr4::ParserRuleContext {
  public:
    TranslationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TranslationUnitContext* translationUnit();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableDeclarationContext *variableDeclaration();
    FunctionDeclarationContext *functionDeclaration();
    FunctionDefinitionContext *functionDefinition();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationContext* declaration();

  class  VariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    std::vector<InitDeclaratorContext *> initDeclarator();
    InitDeclaratorContext* initDeclarator(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclarationContext* variableDeclaration();

  class  InitDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    InitDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();
    ArrayDimensionListContext *arrayDimensionList();
    InitializerContext *initializer();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitDeclaratorContext* initDeclarator();

  class  InitializerContext : public antlr4::ParserRuleContext {
  public:
    InitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionalExpressionContext *conditionalExpression();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitializerContext* initializer();

  class  FunctionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    FunctionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionPrototypeContext *functionPrototype();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDeclarationContext* functionDeclaration();

  class  FunctionDefinitionContext : public antlr4::ParserRuleContext {
  public:
    FunctionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionPrototypeContext *functionPrototype();
    CompoundStatementContext *compoundStatement();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDefinitionContext* functionDefinition();

  class  FunctionPrototypeContext : public antlr4::ParserRuleContext {
  public:
    FunctionPrototypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *EXTERN();
    FormalParameterListContext *formalParameterList();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionPrototypeContext* functionPrototype();

  class  FormalParameterListContext : public antlr4::ParserRuleContext {
  public:
    FormalParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FormalParameterContext *> formalParameter();
    FormalParameterContext* formalParameter(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FormalParameterListContext* formalParameterList();

  class  FormalParameterContext : public antlr4::ParserRuleContext {
  public:
    FormalParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *IDENT();
    ArrayDimensionListContext *arrayDimensionList();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FormalParameterContext* formalParameter();

  class  ArrayDimensionListContext : public antlr4::ParserRuleContext {
  public:
    ArrayDimensionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArrayDimExprContext *> arrayDimExpr();
    ArrayDimExprContext* arrayDimExpr(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayDimensionListContext* arrayDimensionList();

  class  ArrayDimExprContext : public antlr4::ParserRuleContext {
  public:
    ArrayDimExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstantExpressionContext *constantExpression();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayDimExprContext* arrayDimExpr();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StatementContext() = default;
    void copyFrom(StatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ReturnStatementStatContext : public StatementContext {
  public:
    ReturnStatementStatContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *RETURN();
    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EmptyStatementStatContext : public StatementContext {
  public:
    EmptyStatementStatContext(StatementContext *ctx);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BreakStatementStatContext : public StatementContext {
  public:
    BreakStatementStatContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *BREAK();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassStatementContext : public StatementContext {
  public:
    PassStatementContext(StatementContext *ctx);

    CompoundStatementContext *compoundStatement();
    ExpressionStatementContext *expressionStatement();
    IfStatementContext *ifStatement();
    ForStatementContext *forStatement();
    WhileStatementContext *whileStatement();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VarDeclarationStatementContext : public StatementContext {
  public:
    VarDeclarationStatementContext(StatementContext *ctx);

    VariableDeclarationContext *variableDeclaration();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ContinueStatementStatContext : public StatementContext {
  public:
    ContinueStatementStatContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *CONTINUE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StatementContext* statement();

  class  CompoundStatementContext : public antlr4::ParserRuleContext {
  public:
    CompoundStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompoundStatementContext* compoundStatement();

  class  ExpressionStatementContext : public antlr4::ParserRuleContext {
  public:
    ExpressionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionStatementContext* expressionStatement();

  class  IfStatementContext : public antlr4::ParserRuleContext {
  public:
    IfStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    IfStatementContext() = default;
    void copyFrom(IfStatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IfElseStatementContext : public IfStatementContext {
  public:
    IfElseStatementContext(IfStatementContext *ctx);

    antlr4::tree::TerminalNode *IF();
    ExprContext *expr();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    antlr4::tree::TerminalNode *ELSE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IfOnlyStatementContext : public IfStatementContext {
  public:
    IfOnlyStatementContext(IfStatementContext *ctx);

    antlr4::tree::TerminalNode *IF();
    ExprContext *expr();
    StatementContext *statement();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  IfStatementContext* ifStatement();

  class  ForStatementContext : public antlr4::ParserRuleContext {
  public:
    ForStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR();
    ForInitStatementContext *forInitStatement();
    ExpressionStatementContext *expressionStatement();
    StatementContext *statement();
    ExprContext *expr();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForStatementContext* forStatement();

  class  ForInitStatementContext : public antlr4::ParserRuleContext {
  public:
    ForInitStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionStatementContext *expressionStatement();
    VariableDeclarationContext *variableDeclaration();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForInitStatementContext* forInitStatement();

  class  WhileStatementContext : public antlr4::ParserRuleContext {
  public:
    WhileStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHILE();
    ExprContext *expr();
    StatementContext *statement();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhileStatementContext* whileStatement();

  class  IdExpressionContext : public antlr4::ParserRuleContext {
  public:
    IdExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdExpressionContext* idExpression();

  class  PrimaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PrimaryExpressionContext() = default;
    void copyFrom(PrimaryExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LiteralPrimaryExprContext : public PrimaryExpressionContext {
  public:
    LiteralPrimaryExprContext(PrimaryExpressionContext *ctx);

    LiteralContext *literal();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IdentPrimaryExprContext : public PrimaryExpressionContext {
  public:
    IdentPrimaryExprContext(PrimaryExpressionContext *ctx);

    IdExpressionContext *idExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenPrimaryExprContext : public PrimaryExpressionContext {
  public:
    ParenPrimaryExprContext(PrimaryExpressionContext *ctx);

    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PrimaryExpressionContext* primaryExpression();

  class  PostfixExpressionContext : public antlr4::ParserRuleContext {
  public:
    PostfixExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PostfixExpressionContext() = default;
    void copyFrom(PostfixExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CastExpressionContext : public PostfixExpressionContext {
  public:
    CastExpressionContext(PostfixExpressionContext *ctx);

    antlr4::tree::TerminalNode *STATIC_CAST();
    TypeContext *type();
    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CallExpressionContext : public PostfixExpressionContext {
  public:
    CallExpressionContext(PostfixExpressionContext *ctx);

    PostfixExpressionContext *postfixExpression();
    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DoPostfixExpressionContext : public PostfixExpressionContext {
  public:
    DoPostfixExpressionContext(PostfixExpressionContext *ctx);

    antlr4::Token *op = nullptr;
    PostfixExpressionContext *postfixExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FallbackPostfixExpressionContext : public PostfixExpressionContext {
  public:
    FallbackPostfixExpressionContext(PostfixExpressionContext *ctx);

    PrimaryExpressionContext *primaryExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArraySubscriptExpressionContext : public PostfixExpressionContext {
  public:
    ArraySubscriptExpressionContext(PostfixExpressionContext *ctx);

    PostfixExpressionContext *postfixExpression();
    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PostfixExpressionContext* postfixExpression();
  PostfixExpressionContext* postfixExpression(int precedence);
  class  PrefixExpressionContext : public antlr4::ParserRuleContext {
  public:
    PrefixExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PrefixExpressionContext() = default;
    void copyFrom(PrefixExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DoPrefixExpressionContext : public PrefixExpressionContext {
  public:
    DoPrefixExpressionContext(PrefixExpressionContext *ctx);

    antlr4::Token *op = nullptr;
    PrefixExpressionContext *prefixExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FallbackPrefixExpressionContext : public PrefixExpressionContext {
  public:
    FallbackPrefixExpressionContext(PrefixExpressionContext *ctx);

    PostfixExpressionContext *postfixExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PrefixExpressionContext* prefixExpression();

  class  MultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    MultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    MultiplicativeExpressionContext() = default;
    void copyFrom(MultiplicativeExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DoMultiplicativeExpressionContext : public MultiplicativeExpressionContext {
  public:
    DoMultiplicativeExpressionContext(MultiplicativeExpressionContext *ctx);

    antlr4::Token *op = nullptr;
    MultiplicativeExpressionContext *multiplicativeExpression();
    PrefixExpressionContext *prefixExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FallbackMultiplicativeExpressionContext : public MultiplicativeExpressionContext {
  public:
    FallbackMultiplicativeExpressionContext(MultiplicativeExpressionContext *ctx);

    PrefixExpressionContext *prefixExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  MultiplicativeExpressionContext* multiplicativeExpression();
  MultiplicativeExpressionContext* multiplicativeExpression(int precedence);
  class  AdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    AdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AdditiveExpressionContext() = default;
    void copyFrom(AdditiveExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DoAdditiveExpressionContext : public AdditiveExpressionContext {
  public:
    DoAdditiveExpressionContext(AdditiveExpressionContext *ctx);

    antlr4::Token *op = nullptr;
    AdditiveExpressionContext *additiveExpression();
    MultiplicativeExpressionContext *multiplicativeExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FallbackAdditiveExpressionContext : public AdditiveExpressionContext {
  public:
    FallbackAdditiveExpressionContext(AdditiveExpressionContext *ctx);

    MultiplicativeExpressionContext *multiplicativeExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AdditiveExpressionContext* additiveExpression();
  AdditiveExpressionContext* additiveExpression(int precedence);
  class  RelationalExpressionContext : public antlr4::ParserRuleContext {
  public:
    RelationalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    RelationalExpressionContext() = default;
    void copyFrom(RelationalExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FallbackRelationalExpressionContext : public RelationalExpressionContext {
  public:
    FallbackRelationalExpressionContext(RelationalExpressionContext *ctx);

    AdditiveExpressionContext *additiveExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DoRelationalExpressionContext : public RelationalExpressionContext {
  public:
    DoRelationalExpressionContext(RelationalExpressionContext *ctx);

    antlr4::Token *op = nullptr;
    RelationalExpressionContext *relationalExpression();
    AdditiveExpressionContext *additiveExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  RelationalExpressionContext* relationalExpression();
  RelationalExpressionContext* relationalExpression(int precedence);
  class  EqualityExpressionContext : public antlr4::ParserRuleContext {
  public:
    EqualityExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    EqualityExpressionContext() = default;
    void copyFrom(EqualityExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DoEqualityExpressionContext : public EqualityExpressionContext {
  public:
    DoEqualityExpressionContext(EqualityExpressionContext *ctx);

    antlr4::Token *op = nullptr;
    EqualityExpressionContext *equalityExpression();
    RelationalExpressionContext *relationalExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FallbackEqualityExpressionContext : public EqualityExpressionContext {
  public:
    FallbackEqualityExpressionContext(EqualityExpressionContext *ctx);

    RelationalExpressionContext *relationalExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  EqualityExpressionContext* equalityExpression();
  EqualityExpressionContext* equalityExpression(int precedence);
  class  LogicalAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    LogicalAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LogicalAndExpressionContext() = default;
    void copyFrom(LogicalAndExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DoLogicalAndExpressionContext : public LogicalAndExpressionContext {
  public:
    DoLogicalAndExpressionContext(LogicalAndExpressionContext *ctx);

    LogicalAndExpressionContext *logicalAndExpression();
    EqualityExpressionContext *equalityExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FallbackLogicalAndExpressionContext : public LogicalAndExpressionContext {
  public:
    FallbackLogicalAndExpressionContext(LogicalAndExpressionContext *ctx);

    EqualityExpressionContext *equalityExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LogicalAndExpressionContext* logicalAndExpression();
  LogicalAndExpressionContext* logicalAndExpression(int precedence);
  class  LogicalOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    LogicalOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LogicalOrExpressionContext() = default;
    void copyFrom(LogicalOrExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DoLogicalOrExpressionContext : public LogicalOrExpressionContext {
  public:
    DoLogicalOrExpressionContext(LogicalOrExpressionContext *ctx);

    LogicalOrExpressionContext *logicalOrExpression();
    LogicalAndExpressionContext *logicalAndExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FallbackLogicalOrExpressionContext : public LogicalOrExpressionContext {
  public:
    FallbackLogicalOrExpressionContext(LogicalOrExpressionContext *ctx);

    LogicalAndExpressionContext *logicalAndExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LogicalOrExpressionContext* logicalOrExpression();
  LogicalOrExpressionContext* logicalOrExpression(int precedence);
  class  ConditionalExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ConditionalExpressionContext() = default;
    void copyFrom(ConditionalExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FallbackConditionalExpressionContext : public ConditionalExpressionContext {
  public:
    FallbackConditionalExpressionContext(ConditionalExpressionContext *ctx);

    LogicalOrExpressionContext *logicalOrExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DoConditionalExpressionContext : public ConditionalExpressionContext {
  public:
    DoConditionalExpressionContext(ConditionalExpressionContext *ctx);

    LogicalOrExpressionContext *logicalOrExpression();
    ExprContext *expr();
    ConditionalExpressionContext *conditionalExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ConditionalExpressionContext* conditionalExpression();

  class  AssignmentExpressionContext : public antlr4::ParserRuleContext {
  public:
    AssignmentExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AssignmentExpressionContext() = default;
    void copyFrom(AssignmentExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DoAssignmentExpressionContext : public AssignmentExpressionContext {
  public:
    DoAssignmentExpressionContext(AssignmentExpressionContext *ctx);

    antlr4::Token *op = nullptr;
    PrefixExpressionContext *prefixExpression();
    AssignmentExpressionContext *assignmentExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FallbackAssigmentExpressionContext : public AssignmentExpressionContext {
  public:
    FallbackAssigmentExpressionContext(AssignmentExpressionContext *ctx);

    ConditionalExpressionContext *conditionalExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AssignmentExpressionContext* assignmentExpression();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExprContext() = default;
    void copyFrom(ExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DoExpressionListContext : public ExprContext {
  public:
    DoExpressionListContext(ExprContext *ctx);

    std::vector<AssignmentExpressionContext *> assignmentExpression();
    AssignmentExpressionContext* assignmentExpression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FallbackExprContext : public ExprContext {
  public:
    FallbackExprContext(ExprContext *ctx);

    AssignmentExpressionContext *assignmentExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExprContext* expr();

  class  ConstantExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConstantExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionalExpressionContext *conditionalExpression();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantExpressionContext* constantExpression();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_nameContext *type_name();
    TypemodifierContext *typemodifier();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();

  class  TypemodifierContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *modifier = nullptr;;
    TypemodifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SIGNED();
    antlr4::tree::TerminalNode *UNSIGNED();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypemodifierContext* typemodifier();

  class  Type_nameContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    Type_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VOID();
    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *CHAR();
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *FLOAT();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_nameContext* type_name();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BoolLiteralContext *boolLiteral();
    CharLiteralContext *charLiteral();
    IntegerLiteralContext *integerLiteral();
    FloatLiteralContext *floatLiteral();
    StringLiteralContext *stringLiteral();
    ArrayLiteralContext *arrayLiteral();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();

  class  BoolLiteralContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *value = nullptr;;
    BoolLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BoolLiteralContext* boolLiteral();

  class  CharLiteralContext : public antlr4::ParserRuleContext {
  public:
    CharLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CHARACTER_LITERAL();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CharLiteralContext* charLiteral();

  class  IntegerLiteralContext : public antlr4::ParserRuleContext {
  public:
    IntegerLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER_LITERAL();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntegerLiteralContext* integerLiteral();

  class  FloatLiteralContext : public antlr4::ParserRuleContext {
  public:
    FloatLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FLOAT_LITERAL();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FloatLiteralContext* floatLiteral();

  class  StringLiteralContext : public antlr4::ParserRuleContext {
  public:
    StringLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STRING_LITERAL();
    antlr4::tree::TerminalNode* STRING_LITERAL(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StringLiteralContext* stringLiteral();

  class  ArrayLiteralContext : public antlr4::ParserRuleContext {
  public:
    ArrayLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArrayLiteralListContext *arrayLiteralList();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayLiteralContext* arrayLiteral();

  class  ArrayLiteralListContext : public antlr4::ParserRuleContext {
  public:
    ArrayLiteralListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LiteralContext *> literal();
    LiteralContext* literal(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayLiteralListContext* arrayLiteralList();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool postfixExpressionSempred(PostfixExpressionContext *_localctx, size_t predicateIndex);
  bool multiplicativeExpressionSempred(MultiplicativeExpressionContext *_localctx, size_t predicateIndex);
  bool additiveExpressionSempred(AdditiveExpressionContext *_localctx, size_t predicateIndex);
  bool relationalExpressionSempred(RelationalExpressionContext *_localctx, size_t predicateIndex);
  bool equalityExpressionSempred(EqualityExpressionContext *_localctx, size_t predicateIndex);
  bool logicalAndExpressionSempred(LogicalAndExpressionContext *_localctx, size_t predicateIndex);
  bool logicalOrExpressionSempred(LogicalOrExpressionContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

