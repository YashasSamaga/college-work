#ifndef MINIC_COMPILER_AST_TMP_UTILS_H
#define MINIC_COMPILER_AST_TMP_UTILS_H

#include <type_traits>

template <class T, class... Ts>
struct is_any : std::disjunction<std::is_same<T, Ts>...> {};

template <class T, class... Ts>
inline constexpr bool is_any_v = is_any<T, Ts...>::value;

#endif /* MINIC_COMPILER_AST_TMP_UTILS_H */