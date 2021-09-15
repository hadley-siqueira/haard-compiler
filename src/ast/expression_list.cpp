#include "ast/expression_list.h"

using namespace hdc;
using namespace hdc::ast;

ExpressionList::ExpressionList() {
    set_kind(AST_EXPRESSION_LIST);
}

ExpressionList::~ExpressionList() {
    for (int i = 0; i < expressions.size(); ++i) {
        delete expressions[i];
    }
}

void ExpressionList::add_expression(Expression* expr) {
    expressions.push_back(expr);
    expr->set_parent_node(this);
}
