
#include <stddef.h>
#include <stdlib.h>
#include "lexer.h"
#include "symbol_table.h"
#include "parser.h"

int main() { 

    Token* tokens = lexer("a = 15");
    print_tokens(tokens);
    free_tokens(tokens);

    SymbolTable symbol_table = {
        .data = (Symbol*)malloc(sizeof(Symbol)),
        .length = 0,
    };
    String string = new_string("test");
    Symbol str_sym = new_string_symbol("name", string);
    Number number = new_number(1.234);
    Symbol num_sym = new_number_symbol("number sym", number);
    add_symbol(&symbol_table, str_sym);
    add_symbol(&symbol_table, num_sym);
    add_symbol(&symbol_table, str_sym);
    add_symbol(&symbol_table, str_sym);
    add_symbol(&symbol_table, num_sym);
    print_symbol_table(symbol_table);

    return 0;
}
