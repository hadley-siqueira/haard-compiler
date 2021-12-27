#include <iostream>

#include "cpp/cpp_builder.h"

using namespace hdc;
using namespace hdc::ast;

CppBuilder::CppBuilder() {
    symbol_count = 0;
}

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

void CppBuilder::generate_symbols() {
    std::map<std::string, int>::iterator it = symbol_map.begin();

    while (it != symbol_map.end()) {
        output << "char* _symbol" << it->second << " = \"";
        output << it->first << "\";\n";
        ++it;
    }
}

void CppBuilder::build(ast::Program* program) {
    indent_count = 0;

    generate_prototypes(program);

    for (int i = 0; i < program->source_files_count(); ++i) {
        build_source_file(program->get_source_file(i));
    }
    
    generate_symbols();
}

void CppBuilder::build_source_file(ast::SourceFile* sf) {
    for (int i = 0; i < sf->functions_count(); ++i) {
        build_function(sf->get_function(i));
    }
}

void CppBuilder::build_function(ast::Function* f) {
    int i;

    ++indent_count;

    output << "int ";
    output << f->get_name().get_value();
    output << "(";

    if (f->parameters_count() > 0) {
        for (i = 0; i < f->parameters_count() - 1; ++i) {
            build_type(f->get_parameter(i)->get_type());
            output << ' ' << f->get_parameter(i)->get_name().get_value();
            output << ", ";
        }

        build_type(f->get_parameter(i)->get_type());
        output << ' ' << f->get_parameter(i)->get_name().get_value();
    }

    output << ") {\n";

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
    case AST_IF:
        build_if((ast::IfStatement*) stmt);
        break;

    case AST_ELIF:
        build_elif((ast::ElifStatement*) stmt);
        break;

    case AST_ELSE:
        build_else((ast::ElseStatement*) stmt);
        break;

    default:
        indent();
        build_expression((Expression*) stmt);
        output << ";\n";
        break;
    }
}

void CppBuilder::build_type(ast::Type* type) {
    switch (type->get_kind()) {
    case AST_INT_TYPE:
        output << "int";
        break;

    case AST_FLOAT_TYPE:
        output << "float";
        break;

    case AST_DOUBLE_TYPE:
        output << "double";
        break;
        
    }
}

void CppBuilder::build_expression(ast::Expression* expr) {
    switch (expr->get_kind()) {
    case AST_ASSIGNMENT:
        build_binop("=", (ast::BinaryExpression*) expr);
        break;

    // Binary operators
    case AST_PLUS:
        build_binop("+", (ast::BinaryExpression*) expr);
        break;

    case AST_MINUS:
        build_binop("-", (ast::BinaryExpression*) expr);
        break;

    case AST_IDENTIFIER:
        build_identifier((ast::Identifier*) expr);
        break;

    case AST_DOT:
        build_dot((ast::BinaryExpression*) expr);
        break;

    case AST_CALL:
        build_call((ast::BinaryExpression*) expr);
        break;

    // Unary operators
    case AST_ADDRESS_OF:
        build_unop("&", (ast::UnaryExpression*) expr);
        break;

    case AST_BITWISE_NOT:
        build_unop("~", (ast::UnaryExpression*) expr);
        break;

    case AST_DEREFERENCE:
        build_unop("*", (ast::UnaryExpression*) expr);
        break;

    case AST_UNARY_MINUS:
        build_unop("-", (ast::UnaryExpression*) expr);
        break;

    case AST_UNARY_PLUS:
        build_unop("+", (ast::UnaryExpression*) expr);
        break;

    case AST_PRE_INC:
        build_unop("++", (ast::UnaryExpression*) expr);
        break;

    case AST_PRE_DEC:
        build_unop("--", (ast::UnaryExpression*) expr);
        break;

    case AST_SIZEOF:
        build_sizeof((ast::UnaryExpression*) expr);
        break;

    case AST_LOGICAL_NOT:
        build_unop("!", (ast::UnaryExpression*) expr);
        break;

    case AST_LITERAL_INTEGER:
    case AST_LITERAL_DOUBLE:
    case AST_LITERAL_FLOAT:
    case AST_LITERAL_BOOL:
    case AST_LITERAL_CHAR:
    case AST_LITERAL_STRING:
        build_literal((ast::LiteralExpression*) expr);
        break;
    
    case AST_LITERAL_NULL:
        output << "nullptr";
        break;

    case AST_LITERAL_SYMBOL:
        build_symbol((ast::LiteralExpression*) expr);
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

void CppBuilder::build_unop(const char* op, ast::UnaryExpression* expr) {
    output << "(";
    output << op;

    build_expression(expr->get_expression());
    output << ")";
}

void CppBuilder::build_sizeof(ast::UnaryExpression* expr) {
    output << "sizeof(";
    build_expression(expr->get_expression());
    output << ")";
}

void CppBuilder::build_dot(ast::BinaryExpression* expr) {
    build_expression(expr->get_left());
    output << '.';
    build_expression(expr->get_right());
}

void CppBuilder::build_call(ast::BinaryExpression* expr) {
    int i;
    ExpressionList* list = (ast::ExpressionList*) expr->get_right();

    build_expression(expr->get_left());
    output << "(";

    if (list != nullptr) {
        for (i = 0; i < list->expression_count() - 1; ++i) {
            build_expression(list->get_expression(i));
            output << ", ";
        }

        if (i > 0) {
            build_expression(list->get_expression(i));
        }
    }

    output << ")";
}

void CppBuilder::build_literal(ast::LiteralExpression* expr) {
    output << expr->get_token().get_value();
}

void CppBuilder::build_symbol(ast::LiteralExpression* expr) {
    std::string v = expr->get_token().get_value();

    if (symbol_map.count(v) == 0) {
        symbol_map[v] = symbol_count;
        symbol_count++;
    }

    output << "_symbol" << symbol_map[v];
}

void CppBuilder::build_identifier(ast::Identifier* expr) {
    output << expr->get_name().get_value();
}

void CppBuilder::indent() {
    for (int i = 0; i < indent_count; ++i) {
        output << "    ";
    }
}


void CppBuilder::build_if(ast::IfStatement* stmt) {
    output << "if (";
    build_expression(stmt->get_expression());
    output << ") {\n";

    ++indent_count;
    build_statements(stmt->get_true_statements());
    --indent_count;
    output << "}\n";
}

void CppBuilder::build_elif(ast::ElifStatement* stmt) {

}

void CppBuilder::build_else(ast::ElseStatement* stmt) {

}
