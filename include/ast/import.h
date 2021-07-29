#ifndef HDC_AST_IMPORT_H
#define HDC_AST_IMPORT_H

#include <vector>

#include "token/token.h"
#include "ast_node.h"

namespace hdc {
    namespace ast {
        class Import : public AstNode {
            public:
                Import();

            public:
                void set_token(Token token);
                void set_alias(Token token);

                Token get_token();
                Token get_alias();

                bool has_alias();

                void add_to_path(Token token);

            private:
                Token token;
                Token alias;
                bool alias_flag;
                std::vector<Token> path;
        };
    }
}

#endif
