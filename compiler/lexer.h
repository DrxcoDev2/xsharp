#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TOKEN_EOF,
    TOKEN_USE,
    TOKEN_STD,
    TOKEN_PRINT,
    TOKEN_UNKNOWN,
    TOKEN_STRING,
    TOKEN_INPUT
} TokenType;

typedef struct {
    TokenType type;
    char *value;  // Valor del token (cadena de caracteres)
} Token;

Token* get_next_token(FILE* file);

#endif
