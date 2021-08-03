#ifndef HDC_AST_VARIABLE_H
#define HDC_AST_VARIABLE_H

#include <vector>

#include "token/token.h"
#include "ast_node.h"

namespace hdc {
    namespace ast {
        class Variable : public AstNode {
            public:
                Variable();
                Variable(AstKind kind);
                ~Variable();

            public:
                void set_name(Token token);
                // void set_type(Token token);

                Token get_name();
                // Type* get_type();

            private:
                Token name;
        };
    }
}

#endif
