#ifndef HDC_AST_IDENTIFIER_H
#define HDC_AST_IDENTIFIER_H

#include "token/token.h"
#include "ast_node.h"
#include "type.h"
#include "template_list.h"
#include "expression.h"
#include "symtab/scope.h"
#include "symtab/symbol.h"

namespace hdc {
    namespace ast {
        class Identifier : public Expression {
            public:
                Identifier();
                ~Identifier();

            public:
                void set_alias(Token alias);
                void set_name(Token name);
                void set_alias_flag(bool value);
                void set_global_flag(bool value);
                void set_template_list(TemplateList* value);
                void set_symbol(Symbol* symbol);
                void set_scope(Scope* scope);

                Token get_alias();
                Token get_name();
                bool has_alias();
                bool has_global_alias();
                TemplateList* get_template_list();
                Symbol* get_symbol();
                
            private:
                Token alias;
                Token name;
                bool alias_flag;
                bool global_alias_flag;
                TemplateList* template_list;
                Symbol* symbol;
                Scope* scope;
        };
    }
}

#endif
