//
// Created by brage on 6. okt 2023.
//

#include "Lexer.h"
#include <string>
#include <vector>
#include <cctype>
#include <iostream>

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
    return {TokenEnum::TOKEN_INTEGER_LITERAL, result};
}

Token Lexer::identifier() {
    std::string result;
    while (currentChar != '\0' && (isalnum(currentChar) || currentChar == '_')) {
        result += currentChar;
        advance();
    }
    return {TokenEnum::TOKEN_IDENTIFICATOR, result};
}

Token Lexer::getNextToken() {
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

        switch (currentChar) {
            case '+':
                advance();
                return {TokenEnum::TOKEN_ADD, "+"};
            case '-':
                advance();
                return {TokenEnum::TOKEN_SUB, "-"};
            case '*':
                advance();
                return {TokenEnum::TOKEN_MULT, "*"};
            case '/':
                advance();
                return {TokenEnum::TOKEN_DIV, "/"};
            case '(':
                advance();
                return {TokenEnum::TOKEN_RPAREN, "("};
            case ')':
                advance();
                return {TokenEnum::TOKEN_LPAREN, ")"};
            default:
                std::cerr << "Invalid character: " << currentChar << ". Error at line: " << "line" << std::endl;
                exit(1);
        }
    }

    return {TokenEnum::TOKEN_EOF, ""};
}

std::vector<Token> Lexer::generateTokens() {
    std::vector<Token> tokens;
    Token token = getNextToken();
    while (token.type != TokenEnum::TOKEN_EOF) {
        tokens.emplace_back(token);
        token = getNextToken();
    }
    return tokens;
}
