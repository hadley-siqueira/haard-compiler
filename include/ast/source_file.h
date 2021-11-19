#ifndef HDC_AST_SOURCE_FILE_H
#define HDC_AST_SOURCE_FILE_H

#include <vector>

#include "token/token.h"
#include "ast_node.h"
#include "import.h"
#include "function.h"
#include "class.h"

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
                void add_class(Class* klass);

                int imports_count();
                int functions_count();
                int classes_count();

                Import* get_import(int i);
                Function* get_function(int i);
                Class* get_class(int i);

            private:
                std::string path;
                std::vector<Import*> imports;
                std::vector<Function*> functions;
                std::vector<Class*> classes;
        };
    }
}

#endif
