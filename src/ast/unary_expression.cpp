#include "ast/unary_expression.h"

using namespace hdc;
using namespace hdc::ast;

UnaryExpression::UnaryExpression(AstKind kind, Token token, Expression* expr) {
    set_kind(kind);
    this->expr = expr;
    this->token = token;

    expr->set_parent_node(this);
}

UnaryExpression::~UnaryExpression() {
    delete expr;
}
