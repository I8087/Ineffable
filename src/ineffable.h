#ifndef INEFFABLE_H
#define INEFFABLE_H

/* Include dependency header file(s). */
#include "da.h"

/* List of Ineffable VM opcode. */
#define NOP 0xA0
#define EXIT 0x33

#define CALL_SET 0x01
#define CALL_ADD 0x02
#define CALL_SUB 0x03

#define NEW_OBJECT 0x10
#define NEW_NUMBER 0x11

#define LOAD_OBJECT 0x20

typedef struct Ineffable {
    DA *vars; /* List of references to objects defined by the assembler? */
    DA *objs; /* The object heap for all objects in the VM. */
    DA *stack;
    DA *SP;
    int CP;
    char *heap;
    char *RAM;
    int RAM_size;
} Ineffable;

typedef struct Ineffable_BNF {
    char *code;
    unsigned int len; /* Does NOT include string null! */
    int line;
    int chr;
    enum {
        unknown,
        identifer,
        number,
        op,
        constant,
        whitespace,
        newline,
        comment
      } type;
} Ineffable_BNF;

typedef struct Ineffable_Object {
    DA* methods; /* Holds a reference to methods. */

    /* Define the type of primitive types. */
    enum {
        NONE,
        EMPTY,
        OBJ,
        INT,
        FLOAT,
        STRING,
        BOOL,
    } type;
} Ineffable_Object;

typedef struct Ineffable_Object_ {
    int obj;
    char* name;
} Ineffable_Object_;

/* Prototype functions intended for developers. */
void *Ineffable_Malloc(size_t size);
DA *Ineffable_Lexer(Ineffable *ineffable, char* code);
void Ineffable_VM(Ineffable *ineffable, char *incode);
Ineffable_Object_* Ineffable_Assembler(Ineffable *ineffable, char *incode);
char* Ineffable_Parser(Ineffable *ineffable, DA *list);

#endif
