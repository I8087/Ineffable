#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ineffable.h"
#include "da.h"

void Inefable_LexerRPN(Ineffable *ineffable, DA *list) {
    DA* outlist = (DA *) malloc(sizeof(DA));
    DA_qinit(outlist);
    DA* stack = (DA *) malloc(sizeof(DA));
    DA_qinit(stack);

    Ineffable_BNF *b = NULL;
    for (int i = 0; i < list->len; i++) {
        b = (Ineffable_BNF*) DA_get(list, i);
        switch (b->type) {
            case identifer:
            case number:
            case constant:
                DA_append(outlist, b);
                break;
            case op:
                DA_append(stack, b);
                break;
            case newline:
                while (stack->len) DA_append(outlist, DA_pop(stack));
            case whitespace:
            case comment:
                break;
            case unknown:
            default:
                printf("RPN Error!\n");
                exit(-1);
        }
    }

    /* Empty the operator stack. */
    while (stack->len) DA_append(outlist, DA_pop(stack));
    DA_copy(outlist, list);
}
