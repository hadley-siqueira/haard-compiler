#include <iostream>

#include "scanner/scanner.h"
#include "ast/ast.h"

#include "ast/ast_node.h"
#include "ast/source_file.h"

#include "parser/parser.h"

#include "driver/driver.h"

using namespace hdc;
using namespace hdc::ast;

void test_scanner(char* path) {
    Scanner scanner;

    scanner.read(path);

    while (true) {
        Token token = scanner.get_token();
        std::cout << token.to_str() << std::endl;

        if (token.get_kind() == TK_EOF) break;
    }

    std::cout << "end of test_scanner()\n";
}

void test_parser(char* path) {
    SourceFile* node = nullptr;
    Parser parser;

    node = parser.read(path);
    delete node;
}

void test_driver(int argc, char* argv[]) {
    Driver driver;

    driver.set_flags(argc, argv);
    driver.run();
}

int main(int argc, char* argv[]) {
//    test_scanner(argv[1]);
//    test_parser(argv[1]);
    test_driver(argc, argv);

    return 0;
}
