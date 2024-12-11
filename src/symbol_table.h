
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stddef.h>

typedef enum {
    SYMBOL_NUMBER,
    SYMBOL_STRING
} SymbolType;

typedef struct {
    char* data;
    size_t length;
} String;

typedef struct {
    double data;
} Number;

typedef struct {
    String name;
    SymbolType type;
    Number number;
    String string;
} Symbol;

typedef struct {
    Symbol* data;
    size_t length;
} SymbolTable;

Number new_number(const double d);
String new_string(const char* s);
Symbol new_number_symbol(const char* name, const Number number);
Symbol new_string_symbol(const char* name, const String string);
int add_symbol(SymbolTable* symbol_table, const Symbol new_symbol);
void free_string(String* string);
void free_symbol(Symbol* symbol);
void free_symbol_table(SymbolTable* symbol_table);
void print_string(const String string, size_t whitespace);
void print_symbol(const Symbol symbol, size_t whitespace);
void print_symbol_table(const SymbolTable symbol_table);

#endif
