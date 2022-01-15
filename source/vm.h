#pragma once

#include "vector.h"

struct SystemCall
{
    int id;
    int (*func)(struct StackVM *);
};

/**
 * This is a basic operation on the virtual machine.
 */
struct Operation
{
    char *name;
    int argc;
    char *argv[10];
};

/**
 * Thats basically out virtual machine.
 */
struct StackVM
{
    int sp;
    vector *code;
    int stack[1024];
};

/**
 * A basic assembly instruction.
 */
struct Instruction
{
    char *code;
    int (*func)(struct StackVM *, int argc, char *argv[]);
};

/**
 * Throw an error.
 * @param msg 
 */
void error(char *msg, ...);

/**
 * Debugging message
 * @param msg 
 */
void debug(char *msg, ...);

/**
 * Executing all the code in the vm.
 * @param vm 
 */
void execute(struct StackVM vm);