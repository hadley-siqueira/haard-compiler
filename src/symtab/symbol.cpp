#include "symtab/symbol.h"

using namespace hdc;

Symbol::Symbol() {
    descriptor = nullptr;
}

Symbol::Symbol(SymbolKind kind, std::string name, void* descriptor) {
    this->kind = kind;
    this->name = name;
    this->descriptor = descriptor;
}

void Symbol::set_name(std::string name) {
    this->name = name;
}

void Symbol::set_descriptor(void* descriptor) {
    this->descriptor = descriptor;
}

void Symbol::set_kind(SymbolKind kind) {
    this->kind = kind;
}

std::string Symbol::get_name() {
    return name;
}

void* Symbol::get_descriptor() {
    return descriptor;
}

SymbolKind Symbol::get_kind() {
    return kind;
}

