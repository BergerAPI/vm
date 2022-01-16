#include "vm.h"
#include "util/logger.h"

#include <vector>

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

    instructions.push_back({OP_MOV, R1, 100});
    instructions.push_back({OP_MOV, R2, 200});
    instructions.push_back({OP_ADD, R1, R2});

    // Execute the instructions
    run_vm(vm, instructions);

    return 0;
}