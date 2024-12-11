
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Number new_number(const double d)
{
    Number number = {
        .data = d,
    };
    return number;
}

String new_string(const char* s)
{
    size_t string_length = strlen(s);
    String string = {
        .data = (char*)malloc(string_length * sizeof(char)),
        .length = string_length,
    };
    memcpy(string.data, s, string_length);
    return string;
}

Symbol new_number_symbol(const char* name, const Number number)
{
    size_t name_length = strlen(name);
    Symbol symbol = {
        .name = {
            .data = (char*)malloc(name_length * sizeof(char)),
            .length = name_length,
        },
        .type = SYMBOL_NUMBER,
        .number = number,
        .string = {
            .data = NULL,
            .length = 0,
        },
    };
    memcpy(symbol.name.data, name, name_length);
    return symbol;
}

Symbol new_string_symbol(const char* name, const String string)
{
    size_t name_length = strlen(name);
    Symbol symbol = {
        .name = {
            .data = (char*)malloc(name_length * sizeof(char)),
            .length = name_length,
        },
        .type = SYMBOL_NUMBER,
        .number = {
            .data = 0,
        },
        .string = string,
    };
    memcpy(symbol.name.data, name, name_length);
    return symbol;
}

int add_symbol(SymbolTable* symbol_table, const Symbol new_symbol)
{
    for (int i = 0; i < symbol_table->length; i++) {
        const String* name = &symbol_table->data[i].name;
        const String* new_name = &new_symbol.name;

        size_t length = (name->length < new_name->length) ? name->length : new_name->length;

        if (memcmp(name->data, new_name->data, length) == 0) {
            return -1;
        }
    }

    symbol_table->data = (Symbol*)realloc(
        symbol_table->data,
        symbol_table->length + sizeof(Symbol));

    symbol_table->data[symbol_table->length] = new_symbol;
    symbol_table->length++;
    return 0;
}

void free_string(String* string)
{
    free(string->data);
};

void free_symbol(Symbol* symbol)
{
    free_string(&symbol->name);
    free_string(&symbol->string);
}

void free_symbol_table(SymbolTable* symbol_table)
{
    for (int i = 0; i < symbol_table->length; i++) {
        free_symbol(&symbol_table->data[i]);
    }
    free(symbol_table->data);
}

void print_space(size_t n)
{
    for (size_t i = 0; i < n; i++) {
        printf(" ");
    }
}

void print_string(const String string, size_t whitespace)
{
    printf("{\n");
    print_space(whitespace);
    printf("    \"data\": \"%s\n\"", string.data);
    print_space(whitespace);
    printf("    \"length\": %lu\n", string.length);
    print_space(whitespace);
    printf("},\n");
}

void print_symbol(const Symbol symbol, size_t whitespace)
{
    printf("\"Symbol\": {\n");
    print_space(whitespace);
    printf("    \"name\": ");
    print_string(symbol.string, whitespace + 4);
    print_space(whitespace);
    printf("    \"type\": %d,\n", symbol.type);
    print_space(whitespace);
    printf("    \"number\": %f,\n", symbol.number.data);
    print_space(whitespace);
    printf("    \"string\": ");
    print_string(symbol.string, whitespace);
    print_space(whitespace);
    printf("},\n");
}

void print_symbol_table(const SymbolTable symbol_table)
{
    printf("SymbolTable: {\n");
    printf("    \"data\": [\n");
    for (size_t i = 0; i < symbol_table.length; i++) {
        printf("    \"%lu\": {\n", i);
        print_symbol(symbol_table.data[i], 8);
        printf("    },\n");
    }
    printf("    ],\n");
    printf("    \"length\": %lu\n", symbol_table.length);
    printf("}\n");
}
