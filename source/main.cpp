#include "vm.h"
#include "util/logger.h"

#include <vector>
#include <iostream>

void wait_for_input(Virtual_Machine *vm, std::vector<Instruction> instructions)
{
    std::string input;
    std::cout << "> ";
    std::cin >> input;

    if (input == "registers")
        log_registers(vm);
    else if (input == "memory")
    {
        int address;
        std::cout << "Memory Address > ";
        std::cin >> address;

        log_debug("Memory address %d: %d", address, get_memory(vm, address));
    }
    else if (input == "exit")
        exit(EXIT_SUCCESS);
    else if (input == "next")
    {
        // Instruction-Pointer
        int ip = get_register(vm, IP);

        // Getting the next instruction
        step_vm(vm, &instructions[ip]);

        // Increasing the instruction pointer
        write_register(vm, IP, ip + 1);
    }
    else if (input == "run")
    {
        run_vm(vm, instructions);
        exit(EXIT_SUCCESS);
    }
    else
        log_error("Error: unknown command");

    wait_for_input(vm, instructions);
}

/**
 * @brief Entry point
 * 
 * @param argc number of arguments 
 * @param argv arguments
 * @return int the return code
 */
int main(int argc, char *argv[])
{
    Virtual_Machine *vm = vm_create(MB_TO_BYTES(1));

    std::vector<Instruction> instructions;

    instructions.push_back({OP_MOV, R1, 2});
    instructions.push_back({OP_MOV, R2, 7});
    instructions.push_back({OP_ADD, R1, R2});
    instructions.push_back({OP_MOV, R2, 3});
    instructions.push_back({OP_SUB, ACC, R2});

    // Waiting for input
    wait_for_input(vm, instructions);

    return 0;
}