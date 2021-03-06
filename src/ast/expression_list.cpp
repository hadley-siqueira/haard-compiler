#include "ast/expression_list.h"

using namespace hdc;
using namespace hdc::ast;

ExpressionList::ExpressionList() {
    set_kind(AST_EXPRESSION_LIST);
}

ExpressionList::~ExpressionList() {
    /* Empty */
}

void ExpressionList::add_expression(Expression* expr) {
    expressions.push_back(expr);
    expr->set_parent_node(this);
}
                
int ExpressionList::expression_count() {
    return expressions.size();
}

Expression* ExpressionList::get_expression(int i) {
    return expressions[i];
}

