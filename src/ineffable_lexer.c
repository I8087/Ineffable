/* Breaks the code down into a lexer generated structure. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ineffable.h"
#include "ineffable_lexer.h"
#include "da.h"


DA* Ineffable_Lexer(Ineffable *ineffable, char* code) {

    /* The current character position and line number. */
    unsigned int line = 1;
    unsigned int chr = 1;

    /* The Lexer generated list used by the Parser. */
    DA* list = (DA *) malloc(sizeof(DA));
    DA_qinit(list);


    /* The main loop where the Lexer does its job. */
    while (code[0]) {
        Ineffable_BNF *bnf = (Ineffable_BNF *) malloc(sizeof(Ineffable_BNF));
        DA_append(list, (int) bnf);
        bnf->code = NULL;
        bnf->len = 0;
        bnf->line = line;
        bnf->chr = chr;

        /* Handle linefeeds. */
        if (code[0] == '\n') {
            code++;
            chr++;
            chr = 1;
            bnf->type = newline;

        /* Handle Comments. */
        } else if (code[0] == '#') {
            while (code[0] && code[0] != '\n') {
                code++;
                chr++;
            }
            bnf->type = comment;

        /* Handle spaces. */
        } else if (code[0] == ' ') {
            code++;
            chr++;
            bnf->type = whitespace;

        /* Handle operators. */
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

        /* Handle string constants. */
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

        /* Handle numbers. */
        } else if (code[0] >= 0x30 && code[0] <= 0x39) {
            while (code[0] >= 0x30 && code[0] <= 0x39) {
                code++;
                chr++;
                bnf->len++;
                bnf->type = number;
            }

        /* Handle identifers. */
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

        /* If unkown, throw an error. */
        } else {
            printf("Error! Unknown input!\n");
            exit(-1);
        }
        /* Copy the code into the node. */
        if (bnf->len) {
            bnf->code = (char*) calloc(bnf->len+1, sizeof(char));
            strncpy(bnf->code, code-bnf->len, bnf->len);
        }
    }

    return list;
}
