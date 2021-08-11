#include "ast/identifier.h"

using namespace hdc;
using namespace hdc::ast;

Identifier::Identifier() {
    set_kind(AST_IDENTIFIER);
    alias_flag = false;
    global_alias_flag = false;
    template_list = nullptr;
}

Identifier::~Identifier() {
    delete template_list;
}

void Identifier::set_alias(Token alias) {
    this->alias = alias;
    this->alias_flag = true;
}

void Identifier::set_name(Token name) {
    this->name = name;
}

void Identifier::set_alias_flag(bool value) {
    this->alias_flag = value;
}

void Identifier::set_global_flag(bool value) {
    this->global_alias_flag = value;
}

void Identifier::set_template_list(TemplateList* value) {
    this->template_list = value;
    value->set_parent_node(this);
}

Token Identifier::get_alias() {
    return alias;
}

Token Identifier::get_name() {
    return name;
}

bool Identifier::has_alias() {
    return alias_flag;
}

bool Identifier::has_global_alias() {
    return global_alias_flag;
}

TemplateList* Identifier::get_template_list() {
    return template_list;
}