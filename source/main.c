#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "lexer.h"

char *read_file(char *path)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        error("read_file: file not found");
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *buffer = malloc(size + 1);
    if (buffer == NULL)
    {
        error("read_file: memory allocation failed");
    }

    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    fclose(file);

    return buffer;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char *source = read_file(argv[1]);
    vector *tokens = tokenize(source);

    // Logging all tokens
    printf("Tokens:\n");
    for (int i = 0; i < tokens->size; i++)
    {
        struct Token *token = (struct Token *)tokens->data[i];
        printf("%d: %s\n", i, token->value);
    }
}