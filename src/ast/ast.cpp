#include <sstream>

#include "ast/ast.h"

using namespace hdc;

AST::AST(AstKind kind) {
    this->kind = kind;
    parent = nullptr;
}

AST::AST(AstKind kind, Token& token) {
    this->kind = kind;
    this->token = token;
    parent = nullptr;
}

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

std::string AST::to_str() {
    std::stringstream buf;
    int i;

    buf << "(";
    buf << token.get_value();

    if (children.size() > 0) {
        buf << " ";

        for (i = 0; i < children.size() - 1; ++i) {
            buf << children[i]->to_str() << " ";
        }

        buf << children[i]->to_str();
    }

    buf << ")";

    return buf.str();
}

