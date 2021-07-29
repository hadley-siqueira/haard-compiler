#include <iostream>

#include "defs.h"
#include "parser/parser.h"

using namespace hdc;

SourceFile* Parser::read(const char* path) {
    SourceFile* node = nullptr;
    scanner.read(path);
    advance();

    node = parse_sourcefile();
    node->set_path(path);

    return node;
}

SourceFile* Parser::parse_sourcefile() {
    SourceFile* node = new SourceFile();

    while (true) {
        if (lookahead(TK_IMPORT)) {
            node->add_import(parse_import());
        } else if (lookahead(TK_DEF)) {
            //node->add_child(parse_def());
        } else {
            break;
        }
    }

    return node;
}

Import* Parser::parse_import() {
    Import* node = nullptr;

    expect(TK_IMPORT);
    node = new Import();
    node->set_token(matched_token);

    expect(TK_ID);
    node->add_to_path(matched_token);

    while (match(TK_DOT)) {
        if (match(TK_TIMES)) {
            node->add_to_path(matched_token);
            break;
        }

        expect(TK_ID);
        node->add_to_path(matched_token);
    }

    if (match(TK_AS)) {
        expect(TK_ID);
        node->set_alias(matched_token);
    }

    expect(TK_NEWLINE);
    return node;
}

AST* Parser::parse_def() {
    AST* node = nullptr;

    expect(TK_DEF);
    expect(TK_ID);

    node = new AST(AST_DEF, matched_token);

    expect(TK_COLON);
    node->add_child(parse_type());

    expect(TK_NEWLINE);
    expect(TK_BEGIN);

    if (has_parameters()) {
        node->add_child(parse_parameters()); 
    }

    node->add_child(parse_statements());
    expect(TK_END);

    return node;
}

AST* Parser::parse_parameters() {
    AST* node = new AST(AST_PARAMETERS);
    AST* param = nullptr;

    while (has_parameters()) { std::cout << "parsing type\n";
        expect(TK_AT);
        expect(TK_ID);
        param = new AST(AST_PARAMETER, matched_token);

        expect(TK_COLON);
        param->add_child(parse_type());

        expect(TK_NEWLINE);
        node->add_child(param);
    }

    return node;
}

AST* Parser::parse_type() {
    expect(TK_VOID);
    return nullptr;
}

AST* Parser::parse_statements() {
    expect(TK_PASS);
    expect(TK_NEWLINE);
    return nullptr;
}

bool Parser::has_parameters() {
    bool flag = false;
    Token tmp = current_token;

    scanner.save_state();
    flag = match(TK_AT) && match(TK_ID) && match(TK_COLON);
    scanner.restore_state();
    current_token = tmp;

    return flag;
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

    std::cout << "Expected a '" << token.to_str()
              << "' but got a '" << current_token.to_str()
              << "' instead";

    exit(0);
}
