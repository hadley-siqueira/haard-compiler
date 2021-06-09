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
    if (has_next()) {
        if (lookahead('\n')) {
            if (!state.get_new_line() && state.get_block_stack_size() == 0) {
                state.start_lexeme();
                advance();
                return create_token(TK_NEWLINE);
            } else {
                advance();
                return get_token();
            }
        } else if (is_whitespace()) {
            skip_whitespace();
            return get_token();
        } else if (lookahead('#')) {
            skip_comment();
            return get_token();
        } else if (state.get_new_line()) {
            return get_indentation();
        } else if (is_digit()) {
            return get_number();
        } else if (is_alpha()) {
            return get_keyword_or_identifier();
        } else if (is_operator()) {
            return get_operator();
        }
    }

    state.start_lexeme();

    if (state.get_indentation_stack_top() != 0) {
        state.indentation_stack_pop();
        return create_token(TK_END);
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
        state.set_n_spaces(0);
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

bool Lex::is_binary_digit() {
    int index = state.get_buffer_index();

    return buffer[index] == '0' || buffer[index] == '1';
}

bool Lex::is_octal_digit() {
    int index = state.get_buffer_index();

    return buffer[index] >= '0' && buffer[index] <= '7';
}

bool Lex::is_hexa_digit() {
    int index = state.get_buffer_index();

    return buffer[index] >= '0' && buffer[index] <= '9' ||
           buffer[index] >= 'a' && buffer[index] <= 'f' ||
           buffer[index] >= 'A' && buffer[index] <= 'F';
}

bool Lex::has_base() {
    int index = state.get_buffer_index();

    if (index + 2 >= buffer.size()) {
        return false;
    }

    char base = buffer[index + 1];
    bool flag1 = base == 'o' || base == 'b' || base == 'x';
    bool flag2 = base >= '0' && base <= '7';

    return buffer[index] == '0' && (flag1 || flag2);
}

void Lex::skip_whitespace() {
    state.set_n_spaces(0);

    while (is_whitespace()) {
        advance();
        state.increase_n_spaces();
    }
}

void Lex::skip_comment() {
    while (!lookahead('\n')) {
        advance();
    }
}

Token Lex::get_indentation() {
    state.start_lexeme();

    if (state.get_block_stack_size() > 0) {
        state.set_new_line(false);
        return get_token();
    }

    int n_spaces = state.get_n_spaces();

    if (n_spaces > state.get_indentation_stack_top()) {
        state.indentation_stack_push(n_spaces);
        return create_token(TK_BEGIN);
    } else if (n_spaces < state.get_indentation_stack_top()) {
        state.indentation_stack_pop();
        return create_token(TK_END);
    }

    state.set_new_line(false);
    return get_token();
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

Token Lex::get_number() {
    TokenKind kind = TK_LITERAL_INTEGER;

    state.start_lexeme();

    if (has_base()) {
        advance();

        if (lookahead('b')) {
            advance();

            while (is_binary_digit()) {
                advance();
            }
        } else if (lookahead('o')) {
            advance();

            while (is_octal_digit()) {
                advance();
            }
        } else if (lookahead('x')) {
            advance();

            while (is_hexa_digit()) {
                advance();
            }
        } else {
            while (is_octal_digit()) {
                advance();
            }
        }
    } else {
        while (is_digit()) {
            advance();
        }

        if (lookahead('.')) {
            kind = TK_LITERAL_DOUBLE;
            advance();

            while (is_digit()) {
                advance();
            }
        }

        if (lookahead('e') || lookahead('E')) {
            kind = TK_LITERAL_DOUBLE;
            advance();

            if (lookahead('-') || lookahead('+')) {
                advance();
            }

            while (is_digit()) {
                advance();
            }
        }

        if (lookahead('f') || lookahead('F')) {
            kind = TK_LITERAL_FLOAT;
            advance();
        }
    }

    return create_token(kind);
}

Token Lex::get_operator() {

}

Token Lex::create_token(TokenKind kind) {
    Token token;

    token.set_kind(kind);
    token.set_line(state.get_lexeme_row());
    token.set_column(state.get_lexeme_column());
    token.set_value(StringPool::add(state.get_lexeme()));

    return token;
}
