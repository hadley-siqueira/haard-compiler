#ifndef HDC_TYPE_POOL_H
#define HDC_TYPE_POOL_H

#include <vector>

#include "token/token.h"
#include "ast/ast_node.h"

namespace hdc {
    class AstPool {
        public:
            static void add(ast::AstNode* node);
            static void destroy();

        private:
            static std::vector<ast::AstNode*> nodes;
    };
}

#endif
