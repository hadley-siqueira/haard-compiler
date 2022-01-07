#include <iostream>
#include <sstream>

#include "symtab/scope_builder.h"

using namespace hdc;
using namespace hdc::ast;

void ScopeBuilder::visit(ast::AstNode* node) {
    switch (node->get_kind()) {
    case AST_PROGRAM:
        visit_program((ast::Program*) node);
        break;

    case AST_SOURCEFILE:
        visit_source_file((ast::SourceFile*) node);
        break;

    case AST_FUNCTION:
        visit_function((ast::Function*) node);
        break;

    // statements
    case AST_COMPOUND_STATEMENT:
        visit_compound_statement((ast::CompoundStatement*) node);
        break;

    case AST_IF:
        visit_if_statement((ast::IfStatement*) node);
        break;

    case AST_ELIF:
        visit_elif_statement((ast::ElifStatement*) node);
        break;

    case AST_ELSE:
        visit_else_statement((ast::ElseStatement*) node);
        break;

    case AST_EXPRESSION_STATEMENT:
        visit_expression_statement((ast::ExpressionStatement*) node);
        break;

    // expressions
    case AST_IDENTIFIER:
        visit_identifier((ast::Identifier*) node);
        break;

    case AST_LITERAL_INTEGER:
        visit_literal_integer((ast::LiteralExpression*) node);
        break;

    case AST_EXPRESSION_LIST:
        visit_expression_list((ast::ExpressionList*) node);
        break;

    // special operations
    case AST_CALL:
        visit_call((ast::BinaryExpression*) node);
        break;

    // binary operators
    case AST_TIMES:
        visit_times((ast::BinaryExpression*) node);
        break;

    case AST_DIVISION:
        visit_division((ast::BinaryExpression*) node);
        break;

    case AST_INTEGER_DIVISION:
        visit_integer_division((ast::BinaryExpression*) node);
        break;

    case AST_MODULO:
        visit_modulo((ast::BinaryExpression*) node);
        break;

    case AST_POWER:
        visit_power((ast::BinaryExpression*) node);
        break;

    case AST_PLUS:
        visit_plus((ast::BinaryExpression*) node);
        break;

    case AST_MINUS:
        visit_minus((ast::BinaryExpression*) node);
        break;

    case AST_ASSIGNMENT:
        visit_assignment((BinaryExpression*) node);
        break;

    default:
        std::cout << "ERROR: invalid node\n";
        std::cout << hdc_astkind_map.at(node->get_kind()) << std::endl;
        // exit(0);
    }
}

void ScopeBuilder::visit_program(ast::Program* program) {
    function_id_counter = 0;
    class_id_counter = 0;

    first_pass(program);
    second_pass(program);
}

void ScopeBuilder::first_pass(ast::Program* program) {
    ast::SourceFile* source_file = nullptr;

    for (int i = 0; i < program->source_files_count(); ++i) {
        source_file = program->get_source_file(i);
        add_classes(source_file);
        add_functions(source_file);
    }
}

void ScopeBuilder::second_pass(ast::Program* program) {
    for (int i = 0; i < program->source_files_count(); ++i) {
        visit(program->get_source_file(i));
    }
}

void ScopeBuilder::visit_source_file(ast::SourceFile* source_file) {
    for (int i = 0; i < source_file->functions_count(); ++i) {
        visit(source_file->get_function(i));
    }
}

void ScopeBuilder::visit_function(ast::Function* function) {
    function->get_scope()->set_enclosing_scope(current_scope);
    current_scope = function->get_scope();
    current_function = function;
    int lvar_counter = 0;

    add_parameters(function);
    visit(function->get_statements());
   
    for (int i = 0; i < function->local_variables_count(); ++i) {
        std::stringstream ss;
        Variable* var = function->get_local_variable(i);
        ss << "lv" << lvar_counter << "_" << var->get_name().get_value();
        var->set_unique_id(ss.str());
        ++lvar_counter;
        std::cout << var->get_name().get_value() << '\n';
    }

    current_scope = current_scope->get_enclosing_scope();
}

void ScopeBuilder::visit_compound_statement(ast::CompoundStatement* statements) {
    for (int i = 0; i < statements->statements_count(); ++i) {
        visit(statements->get_statement(i));
    }
}

void ScopeBuilder::visit_if_statement(ast::IfStatement* stmt) {
    stmt->get_scope()->set_enclosing_scope(current_scope);
    current_scope = stmt->get_scope();

    visit(stmt->get_expression());
    visit(stmt->get_true_statements());

    current_scope = current_scope->get_enclosing_scope();

    if (stmt->get_false_statements()) {
        visit(stmt->get_false_statements());
    }
}

void ScopeBuilder::visit_elif_statement(ast::ElifStatement* stmt) {
    stmt->get_scope()->set_enclosing_scope(current_scope);
    current_scope = stmt->get_scope();

    visit(stmt->get_expression());
    visit(stmt->get_true_statements());

    current_scope = current_scope->get_enclosing_scope();

    if (stmt->get_false_statements()) {
        visit(stmt->get_false_statements());
    }
}

void ScopeBuilder::visit_else_statement(ast::ElseStatement* stmt) {
    stmt->get_scope()->set_enclosing_scope(current_scope);
    current_scope = stmt->get_scope();

    visit(stmt->get_statements());
    current_scope = current_scope->get_enclosing_scope();
}

void ScopeBuilder::visit_expression_statement(ast::ExpressionStatement* stmt) {
    visit(stmt->get_expression());
}

void ScopeBuilder::visit_identifier(ast::Identifier* id) {
    Symbol* symbol = nullptr;
    std::string name = id->get_name().get_value();
    std::string alias = id->get_alias().get_value();

    symbol = current_scope->resolve(name);

    if (symbol == nullptr) {
        std::cout << "Error: symbol not defined\n"; 
        exit(0);
    } else {
        id->set_symbol(symbol);
        id->set_scope(current_scope);
    }
}

void ScopeBuilder::visit_literal_integer(ast::LiteralExpression* literal) {
    // nothing to yet
}

void ScopeBuilder::visit_expression_list(ast::ExpressionList* list) {
    for (int i = 0; i < list->expression_count(); ++i) {
        visit(list->get_expression(i));
    }
}

void ScopeBuilder::visit_call(ast::BinaryExpression* call) {
    ast::Expression* left = call->get_left();
    ast::Expression* right = call->get_right();

    if (left->get_kind() == AST_IDENTIFIER) {
        visit(left);
    }

    visit(right);
}

void ScopeBuilder::visit_times(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_division(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_integer_division(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_modulo(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_power(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_plus(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_minus(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_assignment(ast::BinaryExpression* bin) {
    Expression* left = bin->get_left();
    Expression* right = bin->get_right();

    visit(right);

    if (left->get_kind() == AST_IDENTIFIER) {
        create_new_variable((Identifier*) left);
    }
}

void ScopeBuilder::create_new_variable(ast::Identifier* id) {
    Symbol* symbol = nullptr;
    std::string name = id->get_name().get_value();
    std::string alias = id->get_alias().get_value();

    symbol = current_scope->resolve(name);

    if (symbol == nullptr) {
        Variable* var = new Variable(AST_LOCAL_VARIABLE);
        var->set_name(id->get_name());
        symbol = new Symbol(SYM_VAR, name, var);
        current_scope->define(symbol);
        current_function->add_variable(var);
    }

    id->set_symbol(symbol);
    id->set_scope(current_scope);
}

void ScopeBuilder::visit_binop(ast::BinaryExpression* bin) {
    visit(bin->get_left());
    visit(bin->get_right());
}

void ScopeBuilder::add_parameters(ast::Function* function) {
    Symbol* symbol = nullptr;
    Variable* var = nullptr;
    int param_counter = 0;

    for (int i = 0; i < function->parameters_count(); ++i) {
        var = function->get_parameter(i);
        std::string name = var->get_name().get_value();
        symbol = current_scope->resolve(name);
        std::stringstream ss;

        if (symbol == nullptr) {
            define_symbol(SYM_PARAM, name, var);
            ss << "p" << param_counter << "_" << name;
            var->set_unique_id(ss.str());
            ++param_counter;
        } else {
            if (symbol->get_kind() == SYM_PARAM) {
                std::cout << "Error: parameter '" << name << "' already defined\n";
                exit(0);
            } else {
                define_symbol(SYM_PARAM, name, var);
            }
        }
    }
}

void ScopeBuilder::add_classes(ast::SourceFile* source_file) {
    current_scope = source_file->get_scope();

    for (int i = 0; i < source_file->classes_count(); ++i) {
        add_class(source_file->get_class(i));
    }
}

void ScopeBuilder::add_class(ast::Class* klass) {
    Symbol* symbol = nullptr;
    std::string name(klass->get_name().get_value());
    std::stringstream ss;

    symbol = current_scope->resolve(name);

    if (symbol == nullptr) {
        define_symbol(SYM_CLASS, name, klass);
        ss << "c" << class_id_counter << "_" << name;
        klass->set_unique_id(ss.str());
        ++class_id_counter;
    } else {
        std::string path = klass->get_source_file()->get_path();
        Class* k = (Class*) symbol->get_descriptor();
        int line = k->get_name().get_line();
        std::cout << "\033[1;31mError\033[0m";
        std::cout << ": class '" << name << "' already defined\n";
        std::cout << "    First occurence on line " << line << " of file '" << path << "'\n";
    }
}

void ScopeBuilder::add_functions(ast::SourceFile* source_file) {
    current_scope = source_file->get_scope();

    for (int i = 0; i < source_file->functions_count(); ++i) {
        add_function(source_file->get_function(i));
    }
}

void ScopeBuilder::add_function(ast::Function* function) {
    Symbol* symbol = nullptr;
    std::string name(function->get_name().get_value());
    std::stringstream ss;

    symbol = current_scope->resolve(name);

    if (symbol == nullptr) {
        define_symbol(SYM_FUNCTION, name, function);
        ss << "f" << function_id_counter << "_" << name;
        function->set_unique_id(ss.str());
        ++function_id_counter;
    } else {
        std::string path = function->get_source_file()->get_path();
        Function* k = (Function*) symbol->get_descriptor();
        int line = k->get_name().get_line();
        std::cout << "\033[1;31mError\033[0m";
        std::cout << ": function '" << name << "' already defined\n";
        std::cout << "    First occurence on line " << line << " of file '" << path << "'\n";
    }
}

void ScopeBuilder::define_symbol(SymbolKind kind, std::string name, void* descriptor) {
    Symbol* symbol = new Symbol(kind, name, descriptor);
    current_scope->define(symbol);
}
