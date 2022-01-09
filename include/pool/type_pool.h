#ifndef HDC_TYPE_POOL_H
#define HDC_TYPE_POOL_H

#include <vector>

#include "ast/type.h"

namespace hdc {
    class TypePool {
        public:
            static ast::Type* get(AstKind kind, Token token);

        private:
            static std::vector<ast::Type*> type_pool;
    };
}

#endif
