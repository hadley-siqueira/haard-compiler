#include "ast/elif_statement.h"

using namespace hdc;
using namespace hdc::ast;

ElifStatement::ElifStatement(Token token, Expression* expr, CompoundStatement* stmts, Statement* false_statement) {
    set_kind(AST_ELIF);
    this->expression = expr;
    this->statements = stmts;
    this->false_statement = false_statement;
    this->token = token;
    expr->set_parent_node(this);
    stmts->set_parent_node(this);
    false_statement->set_parent_node(this);
}

ElifStatement::ElifStatement(Token token, Expression* expr, CompoundStatement* stmts) {
    set_kind(AST_IF);
    this->expression = expr;
    this->statements = stmts;
    this->false_statement = nullptr;
    this->token = token;
    expr->set_parent_node(this);
    stmts->set_parent_node(this);
}

ElifStatement::~ElifStatement() {
    delete expression;
    delete statements;
    delete false_statement;
}
