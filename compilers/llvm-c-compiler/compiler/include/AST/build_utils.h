#ifndef MINIC_COMPILER_AST_BUILD_UTILS_H
#define MINIC_COMPILER_AST_BUILD_UTILS_H

#include "AST/treedefs.h"

// utility class that creates a derived class object but returns it as ASTBase pointer
template <class T, class ...Args>
std::shared_ptr<ast::ASTBase> make_shared_ast(Args&& ...args) {
    return std::static_pointer_cast<ast::ASTBase>(
        std::make_shared<T>(std::forward<Args>(args)...)
    ); 
}

template <class T, class ...Args>
std::shared_ptr<ast::ExpressionBase> make_shared_expr(Args&& ...args) {
    return std::static_pointer_cast<ast::ExpressionBase>(
        std::make_shared<T>(std::forward<Args>(args)...)
    ); 
}

template <class T, class ...Args>
std::shared_ptr<ast::StatementBase> make_shared_stmt(Args&& ...args) {
    return std::static_pointer_cast<ast::StatementBase>(
        std::make_shared<T>(std::forward<Args>(args)...)
    ); 
}

#endif /* ifndef MINIC_COMPILER_AST_BUILD_UTILS_H */