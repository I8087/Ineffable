#ifndef INEFFABLE_LEXER_H
#define INEFFABLE_LEXER_H

#include "da.h"

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

DA *Ineffable_Lexer(Ineffable *ineffable, char* code);

#endif
