#ifndef HDC_SCANNER_H
#define HDC_SCANNER_H

#include <string>
#include <stack>

#include "scanner/scanner_state.h"
#include "token/token.h"

namespace hdc {
    class Scanner {
        public:
            Scanner();

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

            bool is_symbol();
            bool is_alpha();
            bool is_digit();
            bool is_operator();
            bool is_whitespace();
            bool is_binary_digit();
            bool is_octal_digit();
            bool is_hexa_digit();
            bool has_base();

            void skip_whitespace();
            void skip_comment();

            Token get_indentation();
            Token get_keyword_or_identifier();
            Token get_number();
            Token get_char_or_string();
            Token get_string();
            Token get_operator();
            Token get_symbol();

            Token create_token(TokenKind kind);

        private:
            std::string buffer;
            ScannerState state;
            std::stack<ScannerState> state_stack;
    };
}

#endif
