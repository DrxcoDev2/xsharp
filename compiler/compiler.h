#ifndef COMPILER_H
#define COMPILER_H

#include "lexer.h"
#include "parser.h"
#include "codegen.h"

// Prototipo de la funci�n principal del compilador
int compile(const char* source_file);

#endif // COMPILER_H
