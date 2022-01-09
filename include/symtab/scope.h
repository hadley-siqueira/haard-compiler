#ifndef HDC_SCOPE_H
#define HDC_SCOPE_H

#include <map>

#include "symbol.h"

namespace hdc {
    class Scope {
        public:
            Scope();
            ~Scope();

        public:
            Symbol* resolve(std::string& name, bool recursive=true);
            void define(Symbol* symbol);
            Scope* get_enclosing_scope();
            void set_enclosing_scope(Scope* scope);
            void debug();
            void add_sibling(Scope* scope);
            void set_name(std::string name);
            std::string get_name();
            
        private:
            std::map<std::string, Symbol*> symbols;
            Scope* enclosing_scope;
            std::vector<Scope*>* siblings;
            std::string name;
    };
}

#endif
