#ifndef HDC_AST_EXPRESSION_STATEMENT_H
#define HDC_AST_EXPRESSION_STATEMENT_H

#include "ast_node.h"
#include "statement.h"
#include "expression.h"

namespace hdc {
    namespace ast {
        class ExpressionStatement : public Statement {
            public:
                ExpressionStatement();
                ExpressionStatement(Expression* expr);
                virtual ~ExpressionStatement();

            public:
                void set_expression(Expression* expr);
                Expression* get_expression();

            private:
                Expression* expression;
        };
    }
}

#endif
