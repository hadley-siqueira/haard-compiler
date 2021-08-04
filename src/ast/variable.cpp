#include "ast/variable.h"

using namespace hdc;
using namespace hdc::ast;

Variable::Variable() {
    set_kind(AST_VARIABLE);
}

Variable::Variable(AstKind kind) {
    set_kind(kind);
}

Variable::~Variable() {
    delete type;
}

void Variable::set_name(Token name) {
    this->name = name;
}

void Variable::set_type(Type* type) {
    this->type = type;
}

Token Variable::get_name() {
    return name;
}

Type* Variable::get_type() {
    return type;
}
