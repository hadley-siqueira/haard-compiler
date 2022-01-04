#include "ast/source_file.h"
#include "ast/function.h"

using namespace hdc;
using namespace hdc::ast;

Function::Function() {
    set_kind(AST_FUNCTION);
    source_file = nullptr;
    template_list = nullptr;
    return_type = nullptr;
    scope = new Scope();
}

Function::~Function() {
    delete return_type;
    delete template_list;
    delete statements;
    delete scope;

    for (int i = 0; i < parameters.size(); ++i) {
        delete parameters[i];
    }

    for (int i = 0; i < local_variables.size(); ++i) {
        delete local_variables[i];
    }
}

void Function::set_name(Token name) {
    this->name = name;
}

void Function::set_source_file(SourceFile* source_file) {
    this->source_file = source_file;
    set_parent_node(source_file);
}

void Function::set_return_type(Type* type) {
    this->return_type = type;
    type->set_parent_node(this);
}

void Function::set_template_list(TemplateList* list) {
    this->template_list = list;
    list->set_parent_node(this);
}

void Function::set_statements(CompoundStatement* stmts) {
    this->statements = stmts;
    stmts->set_parent_node(this);
}

Token Function::get_name() {
    return name;
}

SourceFile* Function::get_source_file() {
    return source_file;
}

Type* Function::get_return_type() {
    return return_type;
}

TemplateList* Function::get_template_list() {
    return template_list;
}

CompoundStatement* Function::get_statements() {
    return statements;
}

Variable* Function::get_parameter(int i) {
    return parameters[i];
}

Variable* Function::get_local_variable(int i) {
    return local_variables[i];
}

Scope* Function::get_scope() {
    return scope;
}

int Function::parameters_count() {
    return parameters.size();
}

int Function::local_variables_count() {
    return local_variables.size();
}

void Function::add_parameter(Variable* parameter) {
    parameters.push_back(parameter);
    parameter->set_parent_node(this);
}

void Function::add_variable(Variable* variable) {
    local_variables.push_back(variable);
    variable->set_parent_node(this);
}

void Function::set_unique_id(std::string uid) {
    unique_id = uid;
}

std::string Function::get_unique_id() {
    return unique_id;
}
