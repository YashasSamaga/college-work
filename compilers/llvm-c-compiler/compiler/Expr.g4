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
    : functionPrototype ';';

functionDefinition
    : functionPrototype compoundStatement;

functionPrototype: EXTERN? type IDENT '(' formalParameterList? ')';

formalParameterList: formalParameter (',' formalParameter)*;
formalParameter: type IDENT? arrayDimensionList?;

// ARRAY UTILS

arrayDimensionList: ('[' arrayDimExpr ']')+;
arrayDimExpr
    : /* epsilon */
    | constantExpression
    ;

// STATEMENT

statement
    : compoundStatement     #passStatement
    | expressionStatement   #passStatement
    | ';'                   #emptyStatementStat
    | ifStatement           #passStatement
    | forStatement          #passStatement
    | whileStatement        #passStatement
    | RETURN expr? ';'      #returnStatementStat
    | CONTINUE ';'          #continueStatementStat
    | BREAK ';'             #breakStatementStat
    | variableDeclaration   #varDeclarationStatement
;

compoundStatement: '{' statement* '}';

expressionStatement: expr? ';';

ifStatement
    : IF '(' expr ')' statement                                                             #ifOnlyStatement
    | IF '(' expr ')' statement ELSE statement                                              #ifElseStatement
    ;

forStatement: FOR '(' forInitStatement expressionStatement expr? ')' statement;
forInitStatement
    : expressionStatement
    | variableDeclaration
    ;

whileStatement: WHILE '(' expr ')' statement;

// EXPRESSIONS

idExpression: IDENT;

primaryExpression
    : idExpression                                                                          #identPrimaryExpr
    | literal                                                                               #literalPrimaryExpr
    | '(' expr ')'                                                                          #parenPrimaryExpr
    ;

postfixExpression
    : primaryExpression                                                                     #fallbackPostfixExpression
    | postfixExpression '[' expr ']'                                                        #arraySubscriptExpression
    | postfixExpression '(' expr? ')'                                                       #callExpression
    | 'static_cast' '<' type '>' '(' expr ')'                                               #castExpression
    | postfixExpression op=('++'|'--')                                                      #doPostfixExpression
    ;

prefixExpression
    : postfixExpression                                                                     #fallbackPrefixExpression
    | op=('++'|'--'|'+' | '-' | '!') prefixExpression                                       #doPrefixExpression
    ;

multiplicativeExpression
    : prefixExpression                                                                      #fallbackMultiplicativeExpression
    | multiplicativeExpression op=('*'|'/'|'%') prefixExpression                            #doMultiplicativeExpression
    ;

additiveExpression
    : multiplicativeExpression                                                              #fallbackAdditiveExpression
    | additiveExpression op=('+'|'-') multiplicativeExpression                              #doAdditiveExpression
    ;

relationalExpression
    : additiveExpression                                                                    #fallbackRelationalExpression
    | relationalExpression op=('<'|'>'|'<='|'>=') additiveExpression                        #doRelationalExpression
    ;

equalityExpression
    : relationalExpression                                                                  #fallbackEqualityExpression
    | equalityExpression op=('=='|'!=') relationalExpression                                #doEqualityExpression
    ;

logicalAndExpression
    : equalityExpression                                                                    #fallbackLogicalAndExpression
    | logicalAndExpression '&&' equalityExpression                                          #doLogicalAndExpression
    ;

logicalOrExpression                                                         
    : logicalAndExpression                                                                  #fallbackLogicalOrExpression
    | logicalOrExpression '||' logicalAndExpression                                         #doLogicalOrExpression
    ;

conditionalExpression
    : logicalOrExpression                                                                   #fallbackConditionalExpression
    | logicalOrExpression ('?' expr ':' conditionalExpression)                              #doConditionalExpression
    ;

assignmentExpression
    : conditionalExpression                                                                 #fallbackAssigmentExpression
    | prefixExpression op=('=' | '*=' | '/=' | '%=' | '+=' | '-=') assignmentExpression     #doAssignmentExpression
    ;

expr
    : assignmentExpression                                                                  #fallbackExpr
    | assignmentExpression (',' assignmentExpression)*                                      #doExpressionList
    ;

constantExpression: conditionalExpression;

//////////////// EXPRESSION END

// TYPES

type: typemodifier? type_name;
typemodifier: modifier=(SIGNED | UNSIGNED);
type_name: name=(VOID | BOOL | CHAR | INT | FLOAT);

// LITERAL

literal: boolLiteral | charLiteral | integerLiteral | floatLiteral | stringLiteral | arrayLiteral;

boolLiteral: value=(TRUE | FALSE);
charLiteral: CHARACTER_LITERAL;
integerLiteral: INTEGER_LITERAL;
floatLiteral: FLOAT_LITERAL;
stringLiteral: STRING_LITERAL+; // + to allow compile-time string concatenation

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

