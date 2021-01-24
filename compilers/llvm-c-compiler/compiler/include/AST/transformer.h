#ifndef MINIC_COMPILER_AST_TRANSFORMER_H
#define MINIC_COMPILER_AST_TRANSFORMER_H

#include "AST/treedefs.h"

namespace ast {
    class BaseASTTransformer {
    public:
        virtual void visit(TranslationUnit&) = 0;
        virtual void visit(FormalParameter&) = 0;
        virtual void visit(Prototype&) = 0;
        virtual void visit(FunctionDeclaration&) = 0;
        virtual void visit(FunctionDefinition&) = 0;
        virtual void visit(VariableDeclarationList&) = 0;
        virtual void visit(VariableDeclaration&) = 0;

        virtual void visit(CompoundStatement&) = 0;
        virtual void visit(ExpressionStatement&) = 0;
        virtual void visit(EmptyStatement&) = 0;
        virtual void visit(IfStatement&) = 0;
        virtual void visit(ForStatement&) = 0;
        virtual void visit(WhileStatement&) = 0;
        virtual void visit(ReturnStatement&) = 0;
        virtual void visit(ContinueStatement&) = 0;
        virtual void visit(BreakStatement&) = 0;

        virtual void visit(ExpressionList&) = 0;
        virtual void visit(TernaryOpExpression&) = 0;
        virtual void visit(BinaryOpExpression&) = 0;
        virtual void visit(PrefixUnaryOpExpression&) = 0;
        virtual void visit(PostfixUnaryOpExpression&) = 0;
        virtual void visit(ArraySubscriptExpression&) = 0;
        virtual void visit(CallExpression&) = 0;
        virtual void visit(CastExpression&) = 0;
        virtual void visit(IDExpression&) = 0;

        virtual void visit(BooleanLiteral&) = 0;
        virtual void visit(CharacterLiteral&) = 0;
        virtual void visit(IntegerLiteral&) = 0;
        virtual void visit(FloatLiteral&) = 0;
        virtual void visit(StringLiteral&) = 0;
        virtual void visit(ArrayLiteral&) = 0;
    };
}

#endif /* ifndef MINIC_COMPILER_AST_TRANSFORMER_H */