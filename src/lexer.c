
#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token read_string(size_t* i, const char* string)
{
    Token token;
    token.character_postion = *i;
    token.type = SYMBOL;
    token.number_literal = 0.0;
    token.string_literal = NULL;

    size_t start_index = *i;

    size_t size = 0;
    while ((isalpha(string[*i]) || string[*i] == '_' || isdigit(string[*i])) && string[*i] != '\0') {
        size++;
        *i += 1;
    }
    token.lexeme = (char*)malloc(size);
    token.lexeme = memcpy(token.lexeme, &string[start_index], size);
    token.lexeme[size] = '\0';

    return token;
}

Token* lexer(const char* string)
{
    Token* tokens = (Token*)malloc(8 * sizeof(Token));
    memset(tokens, 0, sizeof(Token) * 8);

    size_t tokens_length = 8;
    size_t tokens_index = 0;

    for (size_t string_index = 0; string[string_index] != '\0'; string_index++) {
        if (tokens_index + 1 >= tokens_length) {
            tokens = (Token*)realloc(tokens, (tokens_length * sizeof(Token)) + (8 * sizeof(Token)));
            memset(&tokens[tokens_index], 0, 8 * sizeof(Token));
            tokens_length += 8;
        }

        const char c = string[string_index];

        if (isalpha(c) || c == '_') {
            tokens[tokens_index] = read_string(&string_index, string);
        }

        tokens_index++;
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
