//
// Created by brage on 6. okt 2023.
//

#ifndef NORLANG_TOKENENUM_H
#define NORLANG_TOKENENUM_H

enum class TokenEnum : int {
    TOKEN_INTEGER_LITERAL,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_RPAREN,
    TOKEN_LPAREN,
    TOKEN_IDENTIFICATOR,
    TOKEN_EOF
};

#endif //NORLANG_TOKENENUM_H
