#ifndef MINIC_COMPILER_AST_TYPES_H
#define MINIC_COMPILER_AST_TYPES_H

#include "AST/operators.h"
#include "assertions.h"

#include <vector>
#include <set> 
#include <optional>
#include <utility>
#include <cstddef>

namespace ast {
    enum class TypeModifier {
        Signed,
        Unsigned
    };

    enum class TypeQualifier {
        Const
    };

    enum class BaseType {
        Void,
        Bool,
        Char,
        Int,
        Float
    };

    // TODO function types
    class Type {
    public:
        Type() : base(BaseType::Void) { }
        Type(BaseType base) : base(base) { }
        Type(BaseType base, std::vector<std::size_t> dimensions) : base(base), dimensions(std::move(dimensions)) { } 
        Type(BaseType base, std::set<TypeModifier> modifiers, std::set<TypeQualifier> qualifiers)
            : base(base), modifiers(std::move(modifiers)), qualifiers(std::move(qualifiers)) { }

        bool isArray() const { return dimensions.size(); }
        bool isSigned() const {
            return modifiers.count(TypeModifier::Signed) || modifiers.count(TypeModifier::Unsigned) == 0;
        }

        std::set<TypeModifier> modifiers; //  TODO static_vector?
        std::set<TypeQualifier> qualifiers; // TODO static_vector?

        BaseType base;
        std::vector<std::size_t> dimensions; // unknown initially; filled later

        friend bool operator==(const Type& a, const Type& b) {
            return a.base == b.base &&
                   a.modifiers == b.modifiers &&
                   a.qualifiers == b.qualifiers  &&
                   a.dimensions == b.dimensions;
        }

        friend bool operator!=(const Type& a, const Type& b) {
            return !(a == b);
        }
    };

    inline bool areCompatibleTypes(BinaryOp op, const Type& lhs, const Type& rhs) {
        if (lhs.isArray() || rhs.isArray())
            return false;

        if (op == BinaryOp::Rem) {
            if (lhs.base == BaseType::Float || rhs.base == BaseType::Float) {
                return false;
            }
        }

        return true;
    }

    inline Type GetCombinedType(BinaryOp op, const Type& lhs, const Type& rhs) {
        const auto getTypeRank = [](BaseType type)->int {
            switch(type) {
            case BaseType::Void: return 0;
            case BaseType::Bool: return 1;
            case BaseType::Char: return 2;
            case BaseType::Int: return 3;
            case BaseType::Float: return 4;
            default:
                ASSERT(0);
                break;
            }
        };

        const auto getBaseTypeFromRank = [](int rank) {
            switch(rank) {
                case 0: return BaseType::Void;
                case 1: return BaseType::Bool;
                case 2: return BaseType::Char;
                case 3: return BaseType::Int;
                case 4: return BaseType::Float;
                default:
                    ASSERT(0);
                    break;
            }
        };

        switch (op) {
        case BinaryOp::Mul:
        case BinaryOp::Div:
        case BinaryOp::Rem:
        case BinaryOp::Add:
        case BinaryOp::Sub:
        case BinaryOp::LessThan:
        case BinaryOp::GreaterThan:
        case BinaryOp::LessThanEqual:
        case BinaryOp::GreaterThanEqual:
        case BinaryOp::Equal:
        case BinaryOp::NotEqual:
        {
            int promotion_rank = std::max(getTypeRank(lhs.base), getTypeRank(rhs.base));
            return Type(getBaseTypeFromRank(promotion_rank));
        }
        case BinaryOp::LogicalAnd:
        case BinaryOp::LogicalOr:
            return Type(BaseType::Bool);
        case BinaryOp::Assign:
        case BinaryOp::MulAssign:
        case BinaryOp::DivAssign:
        case BinaryOp::RemAssign:
        case BinaryOp::AddAssign:
        case BinaryOp::SubAssign:
            ASSERT(lhs.qualifiers.count(TypeQualifier::Const) == 0);
            return lhs;
        }

        // CHECK MODIFIERS & QUALIFIERS TODO
        ASSERT(0);
        return lhs;
    }

    inline bool isConvertibleOrSame(const Type& a, const Type& b) {
        if (a.dimensions.size() != b.dimensions.size())
            return false;

        for (int i =  0; i < a.dimensions.size(); i++)
            if (a.dimensions[i] != 0 && b.dimensions[i] != 0 && a.dimensions[i] != b.dimensions[i])
                return false;
        
        return true;
    }
    
    inline bool isImplicitConversionRequired(const Type& a, const Type& b) {
        if (a.base != b.base)
            return true;

        if (a.modifiers != b.modifiers)
            return true;

        return false;
    }
}

#endif /* ifndef MINIC_COMPILER_AST_TYPES_H */