#ifndef MINIC_COMPILER_AST_TREEDEFS_H
#define MINIC_COMPILER_AST_TREEDEFS_H

#include <vector>

namespace ast {
    class ASTBase;
        class TranslationUnit;
        class FormalParameter;
        class Prototype;
        class FunctionDeclaration;
        class FunctionDefinition;
        class StatementBase;
            class VariableDeclarationList;
            class VariableDeclaration;
            class CompoundStatement;
            class ExpressionStatement;
            class EmptyStatement;
            class IfStatement;
            class ForStatement;
            class WhileStatement;
            class ReturnStatement;
            class ContinueStatement;
            class BreakStatement;
        class ExpressionBase;
            class ExpressionList;
            class TernaryOpExpression;
            class BinaryOpExpression;
            class PrefixUnaryOpExpression;
            class PostfixUnaryOpExpression;
            class ArraySubscriptExpression;
            class CallExpression;
            class CastExpression;
            class IDExpression;
            class BooleanLiteral;
            class CharacterLiteral;
            class IntegerLiteral;
            class FloatLiteral;
            class StringLiteral;
            class ArrayLiteral;
}

#endif /* ifndef MINIC_COMPILER_AST_TREEDEFS_H */