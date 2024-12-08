
#include <stddef.h>
#include <stdio.h>
#include "lexer.h"

int main() { 
    // FILE *file = fopen("example.c", "r");
    // if (file == NULL) {
    //     return -1;
    // }

    // while(!run_line(file));

    // fclose(file);

    Token* tokens = lexer("test awgejdvsakeajkdvna______________________________________ twaed awegwaawgdabejdknae kwakgedja\0");
    free_tokens(tokens);

    return 0;
}
