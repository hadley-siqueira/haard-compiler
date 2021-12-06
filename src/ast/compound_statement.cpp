#include "ast/compound_statement.h"

using namespace hdc;
using namespace hdc::ast;

CompoundStatement::CompoundStatement() {
    set_kind(AST_COMPOUND_STATEMENT);
}

CompoundStatement::~CompoundStatement() {
    for (int i = 0; i < statements.size(); ++i) {
        delete statements[i];
    }
};

void CompoundStatement::add_statement(Statement* stmt) {
    statements.push_back(stmt);
    stmt->set_parent_node(this);
}

int CompoundStatement::statements_count() {
    return statements.size();
}

Statement* CompoundStatement::get_statement(int i) {
    return statements[i];
}
