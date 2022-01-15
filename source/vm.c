#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "vm.h"

#define DEBUG 1

void error(char *msg, ...)
{
    // Printing in red
    printf("\033[0;31m");

    // Printing the error message
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);

    printf("\033[0m\n");

    exit(1);
}

void debug(char *msg, ...)
{
#ifdef DEBUG
    // Printing in blue
    printf("\033[0;34m");

    // Printing the error message
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);

    // new line
    printf("\033[0m\n");

#endif
}

/**
 * System call for printing
 * @param argc 
 * @param argv 
 */
void sys_call_0(struct StackVM *vm)
{
    // Checking for an empty stack
    if (vm->sp == 0)
    {
        error("sys_call_0: stack underflow");
    }

    debug("sys_call_0");

    // Printing the top element of the stack
    printf("%i\n", vm->stack[vm->sp - 1]);
}

// System calls
struct SystemCall sys_calls[] = {
    {0, sys_call_0},
};

/**
 * Thats our push instruction.
 * @param vm 
 * @return int 
 */
int pushInstr(struct StackVM *vm, int argc, char *argv[])
{
    // Checking if we have enough arguments
    if (argc != 1)
    {
        error("push: wrong number of arguments\n");
    }

    // Pushing the value
    vm->stack[vm->sp++] = atoi(argv[0]);

    debug("push: %s, Stack-Size: %i", argv[0], vm->sp);
}

/**
 * Thats our pop instruction.
 * @param vm 
 * @return int 
 */
int popInstr(struct StackVM *vm, int argc, char *argv[])
{
    // Checking if we have enough arguments
    if (argc != 0)
    {
        error("pop: wrong number of arguments");
    }

    // Popping the value
    vm->sp--;

    debug("pop, Stack-Size: %i", vm->sp);
}

int addInstr(struct StackVM *vm, int argc, char *argv[])
{
    // Checking if we have enough arguments
    if (argc != 0)
    {
        error("add: wrong number of arguments");
    }

    // Checking the stack size
    if (vm->sp < 2)
    {
        error("add: stack underflow");
    }

    // Adding last 2 values toghether
    vm->stack[vm->sp - 2] += vm->stack[vm->sp - 1];

    // Removing the last value
    vm->sp--;

    debug("add, Stack-Size: %i", vm->sp);

    return 0;
}

int sysInstr(struct StackVM *vm, int argc, char *argv[])
{
    // Checking if we have enough arguments
    if (argc != 1)
    {
        error("syscall: wrong number of arguments");
    }

    // Checking if the argumentois a number
    int sys_call_id = atoi(argv[0]);

    // Checking if the system call exists
    if (sys_call_id < 0 || sys_call_id >= sizeof(sys_calls) / sizeof(struct SystemCall))
    {
        error("syscall: system call does not exist");
    }

    // Calling the system call
    sys_calls[sys_call_id].func(vm);

    return 0;
}

// All our instructions in one list
struct Instruction instrs[] = {
    {"push", pushInstr},
    {"pop", popInstr},
    {"add", addInstr},
    {"syscall", sysInstr},
};

void execute(struct StackVM vm)
{
    for (int i = 0; i < vm.code->size; i++)
    {
        struct Operation *op = (struct Operation *)vector_at(vm.code, i);
        int found_instr = 0;

        // Checking if the instruction is in our list
        for (int j = 0; j < sizeof(instrs) / sizeof(struct Instruction); j++)
        {
            if (strcmp(op->name, instrs[j].code) == 0)
            {
                if (found_instr == 1)
                {
                    error("Multiple instructions with the same name: %s", op->name);
                }

                found_instr = 1;
                instrs[j].func(&vm, op->argc, op->argv);
            }
        }

        if (found_instr == 0)
        {
            error("Unknown instruction: '", op->name, "'");
        }
    }
}