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

    std::cout << "end of test_scanner()\n";
}

void test_parser() {
    AST* root = nullptr;
    Parser parser;

    root = parser.read("import.hd");
    std::cout << "ast: " << root->to_str() << std::endl;
    std::cout << "the end" << std::endl;
    std::cout << "dot: " << root->to_dot() << std::endl;

    delete root;
}

int main(int argc, char* argv[]) {
    test_scanner();
    test_parser();

    return 0;
}
