#include <fstream>
#include <iostream>

#include "utils/string_pool.h"
#include "lex/lex.h"

using namespace hdc;

Lex::Lex() {
    /* Empty */
}

void Lex::read(const char* path) {
    char c;
    std::ifstream file;

    file.open(path);
    reset_state();

    while (file.get(c)) {
        buffer += c;
    }

    file.close();
}

Token Lex::get_token() {
    Token token;

    if (has_next()) {
        if (is_whitespace()) {
            skip_whitespace();
            return get_token();
        } else if (is_alpha()) {
            return get_keyword_or_identifier();
        }
    }

    return create_token(TK_EOF);
}

void Lex::reset_state() {
    buffer = "";
    state = LexState();
    state_stack = std::stack<LexState>();
}

void Lex::save_state() {
    state_stack.push(state);
}

void Lex::restore_state() {
    state = state_stack.top();
    state_stack.pop();
}

bool Lex::has_next() {
    return state.get_buffer_index() < buffer.size();
}

void Lex::advance() {
    if (!has_next())
        return;

    if (buffer[state.get_buffer_index()] == '\n') {
        state.increase_row();
        state.set_column(1);
        state.set_new_line(true);
    } else {
        state.increase_column();
    }

    state.add_to_lexeme(buffer[state.get_buffer_index()]);
    state.increase_buffer_index();
}

bool Lex::lookahead(char c) {
    int index = state.get_buffer_index();

    return index < buffer.size() && buffer[index] == c;
}

bool Lex::is_alpha() {
    int index = state.get_buffer_index();

    return buffer[index] >= 'a' && buffer[index] <= 'z' ||
           buffer[index] >= 'A' && buffer[index] <= 'Z' ||
           buffer[index] == '_';
}

bool Lex::is_digit() {
    int index = state.get_buffer_index();

    return buffer[index] >= '0' && buffer[index] <= '9';
}

bool Lex::is_operator() {
    std::string oper;

    oper += buffer[state.get_buffer_index()];
    return hdc_operators_map.count(oper) > 0;
}

bool Lex::is_whitespace() {
    return lookahead(' ');
}

void Lex::skip_whitespace() {
    while (is_whitespace()) {
        advance();
    }
}

Token Lex::get_keyword_or_identifier() {
    TokenKind kind = TK_ID;

    state.start_lexeme();

    while (is_alpha() || is_digit()) {
        advance();
    }

    if (hdc_keywords_map.count(state.get_lexeme()) > 0) {
        kind = hdc_keywords_map.at(state.get_lexeme());
    }

    return create_token(kind);
}

Token Lex::create_token(TokenKind kind) {
    Token token;

    token.set_kind(kind);
    token.set_line(state.get_lexeme_row());
    token.set_column(state.get_lexeme_column());
    token.set_value(StringPool::add(state.get_lexeme()));

    return token;
}
