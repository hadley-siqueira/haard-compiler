#include "ast/source_file.h"
#include "ast/function.h"

using namespace hdc;
using namespace hdc::ast;

Function::Function() {
    set_kind(AST_FUNCTION);
    source_file = nullptr;
}

Function::~Function() {
    delete return_type;

    for (int i = 0; i < parameters.size(); ++i) {
        delete parameters[i];
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

Token Function::get_name() {
    return name;
}

SourceFile* Function::get_source_file() {
    return source_file;
}

Type* Function::get_return_type() {
    return return_type;
}

void Function::add_parameter(Variable* parameter) {
    parameters.push_back(parameter);
    parameter->set_parent_node(this);
}

