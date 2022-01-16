#include "vm.h"
#include "util/logger.h"

#include <vector>
#include <iostream>
#include <map>

void wait_for_input(Virtual_Machine *vm, std::vector<Label> labels)
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
        UINT16 ip = get_register(vm, IP);
        step_vm(vm, labels);
        write_register(vm, IP, ++ip);
        write_register(vm, SP, 0);
    }
    else if (input == "run")
    {
        run_vm(vm, labels);
        exit(EXIT_SUCCESS);
    }
    else
        log_error("Error: unknown command");

    wait_for_input(vm, labels);
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

    std::vector<Instruction> _main;
    std::vector<Label> labels;

    _main.push_back({OP_MOV, R1, 2});
    _main.push_back({OP_MOV, R2, 7});
    _main.push_back({OP_ADD, R1, R2});
    _main.push_back({OP_MOV, R2, 3});
    _main.push_back({OP_SUB, ACC, R2});

    // Adding the main entry point ("_main")
    labels.push_back({0, ENTRY_POINT, _main});

    // Waiting for input
    wait_for_input(vm, labels);

    return 0;
}