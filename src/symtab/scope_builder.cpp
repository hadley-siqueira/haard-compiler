#include <iostream>

#include "symtab/scope_builder.h"

using namespace hdc;
using namespace hdc::ast;

void ScopeBuilder::visit(ast::SourceFile* source_file) {
    add_classes(source_file);
}

void ScopeBuilder::add_classes(ast::SourceFile* source_file) {
    current_scope = source_file->get_scope();

    for (int i = 0; i < source_file->classes_count(); ++i) {
        add_class(source_file->get_class(i));
    }
}

void ScopeBuilder::add_class(ast::Class* klass) {
    Symbol* symbol = nullptr;
    std::string name(klass->get_name().get_value());

    symbol = current_scope->resolve(name);

    if (symbol == nullptr) {
        symbol = new Symbol(SYM_CLASS, name, klass);
        current_scope->define(symbol);
    } else {
        std::string path = klass->get_source_file()->get_path();
        Class* k = (Class*) symbol->get_descriptor();
        int line = k->get_name().get_line();
        std::cout << "\033[1;31mError\033[0m";
        std::cout << ": class '" << name << "' already defined\n";
        std::cout << "    First occurence on line " << line << " of file '" << path << "'\n";
    }
}

