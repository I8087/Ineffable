/* Breaks the code down into a lexer */

typedef struct Foxxo_BNF {
    char *code;
    unsigned int len; /* Does NOT include string null! */
    enum {
        identifer,
        number,
        operator,
        string
      } type;
} Foxxo_BNF;

void Foxxo_Lexer(Foxxo *foxxo, char* code) {
    unsigned int line = 1;
    unsigned int chr = 1;
    //int llist_size = 0;
    //void **llist = (void*) malloc(sizeof(Foxxo_BNF));
    while (code[0]) {
        Foxxo_BNF* bnf = (Foxxo_BNF *) malloc(sizeof(Foxxo_BNF));
        bnf->code = NULL;
        bnf->len = 0;
        if (code[0] == '\n') {
            code++;
            line++;
            chr =1;
        } else if (code[0] == ' ') {
            code++;
            chr++;
        } else if (code[0] == '=') {
            code++;
            chr++;
        } else if (code[0] == '\"') {
            code++;
            chr++;
            while (code[0] != '\"') {
                bnf->len++;
                code++;
                chr++;
            }
            code++;
            chr++;
        } else if (code[0] >= 0x30 && code[0] <= 0x39) {
            while (code[0] >= 0x30 && code[0] <= 0x39) {
                code++;
                chr++;
            }
        } else if (
            (code[0] >= 0x41 && code[0] <= 0x5A) ||
            (code[0] >= 0x61 && code[0] <= 0x7A) ||
            code[0] == 0x5F) {

            while ((code[0] >= 0x30 && code[0] <= 0x39) ||
                (code[0] >= 0x41 && code[0] <= 0x5A) ||
                (code[0] >= 0x61 && code[0] <= 0x7A) ||
                code[0] == 0x5F) {
                bnf->len++;
                code++;
                chr++;
            }
            bnf->code = (char*) malloc((bnf->len+1) * sizeof(char));
            strncpy(bnf->code, code-bnf->len, bnf->len);
        } else {
            printf("Error! Unknown input!\n");
            exit(-1);
        }
    }
}
