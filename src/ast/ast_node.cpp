#include "ast/ast_node.h"

using namespace hdc;
using namespace hdc::ast;

AstNode::AstNode() {
    parent_node = nullptr;
}

void AstNode::set_kind(AstKind kind) {
    this->kind = kind;
}

void AstNode::set_parent_node(AstNode* node) {
    parent_node = node;
}

AstKind AstNode::get_kind() {
    return kind;
}

AstNode* AstNode::get_parent_node() {
    return parent_node;
}
