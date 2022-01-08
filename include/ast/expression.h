#ifndef HDC_AST_EXPRESSION_H
#define HDC_AST_EXPRESSION_H

#include "ast_node.h"
#include "statement.h"
#include "type.h"

namespace hdc {
    namespace ast {
        class Expression : public Statement {
            public:
                Expression();
                virtual ~Expression();

                void set_type(Type* type);
                Type* get_type();

            private:
                Type* type;
        };
    }
}

#endif
