
#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <stdint.h>

typedef struct ParseNode {
    struct ParseNode* left;
    struct ParseNode* middle;
    struct ParseNode* right;
} ParseNode;

uint8_t* parser(Token* tokens);

#endif
