#include "ast/template_list.h"

using namespace hdc;
using namespace hdc::ast;

TemplateList::TemplateList() {
    set_kind(AST_TEMPLATE_LIST);
}

TemplateList::~TemplateList() {
    /* Empty */
}

void TemplateList::add_type(Type* type) {
    types.push_back(type);
    type->set_parent_node(this);
}
