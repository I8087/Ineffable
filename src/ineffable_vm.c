#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ineffable.h"
#include "da.h"

void Ineffable_VM(Ineffable *ineffable, char *incode) {

    for(;;) {

        /* For debugging purposes. */
        printf("0x%x\n", incode[ineffable->CP]);

        switch (incode[ineffable->CP]) {
            case NOP:
                ineffable->CP++;
                break;

            case CALL_SET:
            case CALL_ADD:
            case CALL_SUB:
                ineffable->CP++;
                printf("INTERNAL CALL!\n");
                break;

            case NEW_NUMBER:
            case LOAD_OBJECT:
                ineffable->CP += 2;
                break;

            case NEW_OBJECT:
                ineffable->CP +=2;
                Ineffable_New_Object(ineffable);
                break;

            case EXIT:
                printf("Exiting!...\n");
                return 0;

            default:
                /* Quick and dirty error message. */
                printf("0x%x\n", incode[ineffable->CP]);
                printf("VM Error!\n");
                exit(-1);
        }
    }
}
