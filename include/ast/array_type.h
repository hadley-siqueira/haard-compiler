#ifndef HDC_AST_ARRAY_TYPE_H
#define HDC_AST_ARRAY_TYPE_H

#include "type.h"

namespace hdc {
    namespace ast {
        class ArrayType : public Type {
            public:
                ArrayType(Token token, Type* subtype, class Expression* expr=nullptr);
                ArrayType(Type* subtype, class Expression* expr=nullptr);

            public:
                Type* get_subtype();
                class Expression* get_expression();

            private:
                class Expression* expr;
                Type* subtype;
                Token token;
        };
    }
}

#endif
