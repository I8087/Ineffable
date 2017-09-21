#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ineffable.h"
#include "ineffable_lexer.h"
#include "da.h"

/* Initializes the Ineffable VM. */
Ineffable *Ineffable_Init (void) {
    Ineffable *f = (void*) malloc(sizeof(Ineffable));
    f->vars = (DA*) malloc(sizeof(DA));
    DA_qinit(f->vars);
    f->objs = (DA*) malloc(sizeof(DA));
    DA_qinit(f->objs);
    return f;
}

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
