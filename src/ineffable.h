#ifndef INEFFABLE_H
#define INEFFABLE_H

#include "da.h"

typedef struct Ineffable {
    DA *vars; /* List of references to objects defined by the assembler? */
    DA *objs; /* The object heap for all objects in the VM. */
} Ineffable;

#endif
