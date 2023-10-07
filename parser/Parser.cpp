#include <utility>

#include "Parser.h"
#include "../enums/TokenEnum.h"

void Parser::eat(TokenEnum type) {
    if (currentToken.type == type) {
        currentToken = tokens[++currentTokenIndex];
    } else {
        std::cerr << "Error parsing input" << std::endl;
        exit(1);
    }
}

BinOp::~BinOp() {
    delete left;
    delete right;
}

AST* Parser::factor() {
    Token token = currentToken;
    if (token.type == TokenEnum::INTEGER_LITERAL) {
        advance();
        return new Num(token);
    } else if (token.type == TokenEnum::LPAREN) {
        eat(TokenEnum::LPAREN);
        AST* node = expression();
        eat(TokenEnum::LPAREN);
        return node;
    } else {
        std::cerr << "Error parsing input at token no: " << currentTokenIndex << std::endl;
        exit(1);
    }
}

AST* Parser::term() {
    AST* node = factor();

    while (currentToken.type == TokenEnum::MULT || currentToken.type == TokenEnum::DIV) {
        Token token = currentToken;
        if (token.type == TokenEnum::MULT) {
            eat(TokenEnum::MULT);
        } else if (token.type == TokenEnum::DIV) {
            eat(TokenEnum::DIV);
        }

        node = new BinOp(node, token, factor());
    }

    return node;
}

AST* Parser::expression() {
    AST* node = term();

    while (currentToken.type == TokenEnum::ADD || currentToken.type == TokenEnum::SUB) {
        Token token = currentToken;
        if (token.type == TokenEnum::ADD) {
            eat(TokenEnum::ADD);
        } else if (token.type == TokenEnum::SUB) {
            eat(TokenEnum::SUB);
        }

        node = new BinOp(node, token, term());
    }

    return node;
}

AST* Parser::parse() {
    return expression();
}

void Parser::advance() {
    currentToken = tokens[++currentTokenIndex];
}
