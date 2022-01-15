#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "lexer.h"
#include "vm.h"
#include "util/vector.h"

char *read_file(char *path)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        log_error("read_file: file not found");
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *buffer = malloc(size + 1);
    if (buffer == NULL)
    {
        log_error("read_file: memory allocation failed");
    }

    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    fclose(file);

    return buffer;
}

vector *parse_tokens(vector *tokens)
{
    // We need to search for labels first
    vector *labels = vector_new(1);

    // Labels look like this: _main:
    // We need to find the colon and then the name
    for (int i = 0; i < tokens->size; i++)
    {
        Token *token = (Token *)tokens->data[i];

        if (token->type == TOKEN_IDENTIFIER)
        {
            Token *next = (Token *)tokens->data[++i];

            if (next->type == TOKEN_COLON)
            {
                i++;

                // We found a label
                Label *l = malloc(sizeof(Label));
                l->instructions = vector_new(1);
                l->name = malloc(strlen(token->value) + 1);
                strcpy(l->name, token->value);

                log_debug("Found label: \"%s\"", l->name);

                int increment = 0;

                // Parse the instructions until we find a new label
                for (int j = i; j < tokens->size; j++)
                {
                    Token *t = (Token *)tokens->data[j];

                    if (t->type != TOKEN_IDENTIFIER)
                    {
                        log_error("Expected an instruction");
                    }

                    Instruction *instruction = malloc(sizeof(Instruction));

                    // Looking forward to see if we have operands
                    Token *next = (Token *)tokens->data[j + 1];

                    if (next->type == TOKEN_COLON)
                        break;

                    instruction->opcode = get_op_code(t->value);

                    log_debug("Found instruction: \"%s\", OP-Code: %d", t->value, instruction->opcode);

                    // We have an operand
                    if (next->type != TOKEN_IDENTIFIER)
                    {
                        log_debug("Found operand: \"%s\", \"%s\"", next->value, t->value);

                        instruction->operand = atoi(next->value);
                        j++;
                        increment++;
                    }

                    push_back(l->instructions, instruction);
                    increment++;
                }

                i += increment;

                log_debug("Parsed %d instructions for label \"%s\"", l->instructions->size, token->value);

                push_back(labels, l);
            }
            else
            {
                log_error("parse_tokens: expected colon (%s, found %s)", token->value, next->value);
            }
        }
        else
        {
            log_error("parse_tokens: expected identifier (found %s)", token->value);
        }
    }

    return labels;
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

    // New Virtual Machine
    VirtualMachine *vm = vm_new();

    // Parsing the tokens
    vector *labels = parse_tokens(tokens);

    // Executing the instructions
    run(vm, labels);

    return 0;
}