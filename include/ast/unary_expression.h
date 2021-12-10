#ifndef HDC_AST_UNARY_EXPRESSION_H
#define HDC_AST_UNARY_EXPRESSION_H

#include "expression.h"
#include "token/token.h"

namespace hdc {
    namespace ast {
        class UnaryExpression : public Expression {
            public:
                UnaryExpression(AstKind kind, Token token, Expression* expr);
                ~UnaryExpression();

                Expression* get_expression();

            private:
                Token token;
                Expression* expr;
        };
    }
}

#endif
