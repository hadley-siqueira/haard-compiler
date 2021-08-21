#include "ast/indirection_type.h"

using namespace hdc;
using namespace hdc::ast;

IndirectionType::IndirectionType(AstKind kind, Token token, Type* subtype) {
    set_kind(kind);
    this->subtype = subtype;
    this->token = token;
    subtype->set_parent_node(this);
}

IndirectionType::~IndirectionType() {
    delete subtype;
}
