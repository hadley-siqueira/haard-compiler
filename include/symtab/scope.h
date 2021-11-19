#ifndef HDC_SCOPE_H
#define HDC_SCOPE_H

#include <map>

#include "symbol.h"

namespace hdc {
    class Scope {
        public:
            Scope();

        public:
            Symbol* resolve(std::string& name);
            void define(Symbol* symbol);
            Scope* get_enclosing_scope();
            
        private:
            std::map<std::string, Symbol*> symbols;
            Scope* enclosing_scope;
    };
}

#endif