#ifndef HDC_AST_FUNCTION_H
#define HDC_AST_FUNCTION_H

#include <vector>

#include "token/token.h"
#include "ast_node.h"
#include "variable.h"
#include "type.h"
#include "template_list.h"
#include "compound_statement.h"
#include "symtab/scope.h"

namespace hdc {
    namespace ast {
        class SourceFile;

        class Function : public AstNode {
            public:
                Function();
                virtual ~Function();

            public:
                void set_name(Token name);
                void set_source_file(SourceFile* source_file);
                void set_return_type(Type* type);
                void set_template_list(TemplateList* list);
                void set_statements(CompoundStatement* stmts);
                void set_unique_id(std::string uid);

                Token get_name();
                SourceFile* get_source_file();
                Type* get_return_type();
                TemplateList* get_template_list();
                CompoundStatement* get_statements();
                Variable* get_parameter(int i);
                Variable* get_local_variable(int i);
                Scope* get_scope();

                int parameters_count();
                int local_variables_count();
                void add_parameter(Variable* parameter);
                void add_variable(Variable* variable);
                std::string get_unique_id();

            private:
                Token name;
                SourceFile* source_file;
                std::vector<Variable*> parameters;
                std::vector<Variable*> local_variables;
                Type* return_type;
                TemplateList* template_list;
                CompoundStatement* statements;
                Scope* scope;
                std::string unique_id;
        };
    }
}

#endif
