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
            node->add_function(parse_function());
        } else if (lookahead(TK_CLASS)) {
            node->add_class(parse_class());
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

Class* Parser::parse_class() {
    Token name;
    Class* klass = new Class();

    expect(TK_CLASS);
    expect(TK_ID);
    klass->set_name(matched_token);

    if (lookahead(TK_BEGIN_TEMPLATE)) {
        klass->set_template_list(parse_template_list());
    }

    if (match(TK_LEFT_PARENTHESIS)) {
        klass->set_parent(parse_type());
        expect(TK_RIGHT_PARENTHESIS);
    }

    expect(TK_COLON);
    expect(TK_NEWLINE);
    expect(TK_BEGIN);

    while (true) {
        if (lookahead(TK_DEF)) {
            klass->add_method(parse_method());
        } else if (lookahead(TK_ID)){
            klass->add_variable(parse_class_variable());
        } else {
            break;
        }
    }

    expect(TK_END);
    return klass;
}

Function* Parser::parse_function() {
    Function* node = nullptr;

    expect(TK_DEF);
    expect(TK_ID);

    node = new Function();
    node->set_name(matched_token);

    if (lookahead(TK_BEGIN_TEMPLATE)) {
        node->set_template_list(parse_template_list());
    }

    expect(TK_COLON);
    node->set_return_type(parse_type());

    expect(TK_NEWLINE);
    expect(TK_BEGIN);

    if (has_parameters()) {
        parse_parameters(node);
    }

    parse_statements(); //node->add_child(parse_statements());
    expect(TK_END);

    return node;
}

Method* Parser::parse_method() {
    Method* node = nullptr;

    expect(TK_DEF);
    expect(TK_ID);

    node = new Method();
    node->set_name(matched_token);

    if (lookahead(TK_BEGIN_TEMPLATE)) {
        node->set_template_list(parse_template_list());
    }

    expect(TK_COLON);
    node->set_return_type(parse_type());

    expect(TK_NEWLINE);
    expect(TK_BEGIN);

    if (has_parameters()) {
        parse_parameters(node);
    }

    parse_statements(); //node->add_child(parse_statements());
    expect(TK_END);

    return node;
}

Variable* Parser::parse_class_variable() {
    Variable* var = new Variable(AST_CLASS_VARIABLE);

    expect(TK_ID);
    var->set_name(matched_token);

    expect(TK_COLON);
    var->set_type(parse_type());
    expect(TK_NEWLINE);

    return var;
}

void Parser::parse_parameters(Function* function) {
    Variable* parameter = nullptr;

    while (has_parameters()) {
        expect(TK_AT);
        expect(TK_ID);
        parameter = new Variable(AST_PARAMETER);
        parameter->set_name(matched_token);

        expect(TK_COLON);
        parameter->set_type(parse_type());

        expect(TK_NEWLINE);
        function->add_parameter(parameter);
    }
}

Type* Parser::parse_type() {
    Type* type = nullptr;

    if (match(TK_INT)) {
        type = new Type(AST_INT_TYPE, matched_token);
    } else if (match(TK_UINT)) {
        type = new Type(AST_UINT_TYPE, matched_token);
    } else if (match(TK_FLOAT)) {
        type = new Type(AST_FLOAT_TYPE, matched_token);
    } else if (match(TK_DOUBLE)) {
        type = new Type(AST_DOUBLE_TYPE, matched_token);
    } else if (match(TK_SHORT)) {
        type = new Type(AST_SHORT_TYPE, matched_token);
    } else if (match(TK_USHORT)) {
        type = new Type(AST_USHORT_TYPE, matched_token);
    } else if (match(TK_LONG)) {
        type = new Type(AST_LONG_TYPE, matched_token);
    } else if (match(TK_ULONG)) {
        type = new Type(AST_ULONG_TYPE, matched_token);
    } else if (match(TK_CHAR)) {
        type = new Type(AST_CHAR_TYPE, matched_token);
    } else if (match(TK_UCHAR)) {
        type = new Type(AST_UCHAR_TYPE, matched_token);
    } else if (match(TK_SYMBOL)) {
        type = new Type(AST_SYMBOL_TYPE, matched_token);
    } else if (match(TK_VOID)) {
        type = new Type(AST_VOID_TYPE, matched_token);
    } else if (match(TK_BOOL)) {
        type = new Type(AST_BOOL_TYPE, matched_token);
    } else if (match(TK_I8)) {
        type = new Type(AST_I8_TYPE, matched_token);
    } else if (match(TK_I16)) {
        type = new Type(AST_I16_TYPE, matched_token);
    } else if (match(TK_I32)) {
        type = new Type(AST_I32_TYPE, matched_token);
    } else if (match(TK_I64)) {
        type = new Type(AST_I64_TYPE, matched_token);
    } else if (match(TK_U8)) {
        type = new Type(AST_U8_TYPE, matched_token);
    } else if (match(TK_U16)) {
        type = new Type(AST_U16_TYPE, matched_token);
    } else if (match(TK_U32)) {
        type = new Type(AST_U32_TYPE, matched_token);
    } else if (match(TK_U64)) {
        type = new Type(AST_U64_TYPE, matched_token);
    } else if (lookahead(TK_ID) || lookahead(TK_SCOPE)) {
        type = new NamedType(parse_identifier());
    }

    return type;
}

Identifier* Parser::parse_identifier() {
    Identifier* node = new Identifier();

    // matches ::name (a global scope)
    if (match(TK_SCOPE)) {
        expect(TK_ID);
        node->set_global_flag(true);
        node->set_alias_flag(true);
        node->set_name(matched_token);
    } else {
        expect(TK_ID);
        node->set_alias(matched_token); // we set both name and alias and let the
        node->set_name(matched_token);  // alias_flag decide if alias should be used

        if (match(TK_SCOPE)) {
            expect(TK_ID);
            node->set_name(matched_token); // update to the correct name
            node->set_alias_flag(true);    // indicates that indeed has an alias
        }
    }

    if (lookahead(TK_BEGIN_TEMPLATE)) {
        node->set_template_list(parse_template_list());
    }

    return node;
}

TemplateList* Parser::parse_template_list() {
    TemplateList* list = new TemplateList();

    expect(TK_BEGIN_TEMPLATE);

    list->add_type(parse_type());

    while (match(TK_COMMA)) {
        list->add_type(parse_type());
    }

    expect(TK_END_TEMPLATE);
    return list;
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
              << "' instead\n";

    exit(0);
}
