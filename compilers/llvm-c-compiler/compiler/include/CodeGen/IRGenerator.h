#ifndef MINIC_COMPILER_CODEGEN_IRGENERATOR_H
#define MINIC_COMPILER_CODEGEN_IRGENERATOR_H

#include "AST/types.h"
#include "AST/consumer.h"

#include "CodeGen/AllocaTable.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include <variant>
#include <string_view>

namespace codegen {

    class IRGenerator : public ast::BaseASTConsumer {
    public:
        IRGenerator(std::string_view mname);

        void dump(std::string& os);

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
        llvm::Type* getLLVMBaseType(ast::BaseType type);
        llvm::ArrayType* getLLVMArrayType(llvm::Type* base, const std::vector<std::size_t>& dims);
        llvm::Type* getLLVMType(const ast::Type& type);
        llvm::Value* loadAddress(const std::string& id);
        llvm::Value* loadValue(const std::string& id);
        llvm::StoreInst* storeValue(const std::string& id, llvm::Value* value);

    private:
        std::variant<std::monostate, llvm::Value*, llvm::Type*, llvm::Function*> exchange_v;
        std::variant<std::monostate, llvm::Value*, llvm::Type*, llvm::Function*> exchange_addr;

        std::unique_ptr<llvm::LLVMContext> context;
        std::unique_ptr<llvm::Module> module;
        std::unique_ptr<llvm::IRBuilder<>> builder;

        codegen::AllocaTable table;
    };
}
#endif /* MINIC_COMPILER_CODEGEN_IRGENERATOR_H */