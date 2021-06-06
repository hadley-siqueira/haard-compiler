#ifndef HDC_TOKEN_H
#define HDC_TOKEN_H

#include "defs.h"

namespace hdc {
    class Token {
        public:
            Token();
            Token(TokenKind kind, int line, int column, const char* value);

        public:
            /* Setters */
            void set_kind(TokenKind kind);
            void set_line(int line);
            void set_column(int column);
            void set_value(const char* value);

            /* Getters */
            TokenKind get_kind();
            int get_line();
            int get_column();
            const char* get_value();

        private:
            TokenKind kind;
            int line;
            int column;
            const char* value;
    };
}

#endif
