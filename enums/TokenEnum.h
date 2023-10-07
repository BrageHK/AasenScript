//
// Created by brage on 6. okt 2023.
//

#ifndef NORLANG_TOKENENUM_H
#define NORLANG_TOKENENUM_H

enum class TokenEnum : int {
    INTEGER_LITERAL,      // heiltall
    IDENTIFICATOR,        //
    STRING_LITERAL,       // streng

    ADD,                  // +
    SUB,                  // -
    MULT,                 // *
    DIV,                  // /
    RPAREN,               // )
    LPAREN,               // (

    TOKEN_EOF,            // slutten av fil
    DOT,                  // .
    COMMA,                // ,
    SEMICOLON,            // ;
    LBRACE,               // {
    RBRACE,               // }
    COLON,                // :
    LESS_THAN_LESS_THAN,  // <<
    GREATER_THAN_GREATER_THAN, // >>
    LESS_TAN,             // <
    GREATER_THAN,         // >
    EQUAL,                // =
    EQUAL_EQUAL,          // ==
    LESS_THAN_EQUAL,      // <=
    GREATER_THAN_EQUAL,   // >=
    NOT_EQUAL,            // !=
    AND,                  // &&
    OR,                   // ||
    NOT,                  // !
    IF,                   // hvis
    ELSE,                 // ellers
    WHILE,                // mens
    FOR,                  // for
    PRINT,                // skriv
    RETURN,               // returner
    FUNCTION,             // funksjon
    CLASS,                // klasse
    SUPER,                // super
    THIS,                 // denne
    INTET,                // null/intet
    ERROR,                // feil
    CONST,                // urørleg
    BOOL,                 // Sanning


};

#endif //NORLANG_TOKENENUM_H
