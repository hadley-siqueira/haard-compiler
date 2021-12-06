#ifndef HDC_AST_BINARY_EXPRESSION_H
#define HDC_AST_BINARY_EXPRESSION_H

#include "expression.h"
#include "token/token.h"

namespace hdc {
    namespace ast {
        class BinaryExpression : public Expression {
            public:
                BinaryExpression(AstKind kind, Token token, Expression* left, Expression* right);
                ~BinaryExpression();

                Expression* get_left();
                Expression* get_right();

            private:
                Token token;
                Expression* left;
                Expression* right;
        };
    }
}

#endif
