#include "token/token.h"

using namespace hdc;

/* Setters */
void Token::set_kind(TokenKind kind) {
    this->kind = kind;
}

void Token::set_line(int line) {
    this->line = line;
}

void Token::set_column(int column) {
    this->column = column;
}

void Token::set_value(char* value) {
    this->value = value;
}

/* Getters */
TokenKind Token::get_kind() {
    return kind;
}

int Token::get_line() {
    return line;
}

int Token::get_column() {
    return column;
}

char* Token::get_value() {
    return value;
}

