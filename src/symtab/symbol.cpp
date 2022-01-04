#include "symtab/symbol.h"
#include "ast/variable.h"
#include "ast/class.h"
#include "ast/function.h"

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

std::string Symbol::get_unique_id() {
    ast::Variable* var;
    ast::Class* klass;
    ast::Function* func;

    switch (kind) {
    case SYM_VAR:
    case SYM_PARAM:
        var = (ast::Variable*) descriptor;
        return var->get_unique_id();

    case SYM_CLASS:
        klass = (ast::Class*) descriptor;
        return klass->get_unique_id();

    case SYM_FUNCTION:
        func = (ast::Function*) descriptor;
        return func->get_unique_id();
    }

    return "INVALID_UID";
}
