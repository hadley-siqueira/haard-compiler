#include "ast/expression_statement.h"

using namespace hdc;
using namespace hdc::ast;

ExpressionStatement::ExpressionStatement() {
    set_kind(AST_EXPRESSION_STATEMENT);
    expression = nullptr;
}

ExpressionStatement::ExpressionStatement(Expression* expr) {
    set_kind(AST_EXPRESSION_STATEMENT);
    expression = expr;
    expr->set_parent_node(this);
}

ExpressionStatement::~ExpressionStatement() {
    delete expression;
}

void ExpressionStatement::set_expression(Expression* expr) {
    expression = expr;
}

Expression* ExpressionStatement::get_expression() {
    return expression;
}

