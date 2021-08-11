#include "ast/class.h"
#include "ast/source_file.h"

using namespace hdc;
using namespace hdc::ast;

Class::Class() {
    set_kind(AST_CLASS);
    parent = nullptr;
    source_file = nullptr;
    template_list = nullptr;
}

Class::~Class() {
    for (int i = 0; i < methods.size(); ++i) {
        delete methods[i];
    }

    for (int i = 0; i < variables.size(); ++i) {
        delete variables[i];
    }

    delete template_list;
    delete parent;
}

void Class::set_name(Token token) {
    this->name = token;
}

void Class::set_parent(Type* parent) {
    this->parent = parent;
    parent->set_parent_node(this);
}

void Class::set_source_file(SourceFile* source_file) {
    this->source_file = source_file;
    set_parent_node(source_file);
}

void Class::set_template_list(TemplateList* list) {
    this->template_list = list;
    list->set_parent_node(this);
}

Token Class::get_name() {
    return name;
}

Type* Class::get_parent() {
    return parent;
}

SourceFile* Class::get_source_file() {
    return source_file;
}

TemplateList* Class::get_template_list() {
    return template_list;
}

void Class::add_method(Method* method) {
    methods.push_back(method);
    method->set_parent_node(this);
}

void Class::add_variable(Variable* variable) {
    variables.push_back(variable);
    variable->set_parent_node(this);
}

