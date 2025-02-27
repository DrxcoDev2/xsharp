#include <stdio.h>
#include "lexer.h"
#include "parser.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error: archivo fuente no proporcionado.\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: no se puede abrir el archivo.\n");
        return 1;
    }

    parse(file);
    fclose(file);

    return 0;
}
