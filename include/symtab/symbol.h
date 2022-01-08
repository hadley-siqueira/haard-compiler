#ifndef HDC_SYMBOL_H
#define HDC_SYMBOL_H

#include "defs.h"
#include "ast/type.h"

namespace hdc {
    class Symbol {
        public:
            Symbol();
            Symbol(SymbolKind kind, std::string name, void* descriptor);

        public:
            void set_name(std::string name);
            void set_descriptor(void* descriptor);
            void set_kind(SymbolKind kind);

            std::string get_name();
            void* get_descriptor();
            SymbolKind get_kind();
            std::string get_unique_id();
            class Scope* get_scope();
            ast::Type* get_type();
            void set_scope(class Scope* scope);

        private:
            std::string name;
            SymbolKind kind;
            void* descriptor;
            class Scope* scope;
    };
}

#endif
