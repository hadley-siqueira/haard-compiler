#include <iostream>

#include "cpp/cpp_builder.h"

using namespace hdc;
using namespace hdc::ast;

CppBuilder::CppBuilder() {
    symbol_count = 0;
    main_function = nullptr;
}

std::string CppBuilder::get_output() {
    std::stringstream r;

    r << headers_stream.str();
    r << symbols_stream.str();
    r << classes_proto_stream.str();
    r << '\n';
    r << function_proto_stream.str();
    r << '\n';
    r << classes_stream.str();
    r << '\n';
    r << functions_stream.str();
    r << main_function_stream.str();

    return r.str();
}

void CppBuilder::generate_headers() {
    headers_stream << "#include <iostream>\n\n";
}

void CppBuilder::generate_symbols() {
    std::map<std::string, int>::iterator it = symbol_map.begin();
    bool flag = false;

    while (it != symbol_map.end()) {
        symbols_stream << "char* _symbol" << it->second << " = \"";
        symbols_stream << it->first << "\";\n";
        ++it;
        flag = true;
    }

    if (flag) {
        symbols_stream << '\n';
    }
}

void CppBuilder::generate_main_function() {
    main_function_stream << "int main(int argc, char** argv) {\n";

    if (main_function != nullptr) {
        main_function_stream << "    ";
        main_function_stream << main_function->get_unique_id() << "();\n";
    }

    main_function_stream << "    return 0;\n}";
}

void CppBuilder::build(ast::Program* program) {
    indent_count = 0;

    generate_headers();

    for (int i = 0; i < program->source_files_count(); ++i) {
        build_source_file(program->get_source_file(i));
    }
    
    generate_symbols();
    generate_main_function();
}

void CppBuilder::build_source_file(ast::SourceFile* sf) {
    int i;

    if (!source_file_visited(sf)) {
        visit_source_file(sf);

        if (sf->classes_count() > 0) {
            for (i = 0; i < sf->classes_count() - 1; ++i) {
                build_class(sf->get_class(i));
                *output << "\n\n";
            }

            build_class(sf->get_class(i));
            *output << '\n';
        }

        for (i = 0; i < sf->functions_count(); ++i) {
            build_function(sf->get_function(i));
        }
    }
}

void CppBuilder::build_function(ast::Function* f) {
    if (!function_visited(f)) {
        visit_function(f);
        ++indent_count;

        // generate the function signature prototype
        set_output(function_proto_stream);
        build_function_signature(f);
        *output << ";\n";

        set_output(functions_stream);
        build_function_signature(f);
        *output << " {\n";
        build_function_variables(f);
        build_statements(f->get_statements());

        *output << "}\n\n";
        --indent_count;

        set_main_function(f);
    }
}

void CppBuilder::build_function_signature(ast::Function* f) {
    int i;

    build_type(f->get_return_type());
    *output << ' ';
    *output << f->get_unique_id();
    *output << "(";

    if (f->parameters_count() > 0) {
        for (i = 0; i < f->parameters_count() - 1; ++i) {
            build_type(f->get_parameter(i)->get_type());
            *output << ' ' << f->get_parameter(i)->get_unique_id();
            *output << ", ";
        }

        build_type(f->get_parameter(i)->get_type());
        *output << ' ' << f->get_parameter(i)->get_unique_id();
    }

    *output << ")";
}

void CppBuilder::build_function_variables(ast::Function* f) {
    if (f->local_variables_count() > 0) {
        for (int i = 0; i < f->local_variables_count(); ++i) {
            indent();
            build_variable(f->get_local_variable(i));
            *output << ";\n";
        }

        *output << '\n';
    }
}

void CppBuilder::build_class(ast::Class* klass) {
    int i;

    if (!class_visited(klass)) {
        visit_class(klass);
        set_output(classes_stream);
        build_class_signature(klass);

        ++indent_count;

        build_class_variables(klass);
        build_class_methods(klass);
        *output << "};";

        --indent_count;
    }
}

void CppBuilder::build_class_signature(ast::Class* klass) {
    *output << "class ";
    *output << klass->get_unique_id();
    classes_proto_stream << "class " << klass->get_unique_id() << ";\n";

    if (klass->get_parent() != nullptr) {
        *output << " : public ";
        build_type(klass->get_parent());
    }

    *output << " {\n";
}

void CppBuilder::build_class_variables(ast::Class* klass) {
    if (klass->variables_count() > 0) {
        *output << "public:\n";
    }

    for (int i = 0; i < klass->variables_count(); ++i) {
        indent();
        build_variable(klass->get_variable(i));
        *output << ";\n";
    }
}

void CppBuilder::build_class_methods(ast::Class* klass) {
    int i;

    if (klass->methods_count() > 0) {
        if (klass->variables_count() > 0) {
            *output << '\n';
        }

        *output << "public:\n";
        for (i = 0; i < klass->methods_count() - 1; ++i) {
            build_method(klass->get_method(i));
            *output << "\n\n";
        }

        build_method(klass->get_method(i));
        *output << "\n";
    }
}

void CppBuilder::build_method(ast::Method* f) {
    if (!function_visited(f)) {
        visit_function(f);

        indent();
        build_function_signature(f);
        *output << " {\n";
        ++indent_count;
        build_statements(f->get_statements());

        --indent_count;
        indent();
        *output << "}";
    }
}

void CppBuilder::build_variable(ast::Variable* v) {
    if (v->get_type() != nullptr) {
        build_type(v->get_type());
    } else {
        *output << "int";
    }

    *output << ' ' << v->get_unique_id();
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

    case AST_WHILE:
        build_while((ast::WhileStatement*) stmt);
        break;

    case AST_EXPRESSION_STATEMENT:
        build_expression_statement((ast::ExpressionStatement*) stmt);
        break;

    }
}

void CppBuilder::build_type(ast::Type* type) {
    NamedType* nm;

    switch (type->get_kind()) {
    case AST_INT_TYPE:
        *output << "int";
        break;

    case AST_FLOAT_TYPE:
        *output << "float";
        break;

    case AST_DOUBLE_TYPE:
        *output << "double";
        break;

    case AST_VOID_TYPE:
        *output << "void";
        break;

    case AST_CHAR_TYPE:
        *output << "char";
        break;

    case AST_POINTER_TYPE:
        build_type(((ast::IndirectionType*) type)->get_subtype());
        *output << '*';
        break;

    case AST_NAMED_TYPE:
        nm = (NamedType*) type;
        *output << nm->get_id()->get_symbol()->get_unique_id();
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

    case AST_TIMES:
        build_binop("*", (ast::BinaryExpression*) expr);
        break;

    case AST_DIVISION:
        build_binop("/", (ast::BinaryExpression*) expr);
        break;

    case AST_INTEGER_DIVISION:
        build_binop("/", (ast::BinaryExpression*) expr);
        break;

    case AST_MODULO:
        build_binop("%", (ast::BinaryExpression*) expr);
        break;

    case AST_LT:
        build_binop("<", (ast::BinaryExpression*) expr);
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
        build_literal((ast::LiteralExpression*) expr);
        break;

    case AST_LITERAL_STRING:
        build_string((ast::LiteralExpression*) expr);
        break;
    
    case AST_LITERAL_NULL:
        *output << "nullptr";
        break;

    case AST_LITERAL_SYMBOL:
        build_symbol((ast::LiteralExpression*) expr);
        break;

    case AST_DOLAR:
        build_dolar((ast::UnaryExpression*) expr);
        break;
    }
}

void CppBuilder::build_dolar(ast::UnaryExpression* dolar) {
    ast::LiteralExpression* l = (ast::LiteralExpression*) dolar->get_expression();
    std::string s = l->get_token().get_value();
    s[0] = ' ';
    s[s.size() - 1] = ' ';
    *output << s;
}

void CppBuilder::build_binop(const char* op, ast::BinaryExpression* expr) {
    *output << "(";
    build_expression(expr->get_left());
    *output << ' ' << op << ' ';
    build_expression(expr->get_right());
    *output << ")";
}

void CppBuilder::build_unop(const char* op, ast::UnaryExpression* expr) {
    *output << "(";
    *output << op;

    build_expression(expr->get_expression());
    *output << ")";
}

void CppBuilder::build_sizeof(ast::UnaryExpression* expr) {
    *output << "sizeof(";
    build_expression(expr->get_expression());
    *output << ")";
}

void CppBuilder::build_dot(ast::BinaryExpression* expr) {
    build_expression(expr->get_left());
    *output << '.';
    build_expression(expr->get_right());
}

void CppBuilder::build_call(ast::BinaryExpression* expr) {
    int i;
    ExpressionList* list = (ast::ExpressionList*) expr->get_right();

    build_expression(expr->get_left());
    *output << "(";

    if (list != nullptr) {
        for (i = 0; i < list->expression_count() - 1; ++i) {
            build_expression(list->get_expression(i));
            *output << ", ";
        }

        build_expression(list->get_expression(i));
    }

    *output << ")";
}

void CppBuilder::build_literal(ast::LiteralExpression* expr) {
    *output << expr->get_token().get_value();
}

void CppBuilder::build_string(ast::LiteralExpression* expr) {
    std::string tmp = expr->get_token().get_value(); 

    tmp[0] = '"';
    tmp[tmp.size() - 1] = '"';
    *output << tmp;
}

void CppBuilder::build_symbol(ast::LiteralExpression* expr) {
    std::string v = expr->get_token().get_value();

    if (symbol_map.count(v) == 0) {
        symbol_map[v] = symbol_count;
        symbol_count++;
    }

    *output << "_symbol" << symbol_map[v];
}

void CppBuilder::build_identifier(ast::Identifier* expr) {
    if (expr->get_symbol() != nullptr) {
        *output << expr->get_symbol()->get_unique_id();
    } else {
        *output << expr->get_name().get_value();
    }
}

void CppBuilder::indent() {
    for (int i = 0; i < indent_count; ++i) {
        *output << "    ";
    }
}


void CppBuilder::build_if(ast::IfStatement* stmt) {
    indent();
    *output << "if (";
    build_expression(stmt->get_expression());
    *output << ") {\n";

    ++indent_count;
    build_statements(stmt->get_true_statements());
    --indent_count;
    indent();
    *output << "}\n";

    if (stmt->get_false_statements()) {
        build_statement(stmt->get_false_statements());
    }
}

void CppBuilder::build_elif(ast::ElifStatement* stmt) {
    indent();
    *output << "else if (";
    build_expression(stmt->get_expression());
    *output << ") {\n";

    ++indent_count;
    build_statements(stmt->get_true_statements());
    --indent_count;
    indent();
    *output << "}\n";

    if (stmt->get_false_statements()) {
        build_statement(stmt->get_false_statements());
    }
}

void CppBuilder::build_else(ast::ElseStatement* stmt) {
    indent();
    *output << "else {\n";

    ++indent_count;
    build_statements(stmt->get_statements());
    --indent_count;
    indent();
    *output << "}\n";
}

void CppBuilder::build_while(ast::WhileStatement* stmt) {
    indent();
    *output << "while (";
    build_expression(stmt->get_expression());
    *output << ") {\n";

    indent_count++;
    build_statements(stmt->get_statements());
    indent_count--;
    indent();
    *output << "}\n";
}

void CppBuilder::build_expression_statement(ast::ExpressionStatement* stmt) {
    indent();
    build_expression(stmt->get_expression());
    *output << ";\n";
}

void CppBuilder::set_output(std::stringstream& stream) {
    output = &stream;
}

bool CppBuilder::function_visited(ast::Function* f) {
    return visited_functions.count(f) > 0;
}

void CppBuilder::visit_function(ast::Function* f) {
    visited_functions.insert(f);
}

bool CppBuilder::source_file_visited(ast::SourceFile* sf) {
    return visited_source_files.count(sf) > 0;
}

void CppBuilder::visit_source_file(ast::SourceFile* sf) {
    visited_source_files.insert(sf);
}

bool CppBuilder::class_visited(ast::Class* klass) {
    return visited_classes.count(klass) > 0;
}

void CppBuilder::visit_class(ast::Class* klass) {
    visited_classes.insert(klass);
}

void CppBuilder::set_main_function(ast::Function* f) {
    std::string name = f->get_name().get_value();

    if (name == "main") {
        main_function = f;
    }
}
