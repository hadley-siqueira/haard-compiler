#ifndef HDC_AST_TEMPLATE_LIST_H
#define HDC_AST_TEMPLATE_LIST_H

#include <vector>

#include "token/token.h"
#include "ast_node.h"
#include "type.h"

namespace hdc {
    namespace ast {
        class TemplateList : public AstNode {
            public:
                TemplateList();
                ~TemplateList();

            public:
                void add_type(Type* type);

            private:
                std::vector<Type*> types;
        };
    }
}

#endif
