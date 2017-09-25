#ifndef INEFFABLE_H
#define INEFFABLE_H

#include "da.h"

typedef struct Ineffable {
    DA *vars; /* List of references to objects defined by the assembler? */
    DA *objs; /* The object heap for all objects in the VM. */
} Ineffable;

typedef struct Ineffable_BNF {
    char *code;
    unsigned int len; /* Does NOT include string null! */
    int line;
    int chr;
    enum {
        unknown,
        identifer,
        number,
        op,
        constant,
        whitespace,
        newline,
        comment
      } type;
} Ineffable_BNF;

/* Prototype functions intended for developers. */
void *Ineffable_Malloc(size_t size);
DA *Ineffable_Lexer(Ineffable *ineffable, char* code);

#endif
