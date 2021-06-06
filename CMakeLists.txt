cmake_minimum_required(VERSION 2.8)
project(hdc)

include_directories(include)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(UTILS_SRC
    src/utils/string_pool.cpp
)

set(TOKEN_SRC
    src/token/token.cpp
)

set(SOURCES
    ${UTILS_SRC}
    ${TOKEN_SRC}
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
