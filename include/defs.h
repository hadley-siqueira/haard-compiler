#ifndef HDC_DEFS_H
#define HDC_DEFS_H

#include <map>

namespace hdc {
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
        {"}", TK_RIGHT_CURLY_BRACKET}
    };

    typedef enum AstKind {
        AST_PROGRAM,
        AST_SOURCEFILE,
        AST_IMPORT,
        AST_CLASS,
        AST_FUNCTION,
        AST_METHOD,
        AST_VARIABLE,
        AST_LOCAL_VARIABLE,
        AST_GLOBAL_VARIABLE,
        AST_PARAMETER,
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
        AST_I8_TYPE,
        AST_I16_TYPE,
        AST_I32_TYPE,
        AST_I64_TYPE,
        AST_U8_TYPE,
        AST_U16_TYPE,
        AST_U32_TYPE,
        AST_U64_TYPE,
    } AstKind;

    const std::map<AstKind, std::string> hdc_astkind_map = {
        {AST_PROGRAM, "AST_PROGRAM"},
        {AST_SOURCEFILE, "AST_SOURCEFILE"},
        {AST_IMPORT, "AST_IMPORT"},
        {AST_CLASS, "AST_CLASS"},
        {AST_FUNCTION, "AST_FUNCTION"},
        {AST_METHOD, "AST_METHOD"},
        {AST_VARIABLE, "AST_VARIABLE"},
        {AST_LOCAL_VARIABLE, "AST_LOCAL_VARIABLE"},
        {AST_GLOBAL_VARIABLE, "AST_GLOBAL_VARIABLE"},
        {AST_PARAMETER, "AST_PARAMETER"},
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
        {AST_I8_TYPE, "AST_I8_TYPE"},
        {AST_I16_TYPE, "AST_I16_TYPE"},
        {AST_I32_TYPE, "AST_I32_TYPE"},
        {AST_I64_TYPE, "AST_I64_TYPE"},
        {AST_U8_TYPE, "AST_U8_TYPE"},
        {AST_U16_TYPE, "AST_U16_TYPE"},
        {AST_U32_TYPE, "AST_U32_TYPE"},
        {AST_U64_TYPE, "AST_U64_TYPE"},
    };
}

#endif
