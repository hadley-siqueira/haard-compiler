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

}

void Variable::set_name(Token name) {
    this->name = name;
}

Token Variable::get_name() {
    return name;
}
