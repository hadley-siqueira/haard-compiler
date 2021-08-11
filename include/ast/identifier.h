#ifndef HDC_AST_IDENTIFIER_H
#define HDC_AST_IDENTIFIER_H

#include "token/token.h"
#include "ast_node.h"
#include "type.h"
#include "template_list.h"

namespace hdc {
    namespace ast {
        class Identifier : public AstNode {
            public:
                Identifier();
                ~Identifier();

            public:
                void set_alias(Token alias);
                void set_name(Token name);
                void set_alias_flag(bool value);
                void set_global_flag(bool value);
                void set_template_list(TemplateList* value);

                Token get_alias();
                Token get_name();
                bool has_alias();
                bool has_global_alias();
                TemplateList* get_template_list();
                
            private:
                Token alias;
                Token name;
                bool alias_flag;
                bool global_alias_flag;
                TemplateList* template_list;
        };
    }
}

#endif
