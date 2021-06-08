#ifndef HDC_LEX_H
#define HDC_LEX_H

#include <string>
#include <stack>

#include "lex/lex_state.h"
#include "token/token.h"

namespace hdc {
    class Lex {
        public:
            Lex();

        public:
            void read(const char* path);
            Token get_token();

            void reset_state();
            void save_state();
            void restore_state();

        private:
            bool has_next();
            void advance();
            bool lookahead(char c);

            bool is_alpha();
            bool is_digit();
            bool is_operator();
            bool is_whitespace();

            void skip_whitespace();
            void skip_comment();

            Token get_indentation();
            Token get_keyword_or_identifier();
            Token get_operator();

            Token create_token(TokenKind kind);

        private:
            std::string buffer;
            LexState state;
            std::stack<LexState> state_stack;
    };
}

#endif
