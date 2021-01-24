#ifndef MINIC_COMPILER_CODEGEN_ALLOCA_TABLE_H
#define MINIC_COMPILER_CODEGEN_ALLOCA_TABLE_H

#include "assertions.h"

#include "llvm/IR/Instructions.h"

#include <unordered_map>

namespace codegen {

    class Scope {
    public:
        Scope() { }

        void add(const std::string& id, llvm::AllocaInst* entry) { table.emplace(id, entry); }
        bool exists(const std::string& id) { return table.count(id); }

        llvm::AllocaInst* lookup(const std::string& id) {
            auto itr = table.find(id);
            if (itr != table.end())
                return itr->second; // std::unordered_map will noot invalidate references or pointers to elements
            return nullptr;
        }

    private:
        std::unordered_map<std::string, llvm::AllocaInst*> table;
    };

    class AllocaTable {
    public:
        void addScope() { scopes.push_back({}); }
        void removeScope() { scopes.pop_back(); }

        void addAlloca(const std::string& id, llvm::AllocaInst* entry) {
            ASSERT(scopes.size());
            scopes.back().add(id, entry);
        }
        
        llvm::AllocaInst* lookup(const std::string& id) {
            ASSERT(scopes.size());
            for (auto itr = std::rbegin(scopes); itr != std::rend(scopes); itr++)
                if (auto sym = itr->lookup(id))
                    return sym;
            return nullptr;
        }

        bool exists(const std::string& id) {
            ASSERT(scopes.size());
            for (auto itr = std::rbegin(scopes); itr != std::rend(scopes); itr++)
                if (itr->exists(id))
                    return true;
            return false;
        }

        std::size_t numScopes() { return scopes.size(); }

    private:
        std::vector<Scope> scopes;
    };

    class ScopeEnter {
    public:
        ScopeEnter(AllocaTable& table) : table(table) { table.addScope(); }
        ~ScopeEnter() { table.removeScope(); }

        ScopeEnter(ScopeEnter&) = delete;
        ScopeEnter(ScopeEnter&&) = delete;

        ScopeEnter& operator=(ScopeEnter&) = delete;
        ScopeEnter& operator=(ScopeEnter&&) = delete;

    private:
        AllocaTable& table; 
    };
}

#endif /* ifndef MINIC_COMPILER_CODEGEN_ALLOCA_TABLE_H */