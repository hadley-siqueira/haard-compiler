#ifndef HDC_AST_CLASS_H
#define HDC_AST_CLASS_H

#include <vector>

#include "token/token.h"
#include "ast_node.h"
#include "type.h"
#include "variable.h"
#include "method.h"
#include "template_list.h"

namespace hdc {
    namespace ast {
        class SourceFile;

        class Class : public AstNode {
            public:
                Class();
                ~Class();

            public:
                void set_name(Token token);
                void set_parent(Type* parent);
                void set_source_file(SourceFile* source_file);
                void set_template_list(TemplateList* list);

                Token get_name();
                Type* get_parent();
                SourceFile* get_source_file();
                TemplateList* get_template_list();

                void add_method(Method* method);
                void add_variable(Variable* variable);

            private:
                Token name;
                Type* parent;
                SourceFile* source_file;
                std::vector<Method*> methods;
                std::vector<Variable*> variables;
                TemplateList* template_list;
        };
    }
}

#endif
