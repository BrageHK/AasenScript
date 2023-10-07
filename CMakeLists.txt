cmake_minimum_required(VERSION 3.24)
project(norlang)

set(CMAKE_CXX_STANDARD 23)

add_executable(norlang main.cpp enums/TokenEnum.h lexer/Lexer.cpp lexer/Lexer.h parser/Parser.cpp parser/Parser.h)
