#ifndef HDC_SCOPE_BUILDER_H
#define HDC_SCOPE_BUILDER_H

#include "scope.h"
#include "ast/source_file.h"
#include "ast/class.h"

namespace hdc {
    class ScopeBuilder {
        public:
            void visit(ast::SourceFile* source_file);

        private:
            void add_classes(ast::SourceFile* source_file);
            void add_class(ast::Class* klass);

        private:
            Scope* current_scope;
    };
}

#endif
