//
// Created by brage on 8. okt 2023.
//

#ifndef NORLANG_EXPRESSION_H
#define NORLANG_EXPRESSION_H

#include "../enums/TokenEnum.h"
#include <string>

class Expression {
private:
    void recursivePrint(std::string string, std::string prefix, std::string childPrefix);
public:
    Expression *Left;
    Expression *Right;
    TokenEnum Operator;

    Expression(Expression* left, Expression* right, TokenEnum op)
            : Left(left), Right(right), Operator(op) {};

    void print();
};


#endif //NORLANG_EXPRESSION_H
