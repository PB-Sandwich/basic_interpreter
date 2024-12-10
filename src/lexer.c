
#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TokenType check_string_type(char* lexeme)
{
    size_t str_len = strlen(lexeme);
    if (str_len > KEY_WORDS_WIDTH) {
        return SYMBOL;
    }
    for (size_t i = 0; i < KEY_WORDS_LENGTH; i++) {
        if (memcmp(lexeme, KEY_WORDS[i], str_len) == 0) {
            return ENUM_KEYWORDS_OFFSET + i;
        }
    }
    return SYMBOL;
}

Token read_symbol(size_t* i, const char* string)
{
    Token token;
    token.character_postion = *i;
    token.type = SYMBOL;
    token.number_literal = 0.0;
    token.string_literal = NULL;

    size_t start_index = *i;

    char c = string[*i];
    size_t size = 0;
    while ((isalnum(c) || c == '_') && c != '\0') {
        size++;
        c = string[*i + size];
    }
    token.lexeme = (char*)malloc((size + 1) * sizeof(char));
    token.lexeme = memcpy(token.lexeme, &string[start_index], size);
    token.lexeme[size] = '\0';

    token.type = check_string_type(token.lexeme);

    *i += size - 1;

    return token;
}

Token read_operator(size_t* i, const char* string) {
    char c = string[*i];
    Token token;
    token.lexeme = (char*)malloc(2 * sizeof(char));
    memset(token.lexeme, '\0', 2);
    switch (c) {
        case '=':
            token.type = EQUALS;
            token.lexeme[0] = c;
            token.character_postion = *i;
        break;
        case '+':
            token.type = PLUS;
            token.lexeme[0] = c;
            token.character_postion = *i;
        break;
        case '-':
            token.type = MINUS;
            token.lexeme[0] = c;
            token.character_postion = *i;
        break;
        case '*':
            token.type = STAR;
            token.lexeme[0] = c;
            token.character_postion = *i;
        break;
        case '/':
            token.type = SLASH;
            token.lexeme[0] = c;
            token.character_postion = *i;
        break;
        default: 
            token.type = NONE;
            token.character_postion = *i;
            token.lexeme[0] = c;
        break;
    }
    return token;
}

Token read_number(size_t* i, const char* string) {
    char c = string[*i];
    size_t size = 0;
    while(isdigit(c) || c == '.') {
        size++;
        c = string[*i + size];
    }
    Token token = {
        .type = NUMBER,
        .lexeme = (char*)malloc((size + 1) * sizeof(char)),
        .string_literal = NULL,
        .number_literal = strtod(&string[*i], NULL),
        .character_postion = *i,
    };
    memcpy(token.lexeme, &string[*i], size);
    token.lexeme[size] = '\0';
    *i += size - 1;
    return token;
}

Token read_string(size_t* i, const char* string) {
    char c = string[*i];
    char match = c;
    size_t size = 0;
    do {
        size++;
        c = string[*i + size];
    } while ((c != match) && c != '\0');
    size++;

    size_t string_size = size - 2;
    if (size - 2 + 1 < 0) {
        string_size = 0;
    }

    Token token = {
        .type = STRING,
        .lexeme = (char*)malloc((size + 1) * sizeof(char)),
        .string_literal = (char*)malloc((string_size + 1) * sizeof(char)),
        .number_literal = 0,
        .character_postion = *i,
    };
    memcpy(token.lexeme, &string[*i], size);
    token.lexeme[size] = '\0';
    memcpy(token.string_literal, &string[*i + 1], string_size);
    token.string_literal[string_size] = '\0';

    *i += size - 1;
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
        Token *token = &tokens[tokens_index];

        if (isalpha(c) || c == '_') {
            *token = read_symbol(&string_index, string);
        }
        if (c == '+' || c == '-' || c == '=' || c == '*' || c == '/') {
            *token = read_operator(&string_index, string);
        }
        if (isdigit(c)) {
            *token = read_number(&string_index, string);
        }
        if (c == '\'' || c == '\"') {
            *token = read_string(&string_index, string);
        }
        if (isspace(c)) {
            token->type = WHITESPACE;
            token->lexeme = (char*)malloc(1);
            token->lexeme[0] = c;
            token->character_postion = string_index;
        }

        tokens_index++;
    }

    size_t size = 0;
    for (; tokens[size].type != 0; size++)
        ;
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

void print_tokens(Token* tokens)
{
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
