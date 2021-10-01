#ifndef HDC_AST_ELIF_STATEMENT_H
#define HDC_AST_ELIF_STATEMENT_H

#include "token/token.h"
#include "statement.h"
#include "expression.h"
#include "compound_statement.h"

namespace hdc {
    namespace ast {
        class ElifStatement : public Statement {
            public:
                ElifStatement(Token token, Expression* expr, CompoundStatement* stmts, Statement* false_statement);
                ElifStatement(Token token, Expression* expr, CompoundStatement* stmts);
                ~ElifStatement();

            private:
                Expression* expression;
                CompoundStatement* statements;
                Statement* false_statement;
                Token token;
        };
    }
}

#endif
