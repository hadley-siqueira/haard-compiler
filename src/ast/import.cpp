#include "ast/import.h"

using namespace hdc;
using namespace hdc::ast;

Import::Import() {
    set_kind(AST_IMPORT);
}

void Import::set_token(Token token) {
    this->token = token;
}

void Import::set_alias(Token token) {
    alias = token;
}

Token Import::get_token() {
    return token;
}

Token Import::get_alias() {
    return alias;
}

void Import::add_to_path(Token token) {
    path.push_back(token);
}
