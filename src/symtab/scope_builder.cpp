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

    case AST_IMPORT:
        visit_import((ast::Import*) node);
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

    case AST_RETURN:
        visit_return_statement((ast::ExpressionStatement*) node);
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

    // special operations
    case AST_PARENTHESIS:
        visit_parenthesis((ast::UnaryExpression*) node);
        break;

    case AST_DOLAR:
        visit_dolar((ast::UnaryExpression*) node);
        break;

    case AST_DOT:
        visit_dot((ast::BinaryExpression*) node);
        break;

    case AST_ARROW:
        visit_arrow((ast::BinaryExpression*) node);
        break;

    case AST_INDEX:
        visit_index((ast::BinaryExpression*) node);
        break;

    case AST_CALL:
        visit_call((ast::BinaryExpression*) node);
        break;

    case AST_NEW:
        visit_new((ast::NewExpression*) node);
        break;

    case AST_AT:
        visit_at((ast::UnaryExpression*) node);
        break;

    case AST_EXPRESSION_LIST:
        visit_expression_list((ast::ExpressionList*) node);
        break;

    // Unary Operators
    case AST_ADDRESS_OF:
        visit_address_of((ast::UnaryExpression*) node);
        break;

    case AST_DEREFERENCE:
        visit_dereference((ast::UnaryExpression*) node);
        break;

    case AST_UNARY_MINUS:
        visit_unary_minus((ast::UnaryExpression*) node);
        break;

    case AST_UNARY_PLUS:
        visit_unary_plus((ast::UnaryExpression*) node);
        break;

    case AST_PRE_INC:
        visit_pre_inc((ast::UnaryExpression*) node);
        break;

    case AST_PRE_DEC:
        visit_pre_dec((ast::UnaryExpression*) node);
        break;

    case AST_POS_INC:
        visit_pos_inc((ast::UnaryExpression*) node);
        break;

    case AST_POS_DEC:
        visit_pos_dec((ast::UnaryExpression*) node);
        break;

    case AST_LOGICAL_NOT:
        visit_logical_not((ast::UnaryExpression*) node);
        break;

    case AST_BITWISE_NOT:
        visit_bitwise_not((ast::UnaryExpression*) node);
        break;

    case AST_SIZEOF:
        visit_sizeof((ast::UnaryExpression*) node);
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

    // relational operators
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

    // equality operators
    case AST_EQ:
        visit_eq((ast::BinaryExpression*) node);
        break;

    case AST_NE:
        visit_ne((ast::BinaryExpression*) node);
        break;

    // logical operators
    case AST_LOGICAL_AND:
        visit_logical_and((ast::BinaryExpression*) node);
        break;

    case AST_LOGICAL_OR:
        visit_logical_or((ast::BinaryExpression*) node);
        break;

    // range operators
    case AST_INCLUSIVE_RANGE:
        visit_inclusive_range((ast::BinaryExpression*) node);
        break;

    case AST_EXCLUSIVE_RANGE:
        visit_exclusive_range((ast::BinaryExpression*) node);
        break;

    case AST_ASSIGNMENT:
        visit_assignment((BinaryExpression*) node);
        break;

    case AST_BITWISE_AND_ASSIGNMENT:
        visit_bitwise_and_assignment((BinaryExpression*) node);
        break;

    case AST_BITWISE_XOR_ASSIGNMENT:
        visit_bitwise_xor_assignment((BinaryExpression*) node);
        break;

    case AST_BITWISE_OR_ASSIGNMENT:
        visit_bitwise_or_assignment((ast::BinaryExpression*) node);
        break;

    case AST_BITWISE_NOT_ASSIGNMENT:
        visit_bitwise_not_assignment((ast::BinaryExpression*) node);
        break;

    case AST_DIVISION_ASSIGNMENT:
        visit_division_assignment((ast::BinaryExpression*) node);
        break;

    case AST_INTEGER_DIVISION_ASSIGNMENT:
        visit_integer_division_assignment((ast::BinaryExpression*) node);
        break;

    case AST_MINUS_ASSIGNMENT:
        visit_minus_assignment((ast::BinaryExpression*) node);
        break;

    case AST_MODULO_ASSIGNMENT:
        visit_modulo_assignment((ast::BinaryExpression*) node);
        break;

    case AST_PLUS_ASSIGNMENT:
        visit_plus_assignment((ast::BinaryExpression*) node);
        break;

    case AST_TIMES_ASSIGNMENT:
        visit_times_assignment((ast::BinaryExpression*) node);
        break;

    case AST_SLL_ASSIGNMENT:
        visit_sll_assignment((ast::BinaryExpression*) node);
        break;

    case AST_SRA_ASSIGNMENT:
        visit_sra_assignment((ast::BinaryExpression*) node);
        break;

    case AST_SRL_ASSIGNMENT:
        visit_srl_assignment((ast::BinaryExpression*) node);
        break;

    case AST_SPECIAL_ASSIGNMENT:
        visit_special_assignment((ast::BinaryExpression*) node);
        break;

    // types
    case AST_VOID_TYPE:
        visit_void_type((ast::Type*) node);
        break;

    case AST_INT_TYPE:
        visit_int_type((ast::Type*) node);
        break;

    case AST_UINT_TYPE:
        visit_uint_type((ast::Type*) node);
        break;

    case AST_FLOAT_TYPE:
        visit_float_type((ast::Type*) node);
        break;

    case AST_DOUBLE_TYPE:
        visit_double_type((ast::Type*) node);
        break;

    case AST_SHORT_TYPE:
        visit_short_type((ast::Type*) node);
        break;

    case AST_USHORT_TYPE:
        visit_ushort_type((ast::Type*) node);
        break;

    case AST_LONG_TYPE:
        visit_long_type((ast::Type*) node);
        break;

    case AST_ULONG_TYPE:
        visit_ulong_type((ast::Type*) node);
        break;

    case AST_CHAR_TYPE:
        visit_char_type((ast::Type*) node);
        break;

    case AST_UCHAR_TYPE:
        visit_uchar_type((ast::Type*) node);
        break;

    case AST_SYMBOL_TYPE:
        visit_symbol_type((ast::Type*) node);
        break;

    case AST_BOOL_TYPE:
        visit_bool_type((ast::Type*) node);
        break;

    case AST_STRING_TYPE:
        visit_string_type((ast::Type*) node);
        break;

    case AST_NULL_TYPE:
        visit_null_type((ast::Type*) node);
        break;

    case AST_I8_TYPE:
        visit_i8_type((ast::Type*) node);
        break;

    case AST_I16_TYPE:
        visit_i16_type((ast::Type*) node);
        break;

    case AST_I32_TYPE:
        visit_i32_type((ast::Type*) node);
        break;

    case AST_I64_TYPE:
        visit_i64_type((ast::Type*) node);
        break;

    case AST_U8_TYPE:
        visit_u8_type((ast::Type*) node);
        break;

    case AST_U16_TYPE:
        visit_u16_type((ast::Type*) node);
        break;

    case AST_U32_TYPE:
        visit_u32_type((ast::Type*) node);
        break;

    case AST_U64_TYPE:
        visit_u64_type((ast::Type*) node);
        break;

    case AST_POINTER_TYPE:
        visit_pointer_type((ast::IndirectionType*) node);
        break;

    case AST_REFERENCE_TYPE:
        visit_reference_type((ast::IndirectionType*) node);
        break;

    case AST_ARRAY_TYPE:
        visit_array_type((ast::ArrayType*) node);
        break;

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
        visit(source_file->get_import(i));
    }

    for (int i = 0; i < source_file->classes_count(); ++i) {
        visit(source_file->get_class(i));
    }

    for (int i = 0; i < source_file->functions_count(); ++i) {
        visit(source_file->get_function(i));
    }
}

void ScopeBuilder::visit_import(ast::Import* import) {
    current_scope->add_sibling(import->get_source_file()->get_scope());
}

void ScopeBuilder::visit_class(ast::Class* klass) {
    int var_counter = 0;

    set_new_scope(klass->get_scope());
    current_scope->set_name(klass->get_name().get_value());

    visit(klass->get_as_type());

    for (int i = 0; i < klass->variables_count(); ++i) {
        build_variable(klass->get_variable(i), "cv", var_counter, SYM_CLASS_VAR);
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

        // build_variable(var. "lv", counter, SYM_CLASS_VAR);
    }

    restore_scope();
}

void ScopeBuilder::build_variable(ast::Variable* var, const char* prefix, int& counter, SymbolKind kind) {
    std::stringstream ss;
    ss << prefix << counter << "_" << var->get_name().get_value();
    visit(var->get_type());
    var->set_unique_id(ss.str());
    ++counter;
    std::string name = var->get_name().get_value();
    define_symbol(kind, name, var);
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

void ScopeBuilder::visit_return_statement(ast::ExpressionStatement* stmt) {
    if (stmt->get_expression() != nullptr) {
        visit(stmt->get_expression());
    }
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

void ScopeBuilder::visit_parenthesis(ast::UnaryExpression* node) {
    visit(node->get_expression());
    node->set_type(node->get_expression()->get_type());
}

void ScopeBuilder::visit_dolar(ast::UnaryExpression* node) {
    /* Empty */
}

void ScopeBuilder::visit_dot(ast::BinaryExpression* node) {
    ast::Type* type;
    ast::NamedType* ntype;
    ast::Class* klass;
    ast::Identifier* id;
    Symbol* symbol;

    visit(node->get_left());
    type = node->get_left()->get_type();

    if (type->get_kind() == AST_NAMED_TYPE) {
        ntype = (ast::NamedType*) type;

        klass = (ast::Class*) ntype->get_id()->get_symbol()->get_descriptor();
        std::cout << (klass->get_name().get_value()) << std::endl;
        klass->get_scope()->debug();

        id = (ast::Identifier*) node->get_right();
        std::string name = id->get_name().get_value();
        symbol = klass->get_scope()->resolve(name);

        if (symbol == nullptr) {
            //std::cout << "Error: symbol '" << name << "' not defined\n";
            current_scope->debug();
            std::cout << hdc_astkind_map.at(id->get_parent_node()->get_kind()) << std::endl;
            exit(0);
        } else {
            id->set_symbol(symbol);
            id->set_scope(current_scope);
            id->set_type(symbol->get_type());
        }

        //exit(0);
    }
}

void ScopeBuilder::visit_arrow(ast::BinaryExpression* node) {
    visit_binop(node);
}

void ScopeBuilder::visit_index(ast::BinaryExpression* node) {
    visit_binop(node);
}

void ScopeBuilder::visit_call(ast::BinaryExpression* call) {
    ast::Expression* left = call->get_left();
    ast::Expression* right = call->get_right();

    if (left->get_kind() == AST_IDENTIFIER) {
        visit_identifier_call((ast::Identifier*) left);
        call->set_type(left->get_type());
    } else if (left->get_kind() == AST_DOT) {
        visit_dot((ast::BinaryExpression*) left);
    }

    visit(right);
}

void ScopeBuilder::visit_new(ast::NewExpression* node) {
    visit(node->get_build_type());

    node->set_type(new IndirectionType(AST_POINTER_TYPE, node->get_build_type()));
}

void ScopeBuilder::visit_at(ast::UnaryExpression* node) {
    ast::Identifier* id;
    Symbol* symbol;

    id = (ast::Identifier*) node->get_expression();
    std::string name = id->get_name().get_value();
    symbol = current_scope->resolve_member(name);

    if (symbol == nullptr) {
        std::cout << "Error: no member named '" << name << "'\n";
        exit(0);
    } else {
        id->set_symbol(symbol);
        id->set_scope(current_scope);
        id->set_type(symbol->get_type());
        node->set_type(symbol->get_type());
    }
}

void ScopeBuilder::visit_address_of(ast::UnaryExpression* node) {
    visit(node->get_expression());
    node->set_type(new ast::IndirectionType(AST_POINTER_TYPE, node->get_expression()->get_type()));
}

void ScopeBuilder::visit_dereference(ast::UnaryExpression* node) {
    ast::IndirectionType* p;
    ast::Type* type;

    visit(node->get_expression());
    type = node->get_expression()->get_type();

    if (type->get_kind() != AST_POINTER_TYPE) {
        std::cout << "Error: invalid dereference\n";
        exit(0);
    }

    p = (ast::IndirectionType*) type;
    node->set_type(p->get_subtype());
}

void ScopeBuilder::visit_unary_minus(ast::UnaryExpression* node) {
    visit(node->get_expression());
}

void ScopeBuilder::visit_unary_plus(ast::UnaryExpression* node) {
    visit(node->get_expression());
}

void ScopeBuilder::visit_pre_inc(ast::UnaryExpression* node) {
    visit(node->get_expression());
}

void ScopeBuilder::visit_pre_dec(ast::UnaryExpression* node) {
    visit(node->get_expression());
}

void ScopeBuilder::visit_pos_inc(ast::UnaryExpression* node) {
    visit(node->get_expression());
}

void ScopeBuilder::visit_pos_dec(ast::UnaryExpression* node) {
    visit(node->get_expression());
}

void ScopeBuilder::visit_logical_not(ast::UnaryExpression* node) {
    visit(node->get_expression());
}

void ScopeBuilder::visit_bitwise_not(ast::UnaryExpression* node) {
    visit(node->get_expression());
}

void ScopeBuilder::visit_sizeof(ast::UnaryExpression* node) {
    visit(node->get_expression());
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

void ScopeBuilder::visit_inclusive_range(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_exclusive_range(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_assignment(ast::BinaryExpression* bin) {
    Expression* left = bin->get_left();
    Expression* right = bin->get_right();

    current_scope->debug(); std::cout << '\n';
    visit(right);

    if (left->get_kind() == AST_IDENTIFIER) {
        create_new_variable((Identifier*) left, right->get_type());
    } else {
        visit(left);
    }
}

void ScopeBuilder::visit_bitwise_and_assignment(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_bitwise_xor_assignment(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_bitwise_or_assignment(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_bitwise_not_assignment(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_division_assignment(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_integer_division_assignment(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_minus_assignment(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_modulo_assignment(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_plus_assignment(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_times_assignment(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_sll_assignment(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_sra_assignment(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_srl_assignment(ast::BinaryExpression* bin) {
    visit_binop(bin);
}

void ScopeBuilder::visit_special_assignment(ast::BinaryExpression* bin) {
    visit_binop(bin);
}


// Types
void ScopeBuilder::visit_void_type(ast::Type* type) {

}

void ScopeBuilder::visit_int_type(ast::Type* type) {

}

void ScopeBuilder::visit_uint_type(ast::Type* type) {

}

void ScopeBuilder::visit_float_type(ast::Type* type) {

}

void ScopeBuilder::visit_double_type(ast::Type* type) {

}

void ScopeBuilder::visit_short_type(ast::Type* type) {

}

void ScopeBuilder::visit_ushort_type(ast::Type* type) {

}

void ScopeBuilder::visit_long_type(ast::Type* type) {

}

void ScopeBuilder::visit_ulong_type(ast::Type* type) {

}

void ScopeBuilder::visit_char_type(ast::Type* type) {

}

void ScopeBuilder::visit_uchar_type(ast::Type* type) {

}

void ScopeBuilder::visit_symbol_type(ast::Type* type) {

}

void ScopeBuilder::visit_bool_type(ast::Type* type) {

}

void ScopeBuilder::visit_string_type(ast::Type* type) {

}

void ScopeBuilder::visit_null_type(ast::Type* type) {

}

void ScopeBuilder::visit_i8_type(ast::Type* type) {

}

void ScopeBuilder::visit_i16_type(ast::Type* type) {

}

void ScopeBuilder::visit_i32_type(ast::Type* type) {

}

void ScopeBuilder::visit_i64_type(ast::Type* type) {

}

void ScopeBuilder::visit_u8_type(ast::Type* type) {

}

void ScopeBuilder::visit_u16_type(ast::Type* type) {

}

void ScopeBuilder::visit_u32_type(ast::Type* type) {

}

void ScopeBuilder::visit_u64_type(ast::Type* type) {

}

void ScopeBuilder::visit_pointer_type(ast::IndirectionType* type) {
    visit(type->get_subtype());
}

void ScopeBuilder::visit_reference_type(ast::IndirectionType* type) {
    visit(type->get_subtype());
}

void ScopeBuilder::visit_array_type(ast::ArrayType* type) {
    visit(type->get_subtype());

    if (type->get_expression()) {
        visit(type->get_expression());
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
        } else if (symbol->get_kind() == SYM_METHOD) {
            id->set_symbol(symbol);
            id->set_scope(current_scope);
            f = (ast::Method*) symbol->get_descriptor();
            id->set_type(f->get_return_type());
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
    current_scope->define(new Symbol(kind, name, descriptor));
}

void ScopeBuilder::set_new_scope(Scope* scope) {
    scope->set_enclosing_scope(current_scope);
    current_scope = scope;
}

void ScopeBuilder::restore_scope() {
    current_scope = current_scope->get_enclosing_scope();
}
