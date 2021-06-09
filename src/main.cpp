#include <iostream>

#include "scanner/scanner.h"

using namespace hdc;

int main(int argc, char* argv[]) {
    Scanner lex;

    lex.read("foo.hd");

    while (true) {
        Token token = lex.get_token();
        std::cout << token.to_str() << std::endl;

        if (token.get_kind() == TK_EOF) break;
    }

    return 0;
}
