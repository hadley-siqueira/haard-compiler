#include "ast/binary_expression.h"

using namespace hdc;
using namespace hdc::ast;

BinaryExpression::BinaryExpression(AstKind kind, Token token, Expression* left, Expression* right) {
    set_kind(kind);
    this->left = left;
    this->right = right;
    this->token = token;

    left->set_parent_node(this);
    right->set_parent_node(this);
}

BinaryExpression::~BinaryExpression() {
    /* Empty */
}

Expression* BinaryExpression::get_left() {
    return left;
}

Expression* BinaryExpression::get_right() {
    return right;
}
