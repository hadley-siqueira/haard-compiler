#ifndef HDC_AST_IF_STATEMENT_H
#define HDC_AST_IF_STATEMENT_H

#include "token/token.h"
#include "statement.h"
#include "expression.h"
#include "compound_statement.h"

namespace hdc {
    namespace ast {
        class IfStatement : public Statement {
            public:
                IfStatement(Token token, Expression* expr, CompoundStatement* stmts, Statement* false_statement);
                IfStatement(Token token, Expression* expr, CompoundStatement* stmts);
                ~IfStatement();

            private:
                Expression* expression;
                CompoundStatement* statements;
                Statement* false_statement;
                Token token;
        };
    }
}

#endif
