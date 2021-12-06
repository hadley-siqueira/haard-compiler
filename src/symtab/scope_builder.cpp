#include <iostream>

#include "symtab/scope_builder.h"

using namespace hdc;
using namespace hdc::ast;

void ScopeBuilder::visit(ast::Program* program) {
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

    add_parameters(function);
    visit(function->get_statements());

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
    default:
        visit((Expression*) statement);
        break;
    }
}

void ScopeBuilder::visit(ast::Expression* expr) {
    std::cout << hdc_astkind_map.at(expr->get_kind()) << std::endl;

    switch (expr->get_kind()) {
    case AST_IDENTIFIER:
        visit((Identifier*) expr);
        break;

    case AST_ASSIGNMENT:
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

    if (id->get_parent_node()->get_kind() == AST_ASSIGNMENT) {
        if (symbol == nullptr) {
            Variable* var = new Variable(AST_LOCAL_VARIABLE);
            var->set_name(id->get_name());
            symbol = new Symbol(SYM_VAR, name, var);
            current_scope->define(symbol);
            current_function->add_variable(var);
            id->set_symbol(symbol);
            id->set_scope(current_scope);
        }
    }
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

    for (int i = 0; i < function->parameters_count(); ++i) {
        var = function->get_parameter(i);
        std::string name = var->get_name().get_value();
        symbol = current_scope->resolve(name);

        if (symbol == nullptr) {
            define_symbol(SYM_PARAM, name, var);
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

    symbol = current_scope->resolve(name);

    if (symbol == nullptr) {
        define_symbol(SYM_CLASS, name, klass);
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

    for (int i = 0; i < source_file->classes_count(); ++i) {
        add_function(source_file->get_function(i));
    }
}

void ScopeBuilder::add_function(ast::Function* function) {
    Symbol* symbol = nullptr;
    std::string name(function->get_name().get_value());

    symbol = current_scope->resolve(name);

    if (symbol == nullptr) {
        define_symbol(SYM_FUNCTION, name, function);
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
