#include "ast/literal_expression.h"

using namespace hdc;
using namespace hdc::ast;

LiteralExpression::LiteralExpression(AstKind kind, Token token) {
    set_kind(kind);
    this->token = token;
}
