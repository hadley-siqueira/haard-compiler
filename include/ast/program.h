#ifndef HDC_AST_PROGRAM_H
#define HDC_AST_PROGRAM_H

#include <map>
#include <string>

#include "source_file.h"

namespace hdc {
    namespace ast {
        class Program : public AstNode {
            public:
                Program();
                ~Program();

            public:
                void add_source_file(std::string path, SourceFile* source_file);
                SourceFile* get_source_file(std::string path);
                bool has_source_file(std::string path);

            private:
                std::map<std::string, ast::SourceFile*> source_files;
        };
    }
}

#endif
