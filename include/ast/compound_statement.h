#ifndef HDC_AST_COMPOUND_STATEMENT_H
#define HDC_AST_COMPOUND_STATEMENT_H

#include <vector>

#include "statement.h"

namespace hdc {
    namespace ast {
        class CompoundStatement : public Statement {
            public:
                CompoundStatement();
                ~CompoundStatement();

            public:
                void add_statement(Statement* stmt);
                int statements_count();
                Statement* get_statement(int i);

            private:
                std::vector<Statement*> statements;
                
        };
    }
}

#endif
