#include "ast/ast.h"

using namespace hdc;

AST::~AST() {
    for (int i = 0; i < children.size(); ++i) {
        delete children[i];
    }
}

void AST::set_kind(AstKind kind) {
    this->kind = kind;
}

void AST::set_parent(AST* parent) {
    this->parent = parent;
}

void AST::set_token(Token& token) {
    this->token = token;
}

AstKind AST::get_kind() {
    return kind;
}

AST* AST::get_parent() {
    return parent;
}

Token AST::get_token() {
    return token;
}

void AST::add_child(AST* child) {
    children.push_back(child);
    child->set_parent(this);
}


