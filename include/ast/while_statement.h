#ifndef HDC_AST_WHILE_STATEMENT_H
#define HDC_AST_WHILE_STATEMENT_H

#include "token/token.h"
#include "statement.h"
#include "expression.h"
#include "compound_statement.h"
#include "symtab/scope.h"

namespace hdc {
    namespace ast {
        class WhileStatement : public Statement {
            public:
                WhileStatement(Token token, Expression* expr, CompoundStatement* stmts);
                ~WhileStatement();

                Expression* get_expression();
                CompoundStatement* get_statements();
                Scope* get_scope();

            private:
                Expression* expression;
                CompoundStatement* statements;
                Token token;
                Scope* scope;
        };
    }
}

#endif
