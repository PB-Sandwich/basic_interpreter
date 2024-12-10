
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

    Token* tokens = lexer("for test1 test2 end test3 endtest4 while test5 fn test6\0");
    print_tokens(tokens);
    free_tokens(tokens);

    return 0;
}
