#include "ast/else_statement.h"

using namespace hdc;
using namespace hdc::ast;

ElseStatement::ElseStatement(Token token, CompoundStatement* stmts) {
    set_kind(AST_ELSE);
    this->statements = stmts;
    this->token = token;
    stmts->set_parent_node(this);
    scope = new Scope();
}

ElseStatement::~ElseStatement() {
    delete statements;
    delete scope;
}

Scope* ElseStatement::get_scope() {
    return scope;
}

CompoundStatement* ElseStatement::get_statements() {
    return statements;
}
