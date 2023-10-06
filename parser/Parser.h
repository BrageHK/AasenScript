//
// Created by brage on 6. okt 2023.
//

#ifndef NORLANG_PARSER_H
#define NORLANG_PARSER_H

#include <string>
#include <vector>
#include "../lexer/Lexer.h"

// Abstract Syntax Tree
// Children number 1 is left and number 2 is right
struct AST {
    std::string value;
    std::vector<AST> children;
};

class Parser {
    Lexer lexer;
    Token currentToken;


};


#endif //NORLANG_PARSER_H
