grammar Expr;

translationUnit: declaration* EOF;

declaration
    : variableDeclaration
    | functionDeclaration
    | functionDefinition
    ;

// VARIABLE DECLARATIONS

variableDeclaration
    : type initDeclarator (',' initDeclarator)* ';';

initDeclarator
    : IDENT arrayDimensionList? initializer?;

initializer
    : '=' conditionalExpression;

// FUNCTION DECLARATION & DEFINITION

functionDeclaration
    : EXTERN? functionPrototype ';';

functionDefinition
    : functionPrototype compoundStatement;

functionPrototype: type IDENT '(' formalParameterList? ')';

formalParameterList: formalParameter (',' formalParameter)*;
formalParameter: type IDENT? arrayDimensionList?;

// ARRAY UTILS

arrayDimensionList: ('[' constantExpression? ']')+;

// STATEMENT

statement
    : compoundStatement     #compoundStatementStat
    | expressionStatement   #exprStatementStat
    | ';'                   #emptyStatementStat
    | ifStatement           #ifStatementStat
    | forStatement          #forStatementStat
    | whileStatement        #whileStatementStat
    | RETURN expr? ';'      #returnStatementStat
    | CONTINUE ';'          #continueStatementStat
    | BREAK ';'             #breakStatementStat
    | variableDeclaration   #varDeclarationStatement
;

compoundStatement: '{' statement* '}';

expressionStatement: expr? ';';

ifStatement: IF '(' expr ')' statement (ELSE statement)?;

forStatement: FOR '(' (expressionStatement | variableDeclaration) expressionStatement expr ')' statement;
forDeclaration
    : compoundStatement
    | assignmentExpression? ';'
    ;

whileStatement: WHILE '(' expr ')' statement;

// EXPRESSIONS

primaryExpression
    : idExpression      #identPrimaryExpr
    | boolLiteral       #boolLiteralPrimaryExpr
    | arrayLiteral      #arrayLiteralPrimaryExpr
    | CHARACTER_LITERAL #charLiteralPrimaryExpr
    | INTEGER_LITERAL   #integerLiteralPrimaryExpr
    | FLOAT_LITERAL     #floatLiteralPrimaryExpr
    | STRING_LITERAL+   #stringLiteralPrimaryExpr       // compile-time adjacent string literal concat supported
    | '(' expr ')'      #exprParenthesisPrimaryExpr
    ;

idExpression: IDENT;

postfixExpression
    : primaryExpression                                    #primaryExprPostfixExpr
    | postfixExpression '[' expr ']'                       #arrayIndexingPostfixExpr
    | postfixExpression '(' argumentExpressionList? ')'    #funcCallPostfixExpr // TODO expressionList?
    | 'static_cast' '<' type '>' '(' expr ')'              #unaryPostfixExpr
    | postfixExpression op=('++'|'--')                     #postfixIncDecExpr
    ;

argumentExpressionList
    : assignmentExpression                                 
    | argumentExpressionList ',' assignmentExpression
    ;

prefixExpression
    : postfixExpression                                   #postfixExprUnaryExpr
    | op=('++'|'--'|'+' | '-' | '!') prefixExpression        #unaryOperatorExpr
    ;

multiplicativeExpression
    : prefixExpression                                                     #castExprMultiplicativeExpr
    | multiplicativeExpression op=('*'|'/'|'%') prefixExpression           #mulDivModExprMultiplicativeExpr
    ;

additiveExpression
    : multiplicativeExpression                                           #mulExprAdditiveExpr
    | additiveExpression op=('+'|'-') multiplicativeExpression           #addSubExprAdditiveExpr
    ;

relationalExpression
    : additiveExpression                                                  #additiveExprRelationalExpr
    | relationalExpression op=('<'|'>'|'<='|'>=') additiveExpression      #relExprRelationalExpr
    ;

equalityExpression
    : relationalExpression                                                #relationalExprEqualityExor
    | equalityExpression op=('=='|'!=') relationalExpression              #equalityExprEqualityExpr
    ;

logicalAndExpression
    : equalityExpression                                                  #equalityExprLogicalAndExpr
    | logicalAndExpression '&&' equalityExpression                        #logicalAndExprLogicalAndExpr
    ;

logicalOrExpression                                                         
    : logicalAndExpression                                                #logicalAndExprLogicalOrExpr
    | logicalOrExpression '||' logicalAndExpression                       #logicalOrExprLogicalOrExpr     
    ;

conditionalExpression
    : logicalOrExpression ('?' expr ':' conditionalExpression)?
    ;

assignmentExpression
    : conditionalExpression                                                             #conditionalExpressionAssignmentExpr
    | prefixExpression op=('=' | '*=' | '/=' | '%=' | '+=' | '-=') assignmentExpression #assignmentExprAssignmentExpr
    ;

expr: assignmentExpression (',' assignmentExpression)*;

constantExpression: conditionalExpression;

//////////////// EXPRESSION END

// TYPES

type: typemodifier? type_name;
typemodifier: SIGNED | UNSIGNED;
type_name: VOID | BOOL | CHAR | INT | FLOAT;

// LITERAL

literal: singleLiteral | arrayLiteral | STRING_LITERAL;
singleLiteral: boolLiteral | CHARACTER_LITERAL | INTEGER_LITERAL | FLOAT_LITERAL;
boolLiteral: TRUE | FALSE;

arrayLiteral
    : '{' arrayLiteralList '}';

arrayLiteralList
    : literal (',' literal)*;

// TOKENS

EXTERN: 'extern';

IF: 'if';
ELSE: 'else';
FOR: 'for';
WHILE: 'while';

CONTINUE: 'continue';
BREAK: 'break';
RETURN: 'return';

SIGNED: 'signed';
UNSIGNED: 'unsigned';
INT: 'int';
CHAR: 'char';
BOOL: 'bool';
FLOAT: 'float';
VOID: 'void';

STATIC_CAST: 'static_cast';

TRUE: 'true';
FALSE: 'false';

IDENT  : [_A-Za-z][a-zA-Z0-9_]*;
COMMENT : '//' ~[\r\n]*->skip; 
NS : [ \t\n]+ -> skip;

FLOAT_LITERAL : [0-9]*[.][0-9]+;
INTEGER_LITERAL : [-]?[0-9]+;
CHARACTER_LITERAL : ('\'' . '\'') | ('\'' '\\' 'n' '\'') | ('\'' '\\' '"' '\'') | ('\'' '\\' '\\' '\'') | ('\'' '\\' '\'' '\'') | ('\'' '\\' [0-9]+ '\'');
STRING_LITERAL : '"' .*? '"';

