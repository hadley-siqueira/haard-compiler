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

    node->set_statements(parse_statements()); 
    
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

    node->set_statements(parse_statements()); 
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

    while (type != nullptr) {
        if (match(TK_TIMES)) {
            type = new IndirectionType(AST_POINTER_TYPE, matched_token, type);
        } else if (match(TK_POWER)) {
            type = new IndirectionType(AST_POINTER_TYPE, matched_token, type);
            type = new IndirectionType(AST_POINTER_TYPE, matched_token, type);
        } else if (match(TK_BITWISE_AND)) {
            type = new IndirectionType(AST_REFERENCE_TYPE, matched_token, type);
        } else {
            break;
        }
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

ExpressionList* Parser::parse_argument_list() {
    ExpressionList* arguments = new ExpressionList();

    if (!lookahead(TK_RIGHT_PARENTHESIS)) {
        arguments->add_expression(parse_expression());

        while (match(TK_COMMA)) {
            arguments->add_expression(parse_expression());
        }
    }

    return arguments;
}

Expression* Parser::parse_primary_expression() {
    Expression* expr = nullptr;
    Token oper;

    if (match(TK_LEFT_PARENTHESIS)) {
        oper = matched_token;
        expr = new UnaryExpression(AST_PARENTHESIS, oper, parse_expression());
        expect(TK_RIGHT_PARENTHESIS);
    } else if (match(TK_LITERAL_INTEGER)) {
        expr = new LiteralExpression(AST_LITERAL_INTEGER, matched_token);
    } else if (match(TK_LITERAL_FLOAT)) {
        expr = new LiteralExpression(AST_LITERAL_FLOAT, matched_token);
    } else if (match(TK_LITERAL_DOUBLE)) {
        expr = new LiteralExpression(AST_LITERAL_DOUBLE, matched_token);
    } else if (match(TK_LITERAL_CHAR)) {
        expr = new LiteralExpression(AST_LITERAL_CHAR, matched_token);
    } else if (match(TK_LITERAL_STRING)) {
        expr = new LiteralExpression(AST_LITERAL_STRING, matched_token);
    } else if (match(TK_LITERAL_SYMBOL)) {
        expr = new LiteralExpression(AST_LITERAL_SYMBOL, matched_token);
    } else if (match(TK_NULL)) {
        expr = new LiteralExpression(AST_LITERAL_NULL, matched_token);
    } else if (match(TK_TRUE)) {
        expr = new LiteralExpression(AST_LITERAL_BOOL, matched_token);
    } else if (match(TK_FALSE)) {
        expr = new LiteralExpression(AST_LITERAL_BOOL, matched_token);
    } else if (match(TK_DOLAR)) {
        expr = new UnaryExpression(AST_DOLAR, matched_token, parse_primary_expression());
    } else {
        expr = parse_identifier();
    }

    return expr;
}

Expression* Parser::parse_postfix_expression() {
    Expression* expr = parse_primary_expression();
    Token oper;

    while (true) {
        if (match(TK_DOT)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_DOT, oper, expr, parse_identifier());
        } else if (match(TK_ARROW)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_ARROW, oper, expr, parse_identifier());
        } else if (match(TK_LEFT_SQUARE_BRACKET)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_INDEX, oper, expr, parse_expression());
        } else if (match(TK_LEFT_PARENTHESIS)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_CALL, oper, expr, parse_argument_list());
            expect(TK_RIGHT_PARENTHESIS);
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_unary_expression() {
    Token oper;
    Expression* expr = nullptr;

    if (match(TK_LOGICAL_NOT) || match(TK_NOT)) {
        oper = matched_token;
        expr = new UnaryExpression(AST_LOGICAL_NOT, oper, parse_unary_expression());
    } else if (match(TK_BITWISE_AND)) {
        oper = matched_token;
        expr = new UnaryExpression(AST_ADDRESS_OF, oper, parse_unary_expression());
    } else if (match(TK_TIMES)) {
        oper = matched_token;
        expr = new UnaryExpression(AST_DEREFERENCE, oper, parse_unary_expression());
    } else if (match(TK_POWER)) {
        oper = matched_token;
        expr = new UnaryExpression(AST_DEREFERENCE, oper, parse_unary_expression());
        expr = new UnaryExpression(AST_DEREFERENCE, oper, expr);
    } else if (match(TK_BITWISE_NOT)) {
        oper = matched_token;
        expr = new UnaryExpression(AST_BITWISE_NOT, oper, parse_unary_expression());
    } else if (match(TK_MINUS)) {
        oper = matched_token;
        expr = new UnaryExpression(AST_UNARY_MINUS, oper, parse_unary_expression());
    } else if (match(TK_PLUS)) {
        oper = matched_token;
        expr = new UnaryExpression(AST_UNARY_PLUS, oper, parse_unary_expression());
    } else if (match(TK_INC)) {
        oper = matched_token;
        expr = new UnaryExpression(AST_PRE_INC, oper, parse_unary_expression());
    } else if (match(TK_DEC)) {
        oper = matched_token;
        expr = new UnaryExpression(AST_PRE_DEC, oper, parse_unary_expression());
    } else if (match(TK_SIZEOF)) {
        oper = matched_token;
        expect(TK_LEFT_PARENTHESIS);
        expr = new UnaryExpression(AST_SIZEOF, oper, parse_unary_expression());
        expect(TK_RIGHT_PARENTHESIS);
    } else {
        expr = parse_postfix_expression();
    }

    return expr;
}

Expression* Parser::parse_shift_expression() {
    Token oper;
    Expression* expr = parse_unary_expression();

    while (true) {
        if (match(TK_SLL)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_SLL, oper, expr, parse_unary_expression()); 
        } else if (match(TK_SRL)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_SRL, oper, expr, parse_unary_expression()); 
        } else if (match(TK_SRA)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_SRA, oper, expr, parse_unary_expression()); 
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_bitwise_and_expression() {
    Token oper;
    Expression* expr = parse_shift_expression();

    while (true) {
        if (match(TK_BITWISE_AND)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_BITWISE_AND, oper, expr, parse_shift_expression()); 
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_bitwise_xor_expression() {
    Token oper;
    Expression* expr = parse_bitwise_and_expression();

    while (true) {
        if (match(TK_BITWISE_XOR)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_BITWISE_XOR, oper, expr, parse_bitwise_and_expression()); 
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_bitwise_or_expression() {
    Token oper;
    Expression* expr = parse_bitwise_xor_expression();

    while (true) {
        if (match(TK_BITWISE_OR)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_BITWISE_OR, oper, expr, parse_bitwise_xor_expression()); 
        } else {
            break;
        }
    }

    return expr;
}


Expression* Parser::parse_term_expression() {
    Token oper;
    Expression* expr = parse_bitwise_or_expression();

    while (true) {
        if (match(TK_TIMES)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_TIMES, oper, expr, parse_bitwise_or_expression());
        } else if (match(TK_DIVISION)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_DIVISION, oper, expr, parse_bitwise_or_expression());
        } else if (match(TK_INTEGER_DIVISION)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_INTEGER_DIVISION, oper, expr, parse_bitwise_or_expression());
        } else if (match(TK_MODULO)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_MODULO, oper, expr, parse_bitwise_or_expression());
        } else if (match(TK_POWER)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_POWER, oper, expr, parse_bitwise_or_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_arith_expression() {
    Token oper;
    Expression* expr = parse_term_expression();

    while (true) {
        if (match(TK_PLUS)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_PLUS, oper, expr, parse_term_expression());
        } else if (match(TK_MINUS)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_MINUS, oper, expr, parse_term_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_relational_expression() {
    Token oper;
    Expression* expr = parse_arith_expression();

    while (true) {
        if (match(TK_LT)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_LT, oper, expr, parse_arith_expression());
        } else if (match(TK_GT)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_GT, oper, expr, parse_arith_expression());
        } else if (match(TK_LE)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_LE, oper, expr, parse_arith_expression());
        } else if (match(TK_GE)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_GE, oper, expr, parse_arith_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_equality_expression() {
    Token oper;
    Expression* expr = parse_relational_expression();

    while (true) {
        if (match(TK_EQ)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_EQ, oper, expr, parse_relational_expression());
        } else if (match(TK_NE)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_NE, oper, expr, parse_relational_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_logical_and_expression() {
    Token oper;
    Expression* expr = parse_equality_expression();

    while (true) {
        if (match(TK_AND)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_LOGICAL_AND, oper, expr, parse_equality_expression());
        } else if (match(TK_LOGICAL_AND)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_LOGICAL_AND, oper, expr, parse_equality_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_logical_or_expression() {
    Token oper;
    Expression* expr = parse_logical_and_expression();

    while (true) {
        if (match(TK_OR)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_EQ, oper, expr, parse_logical_and_expression());
        } else if (match(TK_LOGICAL_OR)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_NE, oper, expr, parse_logical_and_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_range_expression() {
    Token oper;
    Expression* expr = parse_logical_or_expression();

    while (true) {
        if (match(TK_INCLUSIVE_RANGE)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_INCLUSIVE_RANGE, oper, expr, parse_logical_or_expression());
        } else if (match(TK_EXCLUSIVE_RANGE)) {
            oper = matched_token;
            expr = new BinaryExpression(AST_EXCLUSIVE_RANGE, oper, expr, parse_logical_or_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_assignment_expression() {
    Token oper;
    Expression* expr = parse_range_expression();

    while (true) {
        if (match(TK_ASSIGNMENT)) {
            expr = new BinaryExpression(AST_ASSIGNMENT, oper, expr, parse_range_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_expression() {
    return parse_assignment_expression();
}

Statement* Parser::parse_statement() {
    Statement* stmt = nullptr;

    if (lookahead(TK_FOR)) {
        stmt = parse_for_statement();
    } else if (lookahead(TK_WHILE)) {
        stmt = parse_while_statement();
    } else if (lookahead(TK_IF)) {
        stmt = parse_if_statement();
    } else if (lookahead(TK_RETURN)) {
        stmt = parse_return_statement();
    } else if (lookahead(TK_VAR)) {
        stmt = parse_variable_statement();
    } else {
        stmt = new ExpressionStatement(parse_expression());
        expect(TK_NEWLINE);
    }

    return stmt;
}

CompoundStatement* Parser::parse_statements() {
    CompoundStatement* stmts = new CompoundStatement();

    if (match(TK_PASS)) {
        expect(TK_NEWLINE);
    } else {
        while (!lookahead(TK_END)) {
            stmts->add_statement(parse_statement());
        }
    }

    return stmts;
}

Statement* Parser::parse_for_statement() {
    return nullptr;
}

Statement* Parser::parse_while_statement() {
    Token token;
    Expression* expression;
    CompoundStatement* statements;

    expect(TK_WHILE);
    token = matched_token;
    expression = parse_expression();

    expect(TK_COLON);
    expect(TK_NEWLINE);
    expect(TK_BEGIN);
    statements = parse_statements();
    expect(TK_END);

    return new WhileStatement(token, expression, statements);
}

Statement* Parser::parse_if_statement() {
    Token token;
    Expression* expression;
    CompoundStatement* statements;

    expect(TK_IF);
    token = matched_token;
    expression = parse_expression();

    expect(TK_COLON);
    expect(TK_NEWLINE);
    expect(TK_BEGIN);
    statements = parse_statements();
    expect(TK_END);

    if (lookahead(TK_ELIF)) {
        return new IfStatement(token, expression, statements, parse_elif_statement());
    } else if (lookahead(TK_ELSE)) {
        return new IfStatement(token, expression, statements, parse_else_statement());
    }

    return new IfStatement(token, expression, statements);
}

Statement* Parser::parse_elif_statement() {
    Token token;
    Expression* expression;
    CompoundStatement* statements;

    expect(TK_ELIF);
    token = matched_token;
    expression = parse_expression();

    expect(TK_COLON);
    expect(TK_NEWLINE);
    expect(TK_BEGIN);
    statements = parse_statements();
    expect(TK_END);

    if (lookahead(TK_ELIF)) {
        return new ElifStatement(token, expression, statements, parse_elif_statement());
    } else if (lookahead(TK_ELSE)) {
        return new ElifStatement(token, expression, statements, parse_else_statement());
    }

    return new ElifStatement(token, expression, statements);
}

Statement* Parser::parse_else_statement() {
    Token token;
    CompoundStatement* statements;

    expect(TK_ELSE);
    token = matched_token;

    expect(TK_COLON);
    expect(TK_NEWLINE);
    expect(TK_BEGIN);
    statements = parse_statements();
    expect(TK_END);

    return new ElseStatement(token, statements);
}

Statement* Parser::parse_return_statement() {
    return nullptr;
}

Statement* Parser::parse_variable_statement() {
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
