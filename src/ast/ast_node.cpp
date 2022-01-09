#include <iostream>

#include "ast/ast_node.h"
#include "pool/ast_pool.h"

using namespace hdc;
using namespace hdc::ast;

AstNode::AstNode() {
    parent_node = nullptr;
    AstPool::add(this);
}

AstNode::~AstNode() {
    if (parent_node == nullptr) {
        std::string s = hdc_astkind_map.at(kind);
        std::cout << "null parent detected " << s << '\n';
    }
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
