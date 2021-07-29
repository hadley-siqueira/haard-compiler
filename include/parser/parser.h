#ifndef HDC_PARSER_H
#define HDC_PARSER_H

#include "scanner/scanner.h"

#include "ast/ast.h"
#include "ast/ast_node.h"
#include "ast/import.h"

namespace hdc {
    using namespace ast;

    class Parser {
        public:
            AST* read(const char* path);

        private:
            AST* parse_sourcefile();
            Import* parse_import();
            AST* parse_def();
            AST* parse_parameters();
            AST* parse_type();
            AST* parse_statements();

            bool has_parameters();

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
