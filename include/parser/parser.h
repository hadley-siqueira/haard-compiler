#ifndef HDC_PARSER_H
#define HDC_PARSER_H

#include "scanner/scanner.h"

#include "ast/ast.h"
#include "ast/ast_node.h"
#include "ast/source_file.h"
#include "ast/import.h"
#include "ast/function.h"

namespace hdc {
    using namespace ast;

    class Parser {
        public:
            SourceFile* read(const char* path);

        private:
            SourceFile* parse_sourcefile();
            Import* parse_import();
            Function* parse_function();
            void parse_parameters(Function* function);
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
