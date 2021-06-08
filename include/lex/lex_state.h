#ifndef HDC_LEX_STATE_H
#define HDC_LEX_STATE_H

#include <stack>

#include "defs.h"

namespace hdc {
    class LexState {
        public:
            LexState();
            LexState(const LexState& other);

        public:
            int get_row();
            int get_column();
            int get_buffer_index();

            void increase_row(int value=1);
            void increase_column(int value=1);
            void increase_buffer_index(int value=1);

            void set_row(int value);
            void set_column(int value);
            void set_buffer_index(int value);
            void set_new_line(bool value);

        private:
            int row;
            int column;
            int buffer_index;
            bool new_line;

            std::stack<int> indentation_stack;
            std::stack<TokenKind> block_stack;
    };
}

#endif
