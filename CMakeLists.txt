cmake_minimum_required(VERSION 2.8)
project(hdc)

include_directories(include)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(UTILS_SRC
    src/utils/utils.cpp
    src/utils/string_pool.cpp
)

set(POOL_SRC
    src/pool/ast_pool.cpp
)

set(TOKEN_SRC
    src/token/token.cpp
)

set(SCANNER_SRC
    src/scanner/scanner_state.cpp
    src/scanner/scanner.cpp
)

set(AST_SRC
    src/ast/ast_node.cpp
    src/ast/program.cpp
    src/ast/source_file.cpp
    src/ast/import.cpp
    src/ast/class.cpp
    src/ast/function.cpp
    src/ast/method.cpp
    src/ast/variable.cpp
    src/ast/type.cpp
    src/ast/named_type.cpp
    src/ast/indirection_type.cpp
    src/ast/array_type.cpp
    src/ast/template_list.cpp
    src/ast/identifier.cpp
    src/ast/expression.cpp
    src/ast/statement.cpp
    src/ast/compound_statement.cpp
    src/ast/while_statement.cpp
    src/ast/if_statement.cpp
    src/ast/elif_statement.cpp
    src/ast/else_statement.cpp
    src/ast/literal_expression.cpp
    src/ast/binary_expression.cpp
    src/ast/unary_expression.cpp
    src/ast/expression_list.cpp
    src/ast/expression_statement.cpp
)

set(PARSER_SRC
    src/parser/parser.cpp
)

set(SYMTAB_SRC
    src/symtab/symbol.cpp
    src/symtab/scope.cpp
    src/symtab/scope_builder.cpp
)

set(IR_SRC
    src/ir/ir.cpp
    src/ir/ir_builder.cpp
)

set(CPP_BUILDER_SRC
    src/cpp/cpp_builder.cpp
)

set(DRIVER_SRC
    src/driver/driver.cpp
)

set(SOURCES
    src/main.cpp
    ${UTILS_SRC}
    ${POOL_SRC}
    ${TOKEN_SRC}
    ${SCANNER_SRC}
    ${AST_SRC}
    ${PARSER_SRC}
    ${SYMTAB_SRC}
    ${IR_SRC}
    ${CPP_BUILDER_SRC}
    ${DRIVER_SRC}
)

add_executable(${PROJECT_NAME} ${SOURCES})
