#ifndef MINIC_COMPILER_AST_SYMBOL_TABLE_H
#define MINIC_COMPILER_AST_SYMBOL_TABLE_H

#include "assertions.h"

#include <unordered_map>
#include <utility>
#include <vector>

namespace ast {
    enum class SymbolType {
        FunctionDeclaration,
        FunctionDefinition,
        FormalParameter,
        Variable
    };

    class SymbolEntry {
    public:
        SymbolEntry() { } // TODO remove this
        SymbolEntry(SymbolType type, ASTBase& node)
            : type(type), node(&node) { }

        auto getType() const { return type; }

        const auto& getNode() const { return *node; }
        auto& getNode() { return *node; }

        template <class T>
        const auto& getNodeAs() const {
            auto ptr = dynamic_cast<T*>(node);
            ASSERT(ptr);
            return *ptr;
        }

        template <class T>
        auto& getNodeAs() {
            auto ptr = dynamic_cast<T*>(node);
            ASSERT(ptr);
            return *ptr;
        }

    private:
        SymbolType type;
        ASTBase* node;
    };

    enum class ScopeType {
        Global,
        Function,
        Compound,
        For
    };

    enum class LookupMode {
        Global,
        BottomUp,
        CurrentScope,
    };

    class Scope {
    public:
        Scope(ScopeType type) : type(type) { }

        auto getType() { return type; }

        void add(const std::string& id, SymbolEntry entry) {
            table.emplace(id, std::move(entry)); // TODO do witout requring default constructor
        }

        template <class ...Args>
        void emplace(const std::string& id, Args&& ...args) {
            table.emplace(id, SymbolEntry(std::forward<Args>(args)...));
        }

        bool exists(const std::string& id) {
            return table.count(id);
        }

        SymbolEntry* lookup(const std::string& id) {
            auto itr = table.find(id);
            if (itr != table.end())
                return &itr->second; // std::unordered_map will noot invalidate references or pointers to elements
            return nullptr;
        }

        std::vector<SymbolEntry*> lookupAll(const std::string& id) {
            std::vector<SymbolEntry*> entries;
            auto [itr, end] = table.equal_range(id);
            while(itr != end) {
                entries.push_back(&itr->second);
                ++itr;
            }
            return entries;
        }

    private:
        ScopeType type;
        std::unordered_multimap<std::string, SymbolEntry> table;
    };

    class SymbolTable {
    public:
        SymbolTable() { scopes.emplace_back(ScopeType::Global); }

        void addScope(ScopeType type) {
            ASSERT(type != ScopeType::Global);
            scopes.emplace_back(type);
        }

        void removeScope() {
            ASSERT(scopes.size() > 1); // cannot remove global scope
            scopes.pop_back();
        }

        void addSymbol(const std::string& id, SymbolEntry entry) {
            ASSERT(scopes.size());
            scopes.back().add(id, std::move(entry));
        }

        template <class ...Args>
        void emplaceSymbol(const std::string& id, Args&& ...args) {
            ASSERT(scopes.size());
            scopes.back().emplace(id, std::forward<Args>(args)...);
        }

        Scope& getFirstScope() {
            ASSERT(scopes.size());
            return scopes.front();
        }

        Scope& getCurrentScope() {
            ASSERT(scopes.size());
            return scopes.back();
        }

        std::size_t numScopes() const { return scopes.size(); }
        
        SymbolEntry* lookup(const std::string& id, LookupMode mode) {
            ASSERT(scopes.size());
            switch(mode) {
                case LookupMode::Global: return scopes.front().lookup(id);
                case LookupMode::CurrentScope: return scopes.back().lookup(id);
                case LookupMode::BottomUp:
                    for (auto itr = std::rbegin(scopes); itr != std::rend(scopes); itr++)
                        if (auto sym = itr->lookup(id))
                            return sym;
                    return nullptr;
            }
            return nullptr;
        }

        std::vector<SymbolEntry*> lookupAll(const std::string& id, LookupMode mode) {
            ASSERT(scopes.size());
            switch(mode) {
                case LookupMode::Global: return scopes.front().lookupAll(id);
                case LookupMode::CurrentScope: return scopes.back().lookupAll(id);
                case LookupMode::BottomUp:
                {   
                    std::vector<SymbolEntry*> entries;
                    for (auto itr = std::rbegin(scopes); itr != std::rend(scopes); itr++) {
                        auto new_entries = itr->lookupAll(id);
                        entries.insert(
                            std::end(entries),
                            std::make_move_iterator(std::begin(new_entries)),
                            std::make_move_iterator(std::end(new_entries))
                        );
                    }
                    return entries;
                }
            }
            return {};
        }

        bool exists(const std::string& id, LookupMode mode) {
            return lookup(id, mode) != nullptr;
        }

    private:
        std::vector<Scope> scopes;
    };

    class ScopeEnter {
    public:
        ScopeEnter(ScopeType type, SymbolTable& table)
            : table(table)
        {
            table.addScope(type);
        }

        ~ScopeEnter() {
            table.removeScope();
        }

        ScopeEnter(ScopeEnter&) = delete;
        ScopeEnter(ScopeEnter&&) = delete;

        ScopeEnter& operator=(ScopeEnter&) = delete;
        ScopeEnter& operator=(ScopeEnter&&) = delete;

    private:
        SymbolTable& table; 
    };
}

#endif /* ifndef MINIC_COMPILER_AST_SYMBOL_TABLE_H */