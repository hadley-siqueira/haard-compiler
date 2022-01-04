#include <iostream>
#include <sstream>

#include "symtab/scope_builder.h"

using namespace hdc;
using namespace hdc::ast;

void ScopeBuilder::visit(ast::Program* program) {
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

void ScopeBuilder::visit(ast::SourceFile* source_file) {
    for (int i = 0; i < source_file->functions_count(); ++i) {
        visit(source_file->get_function(i));
    }
}

void ScopeBuilder::visit(ast::Function* function) {
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

void ScopeBuilder::visit(ast::CompoundStatement* statements) {
    for (int i = 0; i < statements->statements_count(); ++i) {
        visit(statements->get_statement(i));
    }
}

void ScopeBuilder::visit(ast::Statement* statement) {
    std::cout << hdc_astkind_map.at(statement->get_kind()) << std::endl;

    switch (statement->get_kind()) {
    case AST_IF: 
        visit((IfStatement*) statement);
        break;

    case AST_ELIF: 
        visit((ElifStatement*) statement);
        break;

    case AST_ELSE:
        visit((ElseStatement*) statement);
        break;

    default:
        visit((Expression*) statement);
        break;
    }
}

void ScopeBuilder::visit(ast::IfStatement* stmt) {
    stmt->get_scope()->set_enclosing_scope(current_scope);
    current_scope = stmt->get_scope();

    visit(stmt->get_expression());
    visit(stmt->get_true_statements());

    current_scope = current_scope->get_enclosing_scope();

    if (stmt->get_false_statements()) {
        visit(stmt->get_false_statements());
    }
}

void ScopeBuilder::visit(ast::ElifStatement* stmt) {
    stmt->get_scope()->set_enclosing_scope(current_scope);
    current_scope = stmt->get_scope();

    visit(stmt->get_expression());
    visit(stmt->get_true_statements());

    current_scope = current_scope->get_enclosing_scope();

    if (stmt->get_false_statements()) {
        visit(stmt->get_false_statements());
    }
}

void ScopeBuilder::visit(ast::ElseStatement* stmt) {
    stmt->get_scope()->set_enclosing_scope(current_scope);
    current_scope = stmt->get_scope();

    visit(stmt->get_statements());
    current_scope = current_scope->get_enclosing_scope();
}

void ScopeBuilder::visit(ast::Expression* expr) {
    std::cout << hdc_astkind_map.at(expr->get_kind()) << std::endl;

    switch (expr->get_kind()) {
    case AST_IDENTIFIER:
        visit((Identifier*) expr);
        break;

    case AST_ASSIGNMENT:
        handle_assignment((BinaryExpression*) expr);
        break;

    case AST_PLUS:
    case AST_MINUS:
        visit((BinaryExpression*) expr);
        break;
    }
}

void ScopeBuilder::visit(ast::Identifier* id) {
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

void ScopeBuilder::handle_assignment(ast::BinaryExpression* bin) {
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

void ScopeBuilder::visit(ast::BinaryExpression* bin) {
    Expression* left = bin->get_left();
    Expression* right = bin->get_right();

    switch (bin->get_kind()) {
    case AST_ASSIGNMENT:
    case AST_PLUS:
    case AST_MINUS:
        visit(left);
        visit(right);
        break;
    }
}

void ScopeBuilder::add_parameters(ast::Function* function) {
    Symbol* symbol = nullptr;
    Variable* var = nullptr;
    int param_counter = 0;
    std::stringstream ss;

    for (int i = 0; i < function->parameters_count(); ++i) {
        var = function->get_parameter(i);
        std::string name = var->get_name().get_value();
        symbol = current_scope->resolve(name);

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
