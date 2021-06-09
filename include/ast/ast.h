#ifndef HDC_AST_H
#define HDC_AST_H

#include <vector>

#include "defs.h"
#include "token/token.h"

namespace hdc {
    class AST {
        public:
            ~AST();

        public:
            void set_kind(AstKind kind);
            void set_parent(AST* parent);
            void set_token(Token& token);

            AstKind get_kind();
            AST* get_parent();
            Token get_token();

        public:
            void add_child(AST* child);

        private:
            AstKind kind;
            AST* parent;
            std::vector<AST*> children;
            Token token;
    };
}

#endif
