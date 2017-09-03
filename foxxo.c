#include <stdio.h>
#include "foxxo.h"

Foxxo *Foxxo_Init (void) {
    Foxxo *f = (void*) malloc(sizeof(Foxxo));
    *(f->vars) = NULL;
    f->vars_size = 0;
    return f;
}

void Foxxo_Exec(Foxxo *foxxo, char* code) {
    Foxxo_Lexer(foxxo, code);
}

/* Just a placeholder test. */
int main(int argc, char *argv[]) {
    Foxxo *f = Foxxo_Init();
    Foxxo_Exec(f, "abc = 1\nbcd = \"Hello!\"\0\0");
    return 0;
}
