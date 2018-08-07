/**
 *  @file ineffable.c
 *  @brief The main script file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "ineffable.h"
#include "da.h"

/**
 * Creates a new Ineffable object.
 * @param *ineffable The VM.
 * @return An Ineffable_Object.
 */
Ineffable_Object *Ineffable_New_Object(Ineffable *ineffable) {
    Ineffable_Object *o = (Ineffable_Object*) Ineffable_Malloc(sizeof(Ineffable_Object));

    o->methods = (DA*) Ineffable_Malloc(sizeof(DA));
    DA_qinit(o->methods);

    return o;
}

/**
 * Provides a safe way to allocate memory with a built-in fail safe.
 * @param size The number of bytes to allocate.
 * @return The location of the allocation block.
*/
void *Ineffable_Malloc(size_t size) {

    /* Allocate memory via the C Standard Library. */
    void *r = malloc(size);

    /* If memory couldn't be allocated, throw an error! */
    if (r == NULL) {
        printf("MemoryException: Ran out of space!\n");
        exit(-1);
    }

}

/**
 * Initializes the Ineffable VM.
 * @return The VM.
 */
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

    /* Create the VM's stack. */
    f->SP = (DA*) Ineffable_Malloc(sizeof(DA));
    DA_qinit(f->SP);

    /* Create the code pointer. */
    f->CP = 0;

    /* Initialize the RAM. */
    f->RAM = NULL;
    f->RAM_size = 0;

    /* Initialize the heap. */
    f->heap = NULL;

    return f;
}

/**
 * Deinitializes the Ineffable VM and preforms any clean up needed.
 * @param *ineffable The VM.
 */
void Ineffable_Deinit(Ineffable *ineffable) {
    free(ineffable->vars);
    free(ineffable->objs);
    free(ineffable);
}

/**
 * Takes source code, compiles it, and interprets it.
 * @param *ineffable The VM.
 * @param code The source code to compile and interpret.
 */
void Ineffable_Eval(Ineffable *ineffable, char* code) {
    DA *a = Ineffable_Lexer(ineffable, code);
    Inefable_LexerRPN(ineffable, a);
    char *iasm = Ineffable_Parser(ineffable, a);
    char *icode = Ineffable_Assembler(ineffable, iasm);
    Ineffable_VM(ineffable, icode);
    Ineffable_Deinit(ineffable);
}

/**
 * Just a placeholder test to run code.
 * @param argc The number of arguments.
 * @param *argv[] List of arguments.
 * @return 0 for successful, otherwise there was an error.
 */
int main(int argc, char *argv[]) {
    Ineffable *f = Ineffable_Init();
    //Ineffable_Eval(f, "a = 100 + 1\n a = a + 1\0");
    return 0;
}
