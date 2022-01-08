#include "ast/class.h"
#include "ast/source_file.h"

using namespace hdc;
using namespace hdc::ast;

Class::Class() {
    set_kind(AST_CLASS);
    parent = nullptr;
    source_file = nullptr;
    template_list = nullptr;
    scope = new Scope();
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
    delete scope;
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

ast::Type* Class::get_parent() {
    return parent;
}

SourceFile* Class::get_source_file() {
    return source_file;
}

TemplateList* Class::get_template_list() {
    return template_list;
}

Method* Class::get_method(int i) {
    return methods[i];
}

Variable* Class::get_variable(int i) {
    return variables[i];
}

Scope* Class::get_scope() {
    return scope;
}

void Class::add_method(Method* method) {
    methods.push_back(method);
    method->set_parent_node(this);
}

void Class::add_variable(Variable* variable) {
    variables.push_back(variable);
    variable->set_parent_node(this);
}

int Class::variables_count() {
    return variables.size();
}

int Class::methods_count() {
    return methods.size();
}

std::string Class::get_unique_id() {
    return unique_id;
}

void Class::set_unique_id(std::string uid) {
    unique_id = uid;
}


