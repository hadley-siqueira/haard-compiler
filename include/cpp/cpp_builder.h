#ifndef HDC_CPP_BUILDER_H
#define HDC_CPP_BUILDER_H

#include <sstream>
#include <map>

#include "ast/program.h"
#include "ast/source_file.h"
#include "ast/function.h"
#include "ast/compound_statement.h"
#include "ast/expression.h"
#include "ast/binary_expression.h"
#include "ast/unary_expression.h"
#include "ast/literal_expression.h"
#include "ast/expression_list.h"
#include "ast/identifier.h"
#include "ast/type.h"

#include "ast/if_statement.h"
#include "ast/elif_statement.h"
#include "ast/else_statement.h"

namespace hdc {
    class CppBuilder {
        public:
            CppBuilder();

        public:
            void build(ast::Program* program);
            std::string get_output();

        private:
            void generate_prototypes(ast::Program* program);
            void generate_prototypes(ast::SourceFile* sf);

            void generate_prototype(ast::Function* f);
            void generate_symbols();

            void build_source_file(ast::SourceFile* sf);
            void build_function(ast::Function* f);
            void build_statements(ast::CompoundStatement* stmts);
            void build_statement(ast::Statement* stmt);
            void build_expression(ast::Expression* expr);
            void build_binop(const char* op, ast::BinaryExpression* expr);
            void build_unop(const char* op, ast::UnaryExpression* expr);
            void build_sizeof(ast::UnaryExpression* expr);
            void build_type(ast::Type* type);

            // statements
            void build_if(ast::IfStatement* stmt);
            void build_elif(ast::ElifStatement* stmt);
            void build_else(ast::ElseStatement* stmt);

            void build_dot(ast::BinaryExpression* expr);
            void build_call(ast::BinaryExpression* expr);

            void build_literal(ast::LiteralExpression* expr);
            void build_symbol(ast::LiteralExpression* expr);
            void build_identifier(ast::Identifier* expr);

            void indent();

        private:
            std::stringstream output;
            std::map<std::string, int> symbol_map;
            int indent_count;
            int symbol_count;
    };
}

#endif
