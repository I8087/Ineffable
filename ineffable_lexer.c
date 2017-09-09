/* Breaks the code down into a lexer */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ineffable.h"
#include "da.h"

typedef struct Ineffable_BNF {
    char *code;
    unsigned int len; /* Does NOT include string null! */
    enum {
        identifer,
        number,
        operator,
        string
      } type;
} Ineffable_BNF;

void Ineffable_Lexer(Ineffable *ineffable, char* code) {
    unsigned int line = 1;
    unsigned int chr = 1;
    DA list;
    DA_qinit(&list);
    while (code[0]) {
        Ineffable_BNF *bnf = (Ineffable_BNF *) malloc(sizeof(Ineffable_BNF));
        DA_append(&list, (int) bnf);
        bnf->code = NULL;
        bnf->len = 0;
        if (code[0] == '\n') {
            code++;
            chr++;
            chr = 1;
        } else if (code[0] == ' ') {
            code++;
            chr++;
        } else if (code[0] == '=') {
            code++;
            chr++;
            bnf->len++;
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

        } else if (code[0] >= 0x30 && code[0] <= 0x39) {
            while (code[0] >= 0x30 && code[0] <= 0x39) {
                code++;
                chr++;
                bnf->len++;
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

    /* Quick debug. */
    DA_print(&list);
    for (int i = 0; i < list.len; i++) {
        Ineffable_BNF b = (Ineffable_BNF) DA_get(&list, i);
        if (b.code) printf("%d: %s\n", i, b.code);
    }
}
