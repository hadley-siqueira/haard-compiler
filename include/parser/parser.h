#ifndef HDC_PARSER_H
#define HDC_PARSER_H

#include "ast/ast.h"
#include "scanner/scanner.h"

namespace hdc {
    class Parser {
        public:
            AST* read(const char* path);

        private:
            AST* parse_import();

            void advance();
            bool lookahead(TokenKind kind);
            bool match(TokenKind kind);
            void expect(TokenKind kind);

        private:
            Scanner scanner;
            Token current_token;
            Token matched_token;
    };
}

#endif
