#ifndef HDC_AST_EXPRESSION_LIST_H
#define HDC_AST_EXPRESSION_LIST_H

#include <vector>

#include "expression.h"

namespace hdc {
    namespace ast {
        class ExpressionList : public Expression {
            public:
                ExpressionList();
                ~ExpressionList();

            public:
                void add_expression(Expression* expr);
                int expression_count();
                Expression* get_expression(int i);

            private:
                std::vector<Expression*> expressions;
        };
    }
}

#endif
