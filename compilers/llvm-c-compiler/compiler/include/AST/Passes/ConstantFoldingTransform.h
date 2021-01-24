#ifndef MINIC_COMPILER_AST_PASSES_CONSTANT_FOLDING_TRANSFORM_H
#define MINIC_COMPILER_AST_PASSES_CONSTANT_FOLDING_TRANSFORM_H

#include "AST/transformer.h"

#include "AST/base.h"

#include <variant>
#include <memory>

// doesn't make much sense to make a PrettyPrinter with an AST instead of a parse tree
// it's there here because it makes testing the AST construction easier
// i.e. it is easier to understand pretty printed code instead of postfix code -- which my brain isn't used to

class ConstantFoldingTransform : public ast::BaseASTTransformer {
public:
    ConstantFoldingTransform() { }

    void visit(ast::TranslationUnit&) override;

    void visit(ast::FormalParameter&) override;
    void visit(ast::Prototype&) override;
    void visit(ast::FunctionDeclaration&) override;
    void visit(ast::FunctionDefinition&) override;

    void visit(ast::VariableDeclarationList&) override;
    void visit(ast::VariableDeclaration&) override;

    void visit(ast::CompoundStatement&) override;
    void visit(ast::ExpressionStatement&) override;
    void visit(ast::EmptyStatement&) override;
    void visit(ast::IfStatement&) override;
    void visit(ast::ForStatement&) override;
    void visit(ast::WhileStatement&) override;
    void visit(ast::ReturnStatement&) override;
    void visit(ast::ContinueStatement&) override;
    void visit(ast::BreakStatement&) override;
    
    void visit(ast::ExpressionList&) override;
    void visit(ast::TernaryOpExpression&) override;
    void visit(ast::BinaryOpExpression&) override;
    void visit(ast::PrefixUnaryOpExpression&) override;
    void visit(ast::PostfixUnaryOpExpression&) override;
    void visit(ast::ArraySubscriptExpression&) override;
    void visit(ast::CallExpression&) override;
    void visit(ast::CastExpression&) override;
    void visit(ast::IDExpression&) override;

    void visit(ast::BooleanLiteral&) override;
    void visit(ast::CharacterLiteral&) override;
    void visit(ast::IntegerLiteral&) override;
    void visit(ast::FloatLiteral&) override;
    void visit(ast::StringLiteral&) override;
    void visit(ast::ArrayLiteral&) override;

private:
    // if the latest visit returned a constant expression, it is stored in 'value'; otherwise, it's empty (std::monostate)
    std::variant<std::monostate, ast::BooleanType, ast::CharacterType, ast::IntegerType, ast::FloatType> value;

    std::shared_ptr<ast::ExpressionBase> make_literal();
};

#endif /* ifndef MINIC_COMPILER_AST_PASSES_CONSTANT_FOLDING_TRANSFORM_H */