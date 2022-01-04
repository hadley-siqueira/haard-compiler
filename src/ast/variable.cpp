#include "ast/variable.h"

using namespace hdc;
using namespace hdc::ast;

Variable::Variable() {
    set_kind(AST_VARIABLE);
    type = nullptr;
    offset = 0;
}

Variable::Variable(AstKind kind) {
    set_kind(kind);
    type = nullptr;
    offset = 0;
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

void Variable::set_offset(int offset) {
    this->offset = offset;
}

void Variable::set_unique_id(std::string uid) {
    unique_id = uid;
}

Token Variable::get_name() {
    return name;
}

Type* Variable::get_type() {
    return type;
}

int Variable::get_offset() {
    return offset;
}

std::string Variable::get_unique_id() {
    return unique_id;
}
