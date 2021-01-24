#ifndef MINIC_COMPILER_AST_MEMORY_UTILS_H
#define MINIC_COMPILER_AST_MEMORY_UTILS_H

#include "assertions.h"

template <class To, class From>
bool is_dynamic_type(const From& ptr) {
    ASSERT(ptr);
    return dynamic_cast<To*>(ptr.get());
}

#endif /* MINIC_COMPILER_AST_MEMORY_UTILS_H */