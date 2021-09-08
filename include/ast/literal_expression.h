#ifndef HDC_AST_LITERAL_EXPRESSION_H
#define HDC_AST_LITERAL_EXPRESSION_H

#include "expression.h"
#include "token/token.h"

namespace hdc {
    namespace ast {
        class LiteralExpression : public Expression {
            public:
                LiteralExpression(AstKind kind, Token token);

            private:
                Token token;
        };
    }
}

#endif
