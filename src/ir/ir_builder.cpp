#include <iostream>

#include "ir/ir_builder.h"

using namespace hdc;

IRBuilder::IRBuilder() {
    temp_counter = 0;
}

IRBuilder::~IRBuilder() {
    for (int i = 0; i < instructions.size(); ++i) {
        delete instructions[i];
    }
}

void IRBuilder::generate_program(ast::Program* program) {
    for (int i = 0; i < program->source_files_count(); ++i) {
        generate_source_file(program->get_source_file(i));
    }
}

void IRBuilder::generate_source_file(ast::SourceFile* source_file) {
    for (int i = 0; i < source_file->functions_count(); ++i) {
        generate_function(source_file->get_function(i));
    }
}

void IRBuilder::generate_function(ast::Function* function) {
    add_instruction(new IR(IR_LABEL, function->get_name().get_value()));
    reset_temporary_counter();
    generate_statements(function->get_statements());
}

void IRBuilder::generate_statement(ast::Statement* stmt) {
    switch (stmt->get_kind()) {
    case AST_IF:
        generate_if((ast::IfStatement*) stmt);
        break;

    case AST_ELIF:
    case AST_ELSE:
        break;

    default:
        generate_expression((ast::Expression*) stmt);
        break;
    }
}

void IRBuilder::generate_statements(ast::CompoundStatement* stmts) {
    for (int i = 0; i < stmts->statements_count(); ++i) {
        generate_statement(stmts->get_statement(i));
    }
}

void IRBuilder::generate_if(ast::IfStatement* stmt) {
    IR* ir = generate_expression(stmt->get_expression());
}

IR* IRBuilder::generate_expression(ast::Expression* expr) {
    ast::UnaryExpression* unary;
    IR* ir;

    switch (expr->get_kind()) {
    case AST_ASSIGNMENT:
        return generate_assignment((ast::BinaryExpression*) expr);

    case AST_PARENTHESIS:
        unary = (ast::UnaryExpression*) expr;
        return generate_expression(unary->get_expression());

    case AST_PLUS:
        return generate_binop(IR_PLUS, (ast::BinaryExpression*) expr);

    case AST_MINUS:
        return generate_binop(IR_MINUS, (ast::BinaryExpression*) expr);

    case AST_IDENTIFIER:
        //return generate_identifier((ast::Identifier*) expr);
        break;

    case AST_LITERAL_INTEGER:
        ast::LiteralExpression* l = (ast::LiteralExpression*) expr;
        int dst = new_temporary();
        ir = new IR(IR_INTEGER, dst, l->get_token().get_value());
        add_instruction(ir);
        return ir;
    }

    return nullptr;
}

IR* IRBuilder::generate_assignment(ast::BinaryExpression* expr) {
    ast::Identifier* id;
    ast::Variable* var;
    IR* ir;
    IR* right = generate_expression(expr->get_right());
    int offset;

    //mem[fp + var.offset] = tmp
    if (expr->get_left()->get_kind() == AST_IDENTIFIER) {
        id = (ast::Identifier*) expr->get_left();
        var = (ast::Variable*) id->get_symbol()->get_descriptor();
        offset = var->get_offset();
        ir = new IR(IR_SW_FP, offset, right->get_dst());
        add_instruction(ir);
    }

    return right;
}

IR* IRBuilder::generate_binop(IRKind kind, ast::BinaryExpression* expr) {
    IR* left = generate_expression(expr->get_left());
    IR* right = generate_expression(expr->get_right());

    int src1 = left->get_dst();
    int src2 = right->get_dst();
    int dst = new_temporary();

    IR* tmp = new IR(kind, dst, src1, src2);
    add_instruction(tmp);

    return tmp;
}

IR* get_value(ast::Expression* expr) {
    return nullptr;
}

int IRBuilder::new_temporary() {
    return temp_counter++;
}

void IRBuilder::reset_temporary_counter() {
    temp_counter = 0;
}

void IRBuilder::add_instruction(IR* ir) {
    instructions.push_back(ir);
}

void IRBuilder::debug() {
    for (int i = 0; i < instructions.size(); ++i) {
        if (instructions[i]->get_kind() != IR_LABEL) {
            std::cout << "    ";
        }

        std::cout << instructions[i]->to_str() << std::endl;
    }
}

