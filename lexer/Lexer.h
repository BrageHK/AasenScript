//
// Created by brage on 6. okt 2023.
//

#ifndef NORLANG_LEXER_H
#define NORLANG_LEXER_H

#include <string>
#include <vector>
#include "../enums/TokenEnum.h"


struct Token {
    TokenEnum type;
    std::string value;
};

class Lexer {
private:
    std::string input;
    size_t pos = 0;
    char currentChar;

    void advance();

    void skipWhitespace();

    Token integer();

    Token identifier();

public:
    explicit Lexer(const std::string& input) : input(input), currentChar(input[0]) {}

    Token getNextToken();

    std::vector<Token> generateTokens();
};

#endif //NORLANG_LEXER_H
