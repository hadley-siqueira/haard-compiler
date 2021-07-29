cmake_minimum_required(VERSION 2.8)
project(hdc)

include_directories(include)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(UTILS_SRC
    src/utils/utils.cpp
    src/utils/string_pool.cpp
)

set(TOKEN_SRC
    src/token/token.cpp
)

set(SCANNER_SRC
    src/scanner/scanner_state.cpp
    src/scanner/scanner.cpp
)

set(AST_SRC
    src/ast/ast.cpp
    src/ast/ast_node.cpp
    src/ast/source_file.cpp
    src/ast/import.cpp
)

set(PARSER_SRC
    src/parser/parser.cpp
)

set(SOURCES
    src/main.cpp
    ${UTILS_SRC}
    ${TOKEN_SRC}
    ${SCANNER_SRC}
    ${AST_SRC}
    ${PARSER_SRC}
)

add_executable(${PROJECT_NAME} ${SOURCES})
