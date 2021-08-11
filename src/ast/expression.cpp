#include "ast/expression.h"

using namespace hdc;
using namespace hdc::ast;

Expression::Expression() {
    set_kind(AST_EXPRESSION);
}

Expression::~Expression() {

};
