#ifndef HDC_SCANNER_STATE_H
#define HDC_SCANNER_STATE_H

#include <stack>
#include <string>

#include "defs.h"

namespace hdc {
    class ScannerState {
        public:
            ScannerState();
            ScannerState(const ScannerState& other);

        public:
            void start_lexeme();

            int get_row();
            int get_column();
            int get_lexeme_row();
            int get_lexeme_column();
            int get_buffer_index();
            int get_n_spaces();
            bool get_new_line();
            bool get_template_flag();
            int get_template_counter();
            const std::string get_lexeme();
            int get_block_stack_size();
            int get_indentation_stack_top();

            void increase_row(int value=1);
            void increase_column(int value=1);
            void increase_buffer_index(int value=1);
            void increase_n_spaces(int value=1);
            void increase_template_counter_by(int value=1);
            void add_to_lexeme(char value);

            void set_row(int value);
            void set_column(int value);
            void set_buffer_index(int value);
            void set_n_spaces(int value);
            void set_new_line(bool value);
            void set_template_flag(bool value);
            void set_lexem(std::string& value);

            void indentation_stack_push(int value);
            void indentation_stack_pop();
            void block_stack_push(TokenKind value);
            void block_stack_pop();

        private:
            int row;
            int column;
            int lexeme_row;
            int lexeme_column;
            int buffer_index;
            int n_spaces;
            int template_counter;
            bool new_line;
            bool template_flag;

            std::string lexeme;
            std::stack<int> indentation_stack;
            std::stack<TokenKind> block_stack;
    };
}

#endif
