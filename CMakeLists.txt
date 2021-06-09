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

set(LEX_SRC
    src/lex/lex_state.cpp
    src/lex/lex.cpp
)

set(AST_SRC
    src/ast/ast.cpp
)

set(SOURCES
    src/main.cpp
    ${UTILS_SRC}
    ${TOKEN_SRC}
    ${LEX_SRC}
    ${AST_SRC}
)

add_executable(${PROJECT_NAME} ${SOURCES})
