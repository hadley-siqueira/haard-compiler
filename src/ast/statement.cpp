#include "ast/statement.h"

using namespace hdc;
using namespace hdc::ast;

Statement::Statement() {
    set_kind(AST_STATEMENT);
}

Statement::~Statement() {

};
