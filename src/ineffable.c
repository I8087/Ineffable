#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ineffable.h"
#include "ineffable_lexer.h"
#include "da.h"

Ineffable *Ineffable_Init (void) {
    Ineffable *f = (void*) malloc(sizeof(Ineffable));
    f->vars = (DA*) malloc(sizeof(DA));
    DA_qinit(f->vars);
    return f;
}

void Ineffable_Exec(Ineffable *ineffable, char* code) {
    DA *a = Ineffable_Lexer(ineffable, code);
    Inefable_LexerRPN(ineffable, a);
    Ineffable_Parser(ineffable, a);
}

/* Just a placeholder test. */
int main(int argc, char *argv[]) {
    Ineffable *f = Ineffable_Init();
    Ineffable_Exec(f, "a = 1 + 1\n a = a + 1\0");
    return 0;
}
