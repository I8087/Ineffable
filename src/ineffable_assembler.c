#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ineffable.h"
#include "da.h"

/* List of Ineffable VM opcode. */
#define NOP 0xCC

#define CALL_SET 0x01
#define CALL_ADD 0x02
#define CALL_SUB 0x03

#define NEW_OBJECT 0x10
#define NEW_NUMBER 0x11

#define LOAD_OBJECT 0x20

typedef struct Ineffable_Object {
    int obj;
    char* name;
} Ineffable_Object;

void addcode(Ineffable_Object *outcode, char append) {
    if (!outcode->name) {
        outcode->name = (char*) malloc(sizeof(char));
    } else {
        outcode->name = (char*) realloc(outcode->name, (outcode->obj+1) * sizeof(char));
    }
    outcode->name[outcode->obj] = append;
    outcode->obj++;
}

Ineffable_Object* Ineffable_Assembler(Ineffable *ineffable, char *incode) {
    Ineffable_Object *tempobj = NULL;

    /* outcode mimics an Ineffable_Object for covienence. */
    Ineffable_Object *outcode = (Ineffable_Object*) malloc(sizeof(Ineffable_Object));
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
                tempobj = (Ineffable_Object*) malloc(sizeof(Ineffable_Object));
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
                Ineffable_Object *tempobj = (Ineffable_Object*) DA_get(ineffable->objs, i);
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
    for (int i=0; i<outcode->obj; i++) printf("0x%x\n", outcode->name[i]);
    return outcode;
}
