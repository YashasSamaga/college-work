#ifndef MINIC_COMPILER_AST_TREE_H
#define MINIC_COMPILER_AST_TREE_H

#include "AST/base.h"
#include "AST/identifier.h"
#include "AST/operators.h"
#include "AST/treedefs.h"
#include "AST/types.h"
#include "AST/SymbolTable.h"
#include "AST/consumer.h"
#include "AST/transformer.h"

#include "memory_utils.h"
#include "assertions.h"

#include <vector>
#include <memory>
#include <optional>

namespace ast {
    
    class ASTBase {
    public:
        virtual ~ASTBase() { }
        virtual void accept(BaseASTTransformer&) = 0;
        virtual void accept(BaseASTConsumer&) const = 0;
    };

    class TranslationUnit : public ASTBase {
    public:
        TranslationUnit() { }

        const auto& getGlobalDeclarations() const { return gdecls; }

        void add(std::shared_ptr<ASTBase> decl) {
            ASSERT(decl);
            gdecls.emplace_back(std::move(decl));
        }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        std::vector<std::shared_ptr<ASTBase>> gdecls;
    };

    class FormalParameter : public ASTBase {
    public:
        FormalParameter(Identifier id_, Type type_, std::vector<std::shared_ptr<ExpressionBase>> dimExprs_) 
            : id(std::move(id_)), type(std::move(type_)), dimExprs(std::move(dimExprs_))
        {
            if (!id) {
                /* unbound parameter */
            }
        }

        const auto& getType() const { return type; }
        void setType(Type type_) { type = std::move(type_); }

        const auto& getID() const { return id; }

        const auto& getDimExprs() const { return dimExprs; }
        void setDimExprs(std::vector<std::shared_ptr<ExpressionBase>> dimExprs_) {
            dimExprs = std::move(dimExprs_);
            // dimExprs[i] can be empty (left for size-deduction or a variable array parameter)
        }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        Identifier id;
        Type type;
        std::vector<std::shared_ptr<ExpressionBase>> dimExprs;
    };

    class Prototype : public ASTBase {
    public:
        Prototype(Type returnType_, Identifier name_, std::vector<std::shared_ptr<ast::FormalParameter>> formals_, bool external_)
            : returnType(std::move(returnType_)), name(std::move(name_)), formals(std::move(formals_)), external(external_)
        {
            ASSERT(name); /* function name must be present */
        }
        
        const auto& getReturnType() const { return returnType; }
        const auto& getID() const { return name; }
        
        const auto& getFormals() const { return formals; }
        void setFormals(std::vector<std::shared_ptr<ast::FormalParameter>> formals_) {
            formals = std::move(formals_);
        }

        auto isExternal() const { return external; }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        Type returnType;
        Identifier name;
        std::vector<std::shared_ptr<ast::FormalParameter>> formals;
        bool external;
    };

    class FunctionDeclaration : public ASTBase {
    public:
        FunctionDeclaration(std::shared_ptr<Prototype> prototype_)
            : prototype(std::move(prototype_))
        {
            ASSERT(prototype);
        }

        const auto& getPrototype() const { return prototype; }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        std::shared_ptr<Prototype> prototype;
    };

    class FunctionDefinition : public ASTBase {
    public:
        FunctionDefinition(std::shared_ptr<Prototype> prototype_, std::shared_ptr<CompoundStatement> bodyCompoundStmt_)
            : prototype(std::move(prototype_)), bodyCompoundStmt(std::move(bodyCompoundStmt_))
        {
            ASSERT(prototype);
            ASSERT(bodyCompoundStmt);
        }

        const auto& getPrototype() const { return prototype; }
        const auto& getBody() const { return bodyCompoundStmt; }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        std::shared_ptr<Prototype> prototype;
        std::shared_ptr<CompoundStatement> bodyCompoundStmt;
    };

    class StatementBase : public ASTBase {
    public:
        virtual ~StatementBase() { }
        virtual void accept(BaseASTTransformer&) = 0;
        virtual void accept(BaseASTConsumer& V) const = 0;
    };

    class VariableDeclarationList : public StatementBase {
    public:
        VariableDeclarationList(std::vector<std::shared_ptr<VariableDeclaration>> declarations_)
            : declarations(std::move(declarations_))
        {
            for (const auto& decl : declarations) {
                ASSERT(decl);
            }
        }

        const auto& getVariableDeclarations() const { return declarations; }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        std::vector<std::shared_ptr<VariableDeclaration>> declarations;
    };

    class VariableDeclaration : public StatementBase {
    public:
        VariableDeclaration(Identifier id_, Type type_, std::vector<std::shared_ptr<ExpressionBase>> dimExprs_, std::shared_ptr<ExpressionBase> initExpr_)
            : id(std::move(id_)), type(std::move(type_)), dimExprs(std::move(dimExprs_)), initExpr(std::move(initExpr_))
        {
            ASSERT(id); /* can't have nameless declarations in our language but it's a useful thing to have to create temporaries with side-effects */
            // dimExprs[i] can be empty (i.e. user has left it for size deduction)
        }

        const auto& getType() const { return type; }
        void setType(Type type_) { type = std::move(type_); }

        const auto& getID() const { return id; }

        const auto& getInitExpr() const { return initExpr; }
        void setInitExpr(std::shared_ptr<ExpressionBase> initExpr_) {
            initExpr = std::move(initExpr_);
            /* initExpr is optional => user may pass nullptr to reset */
        }

        const auto& getDimExprs() const { return dimExprs; }
        void setDimExprs(std::vector<std::shared_ptr<ExpressionBase>> dimExprs_) {
            dimExprs = std::move(dimExprs_);
            // dimExprs[i] can be empty (left for size deduction)
        }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        Identifier id;
        Type type;
        std::vector<std::shared_ptr<ExpressionBase>> dimExprs;
        std::shared_ptr<ExpressionBase> initExpr;
    };

    class CompoundStatement : public StatementBase {
    public:
        CompoundStatement(std::vector<std::shared_ptr<StatementBase>> statements_)
            : statements(std::move(statements_))
        {
            for (const auto& stmt : statements) {
                ASSERT(stmt);
            }
        }

        const auto& getStatementList() const { return statements; }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        std::vector<std::shared_ptr<StatementBase>> statements;
    };

    class EmptyStatement : public StatementBase {
    public:
        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }
    };

    class ExpressionStatement : public StatementBase {
    public:
        ExpressionStatement(std::shared_ptr<ExpressionBase> expr_)
            : expr(std::move(expr_))
        {
            ASSERT(expr);
        }

        const auto& getExpr() const { return expr; }
        void setExpr(std::shared_ptr<ExpressionBase> expr_) {
            expr = std::move(expr_);
            ASSERT(expr);
        }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        std::shared_ptr<ExpressionBase> expr;
    };

    class IfStatement : public StatementBase {
    public:
        IfStatement(std::shared_ptr<ExpressionBase> condExpr_, std::shared_ptr<StatementBase> ifBodyStmt_)
            : condExpr(std::move(condExpr_)), ifBodyStmt(std::move(ifBodyStmt_))
        {
            ASSERT(condExpr);
            ASSERT(ifBodyStmt);
        }

        IfStatement(std::shared_ptr<ExpressionBase> condExpr_, std::shared_ptr<StatementBase> ifBodyStmt_, std::shared_ptr<StatementBase> elseBodyStmt_)
            : condExpr(std::move(condExpr_)), ifBodyStmt(std::move(ifBodyStmt_)), elseBodyStmt(std::move(elseBodyStmt_))
        {
            ASSERT(condExpr);
            ASSERT(ifBodyStmt);
            ASSERT(elseBodyStmt);
        }

        const auto& getCondExpr() const { return condExpr; }
        void setCondExpr(std::shared_ptr<ExpressionBase> condExpr_) {
            condExpr = std::move(condExpr_);
            ASSERT(condExpr);
        }

        const auto& getIfBody() const { return ifBodyStmt; }
        const auto& getElseBody() const { return elseBodyStmt; }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        std::shared_ptr<ExpressionBase> condExpr;
        std::shared_ptr<StatementBase> ifBodyStmt, elseBodyStmt;
    };

    class ForStatement : public StatementBase {
    public:
        ForStatement(std::shared_ptr<StatementBase> initStmt_, std::shared_ptr<ast::StatementBase> condStmt_, std::shared_ptr<ExpressionBase> iterExpr_, std::shared_ptr<StatementBase> bodyStmt_)
            : initStmt(std::move(initStmt_)), condStmt(std::move(condStmt_)), iterExpr(std::move(iterExpr_)), bodyStmt(std::move(bodyStmt_))
        {
            ASSERT(initStmt);
            ASSERT(condStmt); // can be empty statement
            // iterExpr can be empty
            ASSERT(bodyStmt);
        }

        const auto& getInitStmt() const { return initStmt; }

        const auto& getCondStmt() const { return condStmt; }
        void setCondStmt(std::shared_ptr<StatementBase> condStmt_) {
            condStmt = std::move(condStmt_);
            ASSERT(condStmt);
        }

        const auto& getIterExpr() const { return iterExpr; }
        void setIterExpr(std::shared_ptr<ExpressionBase> iterExpr_) {
            iterExpr = std::move(iterExpr_);
            /* iterExpr can be empty => nullptr can be used to reset */
        }

        const auto& getBody() const { return bodyStmt; }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        std::shared_ptr<ASTBase> initStmt; //can be variable decl or an expression statement
        std::shared_ptr<StatementBase> condStmt;
        std::shared_ptr<ExpressionBase> iterExpr; // can be empty
        std::shared_ptr<StatementBase> bodyStmt;
    };

    class WhileStatement : public StatementBase {
    public:
        WhileStatement(std::shared_ptr<ExpressionBase> condExpr_, std::shared_ptr<StatementBase> bodyStmt_)
            : condExpr(std::move(condExpr_)), bodyStmt(std::move(bodyStmt_))
        {
            ASSERT(condExpr);
            ASSERT(bodyStmt);
        }

        const auto& getCondExpr() const { return condExpr; }
        void setCondExpr(std::shared_ptr<ExpressionBase> condExpr_) {
            condExpr = std::move(condExpr_);
            ASSERT(condExpr);
        }

        const auto& getBody() const { return bodyStmt; }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        std::shared_ptr<ExpressionBase> condExpr;
        std::shared_ptr<StatementBase> bodyStmt;
    };

    class ReturnStatement : public StatementBase {
    public:
        ReturnStatement(std::shared_ptr<ExpressionBase> expr_)
            : expr(std::move(expr_))
        {
            ASSERT(expr);
        }

        const auto& getExpr() const { return expr; }
        void setExpr(std::shared_ptr<ExpressionBase> expr_) {
            expr = std::move(expr_);
            ASSERT(expr);
        }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        std::shared_ptr<ExpressionBase> expr;
    };

    class ContinueStatement : public StatementBase {
    public:
        ContinueStatement() { }
        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }
    };

    class BreakStatement : public StatementBase {
    public:
        BreakStatement() { }
        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }
    };

    class ExpressionBase : public ASTBase {
    public:
        ExpressionBase() { }
        ExpressionBase(Type type) : type(std::move(type)) { }
    
        virtual ~ExpressionBase() { }
        virtual const Type& getType() const { ASSERT(type); return type.value(); }
        virtual void setType(Type type_) { type = std::move(type_); }

    protected:
        std::optional<Type> type;
    };

    class ExpressionList : public ExpressionBase {
    public:
        ExpressionList(std::vector<std::shared_ptr<ExpressionBase>> exprs_)
            : exprs(std::move(exprs_))
        {
            ASSERT(exprs.size() >= 1);
            for (const auto& expr : exprs) {
                ASSERT(expr);
            }
        }

        const auto& getExprs() const { return exprs; }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        std::vector<std::shared_ptr<ExpressionBase>> exprs; // comma separated list
    };

    class TernaryOpExpression : public ExpressionBase {
    public:
        TernaryOpExpression(TernaryOp op, std::shared_ptr<ExpressionBase> lhs_, std::shared_ptr<ExpressionBase> middle_, std::shared_ptr<ExpressionBase> rhs_)
            : op(op), lhs(std::move(lhs_)), middle(std::move(middle_)), rhs(std::move(rhs_))
        {
            ASSERT(lhs);
            ASSERT(middle);
            ASSERT(rhs);
        }

        auto getOp() const { return op; }

        const auto& getLHS() const { return lhs; }
        void setLHS(std::shared_ptr<ExpressionBase> lhs_) {
            lhs = std::move(lhs_);
            ASSERT(lhs);
        }

        const auto& getMiddle() const { return middle; }
        void setMiddle(std::shared_ptr<ExpressionBase> middle_) {
            middle = std::move(middle_);
            ASSERT(middle);
        }

        const auto& getRHS() const { return rhs; }
        void setRHS(std::shared_ptr<ExpressionBase> rhs_) {
            rhs = std::move(rhs_);
            ASSERT(rhs);
        }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        TernaryOp op;
        std::shared_ptr<ExpressionBase> lhs, middle, rhs;
    };

    class BinaryOpExpression : public ExpressionBase {
    public:
        BinaryOpExpression(BinaryOp op, std::shared_ptr<ExpressionBase> lhs_, std::shared_ptr<ExpressionBase> rhs_)
            : op(op), lhs(std::move(lhs_)), rhs(std::move(rhs_))
        {
            ASSERT(lhs);
            ASSERT(rhs);
        }

        auto getOp() const { return op; }

        const auto& getLHS() const { return lhs; }
        void setLHS(std::shared_ptr<ExpressionBase> lhs_) {
            lhs = std::move(lhs_);
            ASSERT(lhs);
        }

        const auto& getRHS() const { return rhs; }
        void setRHS(std::shared_ptr<ExpressionBase> rhs_) {
            rhs = std::move(rhs_);
            ASSERT(rhs);
        }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        BinaryOp op;
        std::shared_ptr<ExpressionBase> lhs, rhs;
    };

    class PrefixUnaryOpExpression : public ExpressionBase {
    public:
        PrefixUnaryOpExpression(UnaryOp op, std::shared_ptr<ExpressionBase> expr_)
            : op(op), expr(std::move(expr_))
        {
            ASSERT(expr);
        }
    
        const auto& getOp() const { return op; }
        const auto& getExpr() const { return expr; }
        void setExpr(std::shared_ptr<ExpressionBase> expr_) {
            expr = std::move(expr_);
            ASSERT(expr);
        }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        UnaryOp op;
        std::shared_ptr<ExpressionBase> expr;
    };

    class PostfixUnaryOpExpression : public ExpressionBase {
    public:
        PostfixUnaryOpExpression(UnaryOp op, std::shared_ptr<ExpressionBase> expr_)
            : op(op), expr(std::move(expr_))
        {
            ASSERT(expr);
        }
    
        const auto& getOp() const { return op; }
        const auto& getExpr() const { return expr; }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        UnaryOp op;
        std::shared_ptr<ExpressionBase> expr;
    };

    class ArraySubscriptExpression : public ExpressionBase {
    public:
        ArraySubscriptExpression(std::shared_ptr<ExpressionBase> locationExpr_, std::shared_ptr<ExpressionBase> subscriptExpr_)
            : locationExpr(std::move(locationExpr_)), subscriptExpr(std::move(subscriptExpr_))
        {
            ASSERT(locationExpr);
            ASSERT(subscriptExpr);
        }

        const auto& getLocationExpr() const { return locationExpr; }

        const auto& getSubscriptExpr() const { return subscriptExpr; }
        void setSubscriptExpr(std::shared_ptr<ExpressionBase> subscriptExpr_) {
            subscriptExpr = std::move(subscriptExpr_);
            ASSERT(subscriptExpr);
        }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        std::shared_ptr<ExpressionBase> locationExpr;
        std::shared_ptr<ExpressionBase> subscriptExpr;
    };

    class CallExpression : public ExpressionBase {
    public:
        CallExpression(std::shared_ptr<ExpressionBase> callee_, std::vector<std::shared_ptr<ExpressionBase>> args_)
            : callee(std::move(callee_)), args(std::move(args_))
        {
            ASSERT(callee);
            for (const auto& arg : args) {
                ASSERT(arg);
            }
        }

        auto& getCallee() { return callee; }
        const auto& getCallee() const { return callee; }
        const auto& getFunc() const { return callee; }

        const auto& getArgs() const { return args; }
        void setArgs(std::vector<std::shared_ptr<ExpressionBase>> args_) {
            args = std::move(args_);
            for (const auto& arg : args) {
                ASSERT(arg);
            }
        }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        std::shared_ptr<ExpressionBase> callee;
        std::vector<std::shared_ptr<ExpressionBase>> args;
    };  

    class CastExpression : public ExpressionBase {
    public:
        CastExpression(Type totype, std::shared_ptr<ExpressionBase> expr_)
            : ExpressionBase(std::move(totype)), expr(std::move(expr_))
        {
            ASSERT(expr);
        }

        const auto& getExpr() const { return expr; }
        void setExpr(std::shared_ptr<ExpressionBase> expr_) {
            expr = std::move(expr_);
            ASSERT(expr);
        }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        std::shared_ptr<ExpressionBase> expr;
    };

    class IDExpression : public ExpressionBase {
    public:
        IDExpression(std::string id_)
            : id(std::move(id_))
        {
            ASSERT(id);
        }

        const auto& getID() const { return id; }

        const SymbolEntry& getRefSymbol() const { return refsym; }
        void setRefSymbol(SymbolEntry refsym_) { refsym = std::move(refsym_); }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        Identifier id;
        SymbolEntry refsym;
    };

    class BooleanLiteral : public ExpressionBase {
    public:
        BooleanLiteral(BooleanType value)
            : ExpressionBase(Type(BaseType::Bool)), value(value) { }

        auto getValue() const { return value; }
    
        void setType(Type) override { ASSERT(0 && "cannot set types of literals"); }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        BooleanType value;
    };

    class CharacterLiteral : public ExpressionBase {
    public:
        CharacterLiteral(CharacterType value)
            : ExpressionBase(Type(BaseType::Char)), value(value) { }

        auto getValue() const { return value; }

        void setType(Type) override { ASSERT(0 && "cannot set types of literals"); }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        CharacterType value;
    };

    class IntegerLiteral : public ExpressionBase {
    public:
        IntegerLiteral(IntegerType value)
            : ExpressionBase(Type(BaseType::Int)), value(value) { }

        auto getValue() const { return value; }

        void setType(Type) override { ASSERT(0 && "cannot set types of literals"); }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        IntegerType value;
    };

    class FloatLiteral : public ExpressionBase {
    public:
        FloatLiteral(FloatType value)
            : ExpressionBase(Type(BaseType::Float)), value(value) { }

        auto getValue() const { return value; }

        void setType(Type) override { ASSERT(0 && "cannot set types of literals"); }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        FloatType value;
    };

    class StringLiteral : public ExpressionBase {
    public:
        StringLiteral(StringType value)
            : ExpressionBase(Type(BaseType::Char, {value.length() + 1})), value(std::move(value)) { }

        auto getValue() const { return value; }

        void setType(Type) override { ASSERT(0 && "cannot set types of literals"); }

        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }

    private:
        StringType value;
    };

    class ArrayLiteral : public ExpressionBase {
    public:
        // TODO
        void accept(BaseASTTransformer& V) override { V.visit(*this); }
        void accept(BaseASTConsumer& V) const override { V.visit(*this); }
    };
}

#endif  /* ifndef MINIC_COMPILER_AST_TREE_H */