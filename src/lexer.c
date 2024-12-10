
#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token read_symbol(size_t* i, const char* string)
{
    Token token;
    token.character_postion = *i;
    token.type = SYMBOL;
    token.number_literal = 0.0;
    token.string_literal = NULL;

    size_t size = 0;
    while ((isalpha(string[*i]) || string[*i] == '_') && string[*i] != '\0') {
        size++;
        *i += 1;
    }
    size--;
    token.lexeme = (char*)malloc(size + 1);
    token.lexeme = memcpy(token.lexeme, &string[*i - 1], size);

    return token;
}

Token* lexer(const char* string)
{
    Token* tokens = (Token*)malloc(8 * sizeof(Token));
    memset(tokens, 0, sizeof(Token) * 8);

    for (size_t i = 0, j = 0;
         string[i] != '\0';
         i++, j++) {

        if (j % 8 == 0 && j != 0) {
            tokens = (Token*)realloc(tokens, j * sizeof(Token));
            memset(tokens + (j * sizeof(Token)) - 1, 0, 8 * sizeof(Token));
        }

        const char c = string[i];

        if (isalpha(c) || c == '_') {
            tokens[j] = read_symbol(&i, string);
        }
    }

    size_t size = 0;
    for (; tokens[size].type != 0; size++);
    tokens = (Token*)realloc(tokens, size * sizeof(Token) + 1);
    tokens[size].type = 0;

    return tokens;
}

void free_tokens(Token* tokens)
{
    for (size_t i = 0; tokens[i].type != 0; i++) {
        free(tokens[i].lexeme);
        free(tokens[i].string_literal);
    }
    free(tokens);
}

void print_tokens(Token* tokens) {
    printf("[\n");
    for (size_t i = 0; tokens[i].type != 0; i++) {
        const Token t = tokens[i];
        printf("\"token%lu\": {\n", i);
        printf("    \"type\": %d,\n", t.type);
        printf("    \"lexeme\": \"%s\",\n", t.lexeme);
        printf("    \"string_literal\": \"%s\",\n", t.string_literal);
        printf("    \"number_literal\": %f,\n", t.number_literal);
        printf("    \"character_position\": %lu,\n", t.character_postion);
        printf("}\n");
    }
    printf("]\n");
}
