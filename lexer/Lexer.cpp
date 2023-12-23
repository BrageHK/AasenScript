//
// Created by brage on 6. okt 2023.
//

#include "Lexer.h"
#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, TokenEnum> keywords = {
        {"hvis", TokenEnum::IF},
        {"ellers", TokenEnum::ELSE},
        {"mens", TokenEnum::WHILE},
        {"for", TokenEnum::FOR},
        {"skriv", TokenEnum::PRINT},
        {"returner", TokenEnum::RETURN},
        {"funksjon", TokenEnum::FUNCTION},
        {"klasse", TokenEnum::CLASS},
        {"super", TokenEnum::SUPER},
        {"denne", TokenEnum::THIS},
        {"intet", TokenEnum::INTET},
        {"urørleg", TokenEnum::CONST},
        {"Sanning", TokenEnum::BOOL},
        {"usann", TokenEnum::FALSE},
        {"sann", TokenEnum::TRUE},
        {"variabel", TokenEnum::VAR}, // Hadde vært morsomt å bruke "storleik", men det blir litt feil
};

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
    return {TokenEnum::INTEGER_LITERAL, result, linePos};
}

Token Lexer::identifier() {
    std::string result;
    while (currentChar != '\0' && (isalnum(currentChar) || currentChar == '_')) {
        result += currentChar;
        advance();
    }
    if (keywords.find(result) != keywords.end()) {
        return {keywords.find(result)->second, result};
    }
    return {TokenEnum::IDENTIFICATOR, result, linePos};
}

Token Lexer::nextMatch(char c, TokenEnum match, TokenEnum noMatch) {
    char prevChar = currentChar;
    advance();
    if(currentChar == c) {
        advance();
        return {match, std::string(1, prevChar) + std::string(1, c)};
    }
    return {noMatch, std::string(1, prevChar), linePos};
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

        {
            std::string result;
            switch(currentChar) {
                case '"':
                    advance();

                    while(currentChar != '\0' && currentChar != '"') {
                        result += currentChar;
                        advance();
                    }
                    advance();
                    return {TokenEnum::STRING_LITERAL, result, linePos};
                case '\'':
                    advance();

                    while(currentChar != '\0' && currentChar != '\'') {
                        result += currentChar;
                        advance();
                    }
                    advance();
                    return {TokenEnum::STRING_LITERAL, result, linePos};
                case '!':
                    return nextMatch('=', TokenEnum::NOT_EQUAL, TokenEnum::NOT);
                case '=':
                    return nextMatch('=', TokenEnum::EQUAL_EQUAL, TokenEnum::EQUAL);
                case '<':
                    return nextMatch('=', TokenEnum::LESS_THAN_EQUAL, TokenEnum::LESS_THAN);
                case '>':
                    return nextMatch('=', TokenEnum::GREATER_THAN_EQUAL, TokenEnum::GREATER_THAN);
                case '&':
                    return nextMatch('&', TokenEnum::AND, TokenEnum::ERROR);
                case '|':
                    return nextMatch('|', TokenEnum::OR, TokenEnum::ERROR);
            }
        }

        std::unordered_map<char, std::pair<TokenEnum, std::string>> tokenMap = {
                {'+', {TokenEnum::ADD, "+"}},
                {'-', {TokenEnum::SUB, "-"}},
                {'*', {TokenEnum::MULT, "*"}},
                {'/', {TokenEnum::DIV, "/"}},
                {'(', {TokenEnum::LPAREN, "("}},
                {')', {TokenEnum::RPAREN, ")"}},
                {'.', {TokenEnum::DOT, "."}},
                {',', {TokenEnum::COMMA, ","}},
                {';', {TokenEnum::SEMICOLON, ";"}},
                {'{', {TokenEnum::LBRACE, "{"}},
                {'}', {TokenEnum::RBRACE, "}"}},
                {':', {TokenEnum::COLON, ":"}},
        };
        //std::pair<TokenEnum, std::basic_string<char>> currentToken = tokenMap.find(currentChar)->second;
        if (tokenMap.find(currentChar) != tokenMap.end()) {
            advance();
            return {previous().type, previous().value, linePos};
        } else {
            std::cerr << "Invalid character: [ " << currentChar <<
            " ] Error at line: " << linePos << ". In position: " << pos << "." << std::endl;
            advance();
            return {TokenEnum::ERROR, std::to_string(linePos), linePos};
            //exit(1);
        }
    }

    return {TokenEnum::TOKEN_EOF, "", linePos};
}
Token Lexer::previous() {
    if(pos > 0) {
        return {TokenEnum::ERROR, std::string(1, input[pos - 1]), linePos};
    } else {
        std::cerr << "Invalid character: [ " << currentChar << " ] Error at line: " << linePos << ". In position: " << pos << "." << std::endl;
        return {TokenEnum::ERROR, "", linePos};
    }
}

std::vector<Token> Lexer::generateTokens() {
    std::vector<Token> tokens;
    Token token = getNextToken();
    while (token.type != TokenEnum::TOKEN_EOF) {
        tokens.emplace_back(token);
        token = getNextToken();
    }
    tokens.emplace_back(Token{TokenEnum::TOKEN_EOF, "", linePos});
    return tokens;
}
