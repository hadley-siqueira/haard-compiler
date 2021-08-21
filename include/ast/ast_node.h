#ifndef HDC_AST_ASTNODE_H
#define HDC_AST_ASTNODE_H

#include "defs.h"

namespace hdc {
    namespace ast {
        class AstNode {
            public:
                AstNode();
                virtual ~AstNode();

            public:
                void set_kind(AstKind kind);
                void set_parent_node(AstNode* node);

                AstKind get_kind();
                AstNode* get_parent_node();

            private:
                AstKind kind;
                AstNode* parent_node;
        };
    }
}

#endif
