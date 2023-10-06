//
// Created by brage on 6. okt 2023.
//

#include "Lexer.h"
#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <unordered_map>

void Lexer::advance() {
    pos++;
    if (pos < input.length()) {
        currentChar = input[pos];
    } else {
        currentChar = '\0';
    }
}

void Lexer::skipWhitespace() {
    while (currentChar != '\0' && isspace(currentChar)) {
        advance();
    }
}

Token Lexer::integer() {
    std::string result;
    while (currentChar != '\0' && isdigit(currentChar)) {
        result += currentChar;
        advance();
    }
    return {TokenEnum::INTEGER_LITERAL, result};
}

Token Lexer::identifier() {
    std::string result;
    while (currentChar != '\0' && (isalnum(currentChar) || currentChar == '_')) {
        result += currentChar;
        advance();
    }
    return {TokenEnum::IDENTIFICATOR, result};
}

Token Lexer::getNextToken(int line) {
    while (currentChar != '\0') {
        if (isspace(currentChar)) {
            skipWhitespace();
            continue;
        }

        if (isdigit(currentChar)) {
            return integer();
        }

        if (isalpha(currentChar) || currentChar == '_') {
            return identifier();
        }

        std::unordered_map<char, std::pair<TokenEnum, std::string>> tokenMap = {
                {'+', {TokenEnum::ADD, "+"}},
                {'-', {TokenEnum::SUB, "-"}},
                {'*', {TokenEnum::MULT, "*"}},
                {'/', {TokenEnum::DIV, "/"}},
                {'(', {TokenEnum::RPAREN, "("}},
                {')', {TokenEnum::LPAREN, ")"}}
        };

        if (tokenMap.find(currentChar) != tokenMap.end()) {
            advance();
            return {tokenMap[currentChar].first, std::to_string(currentChar)};
        } else {
            std::cerr << "Invalid character: " << currentChar << " Error at line: " << line << " In position: " << pos << std::endl;
            advance();
            return {TokenEnum::ERROR, std::to_string(line)};
            //exit(1);
        }
    }

    return {TokenEnum::TOKEN_EOF, ""};
}

std::vector<Token> Lexer::generateTokens(int line) {
    std::vector<Token> tokens;
    Token token = getNextToken(line);
    while (token.type != TokenEnum::TOKEN_EOF) {
        tokens.emplace_back(token);
        token = getNextToken(line);
    }
    tokens.emplace_back(Token{TokenEnum::TOKEN_EOF, ""});
    return tokens;
}
