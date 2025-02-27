#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"  // O el archivo donde defines Token y los valores TOKEN_*


Token* get_next_token(FILE* file) {
    int ch;

    // Ignorar espacios en blanco y saltos de l�nea
    do {
        ch = fgetc(file);
    } while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');

    if (ch == EOF) {
        Token* token = malloc(sizeof(Token));
        token->type = TOKEN_EOF;
        token->value = NULL;
        return token;
    }

    Token* token = malloc(sizeof(Token));

    if (ch == 'u') {  
        token->type = TOKEN_USE;
        token->value = strdup("use");
    } else if (ch == 's') {  
        token->type = TOKEN_STD;
        token->value = strdup("std");
    } else if (ch == 'p') {  
        token->type = TOKEN_PRINT;
        token->value = strdup("print");
    } else {
        token->type = TOKEN_UNKNOWN;
        token->value = strdup("UNKNOWN");
    }

    return token;
}
