#include <stdio.h>

typedef struct Foxxo {
    int placeholder;
} Foxxo;

Foxxo *Foxxo_Init (void) {
    return (void*) malloc(sizeof(Foxxo));
}

void Foxxo_Exec(Foxxo foxxo) {
    ;
}

/* Just a placeholder test. */
void main(int argc, char *argv[]) {
    Foxxo *f = Foxxo_Init();
    return 0;
}
