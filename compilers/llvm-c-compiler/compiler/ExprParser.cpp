
// Generated from Expr.g4 by ANTLR 4.8


#include "ExprVisitor.h"

#include "ExprParser.h"


using namespace antlrcpp;
using namespace antlr4;

ExprParser::ExprParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

ExprParser::~ExprParser() {
  delete _interpreter;
}

std::string ExprParser::getGrammarFileName() const {
  return "Expr.g4";
}

const std::vector<std::string>& ExprParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& ExprParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- TranslationUnitContext ------------------------------------------------------------------

ExprParser::TranslationUnitContext::TranslationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ExprParser::TranslationUnitContext::EOF() {
  return getToken(ExprParser::EOF, 0);
}

std::vector<ExprParser::DeclarationContext *> ExprParser::TranslationUnitContext::declaration() {
  return getRuleContexts<ExprParser::DeclarationContext>();
}

ExprParser::DeclarationContext* ExprParser::TranslationUnitContext::declaration(size_t i) {
  return getRuleContext<ExprParser::DeclarationContext>(i);
}


size_t ExprParser::TranslationUnitContext::getRuleIndex() const {
  return ExprParser::RuleTranslationUnit;
}


antlrcpp::Any ExprParser::TranslationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitTranslationUnit(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::TranslationUnitContext* ExprParser::translationUnit() {
  TranslationUnitContext *_localctx = _tracker.createInstance<TranslationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, ExprParser::RuleTranslationUnit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(91);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExprParser::EXTERN)
      | (1ULL << ExprParser::SIGNED)
      | (1ULL << ExprParser::UNSIGNED)
      | (1ULL << ExprParser::INT)
      | (1ULL << ExprParser::CHAR)
      | (1ULL << ExprParser::BOOL)
      | (1ULL << ExprParser::FLOAT)
      | (1ULL << ExprParser::VOID))) != 0)) {
      setState(88);
      declaration();
      setState(93);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(94);
    match(ExprParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

ExprParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExprParser::VariableDeclarationContext* ExprParser::DeclarationContext::variableDeclaration() {
  return getRuleContext<ExprParser::VariableDeclarationContext>(0);
}

ExprParser::FunctionDeclarationContext* ExprParser::DeclarationContext::functionDeclaration() {
  return getRuleContext<ExprParser::FunctionDeclarationContext>(0);
}

ExprParser::FunctionDefinitionContext* ExprParser::DeclarationContext::functionDefinition() {
  return getRuleContext<ExprParser::FunctionDefinitionContext>(0);
}


size_t ExprParser::DeclarationContext::getRuleIndex() const {
  return ExprParser::RuleDeclaration;
}


antlrcpp::Any ExprParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::DeclarationContext* ExprParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 2, ExprParser::RuleDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(99);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(96);
      variableDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(97);
      functionDeclaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(98);
      functionDefinition();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

ExprParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExprParser::TypeContext* ExprParser::VariableDeclarationContext::type() {
  return getRuleContext<ExprParser::TypeContext>(0);
}

std::vector<ExprParser::InitDeclaratorContext *> ExprParser::VariableDeclarationContext::initDeclarator() {
  return getRuleContexts<ExprParser::InitDeclaratorContext>();
}

ExprParser::InitDeclaratorContext* ExprParser::VariableDeclarationContext::initDeclarator(size_t i) {
  return getRuleContext<ExprParser::InitDeclaratorContext>(i);
}


size_t ExprParser::VariableDeclarationContext::getRuleIndex() const {
  return ExprParser::RuleVariableDeclaration;
}


antlrcpp::Any ExprParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::VariableDeclarationContext* ExprParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, ExprParser::RuleVariableDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(101);
    type();
    setState(102);
    initDeclarator();
    setState(107);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExprParser::T__0) {
      setState(103);
      match(ExprParser::T__0);
      setState(104);
      initDeclarator();
      setState(109);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(110);
    match(ExprParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitDeclaratorContext ------------------------------------------------------------------

ExprParser::InitDeclaratorContext::InitDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ExprParser::InitDeclaratorContext::IDENT() {
  return getToken(ExprParser::IDENT, 0);
}

ExprParser::ArrayDimensionListContext* ExprParser::InitDeclaratorContext::arrayDimensionList() {
  return getRuleContext<ExprParser::ArrayDimensionListContext>(0);
}

ExprParser::InitializerContext* ExprParser::InitDeclaratorContext::initializer() {
  return getRuleContext<ExprParser::InitializerContext>(0);
}


size_t ExprParser::InitDeclaratorContext::getRuleIndex() const {
  return ExprParser::RuleInitDeclarator;
}


antlrcpp::Any ExprParser::InitDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitInitDeclarator(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::InitDeclaratorContext* ExprParser::initDeclarator() {
  InitDeclaratorContext *_localctx = _tracker.createInstance<InitDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 6, ExprParser::RuleInitDeclarator);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(112);
    match(ExprParser::IDENT);
    setState(114);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ExprParser::T__5) {
      setState(113);
      arrayDimensionList();
    }
    setState(117);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ExprParser::T__2) {
      setState(116);
      initializer();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitializerContext ------------------------------------------------------------------

ExprParser::InitializerContext::InitializerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExprParser::ConditionalExpressionContext* ExprParser::InitializerContext::conditionalExpression() {
  return getRuleContext<ExprParser::ConditionalExpressionContext>(0);
}


size_t ExprParser::InitializerContext::getRuleIndex() const {
  return ExprParser::RuleInitializer;
}


antlrcpp::Any ExprParser::InitializerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitInitializer(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::InitializerContext* ExprParser::initializer() {
  InitializerContext *_localctx = _tracker.createInstance<InitializerContext>(_ctx, getState());
  enterRule(_localctx, 8, ExprParser::RuleInitializer);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    match(ExprParser::T__2);
    setState(120);
    conditionalExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclarationContext ------------------------------------------------------------------

ExprParser::FunctionDeclarationContext::FunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExprParser::FunctionPrototypeContext* ExprParser::FunctionDeclarationContext::functionPrototype() {
  return getRuleContext<ExprParser::FunctionPrototypeContext>(0);
}


size_t ExprParser::FunctionDeclarationContext::getRuleIndex() const {
  return ExprParser::RuleFunctionDeclaration;
}


antlrcpp::Any ExprParser::FunctionDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFunctionDeclaration(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::FunctionDeclarationContext* ExprParser::functionDeclaration() {
  FunctionDeclarationContext *_localctx = _tracker.createInstance<FunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 10, ExprParser::RuleFunctionDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    functionPrototype();
    setState(123);
    match(ExprParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefinitionContext ------------------------------------------------------------------

ExprParser::FunctionDefinitionContext::FunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExprParser::FunctionPrototypeContext* ExprParser::FunctionDefinitionContext::functionPrototype() {
  return getRuleContext<ExprParser::FunctionPrototypeContext>(0);
}

ExprParser::CompoundStatementContext* ExprParser::FunctionDefinitionContext::compoundStatement() {
  return getRuleContext<ExprParser::CompoundStatementContext>(0);
}


size_t ExprParser::FunctionDefinitionContext::getRuleIndex() const {
  return ExprParser::RuleFunctionDefinition;
}


antlrcpp::Any ExprParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::FunctionDefinitionContext* ExprParser::functionDefinition() {
  FunctionDefinitionContext *_localctx = _tracker.createInstance<FunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 12, ExprParser::RuleFunctionDefinition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    functionPrototype();
    setState(126);
    compoundStatement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionPrototypeContext ------------------------------------------------------------------

ExprParser::FunctionPrototypeContext::FunctionPrototypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExprParser::TypeContext* ExprParser::FunctionPrototypeContext::type() {
  return getRuleContext<ExprParser::TypeContext>(0);
}

tree::TerminalNode* ExprParser::FunctionPrototypeContext::IDENT() {
  return getToken(ExprParser::IDENT, 0);
}

tree::TerminalNode* ExprParser::FunctionPrototypeContext::EXTERN() {
  return getToken(ExprParser::EXTERN, 0);
}

ExprParser::FormalParameterListContext* ExprParser::FunctionPrototypeContext::formalParameterList() {
  return getRuleContext<ExprParser::FormalParameterListContext>(0);
}


size_t ExprParser::FunctionPrototypeContext::getRuleIndex() const {
  return ExprParser::RuleFunctionPrototype;
}


antlrcpp::Any ExprParser::FunctionPrototypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFunctionPrototype(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::FunctionPrototypeContext* ExprParser::functionPrototype() {
  FunctionPrototypeContext *_localctx = _tracker.createInstance<FunctionPrototypeContext>(_ctx, getState());
  enterRule(_localctx, 14, ExprParser::RuleFunctionPrototype);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(129);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ExprParser::EXTERN) {
      setState(128);
      match(ExprParser::EXTERN);
    }
    setState(131);
    type();
    setState(132);
    match(ExprParser::IDENT);
    setState(133);
    match(ExprParser::T__3);
    setState(135);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExprParser::SIGNED)
      | (1ULL << ExprParser::UNSIGNED)
      | (1ULL << ExprParser::INT)
      | (1ULL << ExprParser::CHAR)
      | (1ULL << ExprParser::BOOL)
      | (1ULL << ExprParser::FLOAT)
      | (1ULL << ExprParser::VOID))) != 0)) {
      setState(134);
      formalParameterList();
    }
    setState(137);
    match(ExprParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParameterListContext ------------------------------------------------------------------

ExprParser::FormalParameterListContext::FormalParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExprParser::FormalParameterContext *> ExprParser::FormalParameterListContext::formalParameter() {
  return getRuleContexts<ExprParser::FormalParameterContext>();
}

ExprParser::FormalParameterContext* ExprParser::FormalParameterListContext::formalParameter(size_t i) {
  return getRuleContext<ExprParser::FormalParameterContext>(i);
}


size_t ExprParser::FormalParameterListContext::getRuleIndex() const {
  return ExprParser::RuleFormalParameterList;
}


antlrcpp::Any ExprParser::FormalParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFormalParameterList(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::FormalParameterListContext* ExprParser::formalParameterList() {
  FormalParameterListContext *_localctx = _tracker.createInstance<FormalParameterListContext>(_ctx, getState());
  enterRule(_localctx, 16, ExprParser::RuleFormalParameterList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(139);
    formalParameter();
    setState(144);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExprParser::T__0) {
      setState(140);
      match(ExprParser::T__0);
      setState(141);
      formalParameter();
      setState(146);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParameterContext ------------------------------------------------------------------

ExprParser::FormalParameterContext::FormalParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExprParser::TypeContext* ExprParser::FormalParameterContext::type() {
  return getRuleContext<ExprParser::TypeContext>(0);
}

tree::TerminalNode* ExprParser::FormalParameterContext::IDENT() {
  return getToken(ExprParser::IDENT, 0);
}

ExprParser::ArrayDimensionListContext* ExprParser::FormalParameterContext::arrayDimensionList() {
  return getRuleContext<ExprParser::ArrayDimensionListContext>(0);
}


size_t ExprParser::FormalParameterContext::getRuleIndex() const {
  return ExprParser::RuleFormalParameter;
}


antlrcpp::Any ExprParser::FormalParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFormalParameter(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::FormalParameterContext* ExprParser::formalParameter() {
  FormalParameterContext *_localctx = _tracker.createInstance<FormalParameterContext>(_ctx, getState());
  enterRule(_localctx, 18, ExprParser::RuleFormalParameter);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(147);
    type();
    setState(149);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ExprParser::IDENT) {
      setState(148);
      match(ExprParser::IDENT);
    }
    setState(152);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ExprParser::T__5) {
      setState(151);
      arrayDimensionList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayDimensionListContext ------------------------------------------------------------------

ExprParser::ArrayDimensionListContext::ArrayDimensionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExprParser::ArrayDimExprContext *> ExprParser::ArrayDimensionListContext::arrayDimExpr() {
  return getRuleContexts<ExprParser::ArrayDimExprContext>();
}

ExprParser::ArrayDimExprContext* ExprParser::ArrayDimensionListContext::arrayDimExpr(size_t i) {
  return getRuleContext<ExprParser::ArrayDimExprContext>(i);
}


size_t ExprParser::ArrayDimensionListContext::getRuleIndex() const {
  return ExprParser::RuleArrayDimensionList;
}


antlrcpp::Any ExprParser::ArrayDimensionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitArrayDimensionList(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::ArrayDimensionListContext* ExprParser::arrayDimensionList() {
  ArrayDimensionListContext *_localctx = _tracker.createInstance<ArrayDimensionListContext>(_ctx, getState());
  enterRule(_localctx, 20, ExprParser::RuleArrayDimensionList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(158); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(154);
      match(ExprParser::T__5);
      setState(155);
      arrayDimExpr();
      setState(156);
      match(ExprParser::T__6);
      setState(160); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ExprParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayDimExprContext ------------------------------------------------------------------

ExprParser::ArrayDimExprContext::ArrayDimExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExprParser::ConstantExpressionContext* ExprParser::ArrayDimExprContext::constantExpression() {
  return getRuleContext<ExprParser::ConstantExpressionContext>(0);
}


size_t ExprParser::ArrayDimExprContext::getRuleIndex() const {
  return ExprParser::RuleArrayDimExpr;
}


antlrcpp::Any ExprParser::ArrayDimExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitArrayDimExpr(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::ArrayDimExprContext* ExprParser::arrayDimExpr() {
  ArrayDimExprContext *_localctx = _tracker.createInstance<ArrayDimExprContext>(_ctx, getState());
  enterRule(_localctx, 22, ExprParser::RuleArrayDimExpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(164);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ExprParser::T__6: {
        enterOuterAlt(_localctx, 1);

        break;
      }

      case ExprParser::T__3:
      case ExprParser::T__7:
      case ExprParser::T__11:
      case ExprParser::T__12:
      case ExprParser::T__13:
      case ExprParser::T__14:
      case ExprParser::T__15:
      case ExprParser::STATIC_CAST:
      case ExprParser::TRUE:
      case ExprParser::FALSE:
      case ExprParser::IDENT:
      case ExprParser::FLOAT_LITERAL:
      case ExprParser::INTEGER_LITERAL:
      case ExprParser::CHARACTER_LITERAL:
      case ExprParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(163);
        constantExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

ExprParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::StatementContext::getRuleIndex() const {
  return ExprParser::RuleStatement;
}

void ExprParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ReturnStatementStatContext ------------------------------------------------------------------

tree::TerminalNode* ExprParser::ReturnStatementStatContext::RETURN() {
  return getToken(ExprParser::RETURN, 0);
}

ExprParser::ExprContext* ExprParser::ReturnStatementStatContext::expr() {
  return getRuleContext<ExprParser::ExprContext>(0);
}

ExprParser::ReturnStatementStatContext::ReturnStatementStatContext(StatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::ReturnStatementStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitReturnStatementStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EmptyStatementStatContext ------------------------------------------------------------------

ExprParser::EmptyStatementStatContext::EmptyStatementStatContext(StatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::EmptyStatementStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitEmptyStatementStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakStatementStatContext ------------------------------------------------------------------

tree::TerminalNode* ExprParser::BreakStatementStatContext::BREAK() {
  return getToken(ExprParser::BREAK, 0);
}

ExprParser::BreakStatementStatContext::BreakStatementStatContext(StatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::BreakStatementStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitBreakStatementStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassStatementContext ------------------------------------------------------------------

ExprParser::CompoundStatementContext* ExprParser::PassStatementContext::compoundStatement() {
  return getRuleContext<ExprParser::CompoundStatementContext>(0);
}

ExprParser::ExpressionStatementContext* ExprParser::PassStatementContext::expressionStatement() {
  return getRuleContext<ExprParser::ExpressionStatementContext>(0);
}

ExprParser::IfStatementContext* ExprParser::PassStatementContext::ifStatement() {
  return getRuleContext<ExprParser::IfStatementContext>(0);
}

ExprParser::ForStatementContext* ExprParser::PassStatementContext::forStatement() {
  return getRuleContext<ExprParser::ForStatementContext>(0);
}

ExprParser::WhileStatementContext* ExprParser::PassStatementContext::whileStatement() {
  return getRuleContext<ExprParser::WhileStatementContext>(0);
}

ExprParser::PassStatementContext::PassStatementContext(StatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::PassStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitPassStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarDeclarationStatementContext ------------------------------------------------------------------

ExprParser::VariableDeclarationContext* ExprParser::VarDeclarationStatementContext::variableDeclaration() {
  return getRuleContext<ExprParser::VariableDeclarationContext>(0);
}

ExprParser::VarDeclarationStatementContext::VarDeclarationStatementContext(StatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::VarDeclarationStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitVarDeclarationStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContinueStatementStatContext ------------------------------------------------------------------

tree::TerminalNode* ExprParser::ContinueStatementStatContext::CONTINUE() {
  return getToken(ExprParser::CONTINUE, 0);
}

ExprParser::ContinueStatementStatContext::ContinueStatementStatContext(StatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::ContinueStatementStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitContinueStatementStat(this);
  else
    return visitor->visitChildren(this);
}
ExprParser::StatementContext* ExprParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 24, ExprParser::RuleStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(182);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<ExprParser::PassStatementContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(166);
      compoundStatement();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<ExprParser::PassStatementContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(167);
      expressionStatement();
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<ExprParser::EmptyStatementStatContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(168);
      match(ExprParser::T__1);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<ExprParser::PassStatementContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(169);
      ifStatement();
      break;
    }

    case 5: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<ExprParser::PassStatementContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(170);
      forStatement();
      break;
    }

    case 6: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<ExprParser::PassStatementContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(171);
      whileStatement();
      break;
    }

    case 7: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<ExprParser::ReturnStatementStatContext>(_localctx));
      enterOuterAlt(_localctx, 7);
      setState(172);
      match(ExprParser::RETURN);
      setState(174);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << ExprParser::T__3)
        | (1ULL << ExprParser::T__7)
        | (1ULL << ExprParser::T__11)
        | (1ULL << ExprParser::T__12)
        | (1ULL << ExprParser::T__13)
        | (1ULL << ExprParser::T__14)
        | (1ULL << ExprParser::T__15)
        | (1ULL << ExprParser::STATIC_CAST)
        | (1ULL << ExprParser::TRUE)
        | (1ULL << ExprParser::FALSE)
        | (1ULL << ExprParser::IDENT)
        | (1ULL << ExprParser::FLOAT_LITERAL)
        | (1ULL << ExprParser::INTEGER_LITERAL)
        | (1ULL << ExprParser::CHARACTER_LITERAL)
        | (1ULL << ExprParser::STRING_LITERAL))) != 0)) {
        setState(173);
        expr();
      }
      setState(176);
      match(ExprParser::T__1);
      break;
    }

    case 8: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<ExprParser::ContinueStatementStatContext>(_localctx));
      enterOuterAlt(_localctx, 8);
      setState(177);
      match(ExprParser::CONTINUE);
      setState(178);
      match(ExprParser::T__1);
      break;
    }

    case 9: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<ExprParser::BreakStatementStatContext>(_localctx));
      enterOuterAlt(_localctx, 9);
      setState(179);
      match(ExprParser::BREAK);
      setState(180);
      match(ExprParser::T__1);
      break;
    }

    case 10: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<ExprParser::VarDeclarationStatementContext>(_localctx));
      enterOuterAlt(_localctx, 10);
      setState(181);
      variableDeclaration();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompoundStatementContext ------------------------------------------------------------------

ExprParser::CompoundStatementContext::CompoundStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExprParser::StatementContext *> ExprParser::CompoundStatementContext::statement() {
  return getRuleContexts<ExprParser::StatementContext>();
}

ExprParser::StatementContext* ExprParser::CompoundStatementContext::statement(size_t i) {
  return getRuleContext<ExprParser::StatementContext>(i);
}


size_t ExprParser::CompoundStatementContext::getRuleIndex() const {
  return ExprParser::RuleCompoundStatement;
}


antlrcpp::Any ExprParser::CompoundStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitCompoundStatement(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::CompoundStatementContext* ExprParser::compoundStatement() {
  CompoundStatementContext *_localctx = _tracker.createInstance<CompoundStatementContext>(_ctx, getState());
  enterRule(_localctx, 26, ExprParser::RuleCompoundStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(184);
    match(ExprParser::T__7);
    setState(188);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExprParser::T__1)
      | (1ULL << ExprParser::T__3)
      | (1ULL << ExprParser::T__7)
      | (1ULL << ExprParser::T__11)
      | (1ULL << ExprParser::T__12)
      | (1ULL << ExprParser::T__13)
      | (1ULL << ExprParser::T__14)
      | (1ULL << ExprParser::T__15)
      | (1ULL << ExprParser::IF)
      | (1ULL << ExprParser::FOR)
      | (1ULL << ExprParser::WHILE)
      | (1ULL << ExprParser::CONTINUE)
      | (1ULL << ExprParser::BREAK)
      | (1ULL << ExprParser::RETURN)
      | (1ULL << ExprParser::SIGNED)
      | (1ULL << ExprParser::UNSIGNED)
      | (1ULL << ExprParser::INT)
      | (1ULL << ExprParser::CHAR)
      | (1ULL << ExprParser::BOOL)
      | (1ULL << ExprParser::FLOAT)
      | (1ULL << ExprParser::VOID)
      | (1ULL << ExprParser::STATIC_CAST)
      | (1ULL << ExprParser::TRUE)
      | (1ULL << ExprParser::FALSE)
      | (1ULL << ExprParser::IDENT)
      | (1ULL << ExprParser::FLOAT_LITERAL)
      | (1ULL << ExprParser::INTEGER_LITERAL)
      | (1ULL << ExprParser::CHARACTER_LITERAL)
      | (1ULL << ExprParser::STRING_LITERAL))) != 0)) {
      setState(185);
      statement();
      setState(190);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(191);
    match(ExprParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

ExprParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExprParser::ExprContext* ExprParser::ExpressionStatementContext::expr() {
  return getRuleContext<ExprParser::ExprContext>(0);
}


size_t ExprParser::ExpressionStatementContext::getRuleIndex() const {
  return ExprParser::RuleExpressionStatement;
}


antlrcpp::Any ExprParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::ExpressionStatementContext* ExprParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 28, ExprParser::RuleExpressionStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(194);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExprParser::T__3)
      | (1ULL << ExprParser::T__7)
      | (1ULL << ExprParser::T__11)
      | (1ULL << ExprParser::T__12)
      | (1ULL << ExprParser::T__13)
      | (1ULL << ExprParser::T__14)
      | (1ULL << ExprParser::T__15)
      | (1ULL << ExprParser::STATIC_CAST)
      | (1ULL << ExprParser::TRUE)
      | (1ULL << ExprParser::FALSE)
      | (1ULL << ExprParser::IDENT)
      | (1ULL << ExprParser::FLOAT_LITERAL)
      | (1ULL << ExprParser::INTEGER_LITERAL)
      | (1ULL << ExprParser::CHARACTER_LITERAL)
      | (1ULL << ExprParser::STRING_LITERAL))) != 0)) {
      setState(193);
      expr();
    }
    setState(196);
    match(ExprParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

ExprParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::IfStatementContext::getRuleIndex() const {
  return ExprParser::RuleIfStatement;
}

void ExprParser::IfStatementContext::copyFrom(IfStatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IfElseStatementContext ------------------------------------------------------------------

tree::TerminalNode* ExprParser::IfElseStatementContext::IF() {
  return getToken(ExprParser::IF, 0);
}

ExprParser::ExprContext* ExprParser::IfElseStatementContext::expr() {
  return getRuleContext<ExprParser::ExprContext>(0);
}

std::vector<ExprParser::StatementContext *> ExprParser::IfElseStatementContext::statement() {
  return getRuleContexts<ExprParser::StatementContext>();
}

ExprParser::StatementContext* ExprParser::IfElseStatementContext::statement(size_t i) {
  return getRuleContext<ExprParser::StatementContext>(i);
}

tree::TerminalNode* ExprParser::IfElseStatementContext::ELSE() {
  return getToken(ExprParser::ELSE, 0);
}

ExprParser::IfElseStatementContext::IfElseStatementContext(IfStatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::IfElseStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitIfElseStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfOnlyStatementContext ------------------------------------------------------------------

tree::TerminalNode* ExprParser::IfOnlyStatementContext::IF() {
  return getToken(ExprParser::IF, 0);
}

ExprParser::ExprContext* ExprParser::IfOnlyStatementContext::expr() {
  return getRuleContext<ExprParser::ExprContext>(0);
}

ExprParser::StatementContext* ExprParser::IfOnlyStatementContext::statement() {
  return getRuleContext<ExprParser::StatementContext>(0);
}

ExprParser::IfOnlyStatementContext::IfOnlyStatementContext(IfStatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::IfOnlyStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitIfOnlyStatement(this);
  else
    return visitor->visitChildren(this);
}
ExprParser::IfStatementContext* ExprParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 30, ExprParser::RuleIfStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(212);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<IfStatementContext *>(_tracker.createInstance<ExprParser::IfOnlyStatementContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(198);
      match(ExprParser::IF);
      setState(199);
      match(ExprParser::T__3);
      setState(200);
      expr();
      setState(201);
      match(ExprParser::T__4);
      setState(202);
      statement();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<IfStatementContext *>(_tracker.createInstance<ExprParser::IfElseStatementContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(204);
      match(ExprParser::IF);
      setState(205);
      match(ExprParser::T__3);
      setState(206);
      expr();
      setState(207);
      match(ExprParser::T__4);
      setState(208);
      statement();
      setState(209);
      match(ExprParser::ELSE);
      setState(210);
      statement();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForStatementContext ------------------------------------------------------------------

ExprParser::ForStatementContext::ForStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ExprParser::ForStatementContext::FOR() {
  return getToken(ExprParser::FOR, 0);
}

ExprParser::ForInitStatementContext* ExprParser::ForStatementContext::forInitStatement() {
  return getRuleContext<ExprParser::ForInitStatementContext>(0);
}

ExprParser::ExpressionStatementContext* ExprParser::ForStatementContext::expressionStatement() {
  return getRuleContext<ExprParser::ExpressionStatementContext>(0);
}

ExprParser::StatementContext* ExprParser::ForStatementContext::statement() {
  return getRuleContext<ExprParser::StatementContext>(0);
}

ExprParser::ExprContext* ExprParser::ForStatementContext::expr() {
  return getRuleContext<ExprParser::ExprContext>(0);
}


size_t ExprParser::ForStatementContext::getRuleIndex() const {
  return ExprParser::RuleForStatement;
}


antlrcpp::Any ExprParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::ForStatementContext* ExprParser::forStatement() {
  ForStatementContext *_localctx = _tracker.createInstance<ForStatementContext>(_ctx, getState());
  enterRule(_localctx, 32, ExprParser::RuleForStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(214);
    match(ExprParser::FOR);
    setState(215);
    match(ExprParser::T__3);
    setState(216);
    forInitStatement();
    setState(217);
    expressionStatement();
    setState(219);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExprParser::T__3)
      | (1ULL << ExprParser::T__7)
      | (1ULL << ExprParser::T__11)
      | (1ULL << ExprParser::T__12)
      | (1ULL << ExprParser::T__13)
      | (1ULL << ExprParser::T__14)
      | (1ULL << ExprParser::T__15)
      | (1ULL << ExprParser::STATIC_CAST)
      | (1ULL << ExprParser::TRUE)
      | (1ULL << ExprParser::FALSE)
      | (1ULL << ExprParser::IDENT)
      | (1ULL << ExprParser::FLOAT_LITERAL)
      | (1ULL << ExprParser::INTEGER_LITERAL)
      | (1ULL << ExprParser::CHARACTER_LITERAL)
      | (1ULL << ExprParser::STRING_LITERAL))) != 0)) {
      setState(218);
      expr();
    }
    setState(221);
    match(ExprParser::T__4);
    setState(222);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForInitStatementContext ------------------------------------------------------------------

ExprParser::ForInitStatementContext::ForInitStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExprParser::ExpressionStatementContext* ExprParser::ForInitStatementContext::expressionStatement() {
  return getRuleContext<ExprParser::ExpressionStatementContext>(0);
}

ExprParser::VariableDeclarationContext* ExprParser::ForInitStatementContext::variableDeclaration() {
  return getRuleContext<ExprParser::VariableDeclarationContext>(0);
}


size_t ExprParser::ForInitStatementContext::getRuleIndex() const {
  return ExprParser::RuleForInitStatement;
}


antlrcpp::Any ExprParser::ForInitStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitForInitStatement(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::ForInitStatementContext* ExprParser::forInitStatement() {
  ForInitStatementContext *_localctx = _tracker.createInstance<ForInitStatementContext>(_ctx, getState());
  enterRule(_localctx, 34, ExprParser::RuleForInitStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(226);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ExprParser::T__1:
      case ExprParser::T__3:
      case ExprParser::T__7:
      case ExprParser::T__11:
      case ExprParser::T__12:
      case ExprParser::T__13:
      case ExprParser::T__14:
      case ExprParser::T__15:
      case ExprParser::STATIC_CAST:
      case ExprParser::TRUE:
      case ExprParser::FALSE:
      case ExprParser::IDENT:
      case ExprParser::FLOAT_LITERAL:
      case ExprParser::INTEGER_LITERAL:
      case ExprParser::CHARACTER_LITERAL:
      case ExprParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(224);
        expressionStatement();
        break;
      }

      case ExprParser::SIGNED:
      case ExprParser::UNSIGNED:
      case ExprParser::INT:
      case ExprParser::CHAR:
      case ExprParser::BOOL:
      case ExprParser::FLOAT:
      case ExprParser::VOID: {
        enterOuterAlt(_localctx, 2);
        setState(225);
        variableDeclaration();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStatementContext ------------------------------------------------------------------

ExprParser::WhileStatementContext::WhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ExprParser::WhileStatementContext::WHILE() {
  return getToken(ExprParser::WHILE, 0);
}

ExprParser::ExprContext* ExprParser::WhileStatementContext::expr() {
  return getRuleContext<ExprParser::ExprContext>(0);
}

ExprParser::StatementContext* ExprParser::WhileStatementContext::statement() {
  return getRuleContext<ExprParser::StatementContext>(0);
}


size_t ExprParser::WhileStatementContext::getRuleIndex() const {
  return ExprParser::RuleWhileStatement;
}


antlrcpp::Any ExprParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::WhileStatementContext* ExprParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 36, ExprParser::RuleWhileStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(228);
    match(ExprParser::WHILE);
    setState(229);
    match(ExprParser::T__3);
    setState(230);
    expr();
    setState(231);
    match(ExprParser::T__4);
    setState(232);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdExpressionContext ------------------------------------------------------------------

ExprParser::IdExpressionContext::IdExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ExprParser::IdExpressionContext::IDENT() {
  return getToken(ExprParser::IDENT, 0);
}


size_t ExprParser::IdExpressionContext::getRuleIndex() const {
  return ExprParser::RuleIdExpression;
}


antlrcpp::Any ExprParser::IdExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitIdExpression(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::IdExpressionContext* ExprParser::idExpression() {
  IdExpressionContext *_localctx = _tracker.createInstance<IdExpressionContext>(_ctx, getState());
  enterRule(_localctx, 38, ExprParser::RuleIdExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(234);
    match(ExprParser::IDENT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

ExprParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::PrimaryExpressionContext::getRuleIndex() const {
  return ExprParser::RulePrimaryExpression;
}

void ExprParser::PrimaryExpressionContext::copyFrom(PrimaryExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LiteralPrimaryExprContext ------------------------------------------------------------------

ExprParser::LiteralContext* ExprParser::LiteralPrimaryExprContext::literal() {
  return getRuleContext<ExprParser::LiteralContext>(0);
}

ExprParser::LiteralPrimaryExprContext::LiteralPrimaryExprContext(PrimaryExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::LiteralPrimaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitLiteralPrimaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdentPrimaryExprContext ------------------------------------------------------------------

ExprParser::IdExpressionContext* ExprParser::IdentPrimaryExprContext::idExpression() {
  return getRuleContext<ExprParser::IdExpressionContext>(0);
}

ExprParser::IdentPrimaryExprContext::IdentPrimaryExprContext(PrimaryExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::IdentPrimaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitIdentPrimaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenPrimaryExprContext ------------------------------------------------------------------

ExprParser::ExprContext* ExprParser::ParenPrimaryExprContext::expr() {
  return getRuleContext<ExprParser::ExprContext>(0);
}

ExprParser::ParenPrimaryExprContext::ParenPrimaryExprContext(PrimaryExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::ParenPrimaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitParenPrimaryExpr(this);
  else
    return visitor->visitChildren(this);
}
ExprParser::PrimaryExpressionContext* ExprParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 40, ExprParser::RulePrimaryExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(242);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ExprParser::IDENT: {
        _localctx = dynamic_cast<PrimaryExpressionContext *>(_tracker.createInstance<ExprParser::IdentPrimaryExprContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(236);
        idExpression();
        break;
      }

      case ExprParser::T__7:
      case ExprParser::TRUE:
      case ExprParser::FALSE:
      case ExprParser::FLOAT_LITERAL:
      case ExprParser::INTEGER_LITERAL:
      case ExprParser::CHARACTER_LITERAL:
      case ExprParser::STRING_LITERAL: {
        _localctx = dynamic_cast<PrimaryExpressionContext *>(_tracker.createInstance<ExprParser::LiteralPrimaryExprContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(237);
        literal();
        break;
      }

      case ExprParser::T__3: {
        _localctx = dynamic_cast<PrimaryExpressionContext *>(_tracker.createInstance<ExprParser::ParenPrimaryExprContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(238);
        match(ExprParser::T__3);
        setState(239);
        expr();
        setState(240);
        match(ExprParser::T__4);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PostfixExpressionContext ------------------------------------------------------------------

ExprParser::PostfixExpressionContext::PostfixExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::PostfixExpressionContext::getRuleIndex() const {
  return ExprParser::RulePostfixExpression;
}

void ExprParser::PostfixExpressionContext::copyFrom(PostfixExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CastExpressionContext ------------------------------------------------------------------

tree::TerminalNode* ExprParser::CastExpressionContext::STATIC_CAST() {
  return getToken(ExprParser::STATIC_CAST, 0);
}

ExprParser::TypeContext* ExprParser::CastExpressionContext::type() {
  return getRuleContext<ExprParser::TypeContext>(0);
}

ExprParser::ExprContext* ExprParser::CastExpressionContext::expr() {
  return getRuleContext<ExprParser::ExprContext>(0);
}

ExprParser::CastExpressionContext::CastExpressionContext(PostfixExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::CastExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitCastExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CallExpressionContext ------------------------------------------------------------------

ExprParser::PostfixExpressionContext* ExprParser::CallExpressionContext::postfixExpression() {
  return getRuleContext<ExprParser::PostfixExpressionContext>(0);
}

ExprParser::ExprContext* ExprParser::CallExpressionContext::expr() {
  return getRuleContext<ExprParser::ExprContext>(0);
}

ExprParser::CallExpressionContext::CallExpressionContext(PostfixExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::CallExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitCallExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DoPostfixExpressionContext ------------------------------------------------------------------

ExprParser::PostfixExpressionContext* ExprParser::DoPostfixExpressionContext::postfixExpression() {
  return getRuleContext<ExprParser::PostfixExpressionContext>(0);
}

ExprParser::DoPostfixExpressionContext::DoPostfixExpressionContext(PostfixExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::DoPostfixExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitDoPostfixExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FallbackPostfixExpressionContext ------------------------------------------------------------------

ExprParser::PrimaryExpressionContext* ExprParser::FallbackPostfixExpressionContext::primaryExpression() {
  return getRuleContext<ExprParser::PrimaryExpressionContext>(0);
}

ExprParser::FallbackPostfixExpressionContext::FallbackPostfixExpressionContext(PostfixExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::FallbackPostfixExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFallbackPostfixExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArraySubscriptExpressionContext ------------------------------------------------------------------

ExprParser::PostfixExpressionContext* ExprParser::ArraySubscriptExpressionContext::postfixExpression() {
  return getRuleContext<ExprParser::PostfixExpressionContext>(0);
}

ExprParser::ExprContext* ExprParser::ArraySubscriptExpressionContext::expr() {
  return getRuleContext<ExprParser::ExprContext>(0);
}

ExprParser::ArraySubscriptExpressionContext::ArraySubscriptExpressionContext(PostfixExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::ArraySubscriptExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitArraySubscriptExpression(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::PostfixExpressionContext* ExprParser::postfixExpression() {
   return postfixExpression(0);
}

ExprParser::PostfixExpressionContext* ExprParser::postfixExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ExprParser::PostfixExpressionContext *_localctx = _tracker.createInstance<PostfixExpressionContext>(_ctx, parentState);
  ExprParser::PostfixExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 42;
  enterRecursionRule(_localctx, 42, ExprParser::RulePostfixExpression, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(254);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ExprParser::T__3:
      case ExprParser::T__7:
      case ExprParser::TRUE:
      case ExprParser::FALSE:
      case ExprParser::IDENT:
      case ExprParser::FLOAT_LITERAL:
      case ExprParser::INTEGER_LITERAL:
      case ExprParser::CHARACTER_LITERAL:
      case ExprParser::STRING_LITERAL: {
        _localctx = _tracker.createInstance<FallbackPostfixExpressionContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(245);
        primaryExpression();
        break;
      }

      case ExprParser::STATIC_CAST: {
        _localctx = _tracker.createInstance<CastExpressionContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(246);
        match(ExprParser::STATIC_CAST);
        setState(247);
        match(ExprParser::T__9);
        setState(248);
        type();
        setState(249);
        match(ExprParser::T__10);
        setState(250);
        match(ExprParser::T__3);
        setState(251);
        expr();
        setState(252);
        match(ExprParser::T__4);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(271);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(269);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<ArraySubscriptExpressionContext>(_tracker.createInstance<PostfixExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RulePostfixExpression);
          setState(256);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(257);
          match(ExprParser::T__5);
          setState(258);
          expr();
          setState(259);
          match(ExprParser::T__6);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<CallExpressionContext>(_tracker.createInstance<PostfixExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RulePostfixExpression);
          setState(261);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(262);
          match(ExprParser::T__3);
          setState(264);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << ExprParser::T__3)
            | (1ULL << ExprParser::T__7)
            | (1ULL << ExprParser::T__11)
            | (1ULL << ExprParser::T__12)
            | (1ULL << ExprParser::T__13)
            | (1ULL << ExprParser::T__14)
            | (1ULL << ExprParser::T__15)
            | (1ULL << ExprParser::STATIC_CAST)
            | (1ULL << ExprParser::TRUE)
            | (1ULL << ExprParser::FALSE)
            | (1ULL << ExprParser::IDENT)
            | (1ULL << ExprParser::FLOAT_LITERAL)
            | (1ULL << ExprParser::INTEGER_LITERAL)
            | (1ULL << ExprParser::CHARACTER_LITERAL)
            | (1ULL << ExprParser::STRING_LITERAL))) != 0)) {
            setState(263);
            expr();
          }
          setState(266);
          match(ExprParser::T__4);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<DoPostfixExpressionContext>(_tracker.createInstance<PostfixExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RulePostfixExpression);
          setState(267);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(268);
          dynamic_cast<DoPostfixExpressionContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == ExprParser::T__11

          || _la == ExprParser::T__12)) {
            dynamic_cast<DoPostfixExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          break;
        }

        } 
      }
      setState(273);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PrefixExpressionContext ------------------------------------------------------------------

ExprParser::PrefixExpressionContext::PrefixExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::PrefixExpressionContext::getRuleIndex() const {
  return ExprParser::RulePrefixExpression;
}

void ExprParser::PrefixExpressionContext::copyFrom(PrefixExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DoPrefixExpressionContext ------------------------------------------------------------------

ExprParser::PrefixExpressionContext* ExprParser::DoPrefixExpressionContext::prefixExpression() {
  return getRuleContext<ExprParser::PrefixExpressionContext>(0);
}

ExprParser::DoPrefixExpressionContext::DoPrefixExpressionContext(PrefixExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::DoPrefixExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitDoPrefixExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FallbackPrefixExpressionContext ------------------------------------------------------------------

ExprParser::PostfixExpressionContext* ExprParser::FallbackPrefixExpressionContext::postfixExpression() {
  return getRuleContext<ExprParser::PostfixExpressionContext>(0);
}

ExprParser::FallbackPrefixExpressionContext::FallbackPrefixExpressionContext(PrefixExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::FallbackPrefixExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFallbackPrefixExpression(this);
  else
    return visitor->visitChildren(this);
}
ExprParser::PrefixExpressionContext* ExprParser::prefixExpression() {
  PrefixExpressionContext *_localctx = _tracker.createInstance<PrefixExpressionContext>(_ctx, getState());
  enterRule(_localctx, 44, ExprParser::RulePrefixExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(277);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ExprParser::T__3:
      case ExprParser::T__7:
      case ExprParser::STATIC_CAST:
      case ExprParser::TRUE:
      case ExprParser::FALSE:
      case ExprParser::IDENT:
      case ExprParser::FLOAT_LITERAL:
      case ExprParser::INTEGER_LITERAL:
      case ExprParser::CHARACTER_LITERAL:
      case ExprParser::STRING_LITERAL: {
        _localctx = dynamic_cast<PrefixExpressionContext *>(_tracker.createInstance<ExprParser::FallbackPrefixExpressionContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(274);
        postfixExpression(0);
        break;
      }

      case ExprParser::T__11:
      case ExprParser::T__12:
      case ExprParser::T__13:
      case ExprParser::T__14:
      case ExprParser::T__15: {
        _localctx = dynamic_cast<PrefixExpressionContext *>(_tracker.createInstance<ExprParser::DoPrefixExpressionContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(275);
        dynamic_cast<DoPrefixExpressionContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << ExprParser::T__11)
          | (1ULL << ExprParser::T__12)
          | (1ULL << ExprParser::T__13)
          | (1ULL << ExprParser::T__14)
          | (1ULL << ExprParser::T__15))) != 0))) {
          dynamic_cast<DoPrefixExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(276);
        prefixExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

ExprParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::MultiplicativeExpressionContext::getRuleIndex() const {
  return ExprParser::RuleMultiplicativeExpression;
}

void ExprParser::MultiplicativeExpressionContext::copyFrom(MultiplicativeExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DoMultiplicativeExpressionContext ------------------------------------------------------------------

ExprParser::MultiplicativeExpressionContext* ExprParser::DoMultiplicativeExpressionContext::multiplicativeExpression() {
  return getRuleContext<ExprParser::MultiplicativeExpressionContext>(0);
}

ExprParser::PrefixExpressionContext* ExprParser::DoMultiplicativeExpressionContext::prefixExpression() {
  return getRuleContext<ExprParser::PrefixExpressionContext>(0);
}

ExprParser::DoMultiplicativeExpressionContext::DoMultiplicativeExpressionContext(MultiplicativeExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::DoMultiplicativeExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitDoMultiplicativeExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FallbackMultiplicativeExpressionContext ------------------------------------------------------------------

ExprParser::PrefixExpressionContext* ExprParser::FallbackMultiplicativeExpressionContext::prefixExpression() {
  return getRuleContext<ExprParser::PrefixExpressionContext>(0);
}

ExprParser::FallbackMultiplicativeExpressionContext::FallbackMultiplicativeExpressionContext(MultiplicativeExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::FallbackMultiplicativeExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFallbackMultiplicativeExpression(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::MultiplicativeExpressionContext* ExprParser::multiplicativeExpression() {
   return multiplicativeExpression(0);
}

ExprParser::MultiplicativeExpressionContext* ExprParser::multiplicativeExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ExprParser::MultiplicativeExpressionContext *_localctx = _tracker.createInstance<MultiplicativeExpressionContext>(_ctx, parentState);
  ExprParser::MultiplicativeExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, ExprParser::RuleMultiplicativeExpression, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<FallbackMultiplicativeExpressionContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(280);
    prefixExpression();
    _ctx->stop = _input->LT(-1);
    setState(287);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<DoMultiplicativeExpressionContext>(_tracker.createInstance<MultiplicativeExpressionContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleMultiplicativeExpression);
        setState(282);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(283);
        dynamic_cast<DoMultiplicativeExpressionContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << ExprParser::T__16)
          | (1ULL << ExprParser::T__17)
          | (1ULL << ExprParser::T__18))) != 0))) {
          dynamic_cast<DoMultiplicativeExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(284);
        prefixExpression(); 
      }
      setState(289);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AdditiveExpressionContext ------------------------------------------------------------------

ExprParser::AdditiveExpressionContext::AdditiveExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::AdditiveExpressionContext::getRuleIndex() const {
  return ExprParser::RuleAdditiveExpression;
}

void ExprParser::AdditiveExpressionContext::copyFrom(AdditiveExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DoAdditiveExpressionContext ------------------------------------------------------------------

ExprParser::AdditiveExpressionContext* ExprParser::DoAdditiveExpressionContext::additiveExpression() {
  return getRuleContext<ExprParser::AdditiveExpressionContext>(0);
}

ExprParser::MultiplicativeExpressionContext* ExprParser::DoAdditiveExpressionContext::multiplicativeExpression() {
  return getRuleContext<ExprParser::MultiplicativeExpressionContext>(0);
}

ExprParser::DoAdditiveExpressionContext::DoAdditiveExpressionContext(AdditiveExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::DoAdditiveExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitDoAdditiveExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FallbackAdditiveExpressionContext ------------------------------------------------------------------

ExprParser::MultiplicativeExpressionContext* ExprParser::FallbackAdditiveExpressionContext::multiplicativeExpression() {
  return getRuleContext<ExprParser::MultiplicativeExpressionContext>(0);
}

ExprParser::FallbackAdditiveExpressionContext::FallbackAdditiveExpressionContext(AdditiveExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::FallbackAdditiveExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFallbackAdditiveExpression(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::AdditiveExpressionContext* ExprParser::additiveExpression() {
   return additiveExpression(0);
}

ExprParser::AdditiveExpressionContext* ExprParser::additiveExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ExprParser::AdditiveExpressionContext *_localctx = _tracker.createInstance<AdditiveExpressionContext>(_ctx, parentState);
  ExprParser::AdditiveExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, ExprParser::RuleAdditiveExpression, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<FallbackAdditiveExpressionContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(291);
    multiplicativeExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(298);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<DoAdditiveExpressionContext>(_tracker.createInstance<AdditiveExpressionContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleAdditiveExpression);
        setState(293);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(294);
        dynamic_cast<DoAdditiveExpressionContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == ExprParser::T__13

        || _la == ExprParser::T__14)) {
          dynamic_cast<DoAdditiveExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(295);
        multiplicativeExpression(0); 
      }
      setState(300);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- RelationalExpressionContext ------------------------------------------------------------------

ExprParser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::RelationalExpressionContext::getRuleIndex() const {
  return ExprParser::RuleRelationalExpression;
}

void ExprParser::RelationalExpressionContext::copyFrom(RelationalExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FallbackRelationalExpressionContext ------------------------------------------------------------------

ExprParser::AdditiveExpressionContext* ExprParser::FallbackRelationalExpressionContext::additiveExpression() {
  return getRuleContext<ExprParser::AdditiveExpressionContext>(0);
}

ExprParser::FallbackRelationalExpressionContext::FallbackRelationalExpressionContext(RelationalExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::FallbackRelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFallbackRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DoRelationalExpressionContext ------------------------------------------------------------------

ExprParser::RelationalExpressionContext* ExprParser::DoRelationalExpressionContext::relationalExpression() {
  return getRuleContext<ExprParser::RelationalExpressionContext>(0);
}

ExprParser::AdditiveExpressionContext* ExprParser::DoRelationalExpressionContext::additiveExpression() {
  return getRuleContext<ExprParser::AdditiveExpressionContext>(0);
}

ExprParser::DoRelationalExpressionContext::DoRelationalExpressionContext(RelationalExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::DoRelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitDoRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::RelationalExpressionContext* ExprParser::relationalExpression() {
   return relationalExpression(0);
}

ExprParser::RelationalExpressionContext* ExprParser::relationalExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ExprParser::RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, parentState);
  ExprParser::RelationalExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, ExprParser::RuleRelationalExpression, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<FallbackRelationalExpressionContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(302);
    additiveExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(309);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<DoRelationalExpressionContext>(_tracker.createInstance<RelationalExpressionContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleRelationalExpression);
        setState(304);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(305);
        dynamic_cast<DoRelationalExpressionContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << ExprParser::T__9)
          | (1ULL << ExprParser::T__10)
          | (1ULL << ExprParser::T__19)
          | (1ULL << ExprParser::T__20))) != 0))) {
          dynamic_cast<DoRelationalExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(306);
        additiveExpression(0); 
      }
      setState(311);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- EqualityExpressionContext ------------------------------------------------------------------

ExprParser::EqualityExpressionContext::EqualityExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::EqualityExpressionContext::getRuleIndex() const {
  return ExprParser::RuleEqualityExpression;
}

void ExprParser::EqualityExpressionContext::copyFrom(EqualityExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DoEqualityExpressionContext ------------------------------------------------------------------

ExprParser::EqualityExpressionContext* ExprParser::DoEqualityExpressionContext::equalityExpression() {
  return getRuleContext<ExprParser::EqualityExpressionContext>(0);
}

ExprParser::RelationalExpressionContext* ExprParser::DoEqualityExpressionContext::relationalExpression() {
  return getRuleContext<ExprParser::RelationalExpressionContext>(0);
}

ExprParser::DoEqualityExpressionContext::DoEqualityExpressionContext(EqualityExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::DoEqualityExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitDoEqualityExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FallbackEqualityExpressionContext ------------------------------------------------------------------

ExprParser::RelationalExpressionContext* ExprParser::FallbackEqualityExpressionContext::relationalExpression() {
  return getRuleContext<ExprParser::RelationalExpressionContext>(0);
}

ExprParser::FallbackEqualityExpressionContext::FallbackEqualityExpressionContext(EqualityExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::FallbackEqualityExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFallbackEqualityExpression(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::EqualityExpressionContext* ExprParser::equalityExpression() {
   return equalityExpression(0);
}

ExprParser::EqualityExpressionContext* ExprParser::equalityExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ExprParser::EqualityExpressionContext *_localctx = _tracker.createInstance<EqualityExpressionContext>(_ctx, parentState);
  ExprParser::EqualityExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, ExprParser::RuleEqualityExpression, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<FallbackEqualityExpressionContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(313);
    relationalExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(320);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<DoEqualityExpressionContext>(_tracker.createInstance<EqualityExpressionContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleEqualityExpression);
        setState(315);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(316);
        dynamic_cast<DoEqualityExpressionContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == ExprParser::T__21

        || _la == ExprParser::T__22)) {
          dynamic_cast<DoEqualityExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(317);
        relationalExpression(0); 
      }
      setState(322);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LogicalAndExpressionContext ------------------------------------------------------------------

ExprParser::LogicalAndExpressionContext::LogicalAndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::LogicalAndExpressionContext::getRuleIndex() const {
  return ExprParser::RuleLogicalAndExpression;
}

void ExprParser::LogicalAndExpressionContext::copyFrom(LogicalAndExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DoLogicalAndExpressionContext ------------------------------------------------------------------

ExprParser::LogicalAndExpressionContext* ExprParser::DoLogicalAndExpressionContext::logicalAndExpression() {
  return getRuleContext<ExprParser::LogicalAndExpressionContext>(0);
}

ExprParser::EqualityExpressionContext* ExprParser::DoLogicalAndExpressionContext::equalityExpression() {
  return getRuleContext<ExprParser::EqualityExpressionContext>(0);
}

ExprParser::DoLogicalAndExpressionContext::DoLogicalAndExpressionContext(LogicalAndExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::DoLogicalAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitDoLogicalAndExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FallbackLogicalAndExpressionContext ------------------------------------------------------------------

ExprParser::EqualityExpressionContext* ExprParser::FallbackLogicalAndExpressionContext::equalityExpression() {
  return getRuleContext<ExprParser::EqualityExpressionContext>(0);
}

ExprParser::FallbackLogicalAndExpressionContext::FallbackLogicalAndExpressionContext(LogicalAndExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::FallbackLogicalAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFallbackLogicalAndExpression(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::LogicalAndExpressionContext* ExprParser::logicalAndExpression() {
   return logicalAndExpression(0);
}

ExprParser::LogicalAndExpressionContext* ExprParser::logicalAndExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ExprParser::LogicalAndExpressionContext *_localctx = _tracker.createInstance<LogicalAndExpressionContext>(_ctx, parentState);
  ExprParser::LogicalAndExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, ExprParser::RuleLogicalAndExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<FallbackLogicalAndExpressionContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(324);
    equalityExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(331);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<DoLogicalAndExpressionContext>(_tracker.createInstance<LogicalAndExpressionContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleLogicalAndExpression);
        setState(326);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(327);
        match(ExprParser::T__23);
        setState(328);
        equalityExpression(0); 
      }
      setState(333);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LogicalOrExpressionContext ------------------------------------------------------------------

ExprParser::LogicalOrExpressionContext::LogicalOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::LogicalOrExpressionContext::getRuleIndex() const {
  return ExprParser::RuleLogicalOrExpression;
}

void ExprParser::LogicalOrExpressionContext::copyFrom(LogicalOrExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DoLogicalOrExpressionContext ------------------------------------------------------------------

ExprParser::LogicalOrExpressionContext* ExprParser::DoLogicalOrExpressionContext::logicalOrExpression() {
  return getRuleContext<ExprParser::LogicalOrExpressionContext>(0);
}

ExprParser::LogicalAndExpressionContext* ExprParser::DoLogicalOrExpressionContext::logicalAndExpression() {
  return getRuleContext<ExprParser::LogicalAndExpressionContext>(0);
}

ExprParser::DoLogicalOrExpressionContext::DoLogicalOrExpressionContext(LogicalOrExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::DoLogicalOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitDoLogicalOrExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FallbackLogicalOrExpressionContext ------------------------------------------------------------------

ExprParser::LogicalAndExpressionContext* ExprParser::FallbackLogicalOrExpressionContext::logicalAndExpression() {
  return getRuleContext<ExprParser::LogicalAndExpressionContext>(0);
}

ExprParser::FallbackLogicalOrExpressionContext::FallbackLogicalOrExpressionContext(LogicalOrExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::FallbackLogicalOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFallbackLogicalOrExpression(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::LogicalOrExpressionContext* ExprParser::logicalOrExpression() {
   return logicalOrExpression(0);
}

ExprParser::LogicalOrExpressionContext* ExprParser::logicalOrExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ExprParser::LogicalOrExpressionContext *_localctx = _tracker.createInstance<LogicalOrExpressionContext>(_ctx, parentState);
  ExprParser::LogicalOrExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, ExprParser::RuleLogicalOrExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<FallbackLogicalOrExpressionContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(335);
    logicalAndExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(342);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<DoLogicalOrExpressionContext>(_tracker.createInstance<LogicalOrExpressionContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleLogicalOrExpression);
        setState(337);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(338);
        match(ExprParser::T__24);
        setState(339);
        logicalAndExpression(0); 
      }
      setState(344);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ConditionalExpressionContext ------------------------------------------------------------------

ExprParser::ConditionalExpressionContext::ConditionalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::ConditionalExpressionContext::getRuleIndex() const {
  return ExprParser::RuleConditionalExpression;
}

void ExprParser::ConditionalExpressionContext::copyFrom(ConditionalExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FallbackConditionalExpressionContext ------------------------------------------------------------------

ExprParser::LogicalOrExpressionContext* ExprParser::FallbackConditionalExpressionContext::logicalOrExpression() {
  return getRuleContext<ExprParser::LogicalOrExpressionContext>(0);
}

ExprParser::FallbackConditionalExpressionContext::FallbackConditionalExpressionContext(ConditionalExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::FallbackConditionalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFallbackConditionalExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DoConditionalExpressionContext ------------------------------------------------------------------

ExprParser::LogicalOrExpressionContext* ExprParser::DoConditionalExpressionContext::logicalOrExpression() {
  return getRuleContext<ExprParser::LogicalOrExpressionContext>(0);
}

ExprParser::ExprContext* ExprParser::DoConditionalExpressionContext::expr() {
  return getRuleContext<ExprParser::ExprContext>(0);
}

ExprParser::ConditionalExpressionContext* ExprParser::DoConditionalExpressionContext::conditionalExpression() {
  return getRuleContext<ExprParser::ConditionalExpressionContext>(0);
}

ExprParser::DoConditionalExpressionContext::DoConditionalExpressionContext(ConditionalExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::DoConditionalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitDoConditionalExpression(this);
  else
    return visitor->visitChildren(this);
}
ExprParser::ConditionalExpressionContext* ExprParser::conditionalExpression() {
  ConditionalExpressionContext *_localctx = _tracker.createInstance<ConditionalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 58, ExprParser::RuleConditionalExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(352);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<ConditionalExpressionContext *>(_tracker.createInstance<ExprParser::FallbackConditionalExpressionContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(345);
      logicalOrExpression(0);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<ConditionalExpressionContext *>(_tracker.createInstance<ExprParser::DoConditionalExpressionContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(346);
      logicalOrExpression(0);

      setState(347);
      match(ExprParser::T__25);
      setState(348);
      expr();
      setState(349);
      match(ExprParser::T__26);
      setState(350);
      conditionalExpression();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentExpressionContext ------------------------------------------------------------------

ExprParser::AssignmentExpressionContext::AssignmentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::AssignmentExpressionContext::getRuleIndex() const {
  return ExprParser::RuleAssignmentExpression;
}

void ExprParser::AssignmentExpressionContext::copyFrom(AssignmentExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DoAssignmentExpressionContext ------------------------------------------------------------------

ExprParser::PrefixExpressionContext* ExprParser::DoAssignmentExpressionContext::prefixExpression() {
  return getRuleContext<ExprParser::PrefixExpressionContext>(0);
}

ExprParser::AssignmentExpressionContext* ExprParser::DoAssignmentExpressionContext::assignmentExpression() {
  return getRuleContext<ExprParser::AssignmentExpressionContext>(0);
}

ExprParser::DoAssignmentExpressionContext::DoAssignmentExpressionContext(AssignmentExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::DoAssignmentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitDoAssignmentExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FallbackAssigmentExpressionContext ------------------------------------------------------------------

ExprParser::ConditionalExpressionContext* ExprParser::FallbackAssigmentExpressionContext::conditionalExpression() {
  return getRuleContext<ExprParser::ConditionalExpressionContext>(0);
}

ExprParser::FallbackAssigmentExpressionContext::FallbackAssigmentExpressionContext(AssignmentExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::FallbackAssigmentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFallbackAssigmentExpression(this);
  else
    return visitor->visitChildren(this);
}
ExprParser::AssignmentExpressionContext* ExprParser::assignmentExpression() {
  AssignmentExpressionContext *_localctx = _tracker.createInstance<AssignmentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 60, ExprParser::RuleAssignmentExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(359);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<AssignmentExpressionContext *>(_tracker.createInstance<ExprParser::FallbackAssigmentExpressionContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(354);
      conditionalExpression();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<AssignmentExpressionContext *>(_tracker.createInstance<ExprParser::DoAssignmentExpressionContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(355);
      prefixExpression();
      setState(356);
      dynamic_cast<DoAssignmentExpressionContext *>(_localctx)->op = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << ExprParser::T__2)
        | (1ULL << ExprParser::T__27)
        | (1ULL << ExprParser::T__28)
        | (1ULL << ExprParser::T__29)
        | (1ULL << ExprParser::T__30)
        | (1ULL << ExprParser::T__31))) != 0))) {
        dynamic_cast<DoAssignmentExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(357);
      assignmentExpression();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

ExprParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::ExprContext::getRuleIndex() const {
  return ExprParser::RuleExpr;
}

void ExprParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DoExpressionListContext ------------------------------------------------------------------

std::vector<ExprParser::AssignmentExpressionContext *> ExprParser::DoExpressionListContext::assignmentExpression() {
  return getRuleContexts<ExprParser::AssignmentExpressionContext>();
}

ExprParser::AssignmentExpressionContext* ExprParser::DoExpressionListContext::assignmentExpression(size_t i) {
  return getRuleContext<ExprParser::AssignmentExpressionContext>(i);
}

ExprParser::DoExpressionListContext::DoExpressionListContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::DoExpressionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitDoExpressionList(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FallbackExprContext ------------------------------------------------------------------

ExprParser::AssignmentExpressionContext* ExprParser::FallbackExprContext::assignmentExpression() {
  return getRuleContext<ExprParser::AssignmentExpressionContext>(0);
}

ExprParser::FallbackExprContext::FallbackExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ExprParser::FallbackExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFallbackExpr(this);
  else
    return visitor->visitChildren(this);
}
ExprParser::ExprContext* ExprParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 62, ExprParser::RuleExpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(370);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<ExprContext *>(_tracker.createInstance<ExprParser::FallbackExprContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(361);
      assignmentExpression();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<ExprContext *>(_tracker.createInstance<ExprParser::DoExpressionListContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(362);
      assignmentExpression();
      setState(367);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ExprParser::T__0) {
        setState(363);
        match(ExprParser::T__0);
        setState(364);
        assignmentExpression();
        setState(369);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantExpressionContext ------------------------------------------------------------------

ExprParser::ConstantExpressionContext::ConstantExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExprParser::ConditionalExpressionContext* ExprParser::ConstantExpressionContext::conditionalExpression() {
  return getRuleContext<ExprParser::ConditionalExpressionContext>(0);
}


size_t ExprParser::ConstantExpressionContext::getRuleIndex() const {
  return ExprParser::RuleConstantExpression;
}


antlrcpp::Any ExprParser::ConstantExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitConstantExpression(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::ConstantExpressionContext* ExprParser::constantExpression() {
  ConstantExpressionContext *_localctx = _tracker.createInstance<ConstantExpressionContext>(_ctx, getState());
  enterRule(_localctx, 64, ExprParser::RuleConstantExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(372);
    conditionalExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

ExprParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExprParser::Type_nameContext* ExprParser::TypeContext::type_name() {
  return getRuleContext<ExprParser::Type_nameContext>(0);
}

ExprParser::TypemodifierContext* ExprParser::TypeContext::typemodifier() {
  return getRuleContext<ExprParser::TypemodifierContext>(0);
}


size_t ExprParser::TypeContext::getRuleIndex() const {
  return ExprParser::RuleType;
}


antlrcpp::Any ExprParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::TypeContext* ExprParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 66, ExprParser::RuleType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(375);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ExprParser::SIGNED

    || _la == ExprParser::UNSIGNED) {
      setState(374);
      typemodifier();
    }
    setState(377);
    type_name();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypemodifierContext ------------------------------------------------------------------

ExprParser::TypemodifierContext::TypemodifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ExprParser::TypemodifierContext::SIGNED() {
  return getToken(ExprParser::SIGNED, 0);
}

tree::TerminalNode* ExprParser::TypemodifierContext::UNSIGNED() {
  return getToken(ExprParser::UNSIGNED, 0);
}


size_t ExprParser::TypemodifierContext::getRuleIndex() const {
  return ExprParser::RuleTypemodifier;
}


antlrcpp::Any ExprParser::TypemodifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitTypemodifier(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::TypemodifierContext* ExprParser::typemodifier() {
  TypemodifierContext *_localctx = _tracker.createInstance<TypemodifierContext>(_ctx, getState());
  enterRule(_localctx, 68, ExprParser::RuleTypemodifier);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(379);
    dynamic_cast<TypemodifierContext *>(_localctx)->modifier = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == ExprParser::SIGNED

    || _la == ExprParser::UNSIGNED)) {
      dynamic_cast<TypemodifierContext *>(_localctx)->modifier = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Type_nameContext ------------------------------------------------------------------

ExprParser::Type_nameContext::Type_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ExprParser::Type_nameContext::VOID() {
  return getToken(ExprParser::VOID, 0);
}

tree::TerminalNode* ExprParser::Type_nameContext::BOOL() {
  return getToken(ExprParser::BOOL, 0);
}

tree::TerminalNode* ExprParser::Type_nameContext::CHAR() {
  return getToken(ExprParser::CHAR, 0);
}

tree::TerminalNode* ExprParser::Type_nameContext::INT() {
  return getToken(ExprParser::INT, 0);
}

tree::TerminalNode* ExprParser::Type_nameContext::FLOAT() {
  return getToken(ExprParser::FLOAT, 0);
}


size_t ExprParser::Type_nameContext::getRuleIndex() const {
  return ExprParser::RuleType_name;
}


antlrcpp::Any ExprParser::Type_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitType_name(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::Type_nameContext* ExprParser::type_name() {
  Type_nameContext *_localctx = _tracker.createInstance<Type_nameContext>(_ctx, getState());
  enterRule(_localctx, 70, ExprParser::RuleType_name);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(381);
    dynamic_cast<Type_nameContext *>(_localctx)->name = _input->LT(1);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExprParser::INT)
      | (1ULL << ExprParser::CHAR)
      | (1ULL << ExprParser::BOOL)
      | (1ULL << ExprParser::FLOAT)
      | (1ULL << ExprParser::VOID))) != 0))) {
      dynamic_cast<Type_nameContext *>(_localctx)->name = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

ExprParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExprParser::BoolLiteralContext* ExprParser::LiteralContext::boolLiteral() {
  return getRuleContext<ExprParser::BoolLiteralContext>(0);
}

ExprParser::CharLiteralContext* ExprParser::LiteralContext::charLiteral() {
  return getRuleContext<ExprParser::CharLiteralContext>(0);
}

ExprParser::IntegerLiteralContext* ExprParser::LiteralContext::integerLiteral() {
  return getRuleContext<ExprParser::IntegerLiteralContext>(0);
}

ExprParser::FloatLiteralContext* ExprParser::LiteralContext::floatLiteral() {
  return getRuleContext<ExprParser::FloatLiteralContext>(0);
}

ExprParser::StringLiteralContext* ExprParser::LiteralContext::stringLiteral() {
  return getRuleContext<ExprParser::StringLiteralContext>(0);
}

ExprParser::ArrayLiteralContext* ExprParser::LiteralContext::arrayLiteral() {
  return getRuleContext<ExprParser::ArrayLiteralContext>(0);
}


size_t ExprParser::LiteralContext::getRuleIndex() const {
  return ExprParser::RuleLiteral;
}


antlrcpp::Any ExprParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::LiteralContext* ExprParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 72, ExprParser::RuleLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(389);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ExprParser::TRUE:
      case ExprParser::FALSE: {
        enterOuterAlt(_localctx, 1);
        setState(383);
        boolLiteral();
        break;
      }

      case ExprParser::CHARACTER_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(384);
        charLiteral();
        break;
      }

      case ExprParser::INTEGER_LITERAL: {
        enterOuterAlt(_localctx, 3);
        setState(385);
        integerLiteral();
        break;
      }

      case ExprParser::FLOAT_LITERAL: {
        enterOuterAlt(_localctx, 4);
        setState(386);
        floatLiteral();
        break;
      }

      case ExprParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 5);
        setState(387);
        stringLiteral();
        break;
      }

      case ExprParser::T__7: {
        enterOuterAlt(_localctx, 6);
        setState(388);
        arrayLiteral();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BoolLiteralContext ------------------------------------------------------------------

ExprParser::BoolLiteralContext::BoolLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ExprParser::BoolLiteralContext::TRUE() {
  return getToken(ExprParser::TRUE, 0);
}

tree::TerminalNode* ExprParser::BoolLiteralContext::FALSE() {
  return getToken(ExprParser::FALSE, 0);
}


size_t ExprParser::BoolLiteralContext::getRuleIndex() const {
  return ExprParser::RuleBoolLiteral;
}


antlrcpp::Any ExprParser::BoolLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitBoolLiteral(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::BoolLiteralContext* ExprParser::boolLiteral() {
  BoolLiteralContext *_localctx = _tracker.createInstance<BoolLiteralContext>(_ctx, getState());
  enterRule(_localctx, 74, ExprParser::RuleBoolLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(391);
    dynamic_cast<BoolLiteralContext *>(_localctx)->value = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == ExprParser::TRUE

    || _la == ExprParser::FALSE)) {
      dynamic_cast<BoolLiteralContext *>(_localctx)->value = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CharLiteralContext ------------------------------------------------------------------

ExprParser::CharLiteralContext::CharLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ExprParser::CharLiteralContext::CHARACTER_LITERAL() {
  return getToken(ExprParser::CHARACTER_LITERAL, 0);
}


size_t ExprParser::CharLiteralContext::getRuleIndex() const {
  return ExprParser::RuleCharLiteral;
}


antlrcpp::Any ExprParser::CharLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitCharLiteral(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::CharLiteralContext* ExprParser::charLiteral() {
  CharLiteralContext *_localctx = _tracker.createInstance<CharLiteralContext>(_ctx, getState());
  enterRule(_localctx, 76, ExprParser::RuleCharLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(393);
    match(ExprParser::CHARACTER_LITERAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntegerLiteralContext ------------------------------------------------------------------

ExprParser::IntegerLiteralContext::IntegerLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ExprParser::IntegerLiteralContext::INTEGER_LITERAL() {
  return getToken(ExprParser::INTEGER_LITERAL, 0);
}


size_t ExprParser::IntegerLiteralContext::getRuleIndex() const {
  return ExprParser::RuleIntegerLiteral;
}


antlrcpp::Any ExprParser::IntegerLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitIntegerLiteral(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::IntegerLiteralContext* ExprParser::integerLiteral() {
  IntegerLiteralContext *_localctx = _tracker.createInstance<IntegerLiteralContext>(_ctx, getState());
  enterRule(_localctx, 78, ExprParser::RuleIntegerLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(395);
    match(ExprParser::INTEGER_LITERAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FloatLiteralContext ------------------------------------------------------------------

ExprParser::FloatLiteralContext::FloatLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ExprParser::FloatLiteralContext::FLOAT_LITERAL() {
  return getToken(ExprParser::FLOAT_LITERAL, 0);
}


size_t ExprParser::FloatLiteralContext::getRuleIndex() const {
  return ExprParser::RuleFloatLiteral;
}


antlrcpp::Any ExprParser::FloatLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitFloatLiteral(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::FloatLiteralContext* ExprParser::floatLiteral() {
  FloatLiteralContext *_localctx = _tracker.createInstance<FloatLiteralContext>(_ctx, getState());
  enterRule(_localctx, 80, ExprParser::RuleFloatLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(397);
    match(ExprParser::FLOAT_LITERAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringLiteralContext ------------------------------------------------------------------

ExprParser::StringLiteralContext::StringLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ExprParser::StringLiteralContext::STRING_LITERAL() {
  return getTokens(ExprParser::STRING_LITERAL);
}

tree::TerminalNode* ExprParser::StringLiteralContext::STRING_LITERAL(size_t i) {
  return getToken(ExprParser::STRING_LITERAL, i);
}


size_t ExprParser::StringLiteralContext::getRuleIndex() const {
  return ExprParser::RuleStringLiteral;
}


antlrcpp::Any ExprParser::StringLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitStringLiteral(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::StringLiteralContext* ExprParser::stringLiteral() {
  StringLiteralContext *_localctx = _tracker.createInstance<StringLiteralContext>(_ctx, getState());
  enterRule(_localctx, 82, ExprParser::RuleStringLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(400); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(399);
              match(ExprParser::STRING_LITERAL);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(402); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayLiteralContext ------------------------------------------------------------------

ExprParser::ArrayLiteralContext::ArrayLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExprParser::ArrayLiteralListContext* ExprParser::ArrayLiteralContext::arrayLiteralList() {
  return getRuleContext<ExprParser::ArrayLiteralListContext>(0);
}


size_t ExprParser::ArrayLiteralContext::getRuleIndex() const {
  return ExprParser::RuleArrayLiteral;
}


antlrcpp::Any ExprParser::ArrayLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitArrayLiteral(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::ArrayLiteralContext* ExprParser::arrayLiteral() {
  ArrayLiteralContext *_localctx = _tracker.createInstance<ArrayLiteralContext>(_ctx, getState());
  enterRule(_localctx, 84, ExprParser::RuleArrayLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(404);
    match(ExprParser::T__7);
    setState(405);
    arrayLiteralList();
    setState(406);
    match(ExprParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayLiteralListContext ------------------------------------------------------------------

ExprParser::ArrayLiteralListContext::ArrayLiteralListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExprParser::LiteralContext *> ExprParser::ArrayLiteralListContext::literal() {
  return getRuleContexts<ExprParser::LiteralContext>();
}

ExprParser::LiteralContext* ExprParser::ArrayLiteralListContext::literal(size_t i) {
  return getRuleContext<ExprParser::LiteralContext>(i);
}


size_t ExprParser::ArrayLiteralListContext::getRuleIndex() const {
  return ExprParser::RuleArrayLiteralList;
}


antlrcpp::Any ExprParser::ArrayLiteralListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitArrayLiteralList(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::ArrayLiteralListContext* ExprParser::arrayLiteralList() {
  ArrayLiteralListContext *_localctx = _tracker.createInstance<ArrayLiteralListContext>(_ctx, getState());
  enterRule(_localctx, 86, ExprParser::RuleArrayLiteralList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(408);
    literal();
    setState(413);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExprParser::T__0) {
      setState(409);
      match(ExprParser::T__0);
      setState(410);
      literal();
      setState(415);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool ExprParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 21: return postfixExpressionSempred(dynamic_cast<PostfixExpressionContext *>(context), predicateIndex);
    case 23: return multiplicativeExpressionSempred(dynamic_cast<MultiplicativeExpressionContext *>(context), predicateIndex);
    case 24: return additiveExpressionSempred(dynamic_cast<AdditiveExpressionContext *>(context), predicateIndex);
    case 25: return relationalExpressionSempred(dynamic_cast<RelationalExpressionContext *>(context), predicateIndex);
    case 26: return equalityExpressionSempred(dynamic_cast<EqualityExpressionContext *>(context), predicateIndex);
    case 27: return logicalAndExpressionSempred(dynamic_cast<LogicalAndExpressionContext *>(context), predicateIndex);
    case 28: return logicalOrExpressionSempred(dynamic_cast<LogicalOrExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool ExprParser::postfixExpressionSempred(PostfixExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);
    case 1: return precpred(_ctx, 3);
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool ExprParser::multiplicativeExpressionSempred(MultiplicativeExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool ExprParser::additiveExpressionSempred(AdditiveExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool ExprParser::relationalExpressionSempred(RelationalExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool ExprParser::equalityExpressionSempred(EqualityExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 6: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool ExprParser::logicalAndExpressionSempred(LogicalAndExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 7: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool ExprParser::logicalOrExpressionSempred(LogicalOrExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 8: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> ExprParser::_decisionToDFA;
atn::PredictionContextCache ExprParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN ExprParser::_atn;
std::vector<uint16_t> ExprParser::_serializedATN;

std::vector<std::string> ExprParser::_ruleNames = {
  "translationUnit", "declaration", "variableDeclaration", "initDeclarator", 
  "initializer", "functionDeclaration", "functionDefinition", "functionPrototype", 
  "formalParameterList", "formalParameter", "arrayDimensionList", "arrayDimExpr", 
  "statement", "compoundStatement", "expressionStatement", "ifStatement", 
  "forStatement", "forInitStatement", "whileStatement", "idExpression", 
  "primaryExpression", "postfixExpression", "prefixExpression", "multiplicativeExpression", 
  "additiveExpression", "relationalExpression", "equalityExpression", "logicalAndExpression", 
  "logicalOrExpression", "conditionalExpression", "assignmentExpression", 
  "expr", "constantExpression", "type", "typemodifier", "type_name", "literal", 
  "boolLiteral", "charLiteral", "integerLiteral", "floatLiteral", "stringLiteral", 
  "arrayLiteral", "arrayLiteralList"
};

std::vector<std::string> ExprParser::_literalNames = {
  "", "','", "';'", "'='", "'('", "')'", "'['", "']'", "'{'", "'}'", "'<'", 
  "'>'", "'++'", "'--'", "'+'", "'-'", "'!'", "'*'", "'/'", "'%'", "'<='", 
  "'>='", "'=='", "'!='", "'&&'", "'||'", "'?'", "':'", "'*='", "'/='", 
  "'%='", "'+='", "'-='", "'extern'", "'if'", "'else'", "'for'", "'while'", 
  "'continue'", "'break'", "'return'", "'signed'", "'unsigned'", "'int'", 
  "'char'", "'bool'", "'float'", "'void'", "'static_cast'", "'true'", "'false'"
};

std::vector<std::string> ExprParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "EXTERN", 
  "IF", "ELSE", "FOR", "WHILE", "CONTINUE", "BREAK", "RETURN", "SIGNED", 
  "UNSIGNED", "INT", "CHAR", "BOOL", "FLOAT", "VOID", "STATIC_CAST", "TRUE", 
  "FALSE", "IDENT", "COMMENT", "NS", "FLOAT_LITERAL", "INTEGER_LITERAL", 
  "CHARACTER_LITERAL", "STRING_LITERAL"
};

dfa::Vocabulary ExprParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> ExprParser::_tokenNames;

ExprParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x3b, 0x1a3, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 
    0x2c, 0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x3, 0x2, 0x7, 0x2, 0x5c, 0xa, 
    0x2, 0xc, 0x2, 0xe, 0x2, 0x5f, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x66, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x7, 0x4, 0x6c, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x6f, 0xb, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x75, 0xa, 0x5, 
    0x3, 0x5, 0x5, 0x5, 0x78, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x5, 
    0x9, 0x84, 0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 
    0x8a, 0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 
    0xa, 0x91, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x94, 0xb, 0xa, 0x3, 0xb, 0x3, 
    0xb, 0x5, 0xb, 0x98, 0xa, 0xb, 0x3, 0xb, 0x5, 0xb, 0x9b, 0xa, 0xb, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x6, 0xc, 0xa1, 0xa, 0xc, 0xd, 0xc, 
    0xe, 0xc, 0xa2, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0xa7, 0xa, 0xd, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x5, 0xe, 0xb1, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x5, 0xe, 0xb9, 0xa, 0xe, 0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 
    0xbd, 0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 0xc0, 0xb, 0xf, 0x3, 0xf, 0x3, 0xf, 
    0x3, 0x10, 0x5, 0x10, 0xc5, 0xa, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 
    0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x5, 0x11, 0xd7, 0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x3, 0x12, 0x5, 0x12, 0xde, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0xe5, 0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 
    0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 
    0xf5, 0xa, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x101, 
    0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x10b, 0xa, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x7, 0x17, 0x110, 0xa, 0x17, 0xc, 0x17, 0xe, 0x17, 
    0x113, 0xb, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x118, 
    0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x7, 0x19, 0x120, 0xa, 0x19, 0xc, 0x19, 0xe, 0x19, 0x123, 0xb, 
    0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
    0x7, 0x1a, 0x12b, 0xa, 0x1a, 0xc, 0x1a, 0xe, 0x1a, 0x12e, 0xb, 0x1a, 
    0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x7, 
    0x1b, 0x136, 0xa, 0x1b, 0xc, 0x1b, 0xe, 0x1b, 0x139, 0xb, 0x1b, 0x3, 
    0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x7, 0x1c, 
    0x141, 0xa, 0x1c, 0xc, 0x1c, 0xe, 0x1c, 0x144, 0xb, 0x1c, 0x3, 0x1d, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x7, 0x1d, 0x14c, 
    0xa, 0x1d, 0xc, 0x1d, 0xe, 0x1d, 0x14f, 0xb, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 
    0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x7, 0x1e, 0x157, 0xa, 0x1e, 
    0xc, 0x1e, 0xe, 0x1e, 0x15a, 0xb, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 
    0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x5, 0x1f, 0x163, 0xa, 0x1f, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x16a, 
    0xa, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x7, 0x21, 0x170, 
    0xa, 0x21, 0xc, 0x21, 0xe, 0x21, 0x173, 0xb, 0x21, 0x5, 0x21, 0x175, 
    0xa, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x5, 0x23, 0x17a, 0xa, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x25, 0x3, 0x25, 0x3, 
    0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x5, 0x26, 
    0x188, 0xa, 0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x29, 
    0x3, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2b, 0x6, 0x2b, 0x193, 0xa, 0x2b, 
    0xd, 0x2b, 0xe, 0x2b, 0x194, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 
    0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x7, 0x2d, 0x19e, 0xa, 0x2d, 0xc, 0x2d, 
    0xe, 0x2d, 0x1a1, 0xb, 0x2d, 0x3, 0x2d, 0x2, 0x9, 0x2c, 0x30, 0x32, 
    0x34, 0x36, 0x38, 0x3a, 0x2e, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 
    0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 
    0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 
    0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 
    0x2, 0xc, 0x3, 0x2, 0xe, 0xf, 0x3, 0x2, 0xe, 0x12, 0x3, 0x2, 0x13, 0x15, 
    0x3, 0x2, 0x10, 0x11, 0x4, 0x2, 0xc, 0xd, 0x16, 0x17, 0x3, 0x2, 0x18, 
    0x19, 0x4, 0x2, 0x5, 0x5, 0x1e, 0x22, 0x3, 0x2, 0x2b, 0x2c, 0x3, 0x2, 
    0x2d, 0x31, 0x3, 0x2, 0x33, 0x34, 0x2, 0x1ac, 0x2, 0x5d, 0x3, 0x2, 0x2, 
    0x2, 0x4, 0x65, 0x3, 0x2, 0x2, 0x2, 0x6, 0x67, 0x3, 0x2, 0x2, 0x2, 0x8, 
    0x72, 0x3, 0x2, 0x2, 0x2, 0xa, 0x79, 0x3, 0x2, 0x2, 0x2, 0xc, 0x7c, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x10, 0x83, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x14, 0x95, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x18, 0xa6, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0xb8, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xba, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0xc4, 0x3, 0x2, 0x2, 0x2, 0x20, 0xd6, 0x3, 0x2, 0x2, 0x2, 0x22, 
    0xd8, 0x3, 0x2, 0x2, 0x2, 0x24, 0xe4, 0x3, 0x2, 0x2, 0x2, 0x26, 0xe6, 
    0x3, 0x2, 0x2, 0x2, 0x28, 0xec, 0x3, 0x2, 0x2, 0x2, 0x2a, 0xf4, 0x3, 
    0x2, 0x2, 0x2, 0x2c, 0x100, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x117, 0x3, 0x2, 
    0x2, 0x2, 0x30, 0x119, 0x3, 0x2, 0x2, 0x2, 0x32, 0x124, 0x3, 0x2, 0x2, 
    0x2, 0x34, 0x12f, 0x3, 0x2, 0x2, 0x2, 0x36, 0x13a, 0x3, 0x2, 0x2, 0x2, 
    0x38, 0x145, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x150, 0x3, 0x2, 0x2, 0x2, 0x3c, 
    0x162, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x169, 0x3, 0x2, 0x2, 0x2, 0x40, 0x174, 
    0x3, 0x2, 0x2, 0x2, 0x42, 0x176, 0x3, 0x2, 0x2, 0x2, 0x44, 0x179, 0x3, 
    0x2, 0x2, 0x2, 0x46, 0x17d, 0x3, 0x2, 0x2, 0x2, 0x48, 0x17f, 0x3, 0x2, 
    0x2, 0x2, 0x4a, 0x187, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x189, 0x3, 0x2, 0x2, 
    0x2, 0x4e, 0x18b, 0x3, 0x2, 0x2, 0x2, 0x50, 0x18d, 0x3, 0x2, 0x2, 0x2, 
    0x52, 0x18f, 0x3, 0x2, 0x2, 0x2, 0x54, 0x192, 0x3, 0x2, 0x2, 0x2, 0x56, 
    0x196, 0x3, 0x2, 0x2, 0x2, 0x58, 0x19a, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5c, 
    0x5, 0x4, 0x3, 0x2, 0x5b, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5f, 0x3, 
    0x2, 0x2, 0x2, 0x5d, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5e, 0x3, 0x2, 
    0x2, 0x2, 0x5e, 0x60, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x5d, 0x3, 0x2, 0x2, 
    0x2, 0x60, 0x61, 0x7, 0x2, 0x2, 0x3, 0x61, 0x3, 0x3, 0x2, 0x2, 0x2, 
    0x62, 0x66, 0x5, 0x6, 0x4, 0x2, 0x63, 0x66, 0x5, 0xc, 0x7, 0x2, 0x64, 
    0x66, 0x5, 0xe, 0x8, 0x2, 0x65, 0x62, 0x3, 0x2, 0x2, 0x2, 0x65, 0x63, 
    0x3, 0x2, 0x2, 0x2, 0x65, 0x64, 0x3, 0x2, 0x2, 0x2, 0x66, 0x5, 0x3, 
    0x2, 0x2, 0x2, 0x67, 0x68, 0x5, 0x44, 0x23, 0x2, 0x68, 0x6d, 0x5, 0x8, 
    0x5, 0x2, 0x69, 0x6a, 0x7, 0x3, 0x2, 0x2, 0x6a, 0x6c, 0x5, 0x8, 0x5, 
    0x2, 0x6b, 0x69, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6f, 0x3, 0x2, 0x2, 0x2, 
    0x6d, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6e, 
    0x70, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x70, 0x71, 
    0x7, 0x4, 0x2, 0x2, 0x71, 0x7, 0x3, 0x2, 0x2, 0x2, 0x72, 0x74, 0x7, 
    0x35, 0x2, 0x2, 0x73, 0x75, 0x5, 0x16, 0xc, 0x2, 0x74, 0x73, 0x3, 0x2, 
    0x2, 0x2, 0x74, 0x75, 0x3, 0x2, 0x2, 0x2, 0x75, 0x77, 0x3, 0x2, 0x2, 
    0x2, 0x76, 0x78, 0x5, 0xa, 0x6, 0x2, 0x77, 0x76, 0x3, 0x2, 0x2, 0x2, 
    0x77, 0x78, 0x3, 0x2, 0x2, 0x2, 0x78, 0x9, 0x3, 0x2, 0x2, 0x2, 0x79, 
    0x7a, 0x7, 0x5, 0x2, 0x2, 0x7a, 0x7b, 0x5, 0x3c, 0x1f, 0x2, 0x7b, 0xb, 
    0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x5, 0x10, 0x9, 0x2, 0x7d, 0x7e, 0x7, 
    0x4, 0x2, 0x2, 0x7e, 0xd, 0x3, 0x2, 0x2, 0x2, 0x7f, 0x80, 0x5, 0x10, 
    0x9, 0x2, 0x80, 0x81, 0x5, 0x1c, 0xf, 0x2, 0x81, 0xf, 0x3, 0x2, 0x2, 
    0x2, 0x82, 0x84, 0x7, 0x23, 0x2, 0x2, 0x83, 0x82, 0x3, 0x2, 0x2, 0x2, 
    0x83, 0x84, 0x3, 0x2, 0x2, 0x2, 0x84, 0x85, 0x3, 0x2, 0x2, 0x2, 0x85, 
    0x86, 0x5, 0x44, 0x23, 0x2, 0x86, 0x87, 0x7, 0x35, 0x2, 0x2, 0x87, 0x89, 
    0x7, 0x6, 0x2, 0x2, 0x88, 0x8a, 0x5, 0x12, 0xa, 0x2, 0x89, 0x88, 0x3, 
    0x2, 0x2, 0x2, 0x89, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x8b, 0x3, 0x2, 
    0x2, 0x2, 0x8b, 0x8c, 0x7, 0x7, 0x2, 0x2, 0x8c, 0x11, 0x3, 0x2, 0x2, 
    0x2, 0x8d, 0x92, 0x5, 0x14, 0xb, 0x2, 0x8e, 0x8f, 0x7, 0x3, 0x2, 0x2, 
    0x8f, 0x91, 0x5, 0x14, 0xb, 0x2, 0x90, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x91, 
    0x94, 0x3, 0x2, 0x2, 0x2, 0x92, 0x90, 0x3, 0x2, 0x2, 0x2, 0x92, 0x93, 
    0x3, 0x2, 0x2, 0x2, 0x93, 0x13, 0x3, 0x2, 0x2, 0x2, 0x94, 0x92, 0x3, 
    0x2, 0x2, 0x2, 0x95, 0x97, 0x5, 0x44, 0x23, 0x2, 0x96, 0x98, 0x7, 0x35, 
    0x2, 0x2, 0x97, 0x96, 0x3, 0x2, 0x2, 0x2, 0x97, 0x98, 0x3, 0x2, 0x2, 
    0x2, 0x98, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x99, 0x9b, 0x5, 0x16, 0xc, 0x2, 
    0x9a, 0x99, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x9b, 
    0x15, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9d, 0x7, 0x8, 0x2, 0x2, 0x9d, 0x9e, 
    0x5, 0x18, 0xd, 0x2, 0x9e, 0x9f, 0x7, 0x9, 0x2, 0x2, 0x9f, 0xa1, 0x3, 
    0x2, 0x2, 0x2, 0xa0, 0x9c, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa2, 0x3, 0x2, 
    0x2, 0x2, 0xa2, 0xa0, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa3, 0x3, 0x2, 0x2, 
    0x2, 0xa3, 0x17, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa7, 0x3, 0x2, 0x2, 0x2, 
    0xa5, 0xa7, 0x5, 0x42, 0x22, 0x2, 0xa6, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xa6, 
    0xa5, 0x3, 0x2, 0x2, 0x2, 0xa7, 0x19, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xb9, 
    0x5, 0x1c, 0xf, 0x2, 0xa9, 0xb9, 0x5, 0x1e, 0x10, 0x2, 0xaa, 0xb9, 0x7, 
    0x4, 0x2, 0x2, 0xab, 0xb9, 0x5, 0x20, 0x11, 0x2, 0xac, 0xb9, 0x5, 0x22, 
    0x12, 0x2, 0xad, 0xb9, 0x5, 0x26, 0x14, 0x2, 0xae, 0xb0, 0x7, 0x2a, 
    0x2, 0x2, 0xaf, 0xb1, 0x5, 0x40, 0x21, 0x2, 0xb0, 0xaf, 0x3, 0x2, 0x2, 
    0x2, 0xb0, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xb2, 0x3, 0x2, 0x2, 0x2, 
    0xb2, 0xb9, 0x7, 0x4, 0x2, 0x2, 0xb3, 0xb4, 0x7, 0x28, 0x2, 0x2, 0xb4, 
    0xb9, 0x7, 0x4, 0x2, 0x2, 0xb5, 0xb6, 0x7, 0x29, 0x2, 0x2, 0xb6, 0xb9, 
    0x7, 0x4, 0x2, 0x2, 0xb7, 0xb9, 0x5, 0x6, 0x4, 0x2, 0xb8, 0xa8, 0x3, 
    0x2, 0x2, 0x2, 0xb8, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xaa, 0x3, 0x2, 
    0x2, 0x2, 0xb8, 0xab, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xac, 0x3, 0x2, 0x2, 
    0x2, 0xb8, 0xad, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xae, 0x3, 0x2, 0x2, 0x2, 
    0xb8, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb8, 
    0xb7, 0x3, 0x2, 0x2, 0x2, 0xb9, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbe, 
    0x7, 0xa, 0x2, 0x2, 0xbb, 0xbd, 0x5, 0x1a, 0xe, 0x2, 0xbc, 0xbb, 0x3, 
    0x2, 0x2, 0x2, 0xbd, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xbc, 0x3, 0x2, 
    0x2, 0x2, 0xbe, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xc1, 0x3, 0x2, 0x2, 
    0x2, 0xc0, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xc2, 0x7, 0xb, 0x2, 0x2, 
    0xc2, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xc5, 0x5, 0x40, 0x21, 0x2, 0xc4, 
    0xc3, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc5, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc6, 
    0x3, 0x2, 0x2, 0x2, 0xc6, 0xc7, 0x7, 0x4, 0x2, 0x2, 0xc7, 0x1f, 0x3, 
    0x2, 0x2, 0x2, 0xc8, 0xc9, 0x7, 0x24, 0x2, 0x2, 0xc9, 0xca, 0x7, 0x6, 
    0x2, 0x2, 0xca, 0xcb, 0x5, 0x40, 0x21, 0x2, 0xcb, 0xcc, 0x7, 0x7, 0x2, 
    0x2, 0xcc, 0xcd, 0x5, 0x1a, 0xe, 0x2, 0xcd, 0xd7, 0x3, 0x2, 0x2, 0x2, 
    0xce, 0xcf, 0x7, 0x24, 0x2, 0x2, 0xcf, 0xd0, 0x7, 0x6, 0x2, 0x2, 0xd0, 
    0xd1, 0x5, 0x40, 0x21, 0x2, 0xd1, 0xd2, 0x7, 0x7, 0x2, 0x2, 0xd2, 0xd3, 
    0x5, 0x1a, 0xe, 0x2, 0xd3, 0xd4, 0x7, 0x25, 0x2, 0x2, 0xd4, 0xd5, 0x5, 
    0x1a, 0xe, 0x2, 0xd5, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xc8, 0x3, 0x2, 
    0x2, 0x2, 0xd6, 0xce, 0x3, 0x2, 0x2, 0x2, 0xd7, 0x21, 0x3, 0x2, 0x2, 
    0x2, 0xd8, 0xd9, 0x7, 0x26, 0x2, 0x2, 0xd9, 0xda, 0x7, 0x6, 0x2, 0x2, 
    0xda, 0xdb, 0x5, 0x24, 0x13, 0x2, 0xdb, 0xdd, 0x5, 0x1e, 0x10, 0x2, 
    0xdc, 0xde, 0x5, 0x40, 0x21, 0x2, 0xdd, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xdd, 
    0xde, 0x3, 0x2, 0x2, 0x2, 0xde, 0xdf, 0x3, 0x2, 0x2, 0x2, 0xdf, 0xe0, 
    0x7, 0x7, 0x2, 0x2, 0xe0, 0xe1, 0x5, 0x1a, 0xe, 0x2, 0xe1, 0x23, 0x3, 
    0x2, 0x2, 0x2, 0xe2, 0xe5, 0x5, 0x1e, 0x10, 0x2, 0xe3, 0xe5, 0x5, 0x6, 
    0x4, 0x2, 0xe4, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe3, 0x3, 0x2, 0x2, 
    0x2, 0xe5, 0x25, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xe7, 0x7, 0x27, 0x2, 0x2, 
    0xe7, 0xe8, 0x7, 0x6, 0x2, 0x2, 0xe8, 0xe9, 0x5, 0x40, 0x21, 0x2, 0xe9, 
    0xea, 0x7, 0x7, 0x2, 0x2, 0xea, 0xeb, 0x5, 0x1a, 0xe, 0x2, 0xeb, 0x27, 
    0x3, 0x2, 0x2, 0x2, 0xec, 0xed, 0x7, 0x35, 0x2, 0x2, 0xed, 0x29, 0x3, 
    0x2, 0x2, 0x2, 0xee, 0xf5, 0x5, 0x28, 0x15, 0x2, 0xef, 0xf5, 0x5, 0x4a, 
    0x26, 0x2, 0xf0, 0xf1, 0x7, 0x6, 0x2, 0x2, 0xf1, 0xf2, 0x5, 0x40, 0x21, 
    0x2, 0xf2, 0xf3, 0x7, 0x7, 0x2, 0x2, 0xf3, 0xf5, 0x3, 0x2, 0x2, 0x2, 
    0xf4, 0xee, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xef, 0x3, 0x2, 0x2, 0x2, 0xf4, 
    0xf0, 0x3, 0x2, 0x2, 0x2, 0xf5, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf7, 
    0x8, 0x17, 0x1, 0x2, 0xf7, 0x101, 0x5, 0x2a, 0x16, 0x2, 0xf8, 0xf9, 
    0x7, 0x32, 0x2, 0x2, 0xf9, 0xfa, 0x7, 0xc, 0x2, 0x2, 0xfa, 0xfb, 0x5, 
    0x44, 0x23, 0x2, 0xfb, 0xfc, 0x7, 0xd, 0x2, 0x2, 0xfc, 0xfd, 0x7, 0x6, 
    0x2, 0x2, 0xfd, 0xfe, 0x5, 0x40, 0x21, 0x2, 0xfe, 0xff, 0x7, 0x7, 0x2, 
    0x2, 0xff, 0x101, 0x3, 0x2, 0x2, 0x2, 0x100, 0xf6, 0x3, 0x2, 0x2, 0x2, 
    0x100, 0xf8, 0x3, 0x2, 0x2, 0x2, 0x101, 0x111, 0x3, 0x2, 0x2, 0x2, 0x102, 
    0x103, 0xc, 0x6, 0x2, 0x2, 0x103, 0x104, 0x7, 0x8, 0x2, 0x2, 0x104, 
    0x105, 0x5, 0x40, 0x21, 0x2, 0x105, 0x106, 0x7, 0x9, 0x2, 0x2, 0x106, 
    0x110, 0x3, 0x2, 0x2, 0x2, 0x107, 0x108, 0xc, 0x5, 0x2, 0x2, 0x108, 
    0x10a, 0x7, 0x6, 0x2, 0x2, 0x109, 0x10b, 0x5, 0x40, 0x21, 0x2, 0x10a, 
    0x109, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x10b, 
    0x10c, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x110, 0x7, 0x7, 0x2, 0x2, 0x10d, 
    0x10e, 0xc, 0x3, 0x2, 0x2, 0x10e, 0x110, 0x9, 0x2, 0x2, 0x2, 0x10f, 
    0x102, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x107, 0x3, 0x2, 0x2, 0x2, 0x10f, 
    0x10d, 0x3, 0x2, 0x2, 0x2, 0x110, 0x113, 0x3, 0x2, 0x2, 0x2, 0x111, 
    0x10f, 0x3, 0x2, 0x2, 0x2, 0x111, 0x112, 0x3, 0x2, 0x2, 0x2, 0x112, 
    0x2d, 0x3, 0x2, 0x2, 0x2, 0x113, 0x111, 0x3, 0x2, 0x2, 0x2, 0x114, 0x118, 
    0x5, 0x2c, 0x17, 0x2, 0x115, 0x116, 0x9, 0x3, 0x2, 0x2, 0x116, 0x118, 
    0x5, 0x2e, 0x18, 0x2, 0x117, 0x114, 0x3, 0x2, 0x2, 0x2, 0x117, 0x115, 
    0x3, 0x2, 0x2, 0x2, 0x118, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x119, 0x11a, 0x8, 
    0x19, 0x1, 0x2, 0x11a, 0x11b, 0x5, 0x2e, 0x18, 0x2, 0x11b, 0x121, 0x3, 
    0x2, 0x2, 0x2, 0x11c, 0x11d, 0xc, 0x3, 0x2, 0x2, 0x11d, 0x11e, 0x9, 
    0x4, 0x2, 0x2, 0x11e, 0x120, 0x5, 0x2e, 0x18, 0x2, 0x11f, 0x11c, 0x3, 
    0x2, 0x2, 0x2, 0x120, 0x123, 0x3, 0x2, 0x2, 0x2, 0x121, 0x11f, 0x3, 
    0x2, 0x2, 0x2, 0x121, 0x122, 0x3, 0x2, 0x2, 0x2, 0x122, 0x31, 0x3, 0x2, 
    0x2, 0x2, 0x123, 0x121, 0x3, 0x2, 0x2, 0x2, 0x124, 0x125, 0x8, 0x1a, 
    0x1, 0x2, 0x125, 0x126, 0x5, 0x30, 0x19, 0x2, 0x126, 0x12c, 0x3, 0x2, 
    0x2, 0x2, 0x127, 0x128, 0xc, 0x3, 0x2, 0x2, 0x128, 0x129, 0x9, 0x5, 
    0x2, 0x2, 0x129, 0x12b, 0x5, 0x30, 0x19, 0x2, 0x12a, 0x127, 0x3, 0x2, 
    0x2, 0x2, 0x12b, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x12c, 0x12a, 0x3, 0x2, 
    0x2, 0x2, 0x12c, 0x12d, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x33, 0x3, 0x2, 0x2, 
    0x2, 0x12e, 0x12c, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x130, 0x8, 0x1b, 0x1, 
    0x2, 0x130, 0x131, 0x5, 0x32, 0x1a, 0x2, 0x131, 0x137, 0x3, 0x2, 0x2, 
    0x2, 0x132, 0x133, 0xc, 0x3, 0x2, 0x2, 0x133, 0x134, 0x9, 0x6, 0x2, 
    0x2, 0x134, 0x136, 0x5, 0x32, 0x1a, 0x2, 0x135, 0x132, 0x3, 0x2, 0x2, 
    0x2, 0x136, 0x139, 0x3, 0x2, 0x2, 0x2, 0x137, 0x135, 0x3, 0x2, 0x2, 
    0x2, 0x137, 0x138, 0x3, 0x2, 0x2, 0x2, 0x138, 0x35, 0x3, 0x2, 0x2, 0x2, 
    0x139, 0x137, 0x3, 0x2, 0x2, 0x2, 0x13a, 0x13b, 0x8, 0x1c, 0x1, 0x2, 
    0x13b, 0x13c, 0x5, 0x34, 0x1b, 0x2, 0x13c, 0x142, 0x3, 0x2, 0x2, 0x2, 
    0x13d, 0x13e, 0xc, 0x3, 0x2, 0x2, 0x13e, 0x13f, 0x9, 0x7, 0x2, 0x2, 
    0x13f, 0x141, 0x5, 0x34, 0x1b, 0x2, 0x140, 0x13d, 0x3, 0x2, 0x2, 0x2, 
    0x141, 0x144, 0x3, 0x2, 0x2, 0x2, 0x142, 0x140, 0x3, 0x2, 0x2, 0x2, 
    0x142, 0x143, 0x3, 0x2, 0x2, 0x2, 0x143, 0x37, 0x3, 0x2, 0x2, 0x2, 0x144, 
    0x142, 0x3, 0x2, 0x2, 0x2, 0x145, 0x146, 0x8, 0x1d, 0x1, 0x2, 0x146, 
    0x147, 0x5, 0x36, 0x1c, 0x2, 0x147, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x148, 
    0x149, 0xc, 0x3, 0x2, 0x2, 0x149, 0x14a, 0x7, 0x1a, 0x2, 0x2, 0x14a, 
    0x14c, 0x5, 0x36, 0x1c, 0x2, 0x14b, 0x148, 0x3, 0x2, 0x2, 0x2, 0x14c, 
    0x14f, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x14b, 0x3, 0x2, 0x2, 0x2, 0x14d, 
    0x14e, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x39, 0x3, 0x2, 0x2, 0x2, 0x14f, 0x14d, 
    0x3, 0x2, 0x2, 0x2, 0x150, 0x151, 0x8, 0x1e, 0x1, 0x2, 0x151, 0x152, 
    0x5, 0x38, 0x1d, 0x2, 0x152, 0x158, 0x3, 0x2, 0x2, 0x2, 0x153, 0x154, 
    0xc, 0x3, 0x2, 0x2, 0x154, 0x155, 0x7, 0x1b, 0x2, 0x2, 0x155, 0x157, 
    0x5, 0x38, 0x1d, 0x2, 0x156, 0x153, 0x3, 0x2, 0x2, 0x2, 0x157, 0x15a, 
    0x3, 0x2, 0x2, 0x2, 0x158, 0x156, 0x3, 0x2, 0x2, 0x2, 0x158, 0x159, 
    0x3, 0x2, 0x2, 0x2, 0x159, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x15a, 0x158, 0x3, 
    0x2, 0x2, 0x2, 0x15b, 0x163, 0x5, 0x3a, 0x1e, 0x2, 0x15c, 0x15d, 0x5, 
    0x3a, 0x1e, 0x2, 0x15d, 0x15e, 0x7, 0x1c, 0x2, 0x2, 0x15e, 0x15f, 0x5, 
    0x40, 0x21, 0x2, 0x15f, 0x160, 0x7, 0x1d, 0x2, 0x2, 0x160, 0x161, 0x5, 
    0x3c, 0x1f, 0x2, 0x161, 0x163, 0x3, 0x2, 0x2, 0x2, 0x162, 0x15b, 0x3, 
    0x2, 0x2, 0x2, 0x162, 0x15c, 0x3, 0x2, 0x2, 0x2, 0x163, 0x3d, 0x3, 0x2, 
    0x2, 0x2, 0x164, 0x16a, 0x5, 0x3c, 0x1f, 0x2, 0x165, 0x166, 0x5, 0x2e, 
    0x18, 0x2, 0x166, 0x167, 0x9, 0x8, 0x2, 0x2, 0x167, 0x168, 0x5, 0x3e, 
    0x20, 0x2, 0x168, 0x16a, 0x3, 0x2, 0x2, 0x2, 0x169, 0x164, 0x3, 0x2, 
    0x2, 0x2, 0x169, 0x165, 0x3, 0x2, 0x2, 0x2, 0x16a, 0x3f, 0x3, 0x2, 0x2, 
    0x2, 0x16b, 0x175, 0x5, 0x3e, 0x20, 0x2, 0x16c, 0x171, 0x5, 0x3e, 0x20, 
    0x2, 0x16d, 0x16e, 0x7, 0x3, 0x2, 0x2, 0x16e, 0x170, 0x5, 0x3e, 0x20, 
    0x2, 0x16f, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x170, 0x173, 0x3, 0x2, 0x2, 
    0x2, 0x171, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x171, 0x172, 0x3, 0x2, 0x2, 
    0x2, 0x172, 0x175, 0x3, 0x2, 0x2, 0x2, 0x173, 0x171, 0x3, 0x2, 0x2, 
    0x2, 0x174, 0x16b, 0x3, 0x2, 0x2, 0x2, 0x174, 0x16c, 0x3, 0x2, 0x2, 
    0x2, 0x175, 0x41, 0x3, 0x2, 0x2, 0x2, 0x176, 0x177, 0x5, 0x3c, 0x1f, 
    0x2, 0x177, 0x43, 0x3, 0x2, 0x2, 0x2, 0x178, 0x17a, 0x5, 0x46, 0x24, 
    0x2, 0x179, 0x178, 0x3, 0x2, 0x2, 0x2, 0x179, 0x17a, 0x3, 0x2, 0x2, 
    0x2, 0x17a, 0x17b, 0x3, 0x2, 0x2, 0x2, 0x17b, 0x17c, 0x5, 0x48, 0x25, 
    0x2, 0x17c, 0x45, 0x3, 0x2, 0x2, 0x2, 0x17d, 0x17e, 0x9, 0x9, 0x2, 0x2, 
    0x17e, 0x47, 0x3, 0x2, 0x2, 0x2, 0x17f, 0x180, 0x9, 0xa, 0x2, 0x2, 0x180, 
    0x49, 0x3, 0x2, 0x2, 0x2, 0x181, 0x188, 0x5, 0x4c, 0x27, 0x2, 0x182, 
    0x188, 0x5, 0x4e, 0x28, 0x2, 0x183, 0x188, 0x5, 0x50, 0x29, 0x2, 0x184, 
    0x188, 0x5, 0x52, 0x2a, 0x2, 0x185, 0x188, 0x5, 0x54, 0x2b, 0x2, 0x186, 
    0x188, 0x5, 0x56, 0x2c, 0x2, 0x187, 0x181, 0x3, 0x2, 0x2, 0x2, 0x187, 
    0x182, 0x3, 0x2, 0x2, 0x2, 0x187, 0x183, 0x3, 0x2, 0x2, 0x2, 0x187, 
    0x184, 0x3, 0x2, 0x2, 0x2, 0x187, 0x185, 0x3, 0x2, 0x2, 0x2, 0x187, 
    0x186, 0x3, 0x2, 0x2, 0x2, 0x188, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x189, 0x18a, 
    0x9, 0xb, 0x2, 0x2, 0x18a, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x18b, 0x18c, 0x7, 
    0x3a, 0x2, 0x2, 0x18c, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x18d, 0x18e, 0x7, 
    0x39, 0x2, 0x2, 0x18e, 0x51, 0x3, 0x2, 0x2, 0x2, 0x18f, 0x190, 0x7, 
    0x38, 0x2, 0x2, 0x190, 0x53, 0x3, 0x2, 0x2, 0x2, 0x191, 0x193, 0x7, 
    0x3b, 0x2, 0x2, 0x192, 0x191, 0x3, 0x2, 0x2, 0x2, 0x193, 0x194, 0x3, 
    0x2, 0x2, 0x2, 0x194, 0x192, 0x3, 0x2, 0x2, 0x2, 0x194, 0x195, 0x3, 
    0x2, 0x2, 0x2, 0x195, 0x55, 0x3, 0x2, 0x2, 0x2, 0x196, 0x197, 0x7, 0xa, 
    0x2, 0x2, 0x197, 0x198, 0x5, 0x58, 0x2d, 0x2, 0x198, 0x199, 0x7, 0xb, 
    0x2, 0x2, 0x199, 0x57, 0x3, 0x2, 0x2, 0x2, 0x19a, 0x19f, 0x5, 0x4a, 
    0x26, 0x2, 0x19b, 0x19c, 0x7, 0x3, 0x2, 0x2, 0x19c, 0x19e, 0x5, 0x4a, 
    0x26, 0x2, 0x19d, 0x19b, 0x3, 0x2, 0x2, 0x2, 0x19e, 0x1a1, 0x3, 0x2, 
    0x2, 0x2, 0x19f, 0x19d, 0x3, 0x2, 0x2, 0x2, 0x19f, 0x1a0, 0x3, 0x2, 
    0x2, 0x2, 0x1a0, 0x59, 0x3, 0x2, 0x2, 0x2, 0x1a1, 0x19f, 0x3, 0x2, 0x2, 
    0x2, 0x29, 0x5d, 0x65, 0x6d, 0x74, 0x77, 0x83, 0x89, 0x92, 0x97, 0x9a, 
    0xa2, 0xa6, 0xb0, 0xb8, 0xbe, 0xc4, 0xd6, 0xdd, 0xe4, 0xf4, 0x100, 0x10a, 
    0x10f, 0x111, 0x117, 0x121, 0x12c, 0x137, 0x142, 0x14d, 0x158, 0x162, 
    0x169, 0x171, 0x174, 0x179, 0x187, 0x194, 0x19f, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

ExprParser::Initializer ExprParser::_init;
