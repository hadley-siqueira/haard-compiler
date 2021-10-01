#ifndef HDC_AST_ELSE_STATEMENT_H
#define HDC_AST_ELSE_STATEMENT_H

#include "token/token.h"
#include "statement.h"
#include "compound_statement.h"

namespace hdc {
    namespace ast {
        class ElseStatement : public Statement {
            public:
                ElseStatement(Token token, CompoundStatement* stmts);
                ~ElseStatement();

            private:
                CompoundStatement* statements;
                Token token;
        };
    }
}

#endif
