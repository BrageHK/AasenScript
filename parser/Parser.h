#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../lexer/lexer.h" // Assuming the lexer is defined in "lexer.h"

class Expression {
public:
    Expression *Left;
    Expression *Right;
    TokenEnum Operator;

    Expression(Expression* left, Expression* right, TokenEnum op)
            : Left(left), Right(right), Operator(op) {};
};

// Parser class
class Parser {
private:
    unsigned int currentTokenIndex = 0;
    std::vector<Token> tokens;
    Token currentToken;

    bool match(std::initializer_list<TokenEnum> types);
    void advance();
    Token peek();
    Token previous();
    Token eat(TokenEnum type);

    std::unique_ptr<Expression> expression();
    std::unique_ptr<Expression> equality();
    std::unique_ptr<Expression> comparison();
    std::unique_ptr<Expression> term();
    std::unique_ptr<Expression> factor();
    std::unique_ptr<Expression> unary();
    std::unique_ptr<Expression> primary();

public:
    explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {
        this->currentToken = this->tokens[0];
    }

    void parse();

};

#endif // PARSER_H
