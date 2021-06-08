#include "lex/lex_state.h"

using namespace hdc;

LexState::LexState() {
    row = 1;
    column = 1;
    buffer_index = 0;
    new_line = true;
    indentation_stack.push(0);
}

LexState::LexState(const LexState& other) {
    row = other.row;
    column = other.column;
    buffer_index = other.buffer_index;
    new_line = other.new_line;
    indentation_stack = other.indentation_stack;
}

int LexState::get_row() {
    return row;
}

int LexState::get_column() {
    return column;
}

int LexState::get_buffer_index() {
    return buffer_index;
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
