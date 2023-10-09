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
    int line;
};

class Lexer {
private:
    std::string input;
    size_t pos = 0;
    int linePos;
    char currentChar;

    void advance();

    void skipWhitespace();

    Token integer();

    Token identifier();

    Token nextMatch(char c, TokenEnum match, TokenEnum noMatch);

    Token getNextToken();
public:
    explicit Lexer(const std::string& input, int line) : input(input), currentChar(input[0]), linePos(line) {}

    std::vector<Token> generateTokens();

    Token previous();
};

#endif //NORLANG_LEXER_H
