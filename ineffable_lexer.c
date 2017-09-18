/* Breaks the code down into a lexer */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ineffable.h"
#include "ineffable_lexer.h"
#include "da.h"

void Inefable_RPN(Ineffable *ineffable, DA *list) {
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

DA* Ineffable_Lexer(Ineffable *ineffable, char* code) {
    unsigned int line = 1;
    unsigned int chr = 1;
    DA* list = (DA *) malloc(sizeof(DA));
    DA_qinit(list);
    while (code[0]) {
        Ineffable_BNF *bnf = (Ineffable_BNF *) malloc(sizeof(Ineffable_BNF));
        DA_append(list, (int) bnf);
        bnf->code = NULL;
        bnf->len = 0;
        bnf->line = line;
        bnf->chr = chr;
        if (code[0] == '\n') {
            code++;
            chr++;
            chr = 1;
            bnf->type = newline;
        } else if (code[0] == '#') {
            while (code[0] && code[0] != '\n') {
                code++;
                chr++;
            }
            bnf->type = comment;
        } else if (code[0] == ' ') {
            code++;
            chr++;
            bnf->type = whitespace;
        } else if (code[0] == '=') {
            code++;
            chr++;
            bnf->len++;
            bnf->type = op;
        } else if (code[0] == '+') {
            code++;
            chr++;
            bnf->len++;
            bnf->type = op;
        } else if (code[0] == '-') {
            code++;
            chr++;
            bnf->len++;
            bnf->type = op;
        } else if (code[0] == '\"') {
            code++;
            chr++;
            bnf->len++;
            while (code[0] != '\"') {
                code++;
                chr++;
                bnf->len++;
            }
            code++;
            chr++;
            bnf->len++;
            bnf->type = constant;

        } else if (code[0] >= 0x30 && code[0] <= 0x39) {
            while (code[0] >= 0x30 && code[0] <= 0x39) {
                code++;
                chr++;
                bnf->len++;
                bnf->type = number;
            }
        } else if (
            (code[0] >= 0x41 && code[0] <= 0x5A) ||
            (code[0] >= 0x61 && code[0] <= 0x7A) ||
            code[0] == 0x5F) {

            while ((code[0] >= 0x30 && code[0] <= 0x39) ||
                (code[0] >= 0x41 && code[0] <= 0x5A) ||
                (code[0] >= 0x61 && code[0] <= 0x7A) ||
                code[0] == 0x5F) {
                bnf->len++;
                code++;
                chr++;
                bnf->type = identifer;
            }
        } else {
            printf("Error! Unknown input!\n");
            exit(-1);
        }
        if (bnf->len) {
            bnf->code = (char*) calloc(bnf->len+1, sizeof(char));
            strncpy(bnf->code, code-bnf->len, bnf->len);
        }
    }

    return list;
}
