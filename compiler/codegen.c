#include <stdio.h>
#include "lexer.h"

void generate_code(Token* token) {
    // Aqu� simplemente imprimimos los tokens para ilustrar el proceso.
    if (token->type == TOKEN_PRINT) {
        printf("MOV R0, %s\n", token->value); // Mover valor a un registro
        printf("CALL PrintFunction\n");       // Llamar a la funci�n de impresi�n
    }
}
