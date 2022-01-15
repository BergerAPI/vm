#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "util/vector.h"

#define DEFAULT_HEAP_SIZE 1024
#define DEFAULT_STACK_SIZE 1024

#define PUSH_INST 0
#define POP_INST 1
#define IADD_INST 2
#define ISUB_INST 3
#define IMUL_INST 4
#define IDIV_INST 5
#define ILT_INST 6
#define IEQ_INST 7
#define BR_INST 8
#define BRT_INST 9
#define BRF_INST 10
#define SYS_INST 11
#define HALT_INST 12

typedef struct Instruction
{
    int opcode;
    int operand;
} Instruction;

typedef struct Label
{
    char *name;
    vector *instructions;
} Label;

/**
 * This stores all of our informations we need to run a program.
 */
typedef struct VirtualMachine
{
    int stack[DEFAULT_STACK_SIZE];
    vector *labels;

    int heap[DEFAULT_HEAP_SIZE];
    int sp;
} VirtualMachine;

/**
 * Initializes a new virtual machine.
 * @return VirtualMachine* 
 */
VirtualMachine *vm_new();

/**
 * Running our virtual machine.
 * @param vm
 * @param instructions 
 */
void run(VirtualMachine *vm, vector *labels);

/**
 * Get the op code object
 * @param op 
 * @return int 
 */
int get_op_code(char *op);