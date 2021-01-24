#ifndef MINIC_COMPILER_AST_CONSUMER_H
#define MINIC_COMPILER_AST_CONSUMER_H

#include "AST/treedefs.h"

namespace ast {
    class BaseASTConsumer {
    public:
        virtual void visit(const TranslationUnit&) = 0;
        virtual void visit(const FormalParameter&) = 0;
        virtual void visit(const Prototype&) = 0;
        virtual void visit(const FunctionDeclaration&) = 0;
        virtual void visit(const FunctionDefinition&) = 0;
        virtual void visit(const VariableDeclarationList&) = 0;
        virtual void visit(const VariableDeclaration&) = 0;

        virtual void visit(const CompoundStatement&) = 0;
        virtual void visit(const ExpressionStatement&) = 0;
        virtual void visit(const EmptyStatement&) = 0;
        virtual void visit(const IfStatement&) = 0;
        virtual void visit(const ForStatement&) = 0;
        virtual void visit(const WhileStatement&) = 0;
        virtual void visit(const ReturnStatement&) = 0;
        virtual void visit(const ContinueStatement&) = 0;
        virtual void visit(const BreakStatement&) = 0;

        virtual void visit(const ExpressionList&) = 0;
        virtual void visit(const TernaryOpExpression&) = 0;
        virtual void visit(const BinaryOpExpression&) = 0;
        virtual void visit(const PrefixUnaryOpExpression&) = 0;
        virtual void visit(const PostfixUnaryOpExpression&) = 0;
        virtual void visit(const ArraySubscriptExpression&) = 0;
        virtual void visit(const CallExpression&) = 0;
        virtual void visit(const CastExpression&) = 0;
        virtual void visit(const IDExpression&) = 0;

        virtual void visit(const BooleanLiteral&) = 0;
        virtual void visit(const CharacterLiteral&) = 0;
        virtual void visit(const IntegerLiteral&) = 0;
        virtual void visit(const FloatLiteral&) = 0;
        virtual void visit(const StringLiteral&) = 0;
        virtual void visit(const ArrayLiteral&) = 0;
    };
}

#endif /* ifndef MINIC_COMPILER_AST_CONSUMER_H */