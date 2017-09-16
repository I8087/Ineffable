#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ineffable.h"
#include "ineffable_lexer.h"
#include "da.h"

void Ineffable_Parser(Ineffable *ineffable, DA *list) {
    DA_print(list);
    for (int i = 0; i < list->len; i++) {
        Ineffable_BNF b = (Ineffable_BNF) DA_get(list, i);
        if (b.code) printf("%d: %d:%d - \"%s\"\n", i, b.line, b.chr, b.code);
    }
}
