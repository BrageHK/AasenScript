//
// Created by brage on 6. okt 2023.
//

#ifndef NORLANG_TOKENENUM_H
#define NORLANG_TOKENENUM_H

enum class TokenEnum : int {
    TOKEN_HELTALL_BOKSTAVELIG,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_LPARAN,
    TOKEN_HPARAN,
    TOKEN_IDENTIFIKATOR,
    TOKEN_EOF
};

#endif //NORLANG_TOKENENUM_H
