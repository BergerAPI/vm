#pragma once

#include <stdio.h>
#include "util/vector.h"

/**
 * A simple token.
 */
typedef struct Token
{
    char *value;
    int type;
} Token;

/**
 * Tokens
 */
#define TOKEN_NUMBER 0
#define TOKEN_STRING 1
#define TOKEN_IDENTIFIER 2
#define TOKEN_COLON 3
#define TOKEN_COMMA 4

/**
 * Converting a string to a list of tokens
 * @param input
 */
vector *tokenize(char input[]);
