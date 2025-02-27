#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"  // Aseg�rate de que este archivo contenga las definiciones de Token y los valores TOKEN_*


Token* get_next_token(FILE* file) {
    int ch;

    // Ignorar espacios en blanco y saltos de l�nea
    do {
        ch = fgetc(file);
    } while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');

    if (ch == EOF) {
        Token* token = malloc(sizeof(Token));
        if (token == NULL) {
            fprintf(stderr, "Error al asignar memoria para el token\n");
            exit(1);
        }
        token->type = TOKEN_EOF;
        token->value = NULL;
        return token;
    }

    Token* token = malloc(sizeof(Token));
    if (token == NULL) {
        // Manejar error: fallo al asignar memoria
        fprintf(stderr, "Error al asignar memoria para el token\n");
        exit(1);  // Salir o manejar el error de manera adecuada
    }

    // Detecta las palabras clave
    printf("DEBUG: Caracter le�do: %c\n", ch);  // Muestra el primer car�cter le�do

    // Detecta '1np' (input)
    if (ch == '1') {
        ch = fgetc(file);
        if (ch == 'n') {
            ch = fgetc(file);
            if (ch == 'p') {
                // Ahora que hemos le�do "1np", esperamos un '('
                ch = fgetc(file);
                printf("DEBUG: Caracter despu�s de '1np': %c\n", ch);  // Verifica que est� leyendo '('
                if (ch != '(') {
                    fprintf(stderr, "Esperado '(', pero encontrado '%c'\n", ch);
                    free(token);
                    return NULL;
                }

                // Leer el contenido dentro de las comillas
                ch = fgetc(file);
                if (ch == '"') {  // Detecta inicio de la cadena
                    char buffer[256];
                    int i = 0;
                    while ((ch = fgetc(file)) != '"' && ch != EOF && i < 255) {
                        buffer[i++] = ch;
                    }
                    buffer[i] = '\0';  // Asegurarse de que la cadena termine correctamente

                    // Asignamos el valor del texto dentro de las comillas
                    token->type = TOKEN_INPUT;
                    token->value = strdup(buffer);
                    if (token->value == NULL) {
                        fprintf(stderr, "Error al duplicar la cadena del valor\n");
                        free(token);
                        exit(1);
                    }
                    
                    printf("DEBUG: Cadena dentro de las comillas para input: %s\n", token->value);  // Imprime el contenido dentro de las comillas
                } else {
                    // Si no encontramos una cadena v�lida entre comillas, es un error
                    fprintf(stderr, "Se esperaba una cadena entre comillas, pero no se encontr�\n");
                    free(token);
                    return NULL;
                }
            } else {
                fprintf(stderr, "Se esperaba 'p' despu�s de '1n', pero encontrado '%c'\n", ch);
                free(token);
                return NULL;
            }
        } else {
            fprintf(stderr, "Se esperaba 'n' despu�s de '1', pero encontrado '%c'\n", ch);
            free(token);
            return NULL;
        }
    } else if (ch == 'p') {  
        // Verifica si leemos "print"
        ch = fgetc(file);
        if (ch == 'r') {
            ch = fgetc(file);
            if (ch == 'i') {
                ch = fgetc(file);
                if (ch == 'n') {
                    ch = fgetc(file);
                    if (ch == 't') {
                        // Ahora que hemos le�do "print", esperamos un '('
                        ch = fgetc(file);
                        printf("DEBUG: Caracter despu�s de 'print': %c\n", ch);  // Verifica que est� leyendo '('
                        if (ch != '(') {
                            fprintf(stderr, "Esperado '(', pero encontrado '%c'\n", ch);
                            free(token);
                            return NULL;
                        }

                        // Leer el contenido dentro de las comillas
                        ch = fgetc(file);
                        if (ch == '"') {  // Detecta inicio de la cadena
                            char buffer[256];
                            int i = 0;
                            while ((ch = fgetc(file)) != '"' && ch != EOF && i < 255) {
                                buffer[i++] = ch;
                            }
                            buffer[i] = '\0';  // Asegurarse de que la cadena termine correctamente

                            // Asignamos el valor del texto dentro de las comillas
                            token->type = TOKEN_STRING;
                            token->value = strdup(buffer);
                            if (token->value == NULL) {
                                fprintf(stderr, "Error al duplicar la cadena del valor\n");
                                free(token);
                                exit(1);
                            }
                            
                            printf("DEBUG: Cadena dentro de las comillas para print: %s\n", token->value);  // Imprime el contenido dentro de las comillas
                        } else {
                            // Si no encontramos una cadena v�lida entre comillas, es un error
                            fprintf(stderr, "Se esperaba una cadena entre comillas, pero no se encontr�\n");
                            free(token);
                            return NULL;
                        }
                    } else {
                        fprintf(stderr, "Se esperaba 't' despu�s de 'prin', pero encontrado '%c'\n", ch);
                        free(token);
                        return NULL;
                    }
                } else {
                    fprintf(stderr, "Se esperaba 'n' despu�s de 'pri', pero encontrado '%c'\n", ch);
                    free(token);
                    return NULL;
                }
            } else {
                fprintf(stderr, "Se esperaba 'i' despu�s de 'pr', pero encontrado '%c'\n", ch);
                free(token);
                return NULL;
            }
        } else {
            fprintf(stderr, "Se esperaba 'r' despu�s de 'p', pero encontrado '%c'\n", ch);
            free(token);
            return NULL;
        }
    } else {
        // Si no es un token reconocido, asignamos UNKNOWN
        token->type = TOKEN_UNKNOWN;
        token->value = NULL;
        fprintf(stderr, "Token desconocido encontrado\n");
    }

    return token;
}
