#include "lexer.h"

vector *tokenize(char code[])
{
    vector *tokens = vector_new(1);

    // Going through the code
    char *p = code;
    while (*p != '\0')
    {
        // Skipping whitespace
        while (*p == ' ' || *p == '\t')
            p++;

        // Skipping comments
        if (*p == '#')
        {
            while (*p != '\n')
                p++;
            continue;
        }

        // Skipping newlines
        if (*p == '\n')
        {
            p++;
            continue;
        }

        // Skipping strings
        if (*p == '"')
        {
            char *str = p + 1;
            while (*p != '"')
                p++;
            p++;
            char *value = malloc(p - str);
            strncpy(value, str, p - str);
            value[p - str] = '\0';
            Token *t = malloc(sizeof(Token));
            t->value = value;
            t->type = TOKEN_STRING;
            push_back(tokens, t);
            continue;
        }

        // Skipping numbers
        if (*p >= '0' && *p <= '9')
        {
            char *num = p;
            while (*p >= '0' && *p <= '9')
                p++;
            char *value = malloc(p - num);
            strncpy(value, num, p - num);
            value[p - num] = '\0';
            Token *t = malloc(sizeof(Token));
            t->value = value;
            t->type = TOKEN_NUMBER;
            push_back(tokens, t);
            continue;
        }

        // Skipping identifiers
        if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || *p == '_')
        {
            char *id = p;
            while ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') || *p == '_' || *p == '.')
                p++;
            char *value = malloc(p - id);
            strncpy(value, id, p - id);
            value[p - id] = '\0';
            Token *t = malloc(sizeof(Token));
            t->value = value;
            t->type = TOKEN_IDENTIFIER;
            push_back(tokens, t);
            continue;
        }
    }

    return tokens;
}