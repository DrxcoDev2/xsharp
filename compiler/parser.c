#include <stdio.h>
#include <stdlib.h>  // Necesario para free()
#include "lexer.h"

void parse(FILE* file) {
    Token* token = get_next_token(file);
    while (token->type != TOKEN_EOF) {
        printf("%s\n", token->value);
        free(token);  // Liberar memoria del token actual
        token = get_next_token(file);  // Leer el siguiente token
    }
    free(token);  // Liberar memoria del �ltimo token
}
