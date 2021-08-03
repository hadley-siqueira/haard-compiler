#ifndef HDC_AST_SOURCE_FILE_H
#define HDC_AST_SOURCE_FILE_H

#include <vector>

#include "token/token.h"
#include "ast_node.h"
#include "import.h"
#include "function.h"

namespace hdc {
    namespace ast {
        class SourceFile : public AstNode {
            public:
                SourceFile();
                ~SourceFile();

            public:
                void set_path(std::string path);

                std::string get_path();

                void add_import(Import* import);
                void add_function(Function* function);

            private:
                std::string path;
                std::vector<Import*> imports;
                std::vector<Function*> functions;
        };
    }
}

#endif
