#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ineffable.h"
#include "ineffable_lexer.h"
#include "da.h"

void Ineffable_Parser(Ineffable *ineffable, DA *list) {
    Ineffable_BNF *b = NULL;
    for (int i = 0; i < list->len; i++) {
        b = (Ineffable_BNF*) DA_get(list, i);

        switch (b->type) {
            case identifer:
                printf("identifer!\n");
                break;
            case number:
                printf("Num!\n");
                break;
            case op:
                printf("op!\n");
                break;
            case constant:
                printf("constant!\n");
                break;
            case whitespace:
            case newline:
            case comment:
                break;
            case unknown:
            default:
                printf("Unknown type!\n");
                exit(-1);
        }
    }
}
