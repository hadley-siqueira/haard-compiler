#include "ast/function.h"

using namespace hdc;
using namespace hdc::ast;

Function::Function() {
    set_kind(AST_FUNCTION);
    source_file = nullptr;
}

Function::~Function() {
    for (int i = 0; i < parameters.size(); ++i) {
        delete parameters[i];
    }
}

void Function::set_name(Token name) {
    this->name = name;
}

void Function::set_source_file(SourceFile* source_file) {
    this->source_file = source_file;
}

Token Function::get_name() {
    return name;
}

SourceFile* Function::get_source_file() {
    return source_file;
}

void Function::add_parameter(Variable* parameter) {
    parameters.push_back(parameter);
}

