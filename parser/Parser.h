#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include "../lexer/lexer.h" // Assuming the lexer is defined in "lexer.h"

// Forward declarations
class AST;
class BinOp;
class Num;

// AST base class
class AST {
public:
    virtual ~AST() {}
};

// Binary operation node
class BinOp : public AST {
public:
    Token op;
    AST* left;
    AST* right;

    BinOp(AST* left, Token op, AST* right) : left(left), op(std::move(op)), right(right) {};
    ~BinOp() override;
};

// Number node
class Num : public AST {
public:
    Token token;
    explicit Num(Token token): token(std::move(token)) {};
};

// Parser class
class Parser {
private:
    unsigned int currentTokenIndex = 0;
    std::vector<Token> tokens;
    Token currentToken;

    void advance();

    AST* factor();

    AST* term();

    AST* expression();

public:
    explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {
        this->currentToken = this->tokens[0];
    }
    AST* parse();

    void eat(TokenEnum type);
};

#endif // PARSER_H
