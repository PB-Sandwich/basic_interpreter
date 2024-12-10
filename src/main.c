
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

    Token* tokens = lexer("test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12\0");
    print_tokens(tokens);
    free_tokens(tokens);

    return 0;
}
