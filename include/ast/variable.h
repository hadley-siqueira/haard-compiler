#ifndef HDC_AST_VARIABLE_H
#define HDC_AST_VARIABLE_H

#include <vector>

#include "token/token.h"
#include "ast_node.h"
#include "type.h"

namespace hdc {
    namespace ast {
        class Variable : public AstNode {
            public:
                Variable();
                Variable(AstKind kind);
                ~Variable();

            public:
                void set_name(Token token);
                void set_type(Type* type);

                Token get_name();
                Type* get_type();

            private:
                Token name;
                Type* type;
        };
    }
}

#endif
