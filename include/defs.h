#ifndef HDC_DEFS_H
#define HDC_DEFS_H

#include <map>

namespace hdc {
    typedef enum SymbolKind {
        SYM_VAR,
        SYM_PARAM,
        SYM_CLASS_VAR,
        SYM_CLASS,
        SYM_FUNCTION,
        SYM_METHOD,
    } SymbolKind;

    typedef enum IRKind {
        IR_LABEL,

        /* Memory */
        IR_SW_FP,

        /* Binary operators */
        IR_PLUS,
        IR_MINUS,

        /* Literals */
        IR_INTEGER,
    } IRKind;

    typedef enum TokenKind {
        /* Keywords */
        TK_DEF,
        TK_CLASS,
        TK_VAR,
        TK_CONSTANT,

        TK_STRUCT,
        TK_ENUM,
        TK_UNION,

        TK_IF,
        TK_ELIF,
        TK_ELSE,

        TK_FOR,
        TK_WHILE,

        TK_CONTINUE,
        TK_RETURN,
        TK_GOTO,
        TK_BREAK,
        TK_YIELD,

        TK_FROM,
        TK_AS,
        TK_IMPORT,
        TK_DO,
        TK_IN,
        TK_PASS,

        TK_NEW,
        TK_DELETE,
        TK_CASE,
        TK_DEFAULT,
        TK_WITH,
        TK_SIZEOF,

        TK_AND,
        TK_OR,
        TK_NOT,

        /* types */
        TK_U8, TK_U16, TK_U32, TK_U64,
        TK_I8, TK_I16, TK_I32, TK_I64,

        TK_VOID,
        TK_SYMBOL,
        TK_BOOL,
        TK_UCHAR, TK_CHAR,
        TK_USHORT, TK_SHORT,
        TK_UINT, TK_INT,
        TK_ULONG, TK_LONG,
        TK_FLOAT,
        TK_DOUBLE,


        /* Identifiers and literals */
        TK_ID,
        TK_TRUE,
        TK_FALSE,
        TK_NULL,
        TK_LITERAL_CHAR,
        TK_LITERAL_INTEGER,
        TK_LITERAL_FLOAT,
        TK_LITERAL_DOUBLE,
        TK_LITERAL_STRING,
        TK_LITERAL_SYMBOL,

        /* Operators */

        /* arithmetic */
        TK_PLUS,
        TK_MINUS,
        TK_TIMES,
        TK_DIVISION,
        TK_INTEGER_DIVISION,
        TK_MODULO,
        TK_POWER,

        TK_INC,
        TK_DEC,

        /* bitwise */
        TK_BITWISE_AND,
        TK_BITWISE_NOT,
        TK_BITWISE_OR,
        TK_BITWISE_XOR,
        TK_SLL,
        TK_SRL,
        TK_SRA,

        /* member access operators */
        TK_ARROW,
        TK_DOT,

        /* scope */
        TK_DOLAR,
        TK_SCOPE,

        /* ranges */
        TK_INCLUSIVE_RANGE,
        TK_EXCLUSIVE_RANGE,

        /* relational operators */
        TK_EQ,
        TK_NE,
        TK_GT,
        TK_LT,
        TK_GE,
        TK_LE,

        /* logical operators */
        TK_LOGICAL_AND,
        TK_LOGICAL_OR,
        TK_LOGICAL_NOT,

        /* conditional */
        TK_TERNARY,

        /* assignments */
        TK_ASSIGNMENT,
        TK_BITWISE_AND_ASSIGNMENT,
        TK_BITWISE_XOR_ASSIGNMENT,
        TK_BITWISE_OR_ASSIGNMENT,
        TK_BITWISE_NOT_ASSIGNMENT,
        TK_DIVISION_ASSIGNMENT,
        TK_INTEGER_DIVISION_ASSIGNMENT,
        TK_MINUS_ASSIGNMENT,
        TK_MODULO_ASSIGNMENT,
        TK_PLUS_ASSIGNMENT,
        TK_TIMES_ASSIGNMENT,
        TK_SLL_ASSIGNMENT,
        TK_SRA_ASSIGNMENT,
        TK_SRL_ASSIGNMENT,
        TK_SPECIAL_ASSIGNMENT,

        /* others */
        TK_HASH_ARROW,

        /* punctuation */
        TK_NEWLINE,
        TK_EOF,
        TK_AT,
        TK_BEGIN,
        TK_END,
        TK_COLON,
        TK_COMMA,
        TK_SEMICOLON,
        TK_LEFT_CURLY_BRACKET,
        TK_LEFT_PARENTHESIS,
        TK_LEFT_SQUARE_BRACKET,
        TK_RIGHT_CURLY_BRACKET,
        TK_RIGHT_PARENTHESIS,
        TK_RIGHT_SQUARE_BRACKET,
        TK_BEGIN_TEMPLATE,
        TK_END_TEMPLATE,

        /* For debug purpose */
        TK_UNKNOWN
    } TokenKind;

    const std::map<std::string, TokenKind> hdc_keywords_map = {
        {"def", TK_DEF},
        {"class", TK_CLASS},
        {"var", TK_VAR},
        {"const", TK_CONSTANT},
        {"constant", TK_CONSTANT},

        {"struct", TK_STRUCT},
        {"enum", TK_ENUM},
        {"union", TK_UNION},

        {"new", TK_NEW},
        {"delete", TK_DELETE},
        {"case", TK_CASE},
        {"default", TK_DEFAULT},
        {"with", TK_WITH},
        {"pass", TK_PASS},
        {"do", TK_DO},
        {"from", TK_FROM},
        {"sizeof", TK_SIZEOF},

        {"import", TK_IMPORT},
        {"as", TK_AS},
        {"in", TK_IN},
        {"null", TK_NULL},
        {"true", TK_TRUE},
        {"false", TK_FALSE},

        {"if", TK_IF},
        {"elif", TK_ELIF},
        {"else", TK_ELSE},

        {"for", TK_FOR},
        {"while", TK_WHILE},

        {"break", TK_BREAK},
        {"continue", TK_CONTINUE},
        {"goto", TK_GOTO},
        {"yield", TK_YIELD},
        {"return", TK_RETURN},

        {"and", TK_AND},
        {"or", TK_OR},
        {"not", TK_NOT},

        /* types */
        {"u8", TK_U8},
        {"u16", TK_U16},
        {"u32", TK_U32},
        {"u64", TK_U64},

        {"i8", TK_I8},
        {"i16", TK_I16},
        {"i32", TK_I32},
        {"i64", TK_I64},

        {"void", TK_VOID},
        {"symbol", TK_SYMBOL},
        {"bool", TK_BOOL},
        {"uchar", TK_UCHAR},
        {"char", TK_CHAR},
        {"ushort", TK_USHORT},
        {"short", TK_SHORT},
        {"uint", TK_UINT},
        {"int", TK_INT},
        {"ulong", TK_ULONG},
        {"long", TK_LONG},
        {"float", TK_FLOAT},
        {"double", TK_DOUBLE}
    };

    const std::map<std::string, TokenKind> hdc_operators_map = {
        {"++", TK_INC},
        {"--", TK_DEC},

        /* arithmetic */
        {"+", TK_PLUS},
        {"-", TK_MINUS},
        {"*", TK_TIMES},
        {"/", TK_DIVISION},
        {"//", TK_INTEGER_DIVISION},
        {"%", TK_MODULO},
        {"**", TK_POWER},

        /* relational */
        {"==", TK_EQ},
        {"!=", TK_NE},
        {">", TK_GT},
        {"<", TK_LT},
        {">=", TK_GE},
        {"<=", TK_LE},

        /* bitwise */
        {"&", TK_BITWISE_AND},
        {"|", TK_BITWISE_OR},
        {"^", TK_BITWISE_XOR},
        {"~", TK_BITWISE_NOT},
        {"<<", TK_SLL},
        {">>", TK_SRA},
        {">>>", TK_SRL},

        /* logical */
        {"&&", TK_LOGICAL_AND},
        {"||", TK_LOGICAL_OR},
        {"!", TK_LOGICAL_NOT},

        /* member access */
        {"->", TK_ARROW},
        {".", TK_DOT},

        /* scope */
        {"::", TK_SCOPE},
        {"$", TK_DOLAR},

        /* ranges */
        {"..", TK_INCLUSIVE_RANGE},
        {"...", TK_EXCLUSIVE_RANGE},

        /* ternary */
        {"?", TK_TERNARY},

        /* hash arrow*/
        {"=>", TK_HASH_ARROW},

        /* assignments */
        {"=", TK_ASSIGNMENT},
        {"&=", TK_BITWISE_AND_ASSIGNMENT},
        {"^=", TK_BITWISE_XOR_ASSIGNMENT},
        {"|=", TK_BITWISE_OR_ASSIGNMENT},
        {"~=", TK_BITWISE_NOT_ASSIGNMENT},
        {"/=", TK_DIVISION_ASSIGNMENT},
        {"//=", TK_INTEGER_DIVISION_ASSIGNMENT},
        {"-=", TK_MINUS_ASSIGNMENT},
        {"%=", TK_MODULO_ASSIGNMENT},
        {"+=", TK_PLUS_ASSIGNMENT},
        {"*=", TK_TIMES_ASSIGNMENT},
        {"<<=", TK_SLL_ASSIGNMENT},
        {">>=", TK_SRA_ASSIGNMENT},
        {">>>=", TK_SRL_ASSIGNMENT},
        {":=", TK_SPECIAL_ASSIGNMENT},

        /* punctuation */
        {"@", TK_AT},
        {":", TK_COLON},
        {",", TK_COMMA},
        {"},", TK_SEMICOLON},
        {"(", TK_LEFT_PARENTHESIS},
        {")", TK_RIGHT_PARENTHESIS},
        {"[", TK_LEFT_SQUARE_BRACKET},
        {"]", TK_RIGHT_SQUARE_BRACKET},
        {"{", TK_LEFT_CURLY_BRACKET},
        {"}", TK_RIGHT_CURLY_BRACKET},
        {"<", TK_BEGIN_TEMPLATE}
    };

    typedef enum AstKind {
        AST_PROGRAM,
        AST_SOURCEFILE,
        AST_IMPORT,
        AST_CLASS,
        AST_FUNCTION,
        AST_METHOD,
        AST_AT,
        AST_VARIABLE,
        AST_LOCAL_VARIABLE,
        AST_GLOBAL_VARIABLE,
        AST_CLASS_VARIABLE,
        AST_PARAMETER,
        AST_STATEMENT,
        AST_COMPOUND_STATEMENT,
        AST_EXPRESSION_STATEMENT,
        AST_WHILE,
        AST_FOR,
        AST_FOREACH,
        AST_IF,
        AST_ELIF,
        AST_ELSE,
        AST_CONTINUE,
        AST_RETURN,
        AST_BREAK,
        AST_YIELD,
        AST_NEW,
        AST_DELETE,
        AST_EXPRESSION,
        AST_IDENTIFIER,
        AST_LITERAL_INTEGER,
        AST_LITERAL_CHAR,
        AST_LITERAL_FLOAT,
        AST_LITERAL_DOUBLE,
        AST_LITERAL_STRING,
        AST_LITERAL_SYMBOL,
        AST_LITERAL_NULL,
        AST_LITERAL_BOOL,
        AST_PARENTHESIS,
        AST_DOLAR,
        AST_DOT,
        AST_ARROW,
        AST_INDEX,
        AST_CALL,
        AST_EXPRESSION_LIST,
        AST_ADDRESS_OF,
        AST_DEREFERENCE,
        AST_UNARY_MINUS,
        AST_UNARY_PLUS,
        AST_PRE_INC,
        AST_PRE_DEC,
        AST_POS_INC,
        AST_POS_DEC,
        AST_LOGICAL_NOT,
        AST_BITWISE_NOT,
        AST_SIZEOF,
        AST_SLL,
        AST_SRL,
        AST_SRA,
        AST_BITWISE_AND,
        AST_BITWISE_XOR,
        AST_BITWISE_OR,
        AST_TIMES,
        AST_DIVISION,
        AST_INTEGER_DIVISION,
        AST_MODULO,
        AST_POWER,
        AST_PLUS,
        AST_MINUS,
        AST_LT,
        AST_GT,
        AST_LE,
        AST_GE,
        AST_EQ,
        AST_NE,
        AST_LOGICAL_AND,
        AST_LOGICAL_OR,
        AST_INCLUSIVE_RANGE,
        AST_EXCLUSIVE_RANGE,
        AST_ASSIGNMENT,
        AST_BITWISE_AND_ASSIGNMENT,
        AST_BITWISE_XOR_ASSIGNMENT,
        AST_BITWISE_OR_ASSIGNMENT,
        AST_BITWISE_NOT_ASSIGNMENT,
        AST_DIVISION_ASSIGNMENT,
        AST_INTEGER_DIVISION_ASSIGNMENT,
        AST_MINUS_ASSIGNMENT,
        AST_MODULO_ASSIGNMENT,
        AST_PLUS_ASSIGNMENT,
        AST_TIMES_ASSIGNMENT,
        AST_SLL_ASSIGNMENT,
        AST_SRA_ASSIGNMENT,
        AST_SRL_ASSIGNMENT,
        AST_SPECIAL_ASSIGNMENT,
        AST_VOID_TYPE,
        AST_INT_TYPE,
        AST_UINT_TYPE,
        AST_FLOAT_TYPE,
        AST_DOUBLE_TYPE,
        AST_SHORT_TYPE,
        AST_USHORT_TYPE,
        AST_LONG_TYPE,
        AST_ULONG_TYPE,
        AST_CHAR_TYPE,
        AST_UCHAR_TYPE,
        AST_SYMBOL_TYPE,
        AST_BOOL_TYPE,
        AST_STRING_TYPE,
        AST_NULL_TYPE,
        AST_I8_TYPE,
        AST_I16_TYPE,
        AST_I32_TYPE,
        AST_I64_TYPE,
        AST_U8_TYPE,
        AST_U16_TYPE,
        AST_U32_TYPE,
        AST_U64_TYPE,
        AST_NAMED_TYPE,
        AST_POINTER_TYPE,
        AST_REFERENCE_TYPE,
        AST_ARRAY_TYPE,
        AST_LIST_TYPE,
        AST_HASH_TYPE,
        AST_FUNCTION_TYPE,
        AST_TEMPLATE_LIST,
    } AstKind;

    const std::map<AstKind, std::string> hdc_astkind_map = {
        {AST_PROGRAM, "AST_PROGRAM"},
        {AST_SOURCEFILE, "AST_SOURCEFILE"},
        {AST_IMPORT, "AST_IMPORT"},
        {AST_CLASS, "AST_CLASS"},
        {AST_FUNCTION, "AST_FUNCTION"},
        {AST_METHOD, "AST_METHOD"},
        {AST_AT, "AST_AT"},
        {AST_VARIABLE, "AST_VARIABLE"},
        {AST_LOCAL_VARIABLE, "AST_LOCAL_VARIABLE"},
        {AST_GLOBAL_VARIABLE, "AST_GLOBAL_VARIABLE"},
        {AST_CLASS_VARIABLE, "AST_CLASS_VARIABLE"},
        {AST_PARAMETER, "AST_PARAMETER"},
        {AST_STATEMENT, "AST_STATEMENT"},
        {AST_COMPOUND_STATEMENT, "AST_COMPOUND_STATEMENT"},
        {AST_EXPRESSION_STATEMENT, "AST_EXPRESSION_STATEMENT"},
        {AST_WHILE, "AST_WHILE"},
        {AST_FOR, "AST_FOR"},
        {AST_FOREACH, "AST_FOREACH"},
        {AST_IF, "AST_IF"},
        {AST_ELIF, "AST_ELIF"},
        {AST_ELSE, "AST_ELSE"},
        {AST_CONTINUE, "AST_CONTINUE"},
        {AST_RETURN, "AST_RETURN"},
        {AST_BREAK, "AST_BREAK"},
        {AST_YIELD, "AST_YIELD"},
        {AST_NEW, "AST_NEW"},
        {AST_DELETE, "AST_DELETE"},
        {AST_EXPRESSION, "AST_EXPRESSION"},
        {AST_IDENTIFIER, "AST_IDENTIFIER"},
        {AST_LITERAL_INTEGER, "AST_LITERAL_INTEGER"},
        {AST_LITERAL_CHAR, "AST_LITERAL_CHAR"},
        {AST_LITERAL_FLOAT, "AST_LITERAL_FLOAT"},
        {AST_LITERAL_DOUBLE, "AST_LITERAL_DOUBLE"},
        {AST_LITERAL_STRING, "AST_LITERAL_STRING"},
        {AST_LITERAL_SYMBOL, "AST_LITERAL_SYMBOL"},
        {AST_LITERAL_NULL, "AST_LITERAL_NULL"},
        {AST_LITERAL_BOOL, "AST_LITERAL_BOOL"},
        {AST_PARENTHESIS, "AST_PARENTHESIS"},
        {AST_DOLAR, "AST_DOLAR"},
        {AST_DOT, "AST_DOT"},
        {AST_ARROW, "AST_ARROW"},
        {AST_INDEX, "AST_INDEX"},
        {AST_CALL, "AST_CALL"},
        {AST_EXPRESSION_LIST, "AST_EXPRESSION_LIST"},
        {AST_ADDRESS_OF, "AST_ADDRESS_OF"},
        {AST_DEREFERENCE, "AST_DEREFERENCE"},
        {AST_UNARY_MINUS, "AST_UNARY_MINUS"},
        {AST_UNARY_PLUS, "AST_UNARY_PLUS"},
        {AST_PRE_INC, "AST_PRE_INC"},
        {AST_PRE_DEC, "AST_PRE_DEC"},
        {AST_POS_INC, "AST_POS_INC"},
        {AST_POS_DEC, "AST_POS_DEC"},
        {AST_LOGICAL_NOT, "AST_LOGICAL_NOT"},
        {AST_BITWISE_NOT, "AST_BITWISE_NOT"},
        {AST_SIZEOF, "AST_SIZEOF"},
        {AST_SLL, "AST_SLL"},
        {AST_SRL, "AST_SRL"},
        {AST_SRA, "AST_SRA"},
        {AST_BITWISE_AND, "AST_BITWISE_AND"},
        {AST_BITWISE_XOR, "AST_BITWISE_XOR"},
        {AST_BITWISE_OR, "AST_BITWISE_OR"},
        {AST_TIMES, "AST_TIMES"},
        {AST_DIVISION, "AST_DIVISION"},
        {AST_INTEGER_DIVISION, "AST_INTEGER_DIVISION"},
        {AST_MODULO, "AST_MODULO"},
        {AST_POWER, "AST_POWER"},
        {AST_PLUS, "AST_PLUS"},
        {AST_MINUS, "AST_MINUS"},
        {AST_LT, "AST_LT"},
        {AST_GT, "AST_GT"},
        {AST_LE, "AST_LE"},
        {AST_GE, "AST_GE"},
        {AST_EQ, "AST_EQ"},
        {AST_NE, "AST_NE"},
        {AST_LOGICAL_AND, "AST_LOGICAL_AND"},
        {AST_LOGICAL_OR, "AST_LOGICAL_OR"},
        {AST_INCLUSIVE_RANGE, "AST_INCLUSIVE_RANGE"},
        {AST_EXCLUSIVE_RANGE, "AST_EXCLUSIVE_RANGE"},
        {AST_ASSIGNMENT, "AST_ASSIGNMENT"},
        {AST_BITWISE_AND_ASSIGNMENT, "AST_BITWISE_AND_ASSIGNMENT"},
        {AST_BITWISE_XOR_ASSIGNMENT, "AST_BITWISE_XOR_ASSIGNMENT"},
        {AST_BITWISE_OR_ASSIGNMENT, "AST_BITWISE_OR_ASSIGNMENT"},
        {AST_BITWISE_NOT_ASSIGNMENT, "AST_BITWISE_NOT_ASSIGNMENT"},
        {AST_DIVISION_ASSIGNMENT, "AST_DIVISION_ASSIGNMENT"},
        {AST_INTEGER_DIVISION_ASSIGNMENT, "AST_INTEGER_DIVISION_ASSIGNMENT"},
        {AST_MINUS_ASSIGNMENT, "AST_MINUS_ASSIGNMENT"},
        {AST_MODULO_ASSIGNMENT, "AST_MODULO_ASSIGNMENT"},
        {AST_PLUS_ASSIGNMENT, "AST_PLUS_ASSIGNMENT"},
        {AST_TIMES_ASSIGNMENT, "AST_TIMES_ASSIGNMENT"},
        {AST_SLL_ASSIGNMENT, "AST_SLL_ASSIGNMENT"},
        {AST_SRA_ASSIGNMENT, "AST_SRA_ASSIGNMENT"},
        {AST_SRL_ASSIGNMENT, "AST_SRL_ASSIGNMENT"},
        {AST_SPECIAL_ASSIGNMENT, "AST_SPECIAL_ASSIGNMENT"},
        {AST_VOID_TYPE, "AST_VOID_TYPE"},
        {AST_INT_TYPE, "AST_INT_TYPE"},
        {AST_UINT_TYPE, "AST_UINT_TYPE"},
        {AST_FLOAT_TYPE, "AST_FLOAT_TYPE"},
        {AST_DOUBLE_TYPE, "AST_DOUBLE_TYPE"},
        {AST_SHORT_TYPE, "AST_SHORT_TYPE"},
        {AST_USHORT_TYPE, "AST_USHORT_TYPE"},
        {AST_LONG_TYPE, "AST_LONG_TYPE"},
        {AST_ULONG_TYPE, "AST_ULONG_TYPE"},
        {AST_CHAR_TYPE, "AST_CHAR_TYPE"},
        {AST_UCHAR_TYPE, "AST_UCHAR_TYPE"},
        {AST_SYMBOL_TYPE, "AST_SYMBOL_TYPE"},
        {AST_BOOL_TYPE, "AST_BOOL_TYPE"},
        {AST_STRING_TYPE, "AST_STRING_TYPE"},
        {AST_NULL_TYPE, "AST_NULL_TYPE"},
        {AST_I8_TYPE, "AST_I8_TYPE"},
        {AST_I16_TYPE, "AST_I16_TYPE"},
        {AST_I32_TYPE, "AST_I32_TYPE"},
        {AST_I64_TYPE, "AST_I64_TYPE"},
        {AST_U8_TYPE, "AST_U8_TYPE"},
        {AST_U16_TYPE, "AST_U16_TYPE"},
        {AST_U32_TYPE, "AST_U32_TYPE"},
        {AST_U64_TYPE, "AST_U64_TYPE"},
        {AST_NAMED_TYPE, "AST_NAMED_TYPE"},
        {AST_POINTER_TYPE, "AST_POINTER_TYPE"},
        {AST_REFERENCE_TYPE, "AST_REFERENCE_TYPE"},
        {AST_ARRAY_TYPE, "AST_ARRAY_TYPE"},
        {AST_LIST_TYPE, "AST_LIST_TYPE"},
        {AST_HASH_TYPE, "AST_HASH_TYPE"},
        {AST_FUNCTION_TYPE, "AST_FUNCTION_TYPE"},
        {AST_TEMPLATE_LIST, "AST_TEMPLATE_LIST"},
    };
}

#endif
