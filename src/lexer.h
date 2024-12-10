
#include <stddef.h>

typedef enum {
    NONE,

    SYMBOL,

    EQUALS,
    PLUS,
    MINUS,
    STAR,
    SLASH,

    NUMBER,
    STRING,

    FOR,
    WHILE,
    FN,
    END,

    EXPRESSION,
    TERM
} TokenType;

static const char* KeyWords[] = {
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
