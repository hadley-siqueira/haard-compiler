#include "ast/array_type.h"

using namespace hdc;
using namespace hdc::ast;

ArrayType::ArrayType(Token token, Type* subtype, class Expression* expr) {
    set_kind(AST_ARRAY_TYPE);
    this->subtype = subtype;
    this->expr = expr;
    this->token = token;
}

ArrayType::ArrayType(Type* subtype, class Expression* expr) {
    set_kind(AST_ARRAY_TYPE);
    this->subtype = subtype;
    this->expr = expr;
    this->token = token;
}
                
Type* ArrayType::get_subtype() {
    return subtype;
}

class Expression* ArrayType::get_expression() {
    return expr;
}
