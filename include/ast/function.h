#ifndef HDC_AST_FUNCTION_H
#define HDC_AST_FUNCTION_H

#include <vector>

#include "token/token.h"
#include "ast_node.h"
#include "variable.h"
#include "type.h"

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

                Token get_name();
                SourceFile* get_source_file();
                Type* get_return_type();

                void add_parameter(Variable* parameter);

            private:
                Token name;
                SourceFile* source_file;
                std::vector<Variable*> parameters;
                Type* return_type;
        };
    }
}

#endif
