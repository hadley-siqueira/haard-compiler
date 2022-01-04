#ifndef HDC_AST_NAMED_TYPE_H
#define HDC_AST_NAMED_TYPE_H

#include <vector>

#include "token/token.h"
#include "ast_node.h"
#include "type.h"
#include "identifier.h"

namespace hdc {
    namespace ast {
        class NamedType : public Type {
            public:
                NamedType(Identifier* id);
                ~NamedType();

            public:
                Identifier* get_id();

            private:
                Identifier* id;
        };
    }
}

#endif
