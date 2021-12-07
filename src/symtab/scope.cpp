#include <iostream>

#include "symtab/scope.h"

using namespace hdc;

Scope::Scope() {
    enclosing_scope = nullptr;
}

Scope::~Scope() {
    std::map<std::string, Symbol*>::iterator it;

    it = symbols.begin();

    while (it != symbols.end()) {
        delete it->second;
        ++it;
    }
}

Symbol* Scope::resolve(std::string& name) {
    if (symbols.count(name) > 0) {
        return symbols.at(name);
    }

    if (enclosing_scope != nullptr) {
        return enclosing_scope->resolve(name);
    }

    return nullptr;
}

void Scope::define(Symbol* symbol) {
    symbols.emplace(symbol->get_name(), symbol);
}

Scope* Scope::get_enclosing_scope() {
    return enclosing_scope;
}

void Scope::set_enclosing_scope(Scope* scope) {
    enclosing_scope = scope;
}

void Scope::debug() {
    std::map<std::string, Symbol*>::iterator it;

    if (get_enclosing_scope() != nullptr) {
        get_enclosing_scope()->debug();
    }

    it = symbols.begin();
    std::cout << "{";

    while (it != symbols.end()) {
        std::cout << it->first << ", ";
        ++it;
    }

    std::cout << "}";

}
