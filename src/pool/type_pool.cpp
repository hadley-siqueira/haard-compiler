#include "pool/type_pool.h"

using namespace hdc;
using namespace ast;

std::vector<ast::Type*> TypePool::type_pool;

ast::Type* TypePool::get(AstKind kind, Token token) {
    ast::Type* type = new Type(kind, token);

    type_pool.push_back(type);

    return type;
}
