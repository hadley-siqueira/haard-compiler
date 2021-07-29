#include "ast/import.h"

using namespace hdc;
using namespace hdc::ast;

Import::Import() {
    set_kind(AST_IMPORT);
    alias_flag = false;
}

void Import::set_token(Token token) {
    this->token = token;
}

void Import::set_alias(Token token) {
    alias = token;
    alias_flag = true;
}

Token Import::get_token() {
    return token;
}

Token Import::get_alias() {
    return alias;
}

bool Import::has_alias() {
    return alias_flag;
}

void Import::add_to_path(Token token) {
    path.push_back(token);
}
