#ifndef HDC_LEX_H
#define HDC_LEX_H

#include <string>
#include <stack>

#include "lex/lex_state.h"

namespace hdc {
    class Lex {
        public:
            Lex();

        public:
            void read(const char* path);

            void reset_state();
            void save_state();
            void restore_state();

        private:
            bool has_next();
            void advance();

        private:
            std::string buffer;
            LexState state;
            std::stack<LexState> state_stack;
            
    };
}

#endif
