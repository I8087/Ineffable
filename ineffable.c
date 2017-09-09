#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ineffable.h"

Ineffable *Ineffable_Init (void) {
    Ineffable *f = (void*) malloc(sizeof(Ineffable));
    f->vars = NULL;
    f->vars_size = 0;
    return f;
}

void Ineffable_Exec(Ineffable *ineffable, char* code) {
    Ineffable_Lexer(ineffable, code);
}

/* Just a placeholder test. */
int main(int argc, char *argv[]) {
    Ineffable *f = Ineffable_Init();
    Ineffable_Exec(f, "abc = 1\nbcd = \"Hello!\"\0\0");
    return 0;
}
