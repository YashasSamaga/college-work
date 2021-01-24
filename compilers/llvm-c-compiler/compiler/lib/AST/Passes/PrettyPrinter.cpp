#include "AST/Passes/PrettyPrintVisitor.h"

#include "AST/types.h"
#include "AST/operators.h"
#include "AST/tree.h"

#include <iostream>

class IndentTracker {
public:
    IndentTracker(int& indent) : indent_p(&indent) { indent++; }
    ~IndentTracker() { (*indent_p)--;  }

private:
    int* indent_p;
};

static void printIndent(int n)
{
    while(n--)
        std::cout << '\t';
}

static std::string getTypeAsString(const ast::Type& type, bool printQualifiers = true, bool printModifiers = true, bool printBaseType = true, bool printDimensions = true) {
    std::string str;

    if (printQualifiers) {
        for (auto q : type.qualifiers) {
            using TypeQualifier = ast::TypeQualifier;
            
            switch(q) {
                case TypeQualifier::Const: str += "const "; break;
            }
        }
    }

    if (printModifiers) {
        for (auto m : type.modifiers) {
            using TypeModifier = ast::TypeModifier;

            switch(m) {
                case TypeModifier::Signed: str += "signed "; break;
                case TypeModifier::Unsigned: str += "unsigned "; break;
            }
        }
    }
    
    if (printBaseType) {
        switch(type.base) {
            using BaseType = ast::BaseType;

            case BaseType::Void: str += "void"; break;
            case BaseType::Bool: str += "bool"; break;
            case BaseType::Char: str += "char"; break;
            case BaseType::Int: str += "int"; break;
            case BaseType::Float: str += "float"; break;
            default:
                ASSERT(0 && "unexpected type");
        }
    }

    if (printDimensions) {
        if (!type.dimensions.empty()) {
            for (auto d : type.dimensions) {
                str += "[";
                str += d;
                str += "]";
            }
        }
    }

    return str;
}

PrettyPrintVisitor::PrettyPrintVisitor() : indent(0) { }

void PrettyPrintVisitor::visit(const ast::TranslationUnit& node) {
    for (auto& child : node.getGlobalDeclarations())
        child->accept(*this);
}

void PrettyPrintVisitor::visit(const ast::FormalParameter& param) {
    std::cout << getTypeAsString(param.getType(), true, true, true, false) << ' ';
    std::cout << param.getID();
    for (auto& dimExpr : param.getDimExprs()) {
        std::cout << '[';
        if (dimExpr)
            dimExpr->accept(*this);
        std::cout << ']';
    }
}

void PrettyPrintVisitor::visit(const ast::Prototype& proto) {
    if (proto.isExternal())
        std::cout << "extern ";
    std::cout << getTypeAsString(proto.getReturnType()) << ' ';
    std::cout << proto.getID();
    std::cout << '(';
    const auto& params = proto.getFormals();
    for (int i = 0; i < params.size(); i++) {
        params[i]->accept(*this);
        if (i < params.size() - 1)
            std::cout << ", ";
    }
    std::cout << ')';
}

void PrettyPrintVisitor::visit(const ast::FunctionDeclaration& decl) {
    decl.getPrototype()->accept(*this);
    std::cout << ";\n";
}

void PrettyPrintVisitor::visit(const ast::FunctionDefinition& decl) {
    decl.getPrototype()->accept(*this);
    std::cout << '\n';
    decl.getBody()->accept(*this);
}

void PrettyPrintVisitor::visit(const ast::VariableDeclarationList& node) {
    printIndent(indent);
    auto varDecls = node.getVariableDeclarations();
    std::cout << getTypeAsString(varDecls[0]->getType(), true, true, true, false) << " ";
    for (int i = 0; i < varDecls.size(); i++)
    {
        varDecls[i]->accept(*this);
        if (i < varDecls.size() - 1)
            std::cout << ", ";
    }
    std::cout << ';' << '\n';
}

void PrettyPrintVisitor::visit(const ast::VariableDeclaration& node) {
    std::cout << node.getID();
    for (auto e : node.getDimExprs()) {
        std::cout << '[';
        if (e)
            e->accept(*this);
        std::cout << ']';
    }

    auto initExpr = node.getInitExpr();
    if (initExpr) {
        std::cout << " = ";
        initExpr->accept(*this);
    }
}

void PrettyPrintVisitor::visit(const ast::CompoundStatement& cstmt) {
    printIndent(indent);
    std::cout << '{';
    {
        IndentTracker itracker(indent);

        const auto& stmts = cstmt.getStatementList();
        std::cout << '\n';

        for (int i = 0; i < stmts.size(); i++) {
            stmts[i]->accept(*this);
            if (i < stmts.size() - 1)
                std::cout << '\n';
        }

        if (stmts.size() == 0)
            std::cout << ' ';
        std::cout << '\n';
    }
    printIndent(indent);
    std::cout << '}';
}

void PrettyPrintVisitor::visit(const ast::ExpressionStatement& stmt) {
    printIndent(indent);
    stmt.getExpr()->accept(*this);
    std::cout << ';';
}

void PrettyPrintVisitor::visit(const ast::EmptyStatement&) { std::cout << ';'; }

void PrettyPrintVisitor::visit(const ast::IfStatement& stmt) {
    printIndent(indent);
    std::cout << "if (";
    stmt.getCondExpr()->accept(*this);
    std::cout << ')';

    auto ifBody = stmt.getIfBody();
    std::cout << '\n';
    if (dynamic_cast<ast::CompoundStatement*>(ifBody.get()) == nullptr) {
        // single statement if
        IndentTracker itracker(indent);
        ifBody->accept(*this);
    } else {
        ifBody->accept(*this);
    }

    auto elseBody = stmt.getElseBody();
    if (elseBody)
    {
        std::cout << "\n";
        printIndent(indent);
        std::cout << "else\n";
        if (dynamic_cast<ast::CompoundStatement*>(elseBody.get()) == nullptr) {
            // single statement else
            IndentTracker itracker(indent);
            elseBody->accept(*this);
        } else {
            elseBody->accept(*this);
        }
    }
}

void PrettyPrintVisitor::visit(const ast::ForStatement& stmt) {
    printIndent(indent);
    std::cout << "for (";
    stmt.getInitStmt()->accept(*this);
    std::cout << " ";
    stmt.getCondStmt()->accept(*this);
    std::cout << " ";
    if (stmt.getIterExpr())
        stmt.getIterExpr()->accept(*this);
    std::cout << ")\n";
    printIndent(indent);
    auto forBody = stmt.getBody();
    if (dynamic_cast<ast::CompoundStatement*>(forBody.get()) == nullptr) {
        // single statement for
        IndentTracker itracker(indent);
        forBody->accept(*this);
    } else {
        forBody->accept(*this);
    }
}

void PrettyPrintVisitor::visit(const ast::WhileStatement& stmt) {
    printIndent(indent);
    std::cout << "while (";
    stmt.getCondExpr()->accept(*this);
    std::cout << ")\n";
    stmt.getBody()->accept(*this);
}

void PrettyPrintVisitor::visit(const ast::ReturnStatement& stmt) {
    printIndent(indent);
    std::cout << "return";
    if (stmt.getExpr()) {
        std::cout << ' ';
        stmt.getExpr()->accept(*this);
        std::cout << ';';
    }
}

void PrettyPrintVisitor::visit(const ast::ContinueStatement& stmt) {
    printIndent(indent);
    std::cout << "continue;";
}

void PrettyPrintVisitor::visit(const ast::BreakStatement& stmt) {
    printIndent(indent);
    std::cout << "break;";
}

void PrettyPrintVisitor::visit(const ast::ExpressionList& exprlist) {
    const auto& exprs = exprlist.getExprs();
    for (int i = 0; i < exprs.size(); i++) {
        exprs[i]->accept(*this);
        if (i < exprs.size() - 1)
            std::cout << ", ";
    }
}

void PrettyPrintVisitor::visit(const ast::TernaryOpExpression& node) {
    std::cout << '(';
    node.getLHS()->accept(*this);
    std::cout << " ? ";
    node.getMiddle()->accept(*this);
    std::cout << " : ";
    node.getRHS()->accept(*this);
    std::cout << ')';
}

void PrettyPrintVisitor::visit(const ast::BinaryOpExpression& node) {
    auto getTextFromBinaryOp = [] (ast::BinaryOp op)->std::string {
        switch(op) {
            case ast::BinaryOp::Mul: return "*";
            case ast::BinaryOp::Div: return "/";
            case ast::BinaryOp::Rem: return "%";
            case ast::BinaryOp::Add: return "+";
            case ast::BinaryOp::Sub: return "-";
            case ast::BinaryOp::LessThan: return "<";
            case ast::BinaryOp::GreaterThan: return ">";
            case ast::BinaryOp::LessThanEqual: return "<=";
            case ast::BinaryOp::GreaterThanEqual: return ">=";
            case ast::BinaryOp::Equal: return "==";
            case ast::BinaryOp::NotEqual: return "!=";
            case ast::BinaryOp::LogicalAnd: return "&&";
            case ast::BinaryOp::LogicalOr: return "||";
            case ast::BinaryOp::Assign: return "=";
            case ast::BinaryOp::MulAssign: return "*=";
            case ast::BinaryOp::DivAssign: return "/=";
            case ast::BinaryOp::RemAssign: return "%=";
            case ast::BinaryOp::AddAssign: return "+=";
            case ast::BinaryOp::SubAssign: return "-=";
        }
        return "UNKNOWN";
    };

    std::cout << '(';
    node.getLHS()->accept(*this);
    std::cout << ' ' << getTextFromBinaryOp(node.getOp()) << ' ';
    node.getRHS()->accept(*this);
    std::cout << ')';
}

void PrettyPrintVisitor::visit(const ast::PrefixUnaryOpExpression& node) {
    auto getTextFromUnaryOp = [] (ast::UnaryOp op)->std::string {
        switch(op) {
            case ast::UnaryOp::Increment: return "++";
            case ast::UnaryOp::Decrement: return "--";
            case ast::UnaryOp::Plus: return "+";
            case ast::UnaryOp::Minus: return "-";
            case ast::UnaryOp::LogicalNot: return "!";
        }
        return "UNKNOWN";
    };

    std::cout << getTextFromUnaryOp(node.getOp());
    node.getExpr()->accept(*this);
}

void PrettyPrintVisitor::visit(const ast::PostfixUnaryOpExpression& node) {
    auto getTextFromUnaryOp = [] (ast::UnaryOp op)->std::string {
        switch(op) {
            case ast::UnaryOp::Increment: return "++";
            case ast::UnaryOp::Decrement: return "--";
        }
        return "UNKNOWN";
    };

    node.getExpr()->accept(*this);
    std::cout << getTextFromUnaryOp(node.getOp());
}

void PrettyPrintVisitor::visit(const ast::ArraySubscriptExpression& expr) {
    expr.getLocationExpr()->accept(*this);
    std::cout << '[';
    expr.getSubscriptExpr()->accept(*this);
    std::cout << ']';
}

void PrettyPrintVisitor::visit(const ast::CallExpression& callexpr) {
    callexpr.getCallee()->accept(*this);
    std::cout << '(';
    const auto& args = callexpr.getArgs();
    for (int i = 0; i < args.size(); i++) {
        args[i]->accept(*this);
        if (i < args.size() - 1)
            std::cout << ", ";
    }
    std::cout << ')';
}

void PrettyPrintVisitor::visit(const ast::CastExpression& cexpr) {
    std::cout << "static_cast<" << getTypeAsString(cexpr.getType()) << ">(";
    cexpr.getExpr()->accept(*this);
    std::cout << ')';
}

void PrettyPrintVisitor::visit(const ast::IDExpression& idexpr) { std::cout << idexpr.getID(); }

void PrettyPrintVisitor::visit(const ast::BooleanLiteral& blit) { std::cout << (blit.getValue() ? "true" : "false"); }
void PrettyPrintVisitor::visit(const ast::CharacterLiteral& clit) { std::cout << '\'' << clit.getValue() << '\''; }
void PrettyPrintVisitor::visit(const ast::IntegerLiteral& ilit) { std::cout << ilit.getValue(); }
void PrettyPrintVisitor::visit(const ast::FloatLiteral& flit) { std::cout << flit.getValue(); }

void PrettyPrintVisitor::visit(const ast::StringLiteral& slit) { std::cout << slit.getValue(); }
void PrettyPrintVisitor::visit(const ast::ArrayLiteral&) { ASSERT(0); }