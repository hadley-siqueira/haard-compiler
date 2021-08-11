#include "ast/named_type.h"

using namespace hdc;
using namespace hdc::ast;

NamedType::NamedType(Identifier* id) {
    this->id = id;
    set_kind(AST_NAMED_TYPE);
}

NamedType::~NamedType() {
    delete id;
}
