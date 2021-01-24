#ifndef MINIC_COMPILER_AST_BASE_H
#define MINIC_COMPILER_AST_BASE_H

#include "tmp_utils.h"

#include <string>

namespace ast {
    constexpr int MAX_IDENTIFIER_LENGTH = 1024; // TODO

    using BooleanType = bool;
    using CharacterType = char;
    using IntegerType = int;
    using FloatType = float;
    using StringType = std::string;

    template <class T>
    inline constexpr bool is_integral_v = is_any_v<T, CharacterType, IntegerType>;
    
    template <class T>
    inline constexpr bool is_arithmetic_v = is_any_v<T, CharacterType, IntegerType, FloatType>;
}

#endif /* ifndef MINIC_COMPILER_AST_BASE_H */