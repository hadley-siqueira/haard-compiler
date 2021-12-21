#include "cpp/cpp_builder.h"

using namespace hdc;
using namespace hdc::ast;
            
std::string CppBuilder::get_output() {
    return output.str();
}

void CppBuilder::generate_prototypes(ast::Program* program) {
    for (int i = 0; i < program->source_files_count(); ++i) {
        generate_prototypes(program->get_source_file(i));
    }
}

void CppBuilder::generate_prototypes(ast::SourceFile* sf) {
    for (int i = 0; i < sf->functions_count(); ++i) {
        generate_prototype(sf->get_function(i));
    }

    output << "\n";
}

void CppBuilder::generate_prototype(ast::Function* f) {
    output << "int " << f->get_name().get_value() << "();\n";
}

void CppBuilder::build(ast::Program* program) {
    indent_count = 0;

    generate_prototypes(program);

    for (int i = 0; i < program->source_files_count(); ++i) {
        build_source_file(program->get_source_file(i));
    }
}

void CppBuilder::build_source_file(ast::SourceFile* sf) {
    for (int i = 0; i < sf->functions_count(); ++i) {
        build_function(sf->get_function(i));
    }
}

void CppBuilder::build_function(ast::Function* f) {
    ++indent_count;

    output << "int ";
    output << f->get_name().get_value();
    output << "() {\n";

    build_statements(f->get_statements());

    output << "\n}\n\n";
    --indent_count;
}

void CppBuilder::build_statements(ast::CompoundStatement* stmts) {
    for (int i = 0; i < stmts->statements_count(); ++i) {
        build_statement(stmts->get_statement(i));
    }
}

void CppBuilder::build_statement(ast::Statement* stmt) {
    switch (stmt->get_kind()) {
    default:
        indent();
        build_expression((Expression*) stmt);
        output << ";\n";
        break;
    }
}

void CppBuilder::build_expression(ast::Expression* expr) {
    switch (expr->get_kind()) {
    case AST_ASSIGNMENT:
        build_binop("=", (ast::BinaryExpression*) expr);
        break;

    case AST_PLUS:
        build_binop("+", (ast::BinaryExpression*) expr);
        break;

    case AST_MINUS:
        build_binop("-", (ast::BinaryExpression*) expr);
        break;

    case AST_IDENTIFIER:
        build_identifier((ast::Identifier*) expr);
        break;

    case AST_LITERAL_INTEGER:
        build_literal((ast::LiteralExpression*) expr);
        break;
    }
}

void CppBuilder::build_binop(const char* op, ast::BinaryExpression* expr) {
    output << "(";
    build_expression(expr->get_left());
    output << ' ' << op << ' ';
    build_expression(expr->get_right());
    output << ")";
}

void CppBuilder::build_literal(ast::LiteralExpression* expr) {
    output << expr->get_token().get_value();
}

void CppBuilder::build_identifier(ast::Identifier* expr) {
    output << expr->get_name().get_value();
}

void CppBuilder::indent() {
    for (int i = 0; i < indent_count; ++i) {
        output << "    ";
    }
}
