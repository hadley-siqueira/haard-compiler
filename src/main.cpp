#include <iostream>

#include "lex/lex.h"

using namespace hdc;

int main(int argc, char* argv[]) {
    Lex lex;

    lex.read("foo.hd");

    for (int i = 0; i < 30; ++i) {
        std::cout << lex.get_token().to_str() << std::endl;
    }

    return 0;
}
