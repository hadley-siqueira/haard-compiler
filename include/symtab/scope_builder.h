#ifndef HDC_SCOPE_BUILDER_H
#define HDC_SCOPE_BUILDER_H

#include "scope.h"
#include "ast/program.h"
#include "ast/source_file.h"
#include "ast/class.h"
#include "ast/function.h"
#include "ast/expression.h"
#include "ast/binary_expression.h"
#include "ast/identifier.h"

namespace hdc {
    class ScopeBuilder {
        public:
            void visit(ast::Program* program);

        private:
            void visit(ast::SourceFile* source_file);
            void visit(ast::Function* function);
            void visit(ast::CompoundStatement* statements);
            void visit(ast::Statement* statement);
            void visit(ast::Expression* expr);
            void visit(ast::BinaryExpression* bin);
            void visit(ast::Identifier* id);

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
    };
}

#endif
