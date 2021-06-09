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
    buf << hdc_astkind_map.at(kind) << ' ';
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

std::string AST::to_dot() {
    std::stringstream buf;
    int count = 0;
    int tc = 0;
    int sz;

    buf << "digraph {\n";

    buf << "    " << count << " [label=\"" << hdc_astkind_map.at(kind) 
        << ' ' << token.get_value() << ' ' << tc << "\"];\n";

    sz = children.size();

    for (int i = 1; i < children.size(); ++i) {
        buf << children[i - 1]->to_dot_aux(count);
        buf << "    " << tc << " -> " << (sz + tc + i) << ";\n";
    }

    buf << "}\n";

    return buf.str();
}

std::string AST::to_dot_aux(int& count) {
    std::stringstream buf;
    int sz;

    if (flag) {
        buf << "digraph {\n";
    }

    buf << "    " << count << " [label=\"" << hdc_astkind_map.at(kind) 
        << ' ' << token.get_value() << ' ' << count << "\"];\n";

    sz = children.size();
    for (int i = 0; i < children.size(); ++i) {
        buf << children[i]->to_dot(false, sz + count + i + 1);
        buf << "    " << count << " -> " << (sz + count + i + 1) << ";\n";
    }

    if (flag) {
        buf << "}\n";
    }

    return buf.str();
}
