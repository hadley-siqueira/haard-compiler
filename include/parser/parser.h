#ifndef HDC_PARSER_H
#define HDC_PARSER_H

#include "scanner/scanner.h"

#include "ast/ast.h"
#include "ast/ast_node.h"
#include "ast/source_file.h"
#include "ast/import.h"
#include "ast/function.h"
#include "ast/type.h"
#include "ast/named_type.h"
#include "ast/indirection_type.h"
#include "ast/template_list.h"

#include "ast/statement.h"
#include "ast/compound_statement.h"
#include "ast/while_statement.h"
#include "ast/if_statement.h"
#include "ast/elif_statement.h"
#include "ast/else_statement.h"

#include "ast/identifier.h"
#include "ast/literal_expression.h"
#include "ast/binary_expression.h"
#include "ast/unary_expression.h"
#include "ast/expression_list.h"

namespace hdc {
    using namespace ast;

    class Parser {
        public:
            SourceFile* read(const char* path);

        private:
            SourceFile* parse_sourcefile();
            Import* parse_import();
            Class* parse_class();
            Function* parse_function();
            Method* parse_method();
            Variable* parse_class_variable();
            void parse_parameters(Function* function);
            Type* parse_type();
            Identifier* parse_identifier();
            TemplateList* parse_template_list();
            ExpressionList* parse_argument_list();
            Expression* parse_primary_expression();
            Expression* parse_postfix_expression();
            Expression* parse_unary_expression();
            Expression* parse_arith_expression();
            Expression* parse_assignment_expression();
            Expression* parse_expression();

            Statement* parse_statement();
            CompoundStatement* parse_statements();
            Statement* parse_for_statement();
            Statement* parse_while_statement();
            Statement* parse_if_statement();
            Statement* parse_elif_statement();
            Statement* parse_else_statement();
            Statement* parse_return_statement();
            Statement* parse_variable_statement();

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
