#ifndef HDC_AST_INDIRECTION_TYPE_H
#define HDC_AST_INDIRECTION_TYPE_H

#include "type.h"

namespace hdc {
    namespace ast {
        class IndirectionType : public Type {
            public:
                IndirectionType(AstKind kind, Token token, Type* subtype);
                IndirectionType(AstKind kind, Type* subtype);
                ~IndirectionType();

                Type* get_subtype();

            private:
                Type* subtype;
                Token token;
        };
    }
}

#endif
