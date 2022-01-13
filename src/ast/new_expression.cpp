#include "ast/new_expression.h"

using namespace hdc;
using namespace hdc::ast;
                
NewExpression::NewExpression(Token token, Type* build_type) {
    set_kind(AST_NEW);
    this->token = token;
    this->build_type = build_type;
    build_type->set_parent_node(this);
}

Type* NewExpression::get_build_type() {
    return build_type;
}
