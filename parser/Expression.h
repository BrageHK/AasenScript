//
// Created by brage on 8. okt 2023.
//

#ifndef NORLANG_EXPRESSION_H
#define NORLANG_EXPRESSION_H

#include "../enums/TokenEnum.h"
#include "../lexer/Lexer.h"
#include <string>
#include <memory>

class Expression {
private:
    void recursivePrint(std::string string, std::string prefix, std::string childPrefix);
public:
    Expression *left;
    Expression *right;
    Token *token;

    Expression(Expression* left, Expression* right, struct Token *token)
            : left(left), right(right), token(token) {
    };

    Expression(Expression* left, Expression* right, TokenEnum op)
            : left(left), right(right) {
        this->token = new Token{op, ""};
    };

    void print();
};


#endif //NORLANG_EXPRESSION_H
