#include "ast/variable.h"

using namespace hdc;
using namespace hdc::ast;

Variable::Variable() {
    set_kind(AST_VARIABLE);
    type = nullptr;
}

Variable::Variable(AstKind kind) {
    set_kind(kind);
    type = nullptr;
}

Variable::~Variable() {
    delete type;
}

void Variable::set_name(Token name) {
    this->name = name;
}

void Variable::set_type(Type* type) {
    this->type = type;
    type->set_parent_node(this);
}

Token Variable::get_name() {
    return name;
}

Type* Variable::get_type() {
    return type;
}
