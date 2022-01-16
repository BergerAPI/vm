#include "vm.h"
#include "util/logger.h"

Virtual_Machine *vm_create(int size)
{
    Virtual_Machine *vm = (Virtual_Machine *)malloc(sizeof(Virtual_Machine));

    if (vm == NULL)
    {
        printf("Error: memory allocation failed\n");
        exit(1);
    }

    vm->memory = memory_allocate(size);

    return vm;
}

UINT16 get_register(Virtual_Machine *vm, int register_number)
{
    if (register_number < 0 || register_number > REGISTER_COUNT)
        log_error("Error: register number out of range");

    return vm->registers[register_number];
}

void write_register(Virtual_Machine *vm, int register_number, UINT16 value)
{
    if (register_number < 0 || register_number > REGISTER_COUNT)
        log_error("Error: register number out of range");

    vm->registers[register_number] = value;
}

UINT16 get_memory(Virtual_Machine *vm, int address)
{
    if (address < 0 || address > (sizeof(vm->memory) / sizeof(UINT16)))
        log_error("Error: memory address out of range");

    return vm->memory[address];
}

void write_memory(Virtual_Machine *vm, int address, UINT16 value)
{
    if (address < 0 || address > (sizeof(vm->memory) / sizeof(UINT16)))
        log_error("Error: memory address out of range");

    vm->memory[address] = value;
}

void log_registers(Virtual_Machine *vm)
{
    printf("Registers:\n");

    for (int i = 0; i < REGISTER_COUNT; i++)
        printf("%d: %d\n", i, vm->registers[i]);
}

void run_vm(Virtual_Machine *vm, std::vector<Instruction> instructions)
{
    vm->instructions = instructions;

    UINT16 ip = get_register(vm, IP);
    UINT16 instr_size = instructions.size();

    log_debug("Starting VM, Instructions: %d, ip = %d", instr_size, ip);

    while (ip < instr_size)
    {
        Instruction *instruction = &vm->instructions[ip];

        switch (instruction->opcode)
        {
        case OP_MOV:
            write_register(vm, instruction->operand_1, instruction->operand_2);
            break;

        case OP_ADD:
            write_register(vm, ACC, get_register(vm, instruction->operand_1) + get_register(vm, instruction->operand_2));
            log_registers(vm);
            break;

        case OP_SUB:
            write_register(vm, ACC, get_register(vm, instruction->operand_1) - get_register(vm, instruction->operand_2));
            break;

        case OP_MUL:
            write_register(vm, ACC, get_register(vm, instruction->operand_1) * get_register(vm, instruction->operand_2));
            break;

        case OP_DIV:
            write_register(vm, ACC, get_register(vm, instruction->operand_1) / get_register(vm, instruction->operand_2));
            break;

        case OP_MOD:
            write_register(vm, ACC, get_register(vm, instruction->operand_1) % get_register(vm, instruction->operand_2));
            break;

        case OP_JE:
            if (get_register(vm, ACC) == get_register(vm, instruction->operand_1))
                ip = instruction->operand_2;
            break;

        case OP_JNE:
            if (get_register(vm, ACC) != get_register(vm, instruction->operand_1))
                ip = instruction->operand_2;
            break;

        default:
            log_error("Error: unknown opcode");
            break;
        }

        // Increment the instruction pointer
        write_register(vm, IP, ++ip);
    }
}