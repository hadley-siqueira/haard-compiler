#ifndef HDC_LEX_STATE_H
#define HDC_LEX_STATE_H

#include <stack>
#include <string>

#include "defs.h"

namespace hdc {
    class LexState {
        public:
            LexState();
            LexState(const LexState& other);

        public:
            void start_lexeme();

            int get_row();
            int get_column();
            int get_lexeme_row();
            int get_lexeme_column();
            int get_buffer_index();
            bool get_new_line();
            const std::string get_lexeme();

            void increase_row(int value=1);
            void increase_column(int value=1);
            void increase_buffer_index(int value=1);
            void add_to_lexeme(char value);

            void set_row(int value);
            void set_column(int value);
            void set_buffer_index(int value);
            void set_new_line(bool value);
            void set_lexem(std::string& value);

        private:
            int row;
            int column;
            int lexeme_row;
            int lexeme_column;
            int buffer_index;
            bool new_line;

            std::string lexeme;
            std::stack<int> indentation_stack;
            std::stack<TokenKind> block_stack;
    };
}

#endif
