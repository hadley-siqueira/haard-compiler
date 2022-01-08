#include "ast/type.h"

using namespace hdc;
using namespace hdc::ast;

Type::Type() {

}

Type::Type(AstKind kind, Token token) {
    set_kind(kind);
    this->token = token;
}

Type::Type(AstKind kind) {
    set_kind(kind);
}

Type::~Type() {

}

void Type::set_token(Token token) {
    this->token = token;
}

Token Type::get_token() {
    return token;
}
                
Type* Type::clone() {
    return new Type(get_kind(), token);
}
