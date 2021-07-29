#ifndef HDC_AST_ASTNODE_H
#define HDC_AST_ASTNODE_H

#include "defs.h"

namespace hdc {
    namespace ast {
        class AstNode {
            public:
                void set_kind(AstKind kind);

                AstKind get_kind();

            private:
                AstKind kind;
        };
    }
}

#endif
