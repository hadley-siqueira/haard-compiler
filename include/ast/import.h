#ifndef HDC_AST_IMPORT_H
#define HDC_AST_IMPORT_H

#include <vector>

#include "token/token.h"
#include "ast_node.h"

namespace hdc {
    namespace ast {
        class SourceFile;

        class Import : public AstNode {
            public:
                Import();

            public:
                void set_token(Token token);
                void set_alias(Token token);
                void set_source_file(SourceFile* source_file);

                Token get_token();
                Token get_alias();
                Token get_path(int i);

                bool has_alias();

                void add_to_path(Token token);
                int path_size();

            private:
                Token token;
                Token alias;
                bool alias_flag;
                std::vector<Token> path;
                SourceFile* source_file;
        };
    }
}

#endif
