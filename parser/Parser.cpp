#include <utility>

#include "Parser.h"
#include "Expression.h"

std::unique_ptr<Expression> Parser::expression() {
    return equality();
}

std::unique_ptr<Expression> Parser::equality() {
    std::unique_ptr<Expression> expr = comparison();

    while(match({TokenEnum::NOT_EQUAL, TokenEnum::EQUAL_EQUAL})) {
        Token op = previous();
        std::unique_ptr<Expression> right = comparison();
        expr = std::make_unique<Expression>(expr.get(), right.get(), op.type);
    }
    return expr;
}

std::unique_ptr<Expression> Parser::comparison() {
    std::unique_ptr<Expression> expr = term();

    while(match({TokenEnum::GREATER_THAN, TokenEnum::GREATER_THAN_EQUAL, TokenEnum::LESS_THAN, TokenEnum::LESS_THAN_EQUAL})) {
        Token op = previous();
        std::unique_ptr<Expression> right = term();
        expr = std::make_unique<Expression>(expr.get(), right.get(), op.type);
    }
    return expr;
}

std::unique_ptr<Expression> Parser::term() {
    std::unique_ptr<Expression> expr = factor();

    while(match({TokenEnum::SUB, TokenEnum::ADD})) {
        Token op = previous();
        std::unique_ptr<Expression> right = factor();
        expr = std::make_unique<Expression>(expr.get(), right.get(), op.type);
    }
    return expr;
}

std::unique_ptr<Expression> Parser::factor() {
    std::unique_ptr<Expression> expr = unary();

    while(match({TokenEnum::DIV, TokenEnum::MULT})) {
        Token op = previous();
        std::unique_ptr<Expression> right = unary();
        expr = std::make_unique<Expression>(expr.get(), right.get(), op.type);
    }
    return expr;
}

std::unique_ptr<Expression> Parser::unary() {
    if(match({TokenEnum::SUB, TokenEnum::NOT})) {
        Token op = previous();
        std::unique_ptr<Expression> right = unary();
        return std::make_unique<Expression>(nullptr, right.get(), op.type);
    }
    return primary();
}

std::unique_ptr<Expression> Parser::primary() {
    if(match({TokenEnum::FALSE})) return std::make_unique<Expression>(nullptr, nullptr, TokenEnum::FALSE);
    if(match({TokenEnum::TRUE})) return std::make_unique<Expression>(nullptr, nullptr, TokenEnum::TRUE);
    if(match({TokenEnum::INTET})) return std::make_unique<Expression>(nullptr, nullptr, TokenEnum::INTET);

    if(match({TokenEnum::INTEGER_LITERAL, TokenEnum::STRING_LITERAL})) {
        return std::make_unique<Expression>(nullptr, nullptr, previous().type);
    }

    if(match({TokenEnum::LPAREN})) {
        std::unique_ptr<Expression> expr = expression();
        eat(TokenEnum::RPAREN);
        return std::make_unique<Expression>(nullptr, expr.get(), TokenEnum::LPAREN);
    }

}

void Parser::advance() {
    if(currentTokenIndex < tokens.size())
        currentToken = tokens[++currentTokenIndex];
}

bool Parser::match(std::initializer_list<TokenEnum> types) {
    for(auto type : types) {
        if(currentToken.type == type) {
            advance();
            return true;
        }
    }
    return false;
}

Token Parser::peek() {
    if(currentTokenIndex < tokens.size())
        return tokens[currentTokenIndex + 1];
    else
        return tokens[currentTokenIndex]; // Will return end of file token
}

Token Parser::previous() {
    if(currentTokenIndex != 0)
        return tokens[currentTokenIndex - 1];
    else
        std::cerr << "No previous token" << std::endl;
        exit(1);
}

Token Parser::eat(TokenEnum type) {
    if(currentToken.type == type) {
        advance();
        return previous();
    } else {
        std::cerr << "Expected token of type: " << static_cast<int>(type) << " but got: " << static_cast<int>(currentToken.type) << std::endl;
        exit(1);
    }
}

void Parser::parse() {
    std::unique_ptr<Expression> expr = expression();
    std::cout << "Printing expression from parser" << std::endl;
    //std::cout << tokens.size() << " " << currentTokenIndex << static_cast<int>(expr->Operator) << std::endl;
    expr->print();
    std::cout << "left node operator number: " << static_cast<int>(expr->Left->Operator) << std::endl;
}
