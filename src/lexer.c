
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

    char* symbol = (char*)malloc(8 * sizeof(char));
    memset(symbol, '\0', sizeof(char) * 8);
    printf("%lu\n", sizeof(char) * 8);

    char c = string[*i];
    for (size_t j = 0;
         (isalpha(c) || c == '_') && c != '\0';
         *i += 1, j++, c = string[*i]) {

        if (j % 8 == 0 && j != 0) {
            symbol = (char*)realloc(symbol, j * sizeof(char));
            memset(symbol + j * sizeof(char), '\0', 8 * sizeof(char));
            printf("%lu\n", j * sizeof(char));
        }
        symbol[j] = c;
    }

    size_t size = 0;
    for (; symbol[size] != '\0'; size++);
    symbol = (char*)realloc(symbol, size * sizeof(char) + 1);

    printf("%s\n", symbol);
    token.lexeme = symbol;

    return token;
}

Token* lexer(const char* string)
{
    Token* tokens = (Token*)malloc(8 * sizeof(Token));
    memset(tokens, 0, sizeof(char) * 8);

    for (size_t i = 0, j = 0;
         string[i] != '\0';
         i++, j++) {

        if (j % 8 == 0 && j != 0) {
            tokens = (Token*)realloc(tokens, j * sizeof(Token));
            memset(tokens + j * sizeof(Token), 0, 8 * sizeof(Token));
            printf("%lu\n", j * sizeof(Token));
        }

        const char c = string[i];

        if (isalpha(c) || c == '_') {
            read_symbol(&i, string);
        }
    }

    size_t size = 0;
    for (; tokens[size].type != 0; size++);
    tokens = (Token*)realloc(tokens, size * sizeof(Token) + 1);
    tokens[size].type = EOT;

    return tokens;
}

void free_tokens(Token* token)
{
    for (size_t i = 0; token->type != EOT; i++) {
        free(token[i].lexeme);
        free(token[i].string_literal);
    }
    free(token);
}
