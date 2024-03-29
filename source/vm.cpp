#include "vm.h"
#include "util/logger.h"

Virtual_Machine *vm_create(int size) {
    auto *vm = (Virtual_Machine *) malloc(sizeof(Virtual_Machine));

    if (vm == nullptr) {
        printf("Error: memory allocation failed\n");
        exit(1);
    }

    vm->memory = memory_allocate(size);

    return vm;
}

UINT16 get_register(Virtual_Machine *vm, int register_number) {
    if (register_number < 0 || register_number > REGISTER_COUNT)
        log_error("Error: register number out of range");

    return vm->registers[register_number];
}

void write_register(Virtual_Machine *vm, int register_number, UINT16 value) {
    if (register_number < 0 || register_number > REGISTER_COUNT)
        log_error("Error: register number out of range");

    vm->registers[register_number] = value;
}

UINT16 get_memory(Virtual_Machine *vm, int address) {
    if (address < 0 || address > (sizeof(vm->memory) / sizeof(UINT16)))
        log_error("Error: memory address out of range");

    return vm->memory[address];
}

void write_memory(Virtual_Machine *vm, int address, UINT16 value) {
    if (address < 0 || address > (sizeof(vm->memory) / sizeof(UINT16)))
        log_error("Error: memory address out of range");

    vm->memory[address] = value;
}

void log_registers(Virtual_Machine *vm) {
    log_debug("Registers:");

    for (int i = 0; i < REGISTER_COUNT; i++)
        log_debug("%d: %d", i, vm->registers[i]);
}

void run_vm(Virtual_Machine *vm, std::vector<Label> labels) {
    bool found_entry = false;

    // Finding the entry point
    for (int i = 0; i < labels.size(); i++) {
        Label *label = &labels[i];

        if (label->name == ENTRY_POINT) {
            if (found_entry)
                log_error("Error: multiple entry points found");

            UINT16 ip = get_register(vm, IP);
            UINT16 instr_size = label->instructions.size();

            log_debug("Starting VM, Instructions: %d, ip = %d", instr_size, ip);

            while (ip < instr_size) {
                step_vm(vm, labels);
                write_register(vm, IP, ++ip);
            }

            found_entry = true;
        }
    }

    if (!found_entry)
        log_error("Error: entry point not found");
}

void step_vm(Virtual_Machine *vm, std::vector<Label> labels) {
    // Flattening the instructions
    std::vector<Instruction> instructions;

    for (auto &i: labels) {
        Label *label = &i;

        for (auto &instruction: label->instructions)
            instructions.push_back(instruction);
    }

    UINT16 ip = get_register(vm, IP);

    if (ip >= instructions.size())
        log_error("Error: instruction pointer out of range");

    Instruction *instruction = &instructions[ip];

    switch (instruction->opcode) {
        case OP_MOV:
            write_register(vm, instruction->operand_1, instruction->operand_2);
            break;

        case OP_ADD:
            write_register(vm, ACC,
                           get_register(vm, instruction->operand_1) + get_register(vm, instruction->operand_2));
            break;

        case OP_SUB:
            write_register(vm, ACC,
                           get_register(vm, instruction->operand_1) - get_register(vm, instruction->operand_2));
            break;

        case OP_MUL:
            write_register(vm, ACC,
                           get_register(vm, instruction->operand_1) * get_register(vm, instruction->operand_2));
            break;

        case OP_DIV:
            write_register(vm, ACC,
                           get_register(vm, instruction->operand_1) / get_register(vm, instruction->operand_2));
            break;

        case OP_MOD:
            write_register(vm, ACC,
                           get_register(vm, instruction->operand_1) % get_register(vm, instruction->operand_2));
            break;

        case OP_JE:
            if (get_register(vm, ACC) == get_register(vm, instruction->operand_1))
                write_register(vm, IP, instruction->operand_2);
            break;

        case OP_JNE:
            if (get_register(vm, ACC) != get_register(vm, instruction->operand_1))
                write_register(vm, IP, instruction->operand_2);
            break;

        case OP_PUSH:
            // Push the value of the register to the stack
            vm->stack[get_register(vm, SP)] = get_register(vm, instruction->operand_1);
            write_register(vm, SP, get_register(vm, SP) + 1);
            break;

        case OP_POP:
            // Pop the value from the stack and store it in the register
            write_register(vm, instruction->operand_1, vm->stack[get_register(vm, SP) - 1]);
            write_register(vm, SP, get_register(vm, SP) - 1);
            break;

        case OP_INT:
            switch (instruction->operand_1) {
                case 0x02:
                    exit(0);

                case 0x01:
                    if (instruction->operand_1 == 0x01)
                        std::cout << get_register(vm, ACC) << std::endl;

                default:
                    log_error("Error: unknown interrupt code");
                    break;
            }

            break;

        default:
            log_error("Error: unknown opcode");
            break;
    }
}