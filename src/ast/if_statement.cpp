#include "ast/if_statement.h"

using namespace hdc;
using namespace hdc::ast;

IfStatement::IfStatement(Token token, Expression* expr, CompoundStatement* stmts, Statement* false_statement) {
    set_kind(AST_IF);
    this->expression = expr;
    this->statements = stmts;
    this->false_statement = false_statement;
    this->token = token;
    expr->set_parent_node(this);
    stmts->set_parent_node(this);
    false_statement->set_parent_node(this);
}

IfStatement::IfStatement(Token token, Expression* expr, CompoundStatement* stmts) {
    set_kind(AST_IF);
    this->expression = expr;
    this->statements = stmts;
    this->false_statement = nullptr;
    this->token = token;
    expr->set_parent_node(this);
    stmts->set_parent_node(this);
}

IfStatement::~IfStatement() {
    delete expression;
    delete statements;
    delete false_statement;
}
