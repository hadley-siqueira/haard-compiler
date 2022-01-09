#include "ast/named_type.h"

using namespace hdc;
using namespace hdc::ast;

NamedType::NamedType(Identifier* id) {
    this->id = id;
    set_kind(AST_NAMED_TYPE);
    id->set_parent_node(this);
}

NamedType::~NamedType() {
    //delete id;
}

Identifier* NamedType::get_id() {
    return id;
}

Type* NamedType::clone() {
    NamedType* tmp = new NamedType(id);
    return tmp;
}
