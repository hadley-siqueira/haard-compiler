#include "symtab/scope.h"

using namespace hdc;

Scope::Scope() {
    enclosing_scope = nullptr;
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
