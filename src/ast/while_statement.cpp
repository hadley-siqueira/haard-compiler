#include "ast/while_statement.h"

using namespace hdc;
using namespace hdc::ast;

WhileStatement::WhileStatement(Token token, Expression* expr, CompoundStatement* stmts) {
    set_kind(AST_WHILE);
    this->token = token;
    this->expression = expr;
    this->statements = stmts;
    scope = new Scope();
    expr->set_parent_node(this);
    stmts->set_parent_node(this);
}

WhileStatement::~WhileStatement() {
    delete expression;
    delete statements;
}

Expression* WhileStatement::get_expression() {
    return expression;
}

CompoundStatement* WhileStatement::get_statements() {
    return statements;
}

Scope* WhileStatement::get_scope() {
    return scope;
}
