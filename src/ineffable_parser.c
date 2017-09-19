#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ineffable.h"
#include "ineffable_lexer.h"
#include "da.h"

char* addout(char* code, char* append) {
    int codelen = strlen(code);
    int appendlen = strlen(append);
    code = (char*) realloc(code, (codelen+appendlen+1) * sizeof(char));
    memcpy(code+codelen, append, appendlen);
    code[codelen+appendlen] = '\0';
    return code;
}

void Ineffable_Parser(Ineffable *ineffable, DA *list) {
    int exists = 0;
    Ineffable_BNF *b = NULL;
    char *outcode = (char*) calloc(1, sizeof(char));
    outcode[0] = 0;
    DA_print(list);
    for (int i = 0; i < list->len; i++) {
        b = (Ineffable_BNF*) DA_get(list, i);

        switch (b->type) {
            case identifer:
            //printf("%d\n", ineffable->vars->len);
            for (int i = 0; i < ineffable->vars->len; i++) {
                if (!strcmp((char*) DA_get(ineffable->vars, i), b->code)) exists = 1;
            }

            if (!exists) {
                char *v = (char *) malloc((strlen(b->code)+1) * sizeof(char));
                strcpy(v, b->code);
                DA_append(ineffable->vars, v);
                outcode = addout(outcode, "new ");
                outcode = addout(outcode, b->code);
                outcode = addout(outcode, "\n");
            }
            outcode = addout(outcode, "load ");
            outcode = addout(outcode, b->code);
            outcode = addout(outcode, "\n");
                break;
            case number:
                outcode = addout(outcode, "push ");
                outcode = addout(outcode, b->code);
                outcode = addout(outcode, "\n");
                break;
            case op:
                if(b->code[0] == '+') outcode = addout(outcode, "add\n");
                else if (b->code[0] == '-') outcode = addout(outcode, "sub\n");
                else if (b->code[0] == '=') outcode = addout(outcode, "set\n");
                else {
                    printf("Unknown operator in parser!\n");
                    exit(-1);
                };
                break;
            case constant:
                //printf("constant!\n");
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
    printf(outcode);
}
