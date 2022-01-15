#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "vm.h"

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

int main()
{
    // Creating a new stack VM
    struct StackVM *vm = malloc(sizeof(struct StackVM *));

    // Initializing the code vector
    vm->code = vector_new(1);

    // Initializing the stack VM
    vm->sp = 0;

    // Some testing
    push(vm, "1");
    push(vm, "2");
    pop(vm);
    push(vm, "7");
    add(vm);
    push(vm, "27");
    add(vm);
    sys(vm, 0);

    // Running the code
    execute(*vm);

    return 0;
}