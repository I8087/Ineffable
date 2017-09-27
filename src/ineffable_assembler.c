#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ineffable.h"
#include "da.h"

void addcode(Ineffable_Object_ *outcode, char append) {
    if (!outcode->name) {
        outcode->name = (char*) Ineffable_Malloc(sizeof(char));
    } else {
        outcode->name = (char*) realloc(outcode->name, (outcode->obj+1) * sizeof(char));
    }
    outcode->name[outcode->obj] = append;
    outcode->obj++;
}


/* NOTE: I dunno what i was thinking, but this Assembler is really busted. */
Ineffable_Object_* Ineffable_Assembler(Ineffable *ineffable, char *incode) {
    Ineffable_Object_ *tempobj = NULL;

    /* outcode mimics an Ineffable_Object for covienence. */
    Ineffable_Object_ *outcode = (Ineffable_Object_*) malloc(sizeof(Ineffable_Object));
    outcode->obj = 0;
    outcode->name = NULL;

    while (incode[0]) {

        if (!strncmp(incode, "new", 3)) {
            incode += 3;
            if (incode[0] != ' ') {
                printf("Expected a space!\n");
                exit(-1);
            }
            incode += 1;
            int c = 0;
            while (incode[c] && incode[c] != '\n') c++;
            if (c) {
                tempobj = (Ineffable_Object_*) malloc(sizeof(Ineffable_Object_));
                tempobj->obj = 0;
                tempobj->name = (char*) calloc(c+2, sizeof(char));
                addcode(outcode, NEW_OBJECT);
                addcode(outcode, 0);
                strncpy(tempobj->name, incode, c);
                DA_append(ineffable->objs, (int) tempobj);
                incode += c;
            } else {
                printf("Error!");
                exit(-1);
            }

            if (incode[0] && incode[0] != '\n') {
                printf("Error!");
                exit(-1);
            }

            incode++;

        } else if (!strncmp(incode, "load", 4)) {
            incode += 4;
            if (incode[0] != ' ') {
                printf("Expected a space!\n");
                exit(-1);
            }
            incode += 1;

            int c = 0;
            int found = 0;
            while (incode[c] && incode[c] != '\n') c++;

            /* Find the objects position. */
            for (int i=0; i< ineffable->objs->len; i++) {
                Ineffable_Object_ *tempobj = (Ineffable_Object_*) DA_get(ineffable->objs, i);
                if (!strncmp(tempobj->name, incode, c) && strlen(tempobj->name) == c) {
                    addcode(outcode, LOAD_OBJECT);
                    addcode(outcode, i);
                    incode += c;
                    found++;
                    break;
                }
            }

            /* Expects EOL or EOF. */
            if (incode[0] && incode[0] != '\n') {
                printf("Error!");
                exit(-1);
            }

            incode++;

        } else if (!strncmp(incode, "pushn", 5)) {
            incode += 5;

            if (incode[0] != ' ') {
                printf("Expected a space!\n");
                exit(-1);
            }

            incode += 1;

            /* Find the end of the number. */
            int c = 0;
            while (incode[c] && incode[c] != '\n') c++;

            char old = incode[c+1];
            incode[c+1] = '\0';

            addcode(outcode, NEW_OBJECT); /* TODO: Create a new object. */
            //atoi(incode);

            incode[c+1] = old;

            incode += c;

            /* Expects EOL or EOF. */
            if (incode[0] && incode[0] != '\n') {
                printf("Error!!");
                exit(-1);
            }

            incode++;

        } else if (!strncmp(incode, "add", 3)) {
            incode += 3;
            addcode(outcode, CALL_ADD);

            /* Expects EOL or EOF. */
            if (incode[0] && incode[0] != '\n') {
                printf("Error!!");
                exit(-1);
            }

            incode++;

        } else if (!strncmp(incode, "sub", 3)) {
            incode += 3;
            addcode(outcode, CALL_SUB);

            /* Expects EOL or EOF. */
            if (incode[0] && incode[0] != '\n') {
                printf("Error!!");
                exit(-1);
            }

            incode++;

        } else if (!strncmp(incode, "set", 3)) {
            incode += 3;
            addcode(outcode, CALL_SET);

            /* Expects EOL or EOF. */
            if (incode[0] && incode[0] != '\n') {
                printf("Error!!");
                exit(-1);
            }

            incode++;

        } else {
            printf("Asm error!\n");
            exit(-1);
        }
    }

    /* Make sure to end the program and properly exit! */
    addcode(outcode, EXIT);

    /* For debugging purposes. */
    //for (int i=0; i<outcode->obj; i++) printf("0x%x\n", outcode->name[i]);

    /* Don't return, just manipulate the ineffable object. */
    return outcode->name;
}
