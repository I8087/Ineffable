#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "ineffable.h"
#include "ineffable_lexer.h"
#include "da.h"

/* Safe way of allocating memory. */
void *Ineffable_Malloc(size_t size) {

    /* Allocate memory via the C Standard Library. */
    void *r = malloc(size);

    /* If memory couldn't be allocated, throw an error! */
    if (r == NULL) {
        printf("MemoryException: Ran out of space!\n");
        exit(-1);
    }

}

/* Initializes the Ineffable VM. */
Ineffable *Ineffable_Init (void) {

    /* Check to make sure a byte has 8 and only 8 bits. */
    if (CHAR_BIT != 8) {
        printf("Error: Byte doesn't contain standard bit size.\n");
        exit(-1);
    }

    /* Create the VM structure. Used to hold all of the code and etc. */
    Ineffable *f = (void*) Ineffable_Malloc(sizeof(Ineffable));

    /* Create the variable buffer. NOTE: Is this really used??? */
    f->vars = (DA*) Ineffable_Malloc(sizeof(DA));
    DA_qinit(f->vars);

    /* Create the object buffer. */
    f->objs = (DA*) Ineffable_Malloc(sizeof(DA));
    DA_qinit(f->objs);

    return f;
}

/* Deinitializes the Ineffable VM and preforms any clean up needed. */
void Ineffable_Deinit(Ineffable *ineffable) {
    free(ineffable->vars);
    free(ineffable->objs);
    free(ineffable);
}

/* Takes source code, compiles it, and interprets it. */
void Ineffable_Exec(Ineffable *ineffable, char* code) {
    DA *a = Ineffable_Lexer(ineffable, code);
    Inefable_LexerRPN(ineffable, a);
    char *iasm = Ineffable_Parser(ineffable, a);
    Ineffable_Assembler(ineffable, iasm);
}

/* Just a placeholder test. */
int main(int argc, char *argv[]) {
    Ineffable *f = Ineffable_Init();
    Ineffable_Exec(f, "a = 100 + 1\n a = a + 1\0");
    return 0;
}
