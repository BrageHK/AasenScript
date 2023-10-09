//
// Created by brage on 10. okt 2023.
//

#ifndef AASENSCRIPT_ERROR_H
#define AASENSCRIPT_ERROR_H


#include "../lexer/Lexer.h"

class error {
public:
    error() = default;

    static void throwError(Token token, std::string message);
};


#endif //AASENSCRIPT_ERROR_H
