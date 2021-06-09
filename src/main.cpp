#include <iostream>

#include "scanner/scanner.h"
#include "ast/ast.h"
#include "parser/parser.h"

using namespace hdc;

void test_scanner() {
    Scanner scanner;

    scanner.read("import.hd");

    while (true) {
        Token token = scanner.get_token();
        std::cout << token.to_str() << std::endl;

        if (token.get_kind() == TK_EOF) break;
    }
}

void test_parser() {
    AST* root;
    Parser parser;

    root = parser.read("import.hd");
    std::cout << "ast: " << root->to_str() << std::endl;
    std::cout << "the end" << std::endl;
}

int main(int argc, char* argv[]) {
    test_scanner();
    test_parser();

    return 0;
}
