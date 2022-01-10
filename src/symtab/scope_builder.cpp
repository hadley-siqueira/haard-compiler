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

    case AST_CLASS:
        visit_class((ast::Class*) node);
        break;

    case AST_FUNCTION:
        visit_function((ast::Function*) node);
        break;

    case AST_METHOD:
        visit_method((ast::Method*) node);
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

    case AST_WHILE:
        visit_while_statement((ast::WhileStatement*) node);
        break;

    case AST_EXPRESSION_STATEMENT:
        visit_expression_statement((ast::ExpressionStatement*) node);
        break;

    // expressions
    case AST_IDENTIFIER:
        visit_identifier((ast::Identifier*) node);
        break;

    case AST_LITERAL_CHAR:
        visit_literal_char((ast::LiteralExpression*) node);
        break;

    case AST_LITERAL_STRING:
        visit_literal_string((ast::LiteralExpression*) node);
        break;

    case AST_LITERAL_SYMBOL:
        visit_literal_symbol((ast::LiteralExpression*) node);
        break;

    case AST_LITERAL_NULL:
        visit_literal_null((ast::LiteralExpression*) node);
        break;

    case AST_LITERAL_BOOL:
        visit_literal_bool((ast::LiteralExpression*) node);
        break;

    case AST_LITERAL_INTEGER:
        visit_literal_integer((ast::LiteralExpression*) node);
        break;

    case AST_LITERAL_FLOAT:
        visit_literal_float((ast::LiteralExpression*) node);
        break;

    case AST_LITERAL_DOUBLE:
        visit_literal_double((ast::LiteralExpression*) node);
        break;

    case AST_EXPRESSION_LIST:
        visit_expression_list((ast::ExpressionList*) node);
        break;

    // special operations
    case AST_CALL:
        visit_call((ast::BinaryExpression*) node);
        break;

    // binary operators
    case AST_SLL:
        visit_sll((ast::BinaryExpression*) node);
        break;

    case AST_SRL:
        visit_srl((ast::BinaryExpression*) node);
        break;

    case AST_SRA:
        visit_sra((ast::BinaryExpression*) node);
        break;

    case AST_BITWISE_AND:
        visit_bitwise_and((ast::BinaryExpression*) node);
        break;

    case AST_BITWISE_XOR:
        visit_bitwise_xor((ast::BinaryExpression*) node);
        break;

    case AST_BITWISE_OR:
        visit_bitwise_or((ast::BinaryExpression*) node);
        break;

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

    case AST_LT:
        visit_lt((ast::BinaryExpression*) node);
        break;

    case AST_GT:
        visit_gt((ast::BinaryExpression*) node);
        break;

    case AST_LE:
        visit_le((ast::BinaryExpression*) node);
        break;

    case AST_GE:
        visit_ge((ast::BinaryExpression*) node);
        break;

    case AST_EQ:
        visit_eq((ast::BinaryExpression*) node);
        break;

    case AST_NE:
        visit_ne((ast::BinaryExpression*) node);
        break;

    case AST_LOGICAL_AND:
        visit_logical_and((ast::BinaryExpression*) node);
        break;

    case AST_LOGICAL_OR:
        visit_logical_or((ast::BinaryExpression*) node);
        break;

    case AST_ASSIGNMENT:
        visit_assignment((BinaryExpression*) node);
        break;

    // types
    case AST_NAMED_TYPE:
        visit_named_type((ast::NamedType*) node);
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
    current_scope = source_file->get_scope();
    current_scope->set_name("source");

    for (int i = 0; i < source_file->imports_count(); ++i) {
        current_scope->add_sibling(source_file->get_import(i)->get_source_file()->get_scope());
    }

    for (int i = 0; i < source_file->classes_count(); ++i) {
        visit(source_file->get_class(i));
    }

    for (int i = 0; i < source_file->functions_count(); ++i) {
        visit(source_file->get_function(i));
    }
}

void ScopeBuilder::visit_class(ast::Class* klass) {
    int var_counter = 0;

    set_new_scope(klass->get_scope());
    current_scope->set_name(klass->get_name().get_value());

    std::cout << "as type\n";
    visit(klass->get_as_type());

    for (int i = 0; i < klass->variables_count(); ++i) {
        std::stringstream ss;
        Variable* var = klass->get_variable(i);
        ss << "cv" << var_counter << "_" << var->get_name().get_value();
        var->set_unique_id(ss.str());
        ++var_counter;
        std::string name = var->get_name().get_value();
        current_scope->define(new Symbol(SYM_CLASS_VAR, name, var));
    }

    for (int i = 0; i < klass->methods_count(); ++i) {
        visit(klass->get_method(i));
    }
    
    restore_scope();
}

void ScopeBuilder::visit_function(ast::Function* function) {
    set_new_scope(function->get_scope());
    current_function = function;
    int lvar_counter = 0;

    add_parameters(function);
    visit(function->get_return_type());
    visit(function->get_statements());
   
    for (int i = 0; i < function->local_variables_count(); ++i) {
        std::stringstream ss;
        Variable* var = function->get_local_variable(i);
        ss << "lv" << lvar_counter << "_" << var->get_name().get_value();
        var->set_unique_id(ss.str());
        ++lvar_counter;
        std::cout << var->get_name().get_value() << '\n';
    }

    restore_scope();
}

void ScopeBuilder::visit_method(ast::Method* method) {
    visit_function(method);
}

void ScopeBuilder::visit_compound_statement(ast::CompoundStatement* statements) {
    for (int i = 0; i < statements->statements_count(); ++i) {
        visit(statements->get_statement(i));
    }
}

void ScopeBuilder::visit_if_statement(ast::IfStatement* stmt) {
    set_new_scope(stmt->get_scope());

    visit(stmt->get_expression());
    visit(stmt->get_true_statements());

    restore_scope();

    if (stmt->get_false_statements()) {
        visit(stmt->get_false_statements());
    }
}

void ScopeBuilder::visit_elif_statement(ast::ElifStatement* stmt) {
    set_new_scope(stmt->get_scope());

    visit(stmt->get_expression());
    visit(stmt->get_true_statements());

    restore_scope();

    if (stmt->get_false_statements()) {
        visit(stmt->get_false_statements());
    }
}

void ScopeBuilder::visit_else_statement(ast::ElseStatement* stmt) {
    set_new_scope(stmt->get_scope());

    visit(stmt->get_statements());
    restore_scope();
}

void ScopeBuilder::visit_while_statement(ast::WhileStatement* stmt) {
    set_new_scope(stmt->get_scope());

    visit(stmt->get_expression());
    visit(stmt->get_statements());

    restore_scope();
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
        std::cout << "Error: symbol '" << name << "' not defined\n";
        current_scope->debug();
        std::cout << hdc_astkind_map.at(id->get_parent_node()->get_kind()) << std::endl;
        exit(0);
    } else {
        id->set_symbol(symbol);
        id->set_scope(current_scope);
        id->set_type(symbol->get_type());
    }
}

void ScopeBuilder::visit_literal_char(ast::LiteralExpression* literal) {
    literal->set_type(new Type(AST_CHAR_TYPE));
}

void ScopeBuilder::visit_literal_string(ast::LiteralExpression* literal) {
    literal->set_type(new Type(AST_STRING_TYPE));
}

void ScopeBuilder::visit_literal_symbol(ast::LiteralExpression* literal) {
    literal->set_type(new Type(AST_SYMBOL_TYPE));
}

void ScopeBuilder::visit_literal_null(ast::LiteralExpression* literal) {
    literal->set_type(new Type(AST_NULL_TYPE));
}

void ScopeBuilder::visit_literal_bool(ast::LiteralExpression* literal) {
    literal->set_type(new Type(AST_BOOL_TYPE));
}

void ScopeBuilder::visit_literal_integer(ast::LiteralExpression* literal) {
    literal->set_type(new Type(AST_INT_TYPE));
}

void ScopeBuilder::visit_literal_float(ast::LiteralExpression* literal) {
    literal->set_type(new Type(AST_FLOAT_TYPE));
}

void ScopeBuilder::visit_literal_double(ast::LiteralExpression* literal) {
    literal->set_type(new Type(AST_DOUBLE_TYPE));
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
        visit_identifier_call((ast::Identifier*) left);
        call->set_type(left->get_type());
    }

    visit(right);
}

void ScopeBuilder::visit_sll(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_sra(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_srl(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_bitwise_and(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_bitwise_xor(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_bitwise_or(ast::BinaryExpression* bin) {
    visit_binop(bin);
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

void ScopeBuilder::visit_lt(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_gt(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_le(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_ge(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_eq(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_ne(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_logical_and(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_logical_or(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_assignment(ast::BinaryExpression* bin) {
    Expression* left = bin->get_left();
    Expression* right = bin->get_right();

    visit(right);

    if (left->get_kind() == AST_IDENTIFIER) {
        create_new_variable((Identifier*) left, right->get_type());
    }
}

void ScopeBuilder::visit_named_type(ast::NamedType* type) {
    visit(type->get_id());
}

void ScopeBuilder::create_new_variable(ast::Identifier* id, ast::Type* type) {
    Symbol* symbol = nullptr;
    std::string name = id->get_name().get_value();
    std::string alias = id->get_alias().get_value();

    symbol = current_scope->resolve(name);

    if (type == nullptr) {
        type = new Type(AST_INT_TYPE);
    }

    if (symbol == nullptr) {
        Variable* var = new Variable(AST_LOCAL_VARIABLE);
        var->set_name(id->get_name());
        var->set_type(type);
        symbol = new Symbol(SYM_VAR, name, var);
        current_scope->define(symbol);
        current_function->add_variable(var);
    }

    id->set_symbol(symbol);
    id->set_scope(current_scope);
    id->set_type(type);
}

void ScopeBuilder::visit_identifier_call(ast::Identifier* id) {
    Symbol* symbol = nullptr;
    std::string name = id->get_name().get_value();
    std::string alias = id->get_alias().get_value();
    ast::Function* f;
    ast::Class* klass;

    symbol = current_scope->resolve(name);

    if (symbol == nullptr) {
        std::cout << "Error: symbol '" << name << "' not defined\n";
        current_scope->debug();
        exit(0);
    } else {
        if (symbol->get_kind() == SYM_FUNCTION) {
            id->set_symbol(symbol);
            id->set_scope(current_scope);
            f = (ast::Function*) symbol->get_descriptor();
            id->set_type(f->get_return_type());
        } else if (symbol->get_kind() == SYM_CLASS) {
            id->set_symbol(symbol);
            id->set_scope(current_scope);
            klass = (ast::Class*) symbol->get_descriptor();
            Token tk = klass->get_name();
            ast::Identifier* idd = new Identifier();
            idd->set_name(tk);
            id->set_type(new NamedType(idd));
            visit_named_type((ast::NamedType*) id->get_type());
        }
    }
}

void ScopeBuilder::visit_binop(ast::BinaryExpression* bin) {
    visit(bin->get_left());
    visit(bin->get_right());
    bin->set_type(bin->get_left()->get_type());
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

        visit(var->get_type());

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
                ss << "p" << param_counter << "_" << name;
                var->set_unique_id(ss.str());
                ++param_counter;
            }
        }
    }
}

void ScopeBuilder::add_classes(ast::SourceFile* source_file) {
    for (int i = 0; i < source_file->classes_count(); ++i) {
        current_scope = source_file->get_scope();
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
        add_methods(klass);
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

void ScopeBuilder::add_methods(ast::Class* klass) {
    current_scope = klass->get_scope();

    for (int i = 0; i < klass->methods_count(); ++i) {
        add_method(klass->get_method(i), i);
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
        if (false) { // check for overload

        } else {
            std::string path = function->get_source_file()->get_path();
            Function* k = (Function*) symbol->get_descriptor();
            int line = k->get_name().get_line();
            std::cout << "\033[1;31mError\033[0m";
            std::cout << ": function '" << name << "' already defined\n";
            std::cout << "    First occurence on line " << line << " of file '" << path << "'\n";
        }
    }
}

void ScopeBuilder::add_method(ast::Method* method, int idx) {
    Symbol* symbol = nullptr;
    std::string name(method->get_name().get_value());
    std::stringstream ss;

    symbol = current_scope->resolve(name);

    if (symbol == nullptr) {
        define_symbol(SYM_METHOD, name, method);
        ss << "m" << idx << "_" << name;
        method->set_unique_id(ss.str());
    } else {
        if (false) { // check for overload

        } else {
            std::string path = method->get_source_file()->get_path();
            Function* k = (Function*) symbol->get_descriptor();
            int line = k->get_name().get_line();
            std::cout << "\033[1;31mError\033[0m";
            std::cout << ": method '" << name << "' already defined\n";
            std::cout << "    First occurence on line " << line << " of file '" << path << "'\n";
        }
    }
}

void ScopeBuilder::define_symbol(SymbolKind kind, std::string name, void* descriptor) {
    Symbol* symbol = new Symbol(kind, name, descriptor);
    current_scope->define(symbol);
}

void ScopeBuilder::set_new_scope(Scope* scope) {
    scope->set_enclosing_scope(current_scope);
    current_scope = scope;
}

void ScopeBuilder::restore_scope() {
    current_scope = current_scope->get_enclosing_scope();
}
