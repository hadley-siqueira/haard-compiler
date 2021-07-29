#include <iostream>

#include "scanner/scanner.h"
#include "ast/ast.h"

#include "ast/ast_node.h"
#include "ast/source_file.h"

#include "parser/parser.h"

using namespace hdc;
using namespace hdc::ast;

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
    SourceFile* node = nullptr;
    Parser parser;

    node = parser.read("import.hd");
}

int main(int argc, char* argv[]) {
    test_scanner();
    test_parser();

    return 0;
}
