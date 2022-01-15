#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "vm.h"
#include "lexer.h"

void push(struct StackVM *vm, char *value)
{
    struct Operation *op = malloc(sizeof(struct Operation *));
    op->name = "push";
    op->argc = 1;
    op->argv[0] = value;

    push_back(vm->code, op);
}

void pop(struct StackVM *vm)
{
    struct Operation *op = malloc(sizeof(struct Operation *));
    op->name = "pop";
    op->argc = 0;

    push_back(vm->code, op);
}

void add(struct StackVM *vm)
{
    struct Operation *op = malloc(sizeof(struct Operation *));
    op->name = "add";
    op->argc = 0;

    push_back(vm->code, op);
}

void sys(struct StackVM *vm, int id)
{
    struct Operation *op = malloc(sizeof(struct Operation *));
    op->name = "syscall";
    op->argc = 1;
    op->argv[0] = malloc(sizeof(int));
    *(int *)op->argv[0] = id;

    push_back(vm->code, op);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    // Reading a file
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Could not open file: %s\n", argv[1]);
        return 1;
    }

    // Reading the file into a string
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *code = malloc(size + 1);
    fread(code, size, 1, file);

    // Tokenizing the code
    vector *tokens = tokenize(code);

    // Creating a new stack VM
    struct StackVM *vm = malloc(sizeof(struct StackVM *));

    // Initializing the code vector
    vm->code = vector_new(1);

    // Initializing the stack VM
    vm->sp = 0;

    // Every identifier is a keyword and the arguments are the folloring literals
    // until the next identifier
    for (int i = 0; i < tokens->size; i++)
    {
        struct Token *token = (struct Token *)vector_at(tokens, i);

        if (token->type == TOKEN_IDENTIFIER)
        {
            // Calling the keyword function
            struct Operation *op = malloc(sizeof(struct Operation *));
            op->name = token->value;

            i++;

            // Advancing until the next identifier
            while (i < tokens->size)
            {
                struct Token *token = (struct Token *)vector_at(tokens, i);

                if (token->type == TOKEN_IDENTIFIER)
                {
                    i--;
                    break;
                }

                op->argc++;
                op->argv[op->argc - 1] = token->value;

                i++;
            }

            push_back(vm->code, op);
        }
        else
        {
            error("Expected an identifier");
        }
    }

    // Running the code
    execute(*vm);

    return 0;
}