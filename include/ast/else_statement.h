#ifndef HDC_AST_ELSE_STATEMENT_H
#define HDC_AST_ELSE_STATEMENT_H

#include "token/token.h"
#include "statement.h"
#include "compound_statement.h"
#include "symtab/scope.h"

namespace hdc {
    namespace ast {
        class ElseStatement : public Statement {
            public:
                ElseStatement(Token token, CompoundStatement* stmts);
                ~ElseStatement();

            public:
                Scope* get_scope();
                CompoundStatement* get_statements();

            private:
                CompoundStatement* statements;
                Token token;
                Scope* scope;
        };
    }
}

#endif
