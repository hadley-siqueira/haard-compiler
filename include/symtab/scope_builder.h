#ifndef HDC_SCOPE_BUILDER_H
#define HDC_SCOPE_BUILDER_H

#include "scope.h"

#include "ast/ast_node.h"
#include "ast/program.h"
#include "ast/source_file.h"
#include "ast/class.h"
#include "ast/function.h"

#include "ast/if_statement.h"
#include "ast/elif_statement.h"
#include "ast/else_statement.h"
#include "ast/while_statement.h"
#include "ast/expression_statement.h"

#include "ast/expression.h"
#include "ast/identifier.h"
#include "ast/literal_expression.h"
#include "ast/expression_list.h"
#include "ast/unary_expression.h"
#include "ast/binary_expression.h"

namespace hdc {
    class ScopeBuilder {
        public:
            void visit(ast::AstNode* node);

        private:
            void visit_program(ast::Program* program);
            void visit_source_file(ast::SourceFile* source_file);

            void visit_function(ast::Function* function);

            // statements
            void visit_compound_statement(ast::CompoundStatement* statements);
            void visit_if_statement(ast::IfStatement* stmt);
            void visit_elif_statement(ast::ElifStatement* stmt);
            void visit_else_statement(ast::ElseStatement* stmt);
            void visit_while_statement(ast::WhileStatement* stmt);
            void visit_expression_statement(ast::ExpressionStatement* stmt);

            // expressions
            void visit_identifier(ast::Identifier* id);
            void visit_literal_integer(ast::LiteralExpression* literal);
            void visit_expression_list(ast::ExpressionList* list);

            void visit_call(ast::BinaryExpression* call);

            void visit_times(ast::BinaryExpression* bin);
            void visit_division(ast::BinaryExpression* bin);
            void visit_integer_division(ast::BinaryExpression* bin);
            void visit_modulo(ast::BinaryExpression* bin);
            void visit_power(ast::BinaryExpression* bin);

            void visit_plus(ast::BinaryExpression* bin);
            void visit_minus(ast::BinaryExpression* bin);

            void visit_lt(ast::BinaryExpression* bin);

            void visit_assignment(ast::BinaryExpression* bin);

        private:
            void visit_binop(ast::BinaryExpression* bin);
            void create_new_variable(ast::Identifier* id);

        private:
            void first_pass(ast::Program* program);
            void second_pass(ast::Program* program);
            void add_classes(ast::SourceFile* source_file);
            void add_class(ast::Class* klass);
            void add_functions(ast::SourceFile* source_file);
            void add_function(ast::Function* function);
            void add_parameters(ast::Function* function);

            void define_symbol(SymbolKind kind, std::string name, void* descriptor);

        private:
            Scope* current_scope;
            ast::Function* current_function;
            int function_id_counter;
            int class_id_counter;
    };
}

#endif
