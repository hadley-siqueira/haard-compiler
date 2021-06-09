#include <iostream>

#include "scanner/scanner.h"
#include "ast/ast.h"

using namespace hdc;

int main(int argc, char* argv[]) {
    Scanner scanner;

    scanner.read("foo.hd");

    while (true) {
        Token token = scanner.get_token();
        std::cout << token.to_str() << std::endl;

        if (token.get_kind() == TK_EOF) break;
    }

    std::cout << "AST size: " << sizeof(AST) << std::endl;

    return 0;
}
