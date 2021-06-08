#include <iostream>

#include "lex/lex.h"

using namespace hdc;

int main(int argc, char* argv[]) {
    Lex lex;

    lex.read("foo.hd");

    while (true) {
        Token token = lex.get_token();
        std::cout << token.to_str() << std::endl;

        if (token.get_kind() == TK_EOF) break;
    }

    return 0;
}
