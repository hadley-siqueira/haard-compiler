#include "ast/ast_node.h"

using namespace hdc;
using namespace hdc::ast;

void AstNode::set_kind(AstKind kind) {
    this->kind = kind;
}

AstKind AstNode::get_kind() {
    return kind;
}
