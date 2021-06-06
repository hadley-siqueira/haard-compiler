#include <sstream>

#include "token/token.h"
#include "utils/utils.h"
#include "utils/string_pool.h"

using namespace hdc;

Token::Token() {
    this->kind = TK_UNKNOWN;
    this-> line = -1;
    this->column = -1;
    this->value = nullptr;
}

Token::Token(TokenKind kind, int line, int column, const char* value) {
    this->kind = kind;
    this->line = line;
    this->column = column;
    this->value = StringPool::add(value);
}

std::string Token::to_str() {
    std::stringstream builder;

    builder << "(";
    builder << get_token_kind_as_string(kind) << ' ';
    builder << line << ' ' << column;

    if (value != nullptr) {
        builder << ' ' << value;
    }

    builder << ')';

    return builder.str();
}

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

void Token::set_value(const char* value) {
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

const char* Token::get_value() {
    return value;
}

