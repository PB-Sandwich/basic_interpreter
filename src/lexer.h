
#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

typedef enum {
    NONE,
    WHITESPACE,

    SYMBOL,

    EQUALS,
    PLUS,
    MINUS,
    STAR,
    SLASH,

    NUMBER,
    STRING,

    FOR, // always keep keywords in same order as KEY_WORDS or offset doesn't work
    WHILE,
    FN,
    END,

    EXPRESSION,
    TERM
} TokenType;

static const size_t ENUM_KEYWORDS_OFFSET = FOR;

#define KEY_WORDS_LENGTH 4
#define KEY_WORDS_WIDTH 6
static const char KEY_WORDS[KEY_WORDS_LENGTH][KEY_WORDS_WIDTH] = {
    "for",
    "while",
    "fn",
    "end",
};

typedef struct {
    TokenType type;
    char* lexeme;
    char* string_literal;
    double number_literal;
    size_t character_postion;
} Token;

Token* lexer(const char* string);
void free_tokens(Token* token);
void print_tokens(Token* tokens);

#endif
