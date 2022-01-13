#ifndef HDC_CPP_BUILDER_H
#define HDC_CPP_BUILDER_H

#include <sstream>
#include <map>
#include <set>

#include "ast/ast_node.h"
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
#include "ast/indirection_type.h"
#include "ast/array_type.h"
#include "ast/named_type.h"

#include "ast/if_statement.h"
#include "ast/elif_statement.h"
#include "ast/else_statement.h"
#include "ast/while_statement.h"
#include "ast/expression_statement.h"

namespace hdc {
    class CppBuilder {
        public:
            CppBuilder();

        public:
            void visit(ast::AstNode* node);

            void build(ast::Program* program);
            std::string get_output();

        private:
            void visit_eq(ast::BinaryExpression* bin);
            void visit_return_statement(ast::ExpressionStatement* stmt);

            void generate_headers();
            void generate_symbols();
            void generate_main_function();

            void build_source_file(ast::SourceFile* sf);

            void build_function(ast::Function* f);
            void build_function_signature(ast::Function* f);
            void build_class(ast::Class* klass);
            void build_class_signature(ast::Class* klass);
            void build_class_variables(ast::Class* klass);
            void build_class_methods(ast::Class* klass);
            void build_method(ast::Method* m);
            void build_variable(ast::Variable* v);
            void build_function_variables(ast::Function* f);

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
            void build_while(ast::WhileStatement* stmt);
            void build_expression_statement(ast::ExpressionStatement* stmt);

            void build_dot(ast::BinaryExpression* expr);
            void build_call(ast::BinaryExpression* expr);

            void build_literal(ast::LiteralExpression* expr);
            void build_symbol(ast::LiteralExpression* expr);
            void build_string(ast::LiteralExpression* expr);
            void build_identifier(ast::Identifier* expr);
            void build_dolar(ast::UnaryExpression* expr);

            void indent();

            void set_output(std::stringstream& stream);

            bool source_file_visited(ast::SourceFile* sf);
            bool function_visited(ast::Function* f);
            bool class_visited(ast::Class* klass);

            void visit_source_file(ast::SourceFile* sf);
            void visit_function(ast::Function* f);
            void visit_class(ast::Class* klass);

            void set_main_function(ast::Function* f);

            void visit_array_type(ast::ArrayType* type);

        private:
            std::stringstream* output;
            std::map<std::string, int> symbol_map;
            std::stringstream symbols_stream;
            std::stringstream headers_stream;
            std::stringstream function_proto_stream;
            std::stringstream classes_proto_stream;
            std::stringstream functions_stream;
            std::stringstream classes_stream;
            std::stringstream main_function_stream;
            std::stringstream tail_stream;
            std::set<ast::Function*> visited_functions;
            std::set<ast::SourceFile*> visited_source_files;
            std::set<ast::Class*> visited_classes;
            ast::Function* main_function;
            int indent_count;
            int symbol_count;
    };
}

#endif
