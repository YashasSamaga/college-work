// Generated from Expr.g4 by ANTLR 4.8
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link ExprParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface ExprVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link ExprParser#translationUnit}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTranslationUnit(ExprParser.TranslationUnitContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDeclaration(ExprParser.DeclarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#variableDeclaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVariableDeclaration(ExprParser.VariableDeclarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#initDeclarator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInitDeclarator(ExprParser.InitDeclaratorContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#initializer}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInitializer(ExprParser.InitializerContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#functionDeclaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionDeclaration(ExprParser.FunctionDeclarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#functionDefinition}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionDefinition(ExprParser.FunctionDefinitionContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#functionPrototype}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionPrototype(ExprParser.FunctionPrototypeContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#formalParameterList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFormalParameterList(ExprParser.FormalParameterListContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#formalParameter}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFormalParameter(ExprParser.FormalParameterContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#arrayDimensionList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArrayDimensionList(ExprParser.ArrayDimensionListContext ctx);
	/**
	 * Visit a parse tree produced by the {@code compoundStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCompoundStatementStat(ExprParser.CompoundStatementStatContext ctx);
	/**
	 * Visit a parse tree produced by the {@code exprStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprStatementStat(ExprParser.ExprStatementStatContext ctx);
	/**
	 * Visit a parse tree produced by the {@code emptyStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEmptyStatementStat(ExprParser.EmptyStatementStatContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ifStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIfStatementStat(ExprParser.IfStatementStatContext ctx);
	/**
	 * Visit a parse tree produced by the {@code forStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitForStatementStat(ExprParser.ForStatementStatContext ctx);
	/**
	 * Visit a parse tree produced by the {@code whileStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitWhileStatementStat(ExprParser.WhileStatementStatContext ctx);
	/**
	 * Visit a parse tree produced by the {@code returnStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitReturnStatementStat(ExprParser.ReturnStatementStatContext ctx);
	/**
	 * Visit a parse tree produced by the {@code continueStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitContinueStatementStat(ExprParser.ContinueStatementStatContext ctx);
	/**
	 * Visit a parse tree produced by the {@code breakStatementStat}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBreakStatementStat(ExprParser.BreakStatementStatContext ctx);
	/**
	 * Visit a parse tree produced by the {@code varDeclarationStatement}
	 * labeled alternative in {@link ExprParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVarDeclarationStatement(ExprParser.VarDeclarationStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#compoundStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCompoundStatement(ExprParser.CompoundStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#expressionStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpressionStatement(ExprParser.ExpressionStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#ifStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIfStatement(ExprParser.IfStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#forStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitForStatement(ExprParser.ForStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#forDeclaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitForDeclaration(ExprParser.ForDeclarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#whileStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitWhileStatement(ExprParser.WhileStatementContext ctx);
	/**
	 * Visit a parse tree produced by the {@code identPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIdentPrimaryExpr(ExprParser.IdentPrimaryExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code boolLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBoolLiteralPrimaryExpr(ExprParser.BoolLiteralPrimaryExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code arrayLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArrayLiteralPrimaryExpr(ExprParser.ArrayLiteralPrimaryExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code charLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCharLiteralPrimaryExpr(ExprParser.CharLiteralPrimaryExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code integerLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIntegerLiteralPrimaryExpr(ExprParser.IntegerLiteralPrimaryExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code floatLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFloatLiteralPrimaryExpr(ExprParser.FloatLiteralPrimaryExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code stringLiteralPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStringLiteralPrimaryExpr(ExprParser.StringLiteralPrimaryExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code exprParenthesisPrimaryExpr}
	 * labeled alternative in {@link ExprParser#primaryExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprParenthesisPrimaryExpr(ExprParser.ExprParenthesisPrimaryExprContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#idExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIdExpression(ExprParser.IdExpressionContext ctx);
	/**
	 * Visit a parse tree produced by the {@code funcCallPostfixExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFuncCallPostfixExpr(ExprParser.FuncCallPostfixExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code postfixIncDecExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPostfixIncDecExpr(ExprParser.PostfixIncDecExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code unaryPostfixExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUnaryPostfixExpr(ExprParser.UnaryPostfixExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code arrayIndexingPostfixExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArrayIndexingPostfixExpr(ExprParser.ArrayIndexingPostfixExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code primaryExprPostfixExpr}
	 * labeled alternative in {@link ExprParser#postfixExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPrimaryExprPostfixExpr(ExprParser.PrimaryExprPostfixExprContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#argumentExpressionList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArgumentExpressionList(ExprParser.ArgumentExpressionListContext ctx);
	/**
	 * Visit a parse tree produced by the {@code postfixExprUnaryExpr}
	 * labeled alternative in {@link ExprParser#prefixExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPostfixExprUnaryExpr(ExprParser.PostfixExprUnaryExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code unaryOperatorExpr}
	 * labeled alternative in {@link ExprParser#prefixExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUnaryOperatorExpr(ExprParser.UnaryOperatorExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code castExprMultiplicativeExpr}
	 * labeled alternative in {@link ExprParser#multiplicativeExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCastExprMultiplicativeExpr(ExprParser.CastExprMultiplicativeExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code mulDivModExprMultiplicativeExpr}
	 * labeled alternative in {@link ExprParser#multiplicativeExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMulDivModExprMultiplicativeExpr(ExprParser.MulDivModExprMultiplicativeExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code addSubExprAdditiveExpr}
	 * labeled alternative in {@link ExprParser#additiveExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAddSubExprAdditiveExpr(ExprParser.AddSubExprAdditiveExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code mulExprAdditiveExpr}
	 * labeled alternative in {@link ExprParser#additiveExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMulExprAdditiveExpr(ExprParser.MulExprAdditiveExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code relExprRelationalExpr}
	 * labeled alternative in {@link ExprParser#relationalExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRelExprRelationalExpr(ExprParser.RelExprRelationalExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code additiveExprRelationalExpr}
	 * labeled alternative in {@link ExprParser#relationalExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAdditiveExprRelationalExpr(ExprParser.AdditiveExprRelationalExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code relationalExprEqualityExor}
	 * labeled alternative in {@link ExprParser#equalityExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRelationalExprEqualityExor(ExprParser.RelationalExprEqualityExorContext ctx);
	/**
	 * Visit a parse tree produced by the {@code equalityExprEqualityExpr}
	 * labeled alternative in {@link ExprParser#equalityExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEqualityExprEqualityExpr(ExprParser.EqualityExprEqualityExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code logicalAndExprLogicalAndExpr}
	 * labeled alternative in {@link ExprParser#logicalAndExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLogicalAndExprLogicalAndExpr(ExprParser.LogicalAndExprLogicalAndExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code equalityExprLogicalAndExpr}
	 * labeled alternative in {@link ExprParser#logicalAndExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEqualityExprLogicalAndExpr(ExprParser.EqualityExprLogicalAndExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code logicalOrExprLogicalOrExpr}
	 * labeled alternative in {@link ExprParser#logicalOrExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLogicalOrExprLogicalOrExpr(ExprParser.LogicalOrExprLogicalOrExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code logicalAndExprLogicalOrExpr}
	 * labeled alternative in {@link ExprParser#logicalOrExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLogicalAndExprLogicalOrExpr(ExprParser.LogicalAndExprLogicalOrExprContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#conditionalExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConditionalExpression(ExprParser.ConditionalExpressionContext ctx);
	/**
	 * Visit a parse tree produced by the {@code conditionalExpressionAssignmentExpr}
	 * labeled alternative in {@link ExprParser#assignmentExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConditionalExpressionAssignmentExpr(ExprParser.ConditionalExpressionAssignmentExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code assignmentExprAssignmentExpr}
	 * labeled alternative in {@link ExprParser#assignmentExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssignmentExprAssignmentExpr(ExprParser.AssignmentExprAssignmentExprContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpr(ExprParser.ExprContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#constantExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConstantExpression(ExprParser.ConstantExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType(ExprParser.TypeContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#typemodifier}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTypemodifier(ExprParser.TypemodifierContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#type_name}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_name(ExprParser.Type_nameContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#literal}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLiteral(ExprParser.LiteralContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#singleLiteral}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSingleLiteral(ExprParser.SingleLiteralContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#boolLiteral}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBoolLiteral(ExprParser.BoolLiteralContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#arrayLiteral}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArrayLiteral(ExprParser.ArrayLiteralContext ctx);
	/**
	 * Visit a parse tree produced by {@link ExprParser#arrayLiteralList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArrayLiteralList(ExprParser.ArrayLiteralListContext ctx);
}