#include "scanner/scanner_state.h"

using namespace hdc;

ScannerState::ScannerState() {
    row = 1;
    column = 1;
    lexeme_row = 1;
    lexeme_column = 1;
    buffer_index = 0;
    n_spaces = 0;
    new_line = true;
    template_flag = false;
    indentation_stack.push(0);
}

ScannerState::ScannerState(const ScannerState& other) {
    row = other.row;
    column = other.column;
    lexeme_row = other.lexeme_row;
    lexeme_column = other.lexeme_column;
    buffer_index = other.buffer_index;
    n_spaces = other.n_spaces;
    new_line = other.new_line;
    template_flag = other.template_flag;
    lexeme = other.lexeme;
    indentation_stack = other.indentation_stack;
}

void ScannerState::start_lexeme() {
    lexeme = "";
    lexeme_row = row;
    lexeme_column = column;
}

int ScannerState::get_row() {
    return row;
}

int ScannerState::get_column() {
    return column;
}

int ScannerState::get_lexeme_row() {
    return lexeme_row;
}

int ScannerState::get_lexeme_column() {
    return lexeme_column;
}

int ScannerState::get_buffer_index() {
    return buffer_index;
}

int ScannerState::get_n_spaces() {
    return n_spaces;
}

bool ScannerState::get_new_line() {
    return new_line;
}

bool ScannerState::get_template_flag() {
    return template_flag;
}

const std::string ScannerState::get_lexeme() {
    return lexeme;
}

int ScannerState::get_block_stack_size() {
    return block_stack.size();
}

int ScannerState::get_indentation_stack_top() {
    return indentation_stack.top();
}

void ScannerState::increase_row(int value) {
    row += value;
}

void ScannerState::increase_column(int value) {
    column += value;
}

void ScannerState::increase_buffer_index(int value) {
    buffer_index += value;
}

void ScannerState::increase_n_spaces(int value) {
    n_spaces += value;
}

void ScannerState::add_to_lexeme(char value) {
    lexeme += value;
}

void ScannerState::set_row(int value) {
    row = value;
}

void ScannerState::set_column(int value) {
    column = value;
}

void ScannerState::set_buffer_index(int value) {
    buffer_index = value;
}

void ScannerState::set_n_spaces(int value) {
    n_spaces = value;
}

void ScannerState::set_new_line(bool value) {
    new_line = value;
}

void ScannerState::set_template_flag(bool value) {
    template_flag = value;
}

void ScannerState::set_lexem(std::string& value) {
    lexeme = value;
}

void ScannerState::indentation_stack_push(int value) {
    indentation_stack.push(value);
}

void ScannerState::indentation_stack_pop() {
    indentation_stack.pop();
}

void ScannerState::block_stack_push(TokenKind value) {
    block_stack.push(value);
}

void ScannerState::block_stack_pop() {
    block_stack.pop();
}
