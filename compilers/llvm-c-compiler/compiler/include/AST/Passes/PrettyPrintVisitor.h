#ifndef MINIC_COMPILER_AST_PASSES_PRETTY_PRINTER_H
#define MINIC_COMPILER_AST_PASSES_PRETTY_PRINTER_H

#include "AST/consumer.h"

// doesn't make much sense to make a PrettyPrinter with an AST instead of a parse tree
// it's there here because it makes testing the AST construction easier (easier to compare code with similar code instead of in postfix notation)

class PrettyPrintVisitor : public ast::BaseASTConsumer {
public:
    PrettyPrintVisitor();

    void visit(const ast::TranslationUnit&) override;

    void visit(const ast::FormalParameter&) override;
    void visit(const ast::Prototype&) override;
    void visit(const ast::FunctionDeclaration&) override;
    void visit(const ast::FunctionDefinition&) override;

    void visit(const ast::VariableDeclarationList&) override;
    void visit(const ast::VariableDeclaration&) override;

    void visit(const ast::CompoundStatement&) override;
    void visit(const ast::ExpressionStatement&) override;
    void visit(const ast::EmptyStatement&) override;
    void visit(const ast::IfStatement&) override;
    void visit(const ast::ForStatement&) override;
    void visit(const ast::WhileStatement&) override;
    void visit(const ast::ReturnStatement&) override;
    void visit(const ast::ContinueStatement&) override;
    void visit(const ast::BreakStatement&) override;

    void visit(const ast::ExpressionList&) override;
    void visit(const ast::TernaryOpExpression&) override;
    void visit(const ast::BinaryOpExpression&) override;
    void visit(const ast::PrefixUnaryOpExpression&) override;
    void visit(const ast::PostfixUnaryOpExpression&) override;
    void visit(const ast::ArraySubscriptExpression&) override;
    void visit(const ast::CallExpression&) override;
    void visit(const ast::CastExpression&) override;
    void visit(const ast::IDExpression&) override;

    void visit(const ast::BooleanLiteral&) override;
    void visit(const ast::CharacterLiteral&) override;
    void visit(const ast::IntegerLiteral&) override;
    void visit(const ast::FloatLiteral&) override;
    void visit(const ast::StringLiteral&) override;
    void visit(const ast::ArrayLiteral&) override;

private:
   int indent;
};

#endif /* ifndef MINIC_COMPILER_AST_PASSES_PRETTY_PRINTER_H */