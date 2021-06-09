#ifndef HDC_AST_H
#define HDC_AST_H

#include <vector>
#include <string>

#include "defs.h"
#include "token/token.h"

namespace hdc {
    class AST {
        public:
            AST(AstKind kind);
            AST(AstKind kind, Token& token);
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
            std::string to_str();
            std::string to_dot();

        private:
            std::string to_dot_aux(int& count);

        private:
            AstKind kind;
            AST* parent;
            std::vector<AST*> children;
            Token token;
    };
}

#endif
