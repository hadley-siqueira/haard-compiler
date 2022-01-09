#include "pool/ast_pool.h"

#include "ast/program.h"

using namespace hdc;
using namespace ast;

std::vector<ast::AstNode*> AstPool::nodes;

void AstPool::add(ast::AstNode* node) {
    nodes.push_back(node);
}

void AstPool::destroy() {
    for (int i = 0; i < nodes.size(); ++i) {
        delete nodes[i];
    }
}
