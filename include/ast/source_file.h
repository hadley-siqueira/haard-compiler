#ifndef HDC_AST_SOURCE_FILE_H
#define HDC_AST_SOURCE_FILE_H

#include <vector>

#include "token/token.h"
#include "ast_node.h"
#include "import.h"

namespace hdc {
    namespace ast {
        class SourceFile : public AstNode {
            public:
                SourceFile();

            public:
                void set_path(std::string path);

                std::string get_path();

                void add_import(Import* import);

            private:
                std::string path;
                std::vector<Import*> imports;
        };
    }
}

#endif
