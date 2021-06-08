#include "lex/lex_state.h"

using namespace hdc;

LexState::LexState() {
    row = 1;
    column = 1;
    lexeme_row = 1;
    lexeme_column = 1;
    buffer_index = 0;
    new_line = true;
    indentation_stack.push(0);
}

LexState::LexState(const LexState& other) {
    row = other.row;
    column = other.column;
    lexeme_row = other.lexeme_row;
    lexeme_column = other.lexeme_column;
    buffer_index = other.buffer_index;
    new_line = other.new_line;
    lexeme = other.lexeme;
    indentation_stack = other.indentation_stack;
}

void LexState::start_lexeme() {
    lexeme = "";
    lexeme_row = row;
    lexeme_column = column;
}

int LexState::get_row() {
    return row;
}

int LexState::get_column() {
    return column;
}

int LexState::get_lexeme_row() {
    return lexeme_row;
}

int LexState::get_lexeme_column() {
    return lexeme_column;
}

int LexState::get_buffer_index() {
    return buffer_index;
}

bool LexState::get_new_line() {
    return new_line;
}

const std::string LexState::get_lexeme() {
    return lexeme;
}

void LexState::increase_row(int value) {
    row += value;
}

void LexState::increase_column(int value) {
    column += value;
}

void LexState::increase_buffer_index(int value) {
    buffer_index += value;
}

void LexState::add_to_lexeme(char value) {
    lexeme += value;
}

void LexState::set_row(int value) {
    row = value;
}

void LexState::set_column(int value) {
    column = value;
}

void LexState::set_buffer_index(int value) {
    buffer_index = value;
}

void LexState::set_new_line(bool value) {
    new_line = value;
}

void LexState::set_lexem(std::string& value) {
    lexeme = value;
}
