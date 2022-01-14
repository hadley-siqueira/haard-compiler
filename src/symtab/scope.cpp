#include <iostream>

#include "symtab/scope.h"

using namespace hdc;

Scope::Scope() {
    enclosing_scope = nullptr;
    siblings = nullptr;
}

Scope::~Scope() {
    std::map<std::string, Symbol*>::iterator it;

    it = symbols.begin();

    while (it != symbols.end()) {
        delete it->second;
        ++it;
    }
}

Symbol* Scope::resolve(std::string& name, bool recursive) {
    if (symbols.count(name) > 0) {
        return symbols.at(name);
    }

    // when searching on siblings, do not go recursive. Imagine the following
    // file a: import b
    // file b: import a
    // if resolve recursively, it will enter on an infinite loop, so the
    // recursive variable stops the search on the currente level
    if (recursive) {
        if (enclosing_scope != nullptr) {
            return enclosing_scope->resolve(name);
        } else if (siblings != nullptr) {
            Symbol* symbol;

            for (int i = 0; i < siblings->size(); ++i) {
                symbol = siblings->at(i)->resolve(name, false);

                if (symbol != nullptr) {
                    return symbol;
                }
            }
        }
    }

    return nullptr;
}

Symbol* Scope::resolve_member(std::string& name) {
    Symbol* sym = nullptr;
    SymbolKind kind;

    if (symbols.count(name) > 0) {
        sym = symbols.at(name);
        kind = sym->get_kind();

        if (kind == SYM_CLASS_VAR || kind == SYM_METHOD) {
            return sym;
        }
    }

    if (enclosing_scope != nullptr) {
        return enclosing_scope->resolve_member(name);
    }

    return nullptr;
}

void Scope::define(Symbol* symbol) {
    symbols.emplace(symbol->get_name(), symbol);
    symbol->set_scope(this);
}

Scope* Scope::get_enclosing_scope() {
    return enclosing_scope;
}

void Scope::set_name(std::string name) {
    this->name = name;
}

std::string Scope::get_name() {
    return name;
}

void Scope::set_enclosing_scope(Scope* scope) {
    enclosing_scope = scope;
}

void Scope::add_sibling(Scope* scope) {
    if (siblings == nullptr) {
        siblings = new std::vector<Scope*>();
    }

    siblings->push_back(scope);
}

void Scope::debug() {
    std::map<std::string, Symbol*>::iterator it;

    if (get_enclosing_scope() != nullptr) {
        get_enclosing_scope()->debug();
    }

    it = symbols.begin();
    std::cout << name <<" {";

    while (it != symbols.end()) {
        std::cout << it->first << ", ";
        ++it;
    }

    if (siblings != nullptr) {
        std::cout << "siblings: ";

        for (int i = 0; i < siblings->size(); ++i) {
            siblings->at(i)->debug();
        }
    }

    std::cout << "}";

}
