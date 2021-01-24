#include "AST/Passes/ConstantFoldingTransform.h"

#include "AST/build_utils.h"
#include "AST/tree.h"
#include "assertions.h"

#include <variant>

std::shared_ptr<ast::ExpressionBase> ConstantFoldingTransform::make_literal() {
    ASSERT(value.index());
    return std::visit([&](auto v)->std::shared_ptr<ast::ExpressionBase> {
        using T = decltype(v);
        using namespace ast;

        if constexpr (std::is_same_v<T, BooleanType>)
            return make_shared_expr<ast::BooleanLiteral>(v);
        if constexpr (std::is_same_v<T, CharacterType>)
            return make_shared_expr<ast::CharacterLiteral>(v);
        if constexpr (std::is_same_v<T, IntegerType>)
            return make_shared_expr<ast::IntegerLiteral>(v);
        if constexpr (std::is_same_v<T, FloatType>)
            return make_shared_expr<ast::FloatLiteral>(v);
        return nullptr;
    }, value);
}

void ConstantFoldingTransform::visit(ast::TranslationUnit& node) {
    for (auto& child : node.getGlobalDeclarations())
        child->accept(*this);
}

void ConstantFoldingTransform::visit(ast::FormalParameter& param) {
    auto dimExprs = param.getDimExprs();
    if (!dimExprs.empty()) {
        for (int i = 0; i < dimExprs.size(); i++) {
            if (dimExprs[i]) {
                dimExprs[i]->accept(*this);
                if (value.index())
                    dimExprs[i] = make_literal(); // TODO use references instead of [i]
            }
        }
        param.setDimExprs(std::move(dimExprs));
    }
}

void ConstantFoldingTransform::visit(ast::Prototype& proto) {
    auto formals = proto.getFormals();
    for (auto& param : formals)
        param->accept(*this);
    proto.setFormals(std::move(formals));
}

void ConstantFoldingTransform::visit(ast::FunctionDeclaration& decl) {
    decl.getPrototype()->accept(*this);
}

void ConstantFoldingTransform::visit(ast::FunctionDefinition& decl) {
    decl.getPrototype()->accept(*this);
    decl.getBody()->accept(*this);
}

void ConstantFoldingTransform::visit(ast::VariableDeclarationList& node) {
    for (auto& decl : node.getVariableDeclarations())
        decl->accept(*this);
}

void ConstantFoldingTransform::visit(ast::VariableDeclaration& node) {
    auto dimExprs = node.getDimExprs();
    if (!dimExprs.empty()) {
        for (int i = 0; i < dimExprs.size(); i++) {
            if (dimExprs[i]) {
                dimExprs[i]->accept(*this);
                if (value.index())
                    dimExprs[i] = make_literal(); // TODO use references instead of [i]
            }
        }
        node.setDimExprs(std::move(dimExprs));
    }

    auto initExpr = node.getInitExpr();
    if (initExpr) {
        initExpr->accept(*this);
        if (value.index())
            node.setInitExpr(make_literal());
    }
}

void ConstantFoldingTransform::visit(ast::CompoundStatement& cstmt) {
    for (auto& stmt : cstmt.getStatementList())
        stmt->accept(*this);
}

void ConstantFoldingTransform::visit(ast::ExpressionStatement& stmt) {
    stmt.getExpr()->accept(*this);
    if (value.index())
        stmt.setExpr(make_literal());
}

void ConstantFoldingTransform::visit(ast::EmptyStatement&) { }

void ConstantFoldingTransform::visit(ast::IfStatement& stmt) {
    stmt.getCondExpr()->accept(*this);
    if (value.index())
        stmt.setCondExpr(make_literal());

    stmt.getIfBody()->accept(*this);
    if (stmt.getElseBody())
        stmt.getElseBody()->accept(*this);
}

void ConstantFoldingTransform::visit(ast::ForStatement& stmt) {
    stmt.getInitStmt()->accept(*this);
    stmt.getCondStmt()->accept(*this);

    if (stmt.getIterExpr()) {
        stmt.getIterExpr()->accept(*this);
        if (value.index())
            stmt.setIterExpr(make_literal());
    }

    stmt.getBody()->accept(*this);
}

void ConstantFoldingTransform::visit(ast::WhileStatement& stmt) {
    stmt.getCondExpr()->accept(*this);
    if (value.index())
        stmt.setCondExpr(make_literal());
    stmt.getBody()->accept(*this);
}

void ConstantFoldingTransform::visit(ast::ReturnStatement& stmt) {
    if (stmt.getExpr()) {
        stmt.getExpr()->accept(*this);
        if (value.index())
            stmt.setExpr(make_literal());
    }
}

void ConstantFoldingTransform::visit(ast::ContinueStatement& stmt) { }

void ConstantFoldingTransform::visit(ast::BreakStatement& stmt) { }

void ConstantFoldingTransform::visit(ast::ExpressionList& exprlist) {
    bool all_replaced = true;

    auto exprs = exprlist.getExprs();
    for (int i = 0; i < exprs.size(); i++) {
        exprs[i]->accept(*this);
        if (value.index())
            exprs[i] = make_literal(); // TODO use ref instead of [i]
        else
            all_replaced = false;
    }

    // comma operator returns the last expression; we can return the last literal iff all the expressions in the list have no side-effects
    if (!all_replaced)
        value = std::monostate();
    // forward last value otherwise
}

void ConstantFoldingTransform::visit(ast::TernaryOpExpression& node) {
    node.getLHS()->accept(*this);
    if (value.index() == 0) {
        /* since cond is not constexpr, we cannot evaluate this node at compile-time */
        /* however, we can still visit the children for folding constant subexpressions */
        node.getMiddle()->accept(*this);
        if (value.index())
            node.setMiddle(make_literal());

        node.getRHS()->accept(*this);
        if (value.index())
            node.setMiddle(make_literal());

        value = std::monostate();
        return;
    }

    bool cond = std::visit([&](auto v)->bool {
        if constexpr (!std::is_same_v<decltype(v), std::monostate>)
            return v;
        return false; /* impossible */
    }, value);
    node.setLHS(make_literal());

    // check if the branch evaluates to a literal; we can return a literal for the whole node in that case
    if (cond)
        node.getMiddle()->accept(*this);
    else
        node.getRHS()->accept(*this);
    // forward the value (which may also forward std::monostate if the branch wasn't a constant expression)
}

void ConstantFoldingTransform::visit(ast::BinaryOpExpression& node) {
    node.getLHS()->accept(*this);
    if (value.index())
        node.setLHS(make_literal());
    const auto lhs = value;

    node.getRHS()->accept(*this);
    if (value.index())
        node.setRHS(make_literal());
    const auto rhs = value;

    std::visit([&](auto lhs, auto rhs) {
        using T1 = decltype(lhs);
        using T2 = decltype(rhs);
        using namespace ast;

        value = std::monostate();
        if constexpr (is_arithmetic_v<T1> && is_arithmetic_v<T2>) { // TODO boolean checks -- require ImplicitCastExpression
            // TODO getCombinedType -- don't rely on C++ rules
            switch(node.getOp()) {
                case BinaryOp::Mul: value = lhs * rhs; break;
                case BinaryOp::Div:
                    ASSERT(rhs != 0); // TODO diagnostics
                    value = lhs / rhs;
                    break;
                case BinaryOp::Rem:
                    if constexpr (is_integral_v<T1> && is_integral_v<T2>) {
                        ASSERT(rhs != 0);
                        value = lhs % rhs;
                    }
                    break;
                case BinaryOp::Add: value = lhs + rhs; break;
                case BinaryOp::Sub: value = lhs + rhs; break;;
                case BinaryOp::LessThan: value = lhs < rhs; break;
                case BinaryOp::GreaterThan: value = lhs > rhs; break;
                case BinaryOp::LessThanEqual: value = lhs <= rhs; break;
                case BinaryOp::GreaterThanEqual:  value = lhs >= rhs; break;
                case BinaryOp::Equal: value = lhs == rhs; break;
                case BinaryOp::NotEqual: value = lhs != rhs; break;
                case BinaryOp::LogicalAnd: value = lhs && rhs; break;
                case BinaryOp::LogicalOr: value = lhs || rhs; break;
            }
        }
    }, lhs, rhs);
}

void ConstantFoldingTransform::visit(ast::PrefixUnaryOpExpression& node) {
    node.getExpr()->accept(*this);
    if (value.index())
        node.setExpr(make_literal());

    std::visit([&](auto v) {
        using T = decltype(v);
        using namespace ast;

        value = std::monostate();
        if constexpr (is_arithmetic_v<T>) {
            switch(node.getOp()) {
                case UnaryOp::Plus: value = +v; break;
                case UnaryOp::Minus: value = -v; break;
                case UnaryOp::LogicalNot: value = !v; break;
            }
        }
    }, value);
}

void ConstantFoldingTransform::visit(ast::PostfixUnaryOpExpression& node) {
    /* increment and decrement are the only two postfix operators and these can be used on lvalues only */
    node.getExpr()->accept(*this);
    value = std::monostate();
}

void ConstantFoldingTransform::visit(ast::ArraySubscriptExpression& expr) {
    expr.getLocationExpr()->accept(*this);
    // ignore -- not useful since the language doesn't support pointers

    expr.getSubscriptExpr()->accept(*this);
    if (value.index())
        expr.setSubscriptExpr(make_literal());

    value = std::monostate();
}

void ConstantFoldingTransform::visit(ast::CallExpression& cexpr) {
    cexpr.getCallee()->accept(*this);
    for (auto& arg : cexpr.getArgs())
        arg->accept(*this);
    value = std::monostate();
}

void ConstantFoldingTransform::visit(ast::CastExpression& expr) {
    expr.getExpr()->accept(*this);
    if (value.index())
        expr.setExpr(make_literal()); // TODO do cast at compile-time
    value = std::monostate();
}

void ConstantFoldingTransform::visit(ast::IDExpression&) { value = std::monostate(); }

void ConstantFoldingTransform::visit(ast::BooleanLiteral& blit) { value = blit.getValue(); }
void ConstantFoldingTransform::visit(ast::CharacterLiteral& clit) { value = clit.getValue(); }
void ConstantFoldingTransform::visit(ast::IntegerLiteral& ilit) { value = ilit.getValue(); }
void ConstantFoldingTransform::visit(ast::FloatLiteral& flit) { value = flit.getValue(); }

void ConstantFoldingTransform::visit(ast::StringLiteral&) { value = std::monostate(); }
void ConstantFoldingTransform::visit(ast::ArrayLiteral&) { value = std::monostate(); }