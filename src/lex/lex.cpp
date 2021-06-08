#include <fstream>

#include "lex/lex.h"

using namespace hdc;

Lex::Lex() {
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

    state.increase_buffer_index();
}
