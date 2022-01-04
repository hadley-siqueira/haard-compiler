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
                void set_offset(int offset);
                void set_unique_id(std::string uid);

                Token get_name();
                Type* get_type();
                int get_offset();
                std::string get_unique_id();

            private:
                Token name;
                Type* type;
                int offset;
                std::string unique_id;
        };
    }
}

#endif
