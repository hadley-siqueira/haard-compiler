#ifndef HDC_CPP_BUILDER_H
#define HDC_CPP_BUILDER_H

#include <sstream>

#include "ast/program.h"
#include "ast/source_file.h"
#include "ast/function.h"
#include "ast/compound_statement.h"
#include "ast/expression.h"
#include "ast/binary_expression.h"
#include "ast/literal_expression.h"
#include "ast/identifier.h"

namespace hdc {
    class CppBuilder {
        public:
            void build(ast::Program* program);
            std::string get_output();

        private:
            void generate_prototypes(ast::Program* program);
            void generate_prototypes(ast::SourceFile* sf);

            void generate_prototype(ast::Function* f);

            void build_source_file(ast::SourceFile* sf);
            void build_function(ast::Function* f);
            void build_statements(ast::CompoundStatement* stmts);
            void build_statement(ast::Statement* stmt);
            void build_expression(ast::Expression* expr);
            void build_binop(const char* op, ast::BinaryExpression* expr);
            void build_literal(ast::LiteralExpression* expr);
            void build_identifier(ast::Identifier* expr);

            void indent();

        private:
            std::stringstream output;
            int indent_count;
    };
}

#endif
