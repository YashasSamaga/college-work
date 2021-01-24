// Generated from Expr.g4 by ANTLR 4.8
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link ExprParser}.
 */
public interface ExprListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link ExprParser#translationUnit}.
	 * @param ctx the parse tree
	 */
	void enterTranslationUnit(ExprParser.TranslationUnitContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#translationUnit}.
	 * @param ctx the parse tree
	 */
	void exitTranslationUnit(ExprParser.TranslationUnitContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#declaration}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration(ExprParser.DeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#declaration}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration(ExprParser.DeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#variableDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterVariableDeclaration(ExprParser.VariableDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#variableDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitVariableDeclaration(ExprParser.VariableDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#initDeclarator}.
	 * @param ctx the parse tree
	 */
	void enterInitDeclarator(ExprParser.InitDeclaratorContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#initDeclarator}.
	 * @param ctx the parse tree
	 */
	void exitInitDeclarator(ExprParser.InitDeclaratorContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#initializer}.
	 * @param ctx the parse tree
	 */
	void enterInitializer(ExprParser.InitializerContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#initializer}.
	 * @param ctx the parse tree
	 */
	void exitInitializer(ExprParser.InitializerContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#functionDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterFunctionDeclaration(ExprParser.FunctionDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#functionDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitFunctionDeclaration(ExprParser.FunctionDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#functionDefinition}.
	 * @param ctx the parse tree
	 */
	void enterFunctionDefinition(ExprParser.FunctionDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#functionDefinition}.
	 * @param ctx the parse tree
	 */
	void exitFunctionDefinition(ExprParser.FunctionDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#functionPrototype}.
	 * @param ctx the parse tree
	 */
	void enterFunctionPrototype(ExprParser.FunctionPrototypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#functionPrototype}.
	 * @param ctx the parse tree
	 */
	void exitFunctionPrototype(ExprParser.FunctionPrototypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#formalParameterList}.
	 * @param ctx the parse tree
	 */
	void enterFormalParameterList(ExprParser.FormalParameterListContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#formalParameterList}.
	 * @param ctx the parse tree
	 */
	void exitFormalParameterList(ExprParser.FormalParameterListContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#formalParameter}.
	 * @param ctx the parse tree
	 */
	void enterFormalParameter(ExprParser.FormalParameterContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#formalParameter}.
	 * @param ctx the parse tree
	 */
	void exitFormalParameter(ExprParser.FormalParameterContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#arrayDimensionList}.
	 * @param ctx the parse tree
	 */
	void enterArrayDimensionList(ExprParser.ArrayDimensionListContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#arrayDimensionList}.
	 * @param ctx the parse tree
	 */
	void exitArrayDimensionList(ExprParser.ArrayDimensionListContext ctx);
	/**
	 * Enter a parse tree produced by the {@code compoundStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterCompoundStatementStat(ExprParser.CompoundStatementStatContext ctx);
	/**
	 * Exit a parse tree produced by the {@code compoundStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitCompoundStatementStat(ExprParser.CompoundStatementStatContext ctx);
	/**
	 * Enter a parse tree produced by the {@code exprStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterExprStatementStat(ExprParser.ExprStatementStatContext ctx);
	/**
	 * Exit a parse tree produced by the {@code exprStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitExprStatementStat(ExprParser.ExprStatementStatContext ctx);
	/**
	 * Enter a parse tree produced by the {@code emptyStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterEmptyStatementStat(ExprParser.EmptyStatementStatContext ctx);
	/**
	 * Exit a parse tree produced by the {@code emptyStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitEmptyStatementStat(ExprParser.EmptyStatementStatContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ifStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterIfStatementStat(ExprParser.IfStatementStatContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ifStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitIfStatementStat(ExprParser.IfStatementStatContext ctx);
	/**
	 * Enter a parse tree produced by the {@code forStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterForStatementStat(ExprParser.ForStatementStatContext ctx);
	/**
	 * Exit a parse tree produced by the {@code forStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitForStatementStat(ExprParser.ForStatementStatContext ctx);
	/**
	 * Enter a parse tree produced by the {@code whileStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterWhileStatementStat(ExprParser.WhileStatementStatContext ctx);
	/**
	 * Exit a parse tree produced by the {@code whileStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitWhileStatementStat(ExprParser.WhileStatementStatContext ctx);
	/**
	 * Enter a parse tree produced by the {@code returnStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterReturnStatementStat(ExprParser.ReturnStatementStatContext ctx);
	/**
	 * Exit a parse tree produced by the {@code returnStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitReturnStatementStat(ExprParser.ReturnStatementStatContext ctx);
	/**
	 * Enter a parse tree produced by the {@code continueStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterContinueStatementStat(ExprParser.ContinueStatementStatContext ctx);
	/**
	 * Exit a parse tree produced by the {@code continueStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitContinueStatementStat(ExprParser.ContinueStatementStatContext ctx);
	/**
	 * Enter a parse tree produced by the {@code breakStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterBreakStatementStat(ExprParser.BreakStatementStatContext ctx);
	/**
	 * Exit a parse tree produced by the {@code breakStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitBreakStatementStat(ExprParser.BreakStatementStatContext ctx);
	/**
	 * Enter a parse tree produced by the {@code varDeclarationStatement}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterVarDeclarationStatement(ExprParser.VarDeclarationStatementContext ctx);
	/**
	 * Exit a parse tree produced by the {@code varDeclarationStatement}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitVarDeclarationStatement(ExprParser.VarDeclarationStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#compoundStatement}.
	 * @param ctx the parse tree
	 */
	void enterCompoundStatement(ExprParser.CompoundStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#compoundStatement}.
	 * @param ctx the parse tree
	 */
	void exitCompoundStatement(ExprParser.CompoundStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#expressionStatement}.
	 * @param ctx the parse tree
	 */
	void enterExpressionStatement(ExprParser.ExpressionStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#expressionStatement}.
	 * @param ctx the parse tree
	 */
	void exitExpressionStatement(ExprParser.ExpressionStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void enterIfStatement(ExprParser.IfStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void exitIfStatement(ExprParser.IfStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#forStatement}.
	 * @param ctx the parse tree
	 */
	void enterForStatement(ExprParser.ForStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#forStatement}.
	 * @param ctx the parse tree
	 */
	void exitForStatement(ExprParser.ForStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#forDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterForDeclaration(ExprParser.ForDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#forDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitForDeclaration(ExprParser.ForDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void enterWhileStatement(ExprParser.WhileStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void exitWhileStatement(ExprParser.WhileStatementContext ctx);
	/**
	 * Enter a parse tree produced by the {@code identPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterIdentPrimaryExpr(ExprParser.IdentPrimaryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code identPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitIdentPrimaryExpr(ExprParser.IdentPrimaryExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code boolLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterBoolLiteralPrimaryExpr(ExprParser.BoolLiteralPrimaryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code boolLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitBoolLiteralPrimaryExpr(ExprParser.BoolLiteralPrimaryExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code arrayLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterArrayLiteralPrimaryExpr(ExprParser.ArrayLiteralPrimaryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code arrayLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitArrayLiteralPrimaryExpr(ExprParser.ArrayLiteralPrimaryExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code charLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterCharLiteralPrimaryExpr(ExprParser.CharLiteralPrimaryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code charLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitCharLiteralPrimaryExpr(ExprParser.CharLiteralPrimaryExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code integerLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterIntegerLiteralPrimaryExpr(ExprParser.IntegerLiteralPrimaryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code integerLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitIntegerLiteralPrimaryExpr(ExprParser.IntegerLiteralPrimaryExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code floatLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterFloatLiteralPrimaryExpr(ExprParser.FloatLiteralPrimaryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code floatLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitFloatLiteralPrimaryExpr(ExprParser.FloatLiteralPrimaryExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code stringLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterStringLiteralPrimaryExpr(ExprParser.StringLiteralPrimaryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code stringLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitStringLiteralPrimaryExpr(ExprParser.StringLiteralPrimaryExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code exprParenthesisPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterExprParenthesisPrimaryExpr(ExprParser.ExprParenthesisPrimaryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code exprParenthesisPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitExprParenthesisPrimaryExpr(ExprParser.ExprParenthesisPrimaryExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#idExpression}.
	 * @param ctx the parse tree
	 */
	void enterIdExpression(ExprParser.IdExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#idExpression}.
	 * @param ctx the parse tree
	 */
	void exitIdExpression(ExprParser.IdExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code funcCallPostfixExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void enterFuncCallPostfixExpr(ExprParser.FuncCallPostfixExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code funcCallPostfixExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void exitFuncCallPostfixExpr(ExprParser.FuncCallPostfixExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code postfixIncDecExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void enterPostfixIncDecExpr(ExprParser.PostfixIncDecExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code postfixIncDecExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void exitPostfixIncDecExpr(ExprParser.PostfixIncDecExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code unaryPostfixExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void enterUnaryPostfixExpr(ExprParser.UnaryPostfixExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code unaryPostfixExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void exitUnaryPostfixExpr(ExprParser.UnaryPostfixExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code arrayIndexingPostfixExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void enterArrayIndexingPostfixExpr(ExprParser.ArrayIndexingPostfixExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code arrayIndexingPostfixExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void exitArrayIndexingPostfixExpr(ExprParser.ArrayIndexingPostfixExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code primaryExprPostfixExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void enterPrimaryExprPostfixExpr(ExprParser.PrimaryExprPostfixExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code primaryExprPostfixExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void exitPrimaryExprPostfixExpr(ExprParser.PrimaryExprPostfixExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#argumentExpressionList}.
	 * @param ctx the parse tree
	 */
	void enterArgumentExpressionList(ExprParser.ArgumentExpressionListContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#argumentExpressionList}.
	 * @param ctx the parse tree
	 */
	void exitArgumentExpressionList(ExprParser.ArgumentExpressionListContext ctx);
	/**
	 * Enter a parse tree produced by the {@code postfixExprUnaryExpr}
	 * labeled alternative in {@link ExprParser#prefixExpression}.
	 * @param ctx the parse tree
	 */
	void enterPostfixExprUnaryExpr(ExprParser.PostfixExprUnaryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code postfixExprUnaryExpr}
	 * labeled alternative in {@link ExprParser#prefixExpression}.
	 * @param ctx the parse tree
	 */
	void exitPostfixExprUnaryExpr(ExprParser.PostfixExprUnaryExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code unaryOperatorExpr}
	 * labeled alternative in {@link ExprParser#prefixExpression}.
	 * @param ctx the parse tree
	 */
	void enterUnaryOperatorExpr(ExprParser.UnaryOperatorExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code unaryOperatorExpr}
	 * labeled alternative in {@link ExprParser#prefixExpression}.
	 * @param ctx the parse tree
	 */
	void exitUnaryOperatorExpr(ExprParser.UnaryOperatorExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code castExprMultiplicativeExpr}
	 * labeled alternative in {@link ExprParser#multiplicativeExpression}.
	 * @param ctx the parse tree
	 */
	void enterCastExprMultiplicativeExpr(ExprParser.CastExprMultiplicativeExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code castExprMultiplicativeExpr}
	 * labeled alternative in {@link ExprParser#multiplicativeExpression}.
	 * @param ctx the parse tree
	 */
	void exitCastExprMultiplicativeExpr(ExprParser.CastExprMultiplicativeExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code mulDivModExprMultiplicativeExpr}
	 * labeled alternative in {@link ExprParser#multiplicativeExpression}.
	 * @param ctx the parse tree
	 */
	void enterMulDivModExprMultiplicativeExpr(ExprParser.MulDivModExprMultiplicativeExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code mulDivModExprMultiplicativeExpr}
	 * labeled alternative in {@link ExprParser#multiplicativeExpression}.
	 * @param ctx the parse tree
	 */
	void exitMulDivModExprMultiplicativeExpr(ExprParser.MulDivModExprMultiplicativeExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code addSubExprAdditiveExpr}
	 * labeled alternative in {@link ExprParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void enterAddSubExprAdditiveExpr(ExprParser.AddSubExprAdditiveExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code addSubExprAdditiveExpr}
	 * labeled alternative in {@link ExprParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void exitAddSubExprAdditiveExpr(ExprParser.AddSubExprAdditiveExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code mulExprAdditiveExpr}
	 * labeled alternative in {@link ExprParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void enterMulExprAdditiveExpr(ExprParser.MulExprAdditiveExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code mulExprAdditiveExpr}
	 * labeled alternative in {@link ExprParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void exitMulExprAdditiveExpr(ExprParser.MulExprAdditiveExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code relExprRelationalExpr}
	 * labeled alternative in {@link ExprParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void enterRelExprRelationalExpr(ExprParser.RelExprRelationalExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code relExprRelationalExpr}
	 * labeled alternative in {@link ExprParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void exitRelExprRelationalExpr(ExprParser.RelExprRelationalExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code additiveExprRelationalExpr}
	 * labeled alternative in {@link ExprParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void enterAdditiveExprRelationalExpr(ExprParser.AdditiveExprRelationalExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code additiveExprRelationalExpr}
	 * labeled alternative in {@link ExprParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void exitAdditiveExprRelationalExpr(ExprParser.AdditiveExprRelationalExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code relationalExprEqualityExor}
	 * labeled alternative in {@link ExprParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void enterRelationalExprEqualityExor(ExprParser.RelationalExprEqualityExorContext ctx);
	/**
	 * Exit a parse tree produced by the {@code relationalExprEqualityExor}
	 * labeled alternative in {@link ExprParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void exitRelationalExprEqualityExor(ExprParser.RelationalExprEqualityExorContext ctx);
	/**
	 * Enter a parse tree produced by the {@code equalityExprEqualityExpr}
	 * labeled alternative in {@link ExprParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void enterEqualityExprEqualityExpr(ExprParser.EqualityExprEqualityExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code equalityExprEqualityExpr}
	 * labeled alternative in {@link ExprParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void exitEqualityExprEqualityExpr(ExprParser.EqualityExprEqualityExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code logicalAndExprLogicalAndExpr}
	 * labeled alternative in {@link ExprParser#logicalAndExpression}.
	 * @param ctx the parse tree
	 */
	void enterLogicalAndExprLogicalAndExpr(ExprParser.LogicalAndExprLogicalAndExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code logicalAndExprLogicalAndExpr}
	 * labeled alternative in {@link ExprParser#logicalAndExpression}.
	 * @param ctx the parse tree
	 */
	void exitLogicalAndExprLogicalAndExpr(ExprParser.LogicalAndExprLogicalAndExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code equalityExprLogicalAndExpr}
	 * labeled alternative in {@link ExprParser#logicalAndExpression}.
	 * @param ctx the parse tree
	 */
	void enterEqualityExprLogicalAndExpr(ExprParser.EqualityExprLogicalAndExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code equalityExprLogicalAndExpr}
	 * labeled alternative in {@link ExprParser#logicalAndExpression}.
	 * @param ctx the parse tree
	 */
	void exitEqualityExprLogicalAndExpr(ExprParser.EqualityExprLogicalAndExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code logicalOrExprLogicalOrExpr}
	 * labeled alternative in {@link ExprParser#logicalOrExpression}.
	 * @param ctx the parse tree
	 */
	void enterLogicalOrExprLogicalOrExpr(ExprParser.LogicalOrExprLogicalOrExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code logicalOrExprLogicalOrExpr}
	 * labeled alternative in {@link ExprParser#logicalOrExpression}.
	 * @param ctx the parse tree
	 */
	void exitLogicalOrExprLogicalOrExpr(ExprParser.LogicalOrExprLogicalOrExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code logicalAndExprLogicalOrExpr}
	 * labeled alternative in {@link ExprParser#logicalOrExpression}.
	 * @param ctx the parse tree
	 */
	void enterLogicalAndExprLogicalOrExpr(ExprParser.LogicalAndExprLogicalOrExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code logicalAndExprLogicalOrExpr}
	 * labeled alternative in {@link ExprParser#logicalOrExpression}.
	 * @param ctx the parse tree
	 */
	void exitLogicalAndExprLogicalOrExpr(ExprParser.LogicalAndExprLogicalOrExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#conditionalExpression}.
	 * @param ctx the parse tree
	 */
	void enterConditionalExpression(ExprParser.ConditionalExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#conditionalExpression}.
	 * @param ctx the parse tree
	 */
	void exitConditionalExpression(ExprParser.ConditionalExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code conditionalExpressionAssignmentExpr}
	 * labeled alternative in {@link ExprParser#assignmentExpression}.
	 * @param ctx the parse tree
	 */
	void enterConditionalExpressionAssignmentExpr(ExprParser.ConditionalExpressionAssignmentExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code conditionalExpressionAssignmentExpr}
	 * labeled alternative in {@link ExprParser#assignmentExpression}.
	 * @param ctx the parse tree
	 */
	void exitConditionalExpressionAssignmentExpr(ExprParser.ConditionalExpressionAssignmentExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code assignmentExprAssignmentExpr}
	 * labeled alternative in {@link ExprParser#assignmentExpression}.
	 * @param ctx the parse tree
	 */
	void enterAssignmentExprAssignmentExpr(ExprParser.AssignmentExprAssignmentExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code assignmentExprAssignmentExpr}
	 * labeled alternative in {@link ExprParser#assignmentExpression}.
	 * @param ctx the parse tree
	 */
	void exitAssignmentExprAssignmentExpr(ExprParser.AssignmentExprAssignmentExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExpr(ExprParser.ExprContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExpr(ExprParser.ExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#constantExpression}.
	 * @param ctx the parse tree
	 */
	void enterConstantExpression(ExprParser.ConstantExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#constantExpression}.
	 * @param ctx the parse tree
	 */
	void exitConstantExpression(ExprParser.ConstantExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#type}.
	 * @param ctx the parse tree
	 */
	void enterType(ExprParser.TypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#type}.
	 * @param ctx the parse tree
	 */
	void exitType(ExprParser.TypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#typemodifier}.
	 * @param ctx the parse tree
	 */
	void enterTypemodifier(ExprParser.TypemodifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#typemodifier}.
	 * @param ctx the parse tree
	 */
	void exitTypemodifier(ExprParser.TypemodifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#type_name}.
	 * @param ctx the parse tree
	 */
	void enterType_name(ExprParser.Type_nameContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#type_name}.
	 * @param ctx the parse tree
	 */
	void exitType_name(ExprParser.Type_nameContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteral(ExprParser.LiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteral(ExprParser.LiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#singleLiteral}.
	 * @param ctx the parse tree
	 */
	void enterSingleLiteral(ExprParser.SingleLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#singleLiteral}.
	 * @param ctx the parse tree
	 */
	void exitSingleLiteral(ExprParser.SingleLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#boolLiteral}.
	 * @param ctx the parse tree
	 */
	void enterBoolLiteral(ExprParser.BoolLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#boolLiteral}.
	 * @param ctx the parse tree
	 */
	void exitBoolLiteral(ExprParser.BoolLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#arrayLiteral}.
	 * @param ctx the parse tree
	 */
	void enterArrayLiteral(ExprParser.ArrayLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#arrayLiteral}.
	 * @param ctx the parse tree
	 */
	void exitArrayLiteral(ExprParser.ArrayLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link ExprParser#arrayLiteralList}.
	 * @param ctx the parse tree
	 */
	void enterArrayLiteralList(ExprParser.ArrayLiteralListContext ctx);
	/**
	 * Exit a parse tree produced by {@link ExprParser#arrayLiteralList}.
	 * @param ctx the parse tree
	 */
	void exitArrayLiteralList(ExprParser.ArrayLiteralListContext ctx);
}