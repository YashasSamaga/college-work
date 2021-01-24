#ifndef MINIC_COMPILER_AST_OPERATORS_H
#define MINIC_COMPILER_AST_OPERATORS_H

#include "third-party/magic_enum.hpp"

#include "assertions.h"

#include <optional>
#include <string>
#include <unordered_map>

namespace ast {
    enum class UnaryOp {
        Increment,
        Decrement,
        Plus,
        Minus,
        LogicalNot
    };

    enum class BinaryOp {
        Mul,
        Div,
        Rem,
        Add,
        Sub,
        LessThan,
        GreaterThan,
        LessThanEqual,
        GreaterThanEqual,
        Equal,
        NotEqual,
        LogicalAnd,
        LogicalOr,
        Assign,
        MulAssign,
        DivAssign,
        RemAssign,
        AddAssign,
        SubAssign
    };

    enum class TernaryOp {
        Conditional
    };

    inline std::optional<UnaryOp> getUnaryOpFromText(const std::string& str) {
        const std::unordered_map<std::string, UnaryOp> keys = {
            {"++", UnaryOp::Increment},
            {"--", UnaryOp::Decrement},
            {"+", UnaryOp::Plus},
            {"-", UnaryOp::Minus},
            {"!", UnaryOp::LogicalNot}
        };
        ASSERT(keys.size() == magic_enum::enum_count<UnaryOp>());

        auto itr = keys.find(str);
        if (itr != keys.end())
            return itr->second;
        return {};
    }

    inline std::optional<BinaryOp> getBinaryOpFromText(const std::string& str) {
        const std::unordered_map<std::string, BinaryOp> keys = {
            {"*", BinaryOp::Mul},
            {"/", BinaryOp::Div},
            {"%", BinaryOp::Rem},
            {"+", BinaryOp::Add},
            {"-", BinaryOp::Sub},
            {"<", BinaryOp::LessThan},
            {">", BinaryOp::GreaterThan},
            {"<=", BinaryOp::LessThanEqual},
            {">=", BinaryOp::GreaterThanEqual},
            {"==", BinaryOp::Equal},
            {"!=", BinaryOp::NotEqual},
            {"&&", BinaryOp::LogicalAnd},
            {"||", BinaryOp::LogicalOr},
            {"=", BinaryOp::Assign},
            {"*=", BinaryOp::MulAssign},
            {"/=", BinaryOp::DivAssign},
            {"%=", BinaryOp::RemAssign},
            {"+=", BinaryOp::AddAssign},
            {"-=", BinaryOp::SubAssign}
        };

        ASSERT(keys.size() == magic_enum::enum_count<BinaryOp>());

        auto itr = keys.find(str);
        if (itr != keys.end())
            return itr->second;
        return {};
    }
}

#endif /* ifndef MINIC_COMPILER_AST_OPERATORS_H */