#ifndef HDC_SCOPE_BUILDER_H
#define HDC_SCOPE_BUILDER_H

#include "scope.h"
#include "ast/program.h"
#include "ast/source_file.h"
#include "ast/class.h"
#include "ast/function.h"

namespace hdc {
    class ScopeBuilder {
        public:
            void visit(ast::Program* program);
            void visit(ast::SourceFile* source_file);
            void visit(ast::Function* function);

        private:
            void first_pass(ast::Program* program);
            void add_classes(ast::SourceFile* source_file);
            void add_class(ast::Class* klass);
            void add_functions(ast::SourceFile* source_file);
            void add_function(ast::Function* function);
            void add_parameters(ast::Function* function);

            void define_symbol(SymbolKind kind, std::string name, void* descriptor);

        private:
            Scope* current_scope;
    };
}

#endif
