#include "symtab/symbol.h"
#include "ast/variable.h"
#include "ast/class.h"
#include "ast/function.h"
#include "symtab/scope.h"
#include "ast/type.h"

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

Scope* Symbol::get_scope() {
    return scope;
}

void Symbol::set_scope(Scope* scope) {
    this->scope = scope;
}

std::string Symbol::get_unique_id() {
    ast::Variable* var;
    ast::Class* klass;
    ast::Function* func;

    switch (kind) {
    case SYM_VAR:
    case SYM_PARAM:
    case SYM_CLASS_VAR:
        var = (ast::Variable*) descriptor;
        return var->get_unique_id();

    case SYM_CLASS:
        klass = (ast::Class*) descriptor;
        return klass->get_unique_id();

    case SYM_FUNCTION:
    case SYM_METHOD:
        func = (ast::Function*) descriptor;
        return func->get_unique_id();
    }

    return "INVALID_UID";
}

ast::Type* Symbol::get_type() {
    ast::Variable* var;
    ast::Class* klass;
    ast::Function* func;

    switch (kind) {
    case SYM_VAR:
    case SYM_PARAM:
    case SYM_CLASS_VAR:
        var = (ast::Variable*) descriptor;
        return var->get_type();

    case SYM_CLASS:
        return nullptr;

    case SYM_FUNCTION:
    case SYM_METHOD:
        return nullptr;
    }

    return nullptr;
}
