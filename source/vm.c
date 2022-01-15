#include "vm.h"
#include "util/logger.h"
#include "string.h"

VirtualMachine *vm_new()
{
    VirtualMachine *vm = (VirtualMachine *)malloc(sizeof(VirtualMachine));
    vm->labels = vector_new(1);
    return vm;
}

void run(VirtualMachine *vm, vector *labels)
{
    int found_entry = 0;

    // Checking if we even have an entry point ("_main")
    for (int i = 0; i < labels->size; i++)
    {
        Label *label = (Label *)vector_at(labels, i);

        log_debug("Label: %s, stack size: %d", label->name, vm->sp);

        if (strcmp(label->name, "_main") == 0)
        {
            log_debug("Found entry point: %d", label->instructions->size);

            if (found_entry == 1)
            {
                log_error("Multiple entry points found");
            }

            // We found our entry point, so we can start executing instructions
            for (int i = 0; i < label->instructions->size; i++)
            {
                Instruction *inst = (Instruction *)vector_at(label->instructions, i);

                switch (inst->opcode)
                {
                case PUSH_INST:
                    // Checking if the operand is not null
                    if (inst->operand == 0)
                    {
                        log_error("Cannot push null");
                    }

                    // Push an integer onto the stack
                    vm->stack[vm->sp++] = inst->operand;
                    break;
                case POP_INST:
                    if (vm->sp == 0)
                    {
                        log_error("POP: Stack underflow");
                    }

                    // Pop an integer from the stack
                    vm->sp--;

                    break;
                case IADD_INST:
                    // Checking if we have an stack underflow
                    if (vm->sp < 2)
                    {
                        log_error("IADD: Stack underflow, stack size: %d", vm->sp);
                    }

                    vm->stack[vm->sp - 2] = vm->stack[vm->sp - 2] + vm->stack[vm->sp - 1];
                    vm->sp--;

                    break;
                case ISUB_INST:
                    // Checking if we have an stack underflow
                    if (vm->sp < 2)
                    {
                        log_error("ISUB: Stack underflow");
                    }

                    vm->stack[vm->sp++] = vm->stack[--vm->sp] - vm->stack[--vm->sp];
                    break;
                case IMUL_INST:
                    log_error("IMUL: Not implemented");
                    break;
                case IDIV_INST:
                    log_error("IDIV: Not implemented");
                    break;
                case SYS_INST:

                    if (inst->operand == 0)
                    {
                        log_error("SYS: Cannot call null");
                    }

                    // Calling a system function
                    switch (inst->operand)
                    {
                    case 1:
                        if (vm->sp < 1)
                        {
                            log_error("SYS: Stack underflow");
                        }

                        printf("%i\n", vm->stack[--vm->sp]);
                        break;

                    default:
                        log_error("SYS: Invalid system function: %d", inst->operand);
                        break;
                    }

                    break;
                case HALT_INST:
                    log_info("HALT: Program halted");
                    break;
                default:
                    log_error("Unknown opcode: %d", inst->opcode);
                    break;
                }
            }

            found_entry = 1;
        }
    }

    if (found_entry == 0)
    {
        log_error("No entry point found");
    }
}

int get_op_code(char *c)
{
    // Detecting the opcode (this is very bad practice, but otherwise we'd have a ton of effort)
    if (strcmp(c, "push") == 0)
        return PUSH_INST;
    else if (strcmp(c, "pop") == 0)
        return POP_INST;
    else if (strcmp(c, "iadd") == 0)
        return IADD_INST;
    else if (strcmp(c, "isub") == 0)
        return ISUB_INST;
    else if (strcmp(c, "imul") == 0)
        return IMUL_INST;
    else if (strcmp(c, "div") == 0)
        return IDIV_INST;
    else if (strcmp(c, "halt") == 0)
        return HALT_INST;
    else if (strcmp(c, "syscall") == 0)
        return SYS_INST;
    else
        log_error("Unknown instruction: %s", c);
}