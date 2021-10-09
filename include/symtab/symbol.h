#ifndef HDC_SYMBOL_H
#define HDC_SYMBOL_H

#include "defs.h"

namespace hdc {
    class Symbol {
        public:
            Symbol();

        public:
            void set_name(std::string name);
            void set_descriptor(void* descriptor);
            void set_kind(SymbolKind kind);

            std::string get_name();
            void* get_descriptor();
            SymbolKind get_kind();

        private:
            std::string name;
            SymbolKind kind;
            void* descriptor;
    };
}

#endif
