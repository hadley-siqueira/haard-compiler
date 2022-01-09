#include <iostream>

#include "ast/expression.h"

using namespace hdc;
using namespace hdc::ast;

Expression::Expression() {
    set_kind(AST_EXPRESSION);
    type = nullptr;
}

Expression::~Expression() {
    delete type;
};
                
void Expression::set_type(Type* type) {
    this->type = type;
}

Type* Expression::get_type() {
    return type;
}
