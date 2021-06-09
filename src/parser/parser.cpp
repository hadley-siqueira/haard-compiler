#include <iostream>

#include "defs.h"
#include "parser/parser.h"

using namespace hdc;

AST* Parser::read(const char* path) {
    AST* node = new AST(AST_SOURCEFILE);

    scanner.read(path);
    advance();

    while (true) {
        if (lookahead(TK_IMPORT)) {
            node->add_child(parse_import());
        } else {
            break;
        }
    }

    return node;
}

AST* Parser::parse_import() {
    AST* node = nullptr;

    expect(TK_IMPORT);
    node = new AST(AST_IMPORT, matched_token);

    expect(TK_ID);
    node->add_child(new AST(AST_IMPORT_PATH, matched_token));

    while (match(TK_DOT)) {
        if (match(TK_TIMES)) {
            node->add_child(new AST(AST_IMPORT_STAR, matched_token));
            break;
        }

        expect(TK_ID);
        node->add_child(new AST(AST_IMPORT_PATH, matched_token));
    }

    if (match(TK_AS)) {
        expect(TK_ID);
        node->add_child(new AST(AST_IMPORT_ALIAS, matched_token));
    }

    expect(TK_NEWLINE);
    return node;
}

void Parser::advance() {
    current_token = scanner.get_token();
}

bool Parser::lookahead(TokenKind kind) {
    return current_token.get_kind() == kind;
}

bool Parser::match(TokenKind kind) {
    if (lookahead(kind)) {
        matched_token = current_token;
        advance();
        return true;
    }

    return false;
}

void Parser::expect(TokenKind kind) {
    if (match(kind)) {
        return;
    }

    Token token;

    token.set_kind(kind);
    std::cout << token.to_str() << std::endl;

    std::cout << "ERROR\n";
    exit(0);
}
