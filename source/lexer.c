#include "lexer.h"

vector *tokenize(char code[])
{
    vector *tokens = vector_new(1);

    // Going through the code
    char *p = code;
    while (*p != '\0')
    {
        // Whitespace
        while (*p == ' ' || *p == '\t')
            p++;

        // Comments
        if (*p == ';')
        {
            while (*p != '\n')
                p++;
            continue;
        }

        // Newlines
        if (*p == '\n')
        {
            p++;
            continue;
        }

        // Strings
        if (*p == '"')
        {
            char *start = p;
            p++;

            while (*p != '"')
            {
                if (*p == '\0')
                    error("Unterminated string");

                p++;
            }

            char *value = malloc(p - start + 1);
            strncpy(value, start, p - start);
            value[p - start] = '\0';

            struct Token *token = malloc(sizeof(struct Token));
            token->type = TOKEN_STRING;

            token->value = value;

            push_back(tokens, token);

            p++;
            continue;
        }

        // Numbers
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

        // Identifiers
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

        // Colon
        if (*p == ':')
        {
            Token *t = malloc(sizeof(Token));
            t->value = ":";
            t->type = TOKEN_COLON;
            push_back(tokens, t);
            p++;
            continue;
        }

        // Comma
        if (*p == ',')
        {
            Token *t = malloc(sizeof(Token));
            t->value = ",";
            t->type = TOKEN_COMMA;
            push_back(tokens, t);
            p++;
            continue;
        }
    }

    return tokens;
}