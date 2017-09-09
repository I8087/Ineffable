/* Breaks the code down into a lexer */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ineffable.h"

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
    int llist_size = 0;
    Ineffable_BNF **llist = NULL;
    while (code[0]) {
        llist_size++;
        llist = (Ineffable_BNF**) realloc(llist, sizeof(Ineffable_BNF*) * llist_size);
        Ineffable_BNF *bnf = (Ineffable_BNF *) malloc(sizeof(Ineffable_BNF));
        llist[llist_size-1] = bnf;
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
        } else if (code[0] == '\"') {
            code++;
            chr++;
            while (code[0] != '\"') {
                bnf->len++;
                code++;
                chr++;
            }
            code++;
            chr++;
        } else if (code[0] >= 0x30 && code[0] <= 0x39) {
            while (code[0] >= 0x30 && code[0] <= 0x39) {
                code++;
                chr++;
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
            bnf->code = (char*) malloc((bnf->len+1) * sizeof(char));
            strncpy(bnf->code, code-bnf->len, bnf->len);
        } else {
            printf("Error! Unknown input!\n");
            exit(-1);
        }
    }
    for (int i = 0; i <llist_size; i++) {
        printf(llist[llist_size]->code);
    }
}
