#ifndef HDC_AST_TYPE_H
#define HDC_AST_TYPE_H

#include <vector>

#include "token/token.h"
#include "ast_node.h"

namespace hdc {
    namespace ast {
        class Type : public AstNode {
            public:
                Type();
                Type(AstKind kind, Token token);
                Type(AstKind kind);
                virtual ~Type();
                virtual Type* clone();

            public:
                void set_token(Token token);

                Token get_token();

            private:
                Token token;
        };
    }
}

#endif
