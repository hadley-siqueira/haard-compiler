#ifndef HDC_AST_ELIF_STATEMENT_H
#define HDC_AST_ELIF_STATEMENT_H

#include "token/token.h"
#include "statement.h"
#include "expression.h"
#include "compound_statement.h"
#include "symtab/scope.h"

namespace hdc {
    namespace ast {
        class ElifStatement : public Statement {
            public:
                ElifStatement(Token token, Expression* expr, CompoundStatement* stmts, Statement* false_statement);
                ElifStatement(Token token, Expression* expr, CompoundStatement* stmts);
                ~ElifStatement();

            public:
                Scope* get_scope();
                Expression* get_expression();
                CompoundStatement* get_true_statements();
                Statement* get_false_statements();

            private:
                Expression* expression;
                CompoundStatement* statements;
                Statement* false_statement;
                Token token;
                Scope* scope;
        };
    }
}

#endif
