cmake_minimum_required(VERSION 3.24)
project(aasenscript)

set(CMAKE_CXX_STANDARD 23 -Wall -Wextra -Wno-unused-parameter)

add_executable(aasenscript main.cpp enums/TokenEnum.h lexer/Lexer.cpp lexer/Lexer.h parser/Parser.cpp parser/Parser.h parser/Expression.cpp parser/Expression.h parser/error.cpp parser/error.h)
