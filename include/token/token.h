#ifndef HDC_TOKEN_H
#define HDC_TOKEN_H

#include "defs.h"

namespace hdc {
    class Token {
        public:
            /* Setters */
            void set_kind(TokenKind kind);
            void set_line(int line);
            void set_column(int column);
            void set_value(char* value);

            /* Getters */
            TokenKind get_kind();
            int get_line();
            int get_column();
            char* get_value();

        private:
            TokenKind kind;
            int line;
            int column;
            char* value;
    };
}

#endif
