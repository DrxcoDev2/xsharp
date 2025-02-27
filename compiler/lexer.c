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

    // Detecta las palabras clave
    if (ch == 'u') {  
        token->type = TOKEN_USE;
        token->value = strdup("use");
    } else if (ch == 's') {  
        token->type = TOKEN_STD;
        token->value = strdup("std");
    } else if (ch == 'p') {  
        token->type = TOKEN_PRINT;
        token->value = strdup("print");
    } else if (ch == '"') {  // Si es una comilla, leer una cadena
        // Leer la cadena entre comillas
        char buffer[256];
        int i = 0;
        while ((ch = fgetc(file)) != '"' && ch != EOF && i < 255) {
            buffer[i++] = ch;
        }
        buffer[i] = '\0';  // Asegurarse de que la cadena termine correctamente

        token->type = TOKEN_STRING;
        token->value = strdup(buffer);
    } else {
        // Si no es un token reconocido, no asignamos un valor y lo omitimos
        token->type = TOKEN_UNKNOWN;
        token->value = NULL; // No se asigna valor si es UNKNOWN
    }

    // Solo se imprime el token si no es UNKNOWN
    if (token->type != TOKEN_UNKNOWN) {
        printf("Token: %s\n", token->value);
    }

    return token;
}
