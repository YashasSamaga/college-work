#ifndef MINIC_COMPILER_AST_IDENTIFIER_H
#define MINIC_COMPILER_AST_IDENTIFIER_H

#include <string>
#include <string_view>
#include <utility>
#include <ostream>

namespace ast {
    class Identifier {
    public:
        Identifier(std::string id) : id(std::move(id)) { }
    
        const auto& str() const { return id; }
        auto& str() { return id; }

        operator bool() const { return !id.empty(); }
        operator std::string() const { return id; }
        operator std::string_view() const { return id; }

    private:
        std::string id;
    
        friend inline std::ostream &operator<<(std::ostream&, const Identifier&);
    };

    inline std::ostream &operator<<(std::ostream& os, const Identifier& id) {
        os << id.id;
        return os;
    }

}

#endif /* ifndef MINIC_COMPILER_AST_IDENTIFIER_H */