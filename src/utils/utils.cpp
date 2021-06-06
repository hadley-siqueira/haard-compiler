#include "utils/utils.h"

namespace hdc {
    const char* get_token_kind_as_string(const TokenKind kind) {
        switch (kind) {
        case TK_DEF:
            return "TK_DEF";

        case TK_CLASS:
            return "TK_CLASS";

        case TK_VAR:
            return "TK_VAR";

        case TK_CONSTANT:
            return "TK_CONSTANT";

        case TK_STRUCT:
            return "TK_STRUCT";

        case TK_ENUM:
            return "TK_ENUM";

        case TK_UNION:
            return "TK_UNION";

        case TK_IF:
            return "TK_IF";

        case TK_ELIF:
            return "TK_ELIF";

        case TK_ELSE:
            return "TK_ELSE";

        case TK_FOR:
            return "TK_FOR";

        case TK_WHILE:
            return "TK_WHILE";

        case TK_CONTINUE:
            return "TK_CONTINUE";

        case TK_RETURN:
            return "TK_RETURN";

        case TK_GOTO:
            return "TK_GOTO";

        case TK_BREAK:
            return "TK_BREAK";

        case TK_YIELD:
            return "TK_YIELD";

        case TK_FROM:
            return "TK_FROM";

        case TK_AS:
            return "TK_AS";

        case TK_IMPORT:
            return "TK_IMPORT";

        case TK_DO:
            return "TK_DO";

        case TK_IN:
            return "TK_IN";

        case TK_PASS:
            return "TK_PASS";

        case TK_NEW:
            return "TK_NEW";

        case TK_DELETE:
            return "TK_DELETE";

        case TK_CASE:
            return "TK_CASE";

        case TK_DEFAULT:
            return "TK_DEFAULT";

        case TK_WITH:
            return "TK_WITH";

        case TK_SIZEOF:
            return "TK_SIZEOF";

        case TK_AND:
            return "TK_AND";

        case TK_OR:
            return "TK_OR";

        case TK_NOT:
            return "TK_NOT";

        case TK_U8:
            return "TK_U8";

        case TK_U16:
            return "TK_U16";

        case TK_U32:
            return "TK_U32";

        case TK_U64:
            return "TK_U64";

        case TK_I8:
            return "TK_I8";

        case TK_I16:
            return "TK_I16";

        case TK_I32:
            return "TK_I32";

        case TK_I64:
            return "TK_I64";

        case TK_VOID:
            return "TK_VOID";

        case TK_SYMBOL:
            return "TK_SYMBOL";

        case TK_BOOL:
            return "TK_BOOL";

        case TK_UCHAR:
            return "TK_UCHAR";

        case TK_CHAR:
            return "TK_CHAR";

        case TK_USHORT:
            return "TK_USHORT";

        case TK_SHORT:
            return "TK_SHORT";

        case TK_UINT:
            return "TK_UINT";

        case TK_INT:
            return "TK_INT";

        case TK_ULONG:
            return "TK_ULONG";

        case TK_LONG:
            return "TK_LONG";

        case TK_FLOAT:
            return "TK_FLOAT";

        case TK_DOUBLE:
            return "TK_DOUBLE";

        case TK_ID:
            return "TK_ID";

        case TK_TRUE:
            return "TK_TRUE";

        case TK_FALSE:
            return "TK_FALSE";

        case TK_NULL:
            return "TK_NULL";

        case TK_LITERAL_CHAR:
            return "TK_LITERAL_CHAR";

        case TK_LITERAL_INTEGER:
            return "TK_LITERAL_INTEGER";

        case TK_LITERAL_FLOAT:
            return "TK_LITERAL_FLOAT";

        case TK_LITERAL_DOUBLE:
            return "TK_LITERAL_DOUBLE";

        case TK_LITERAL_STRING:
            return "TK_LITERAL_STRING";

        case TK_LITERAL_SYMBOL:
            return "TK_LITERAL_SYMBOL";

        case TK_PLUS:
            return "TK_PLUS";

        case TK_MINUS:
            return "TK_MINUS";

        case TK_TIMES:
            return "TK_TIMES";

        case TK_DIVISION:
            return "TK_DIVISION";

        case TK_INTEGER_DIVISION:
            return "TK_INTEGER_DIVISION";

        case TK_MODULO:
            return "TK_MODULO";

        case TK_POWER:
            return "TK_POWER";

        case TK_INC:
            return "TK_INC";

        case TK_DEC:
            return "TK_DEC";

        case TK_BITWISE_AND:
            return "TK_BITWISE_AND";

        case TK_BITWISE_NOT:
            return "TK_BITWISE_NOT";

        case TK_BITWISE_OR:
            return "TK_BITWISE_OR";

        case TK_BITWISE_XOR:
            return "TK_BITWISE_XOR";

        case TK_SLL:
            return "TK_SLL";

        case TK_SRL:
            return "TK_SRL";

        case TK_SRA:
            return "TK_SRA";

        case TK_ARROW:
            return "TK_ARROW";

        case TK_DOT:
            return "TK_DOT";

        case TK_DOLAR:
            return "TK_DOLAR";

        case TK_SCOPE:
            return "TK_SCOPE";

        case TK_INCLUSIVE_RANGE:
            return "TK_INCLUSIVE_RANGE";

        case TK_EXCLUSIVE_RANGE:
            return "TK_EXCLUSIVE_RANGE";

        case TK_EQ:
            return "TK_EQ";

        case TK_NE:
            return "TK_NE";

        case TK_GT:
            return "TK_GT";

        case TK_LT:
            return "TK_LT";

        case TK_GE:
            return "TK_GE";

        case TK_LE:
            return "TK_LE";

        case TK_LOGICAL_AND:
            return "TK_LOGICAL_AND";

        case TK_LOGICAL_OR:
            return "TK_LOGICAL_OR";

        case TK_LOGICAL_NOT:
            return "TK_LOGICAL_NOT";

        case TK_TERNARY:
            return "TK_TERNARY";

        case TK_ASSIGNMENT:
            return "TK_ASSIGNMENT";

        case TK_BITWISE_AND_ASSIGNMENT:
            return "TK_BITWISE_AND_ASSIGNMENT";

        case TK_BITWISE_XOR_ASSIGNMENT:
            return "TK_BITWISE_XOR_ASSIGNMENT";

        case TK_BITWISE_OR_ASSIGNMENT:
            return "TK_BITWISE_OR_ASSIGNMENT";

        case TK_BITWISE_NOT_ASSIGNMENT:
            return "TK_BITWISE_NOT_ASSIGNMENT";

        case TK_DIVISION_ASSIGNMENT:
            return "TK_DIVISION_ASSIGNMENT";

        case TK_INTEGER_DIVISION_ASSIGNMENT:
            return "TK_INTEGER_DIVISION_ASSIGNMENT";

        case TK_MINUS_ASSIGNMENT:
            return "TK_MINUS_ASSIGNMENT";

        case TK_MODULO_ASSIGNMENT:
            return "TK_MODULO_ASSIGNMENT";

        case TK_PLUS_ASSIGNMENT:
            return "TK_PLUS_ASSIGNMENT";

        case TK_TIMES_ASSIGNMENT:
            return "TK_TIMES_ASSIGNMENT";

        case TK_SLL_ASSIGNMENT:
            return "TK_SLL_ASSIGNMENT";

        case TK_SRA_ASSIGNMENT:
            return "TK_SRA_ASSIGNMENT";

        case TK_SRL_ASSIGNMENT:
            return "TK_SRL_ASSIGNMENT";

        case TK_SPECIAL_ASSIGNMENT:
            return "TK_SPECIAL_ASSIGNMENT";

        case TK_HASH_ARROW:
            return "TK_HASH_ARROW";

        case TK_NEWLINE:
            return "TK_NEWLINE";

        case TK_EOF:
            return "TK_EOF";

        case TK_AT:
            return "TK_AT";

        case TK_BEGIN:
            return "TK_BEGIN";

        case TK_END:
            return "TK_END";

        case TK_COLON:
            return "TK_COLON";

        case TK_COMMA:
            return "TK_COMMA";

        case TK_SEMICOLON:
            return "TK_SEMICOLON";

        case TK_LEFT_CURLY_BRACKET:
            return "TK_LEFT_CURLY_BRACKET";

        case TK_LEFT_PARENTHESIS:
            return "TK_LEFT_PARENTHESIS";

        case TK_LEFT_SQUARE_BRACKET:
            return "TK_LEFT_SQUARE_BRACKET";

        case TK_RIGHT_CURLY_BRACKET:
            return "TK_RIGHT_CURLY_BRACKET";

        case TK_RIGHT_PARENTHESIS:
            return "TK_RIGHT_PARENTHESIS";

        case TK_RIGHT_SQUARE_BRACKET:
            return "TK_RIGHT_SQUARE_BRACKET";

        case TK_UNKNOWN:
            return "TK_UNKNOW";

        }

        return "@ERROR@";
    }

}
