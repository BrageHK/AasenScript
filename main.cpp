#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "enums/TokenEnum.h"

struct Token {
    TokenEnum type;
    std::string value;
};

class Lexer {
private:
    std::string input;
    size_t pos = 0;
    char currentChar;

    void advance() {
        pos++;
        if (pos < input.length()) {
            currentChar = input[pos];
        } else {
            currentChar = '\0';
        }
    }

    void skipWhitespace() {
        while (currentChar != '\0' && isspace(currentChar)) {
            advance();
        }
    }

    Token integer() {
        std::string result;
        while (currentChar != '\0' && isdigit(currentChar)) {
            result += currentChar;
            advance();
        }
        return {TokenEnum::TOKEN_HELTALL_BOKSTAVELIG, result};
    }

    Token identifier() {
        std::string result;
        while (currentChar != '\0' && (isalnum(currentChar) || currentChar == '_')) {
            result += currentChar;
            advance();
        }
        return {TokenEnum::TOKEN_IDENTIFIKATOR, result};
    }

public:
    explicit Lexer(const std::string& input) : input(input), currentChar(input[0]) {}

    Token getNextToken() {
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
                    return {TokenEnum::TOKEN_PLUS, "+"};
                case '-':
                    advance();
                    return {TokenEnum::TOKEN_MINUS, "-"};
                case '*':
                    advance();
                    return {TokenEnum::TOKEN_MULT, "*"};
                case '/':
                    advance();
                    return {TokenEnum::TOKEN_DIV, "/"};
                case '(':
                    advance();
                    return {TokenEnum::TOKEN_LPARAN, "("};
                case ')':
                    advance();
                    return {TokenEnum::TOKEN_HPARAN, ")"};
                default:
                    std::cerr << "Invalid character: " << currentChar << std::endl;
                    exit(1);
            }
        }

        return {TokenEnum::TOKEN_EOF, ""};
    }
};

int main() {
    std::string text = "123 + foo - bar * 45 / (abc123)";
    Lexer lexer(text);

    Token token = lexer.getNextToken();
    while (token.type != TokenEnum::TOKEN_EOF) {
        std::cout << "Type: " << static_cast<int>(token.type) << ", Value: " << token.value << std::endl;
        token = lexer.getNextToken();
    }

    return 0;
}
