#ifndef HDC_AST_NEW_EXPRESSION_H
#define HDC_AST_NEW_EXPRESSION_H

#include "token/token.h"
#include "expression.h"

namespace hdc {
    namespace ast {
        class NewExpression : public Expression {
            public:
                NewExpression(Token token, Type* build_type);
                Type* get_build_type();

            private:
                Type* build_type;
                Token token;
        };
    }
}

#endif
