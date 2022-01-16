#pragma once

#include "memory.h"
#include <map>

#define MAX_STACK_SIZE 1024
#define REGISTER_COUNT 7

#define ACC 0
#define IP 1
#define SP 2
#define R1 3
#define R2 4
#define R3 5
#define R4 6

#define OP_MOV 0
#define OP_ADD 1
#define OP_SUB 2
#define OP_MUL 3
#define OP_DIV 4
#define OP_MOD 5
#define OP_PUSH 6
#define OP_POP 7
#define OP_JE 8
#define OP_JNE 9

#define ENTRY_POINT "_main"
/**
 * @brief A simple assembly instruction to tell the virtual machine what to do
 */
typedef struct Instruction
{
    UINT16 opcode;

    UINT16 operand_1;
    UINT16 operand_2;
} Instruction;

/**
 * @brief A basic label that can be used to jump to a specific instruction
 */
typedef struct Label
{
    UINT16 address;

    std::string name;
    std::vector<Instruction> instructions;
} Label;

/**
 * @brief Thats the struct which stores all the information about the virtual machine
 */
typedef struct Virtual_Machine
{
    UINT16 *memory;

    UINT16 registers[REGISTER_COUNT];
    UINT16 stack[MAX_STACK_SIZE];
} Virtual_Machine;

/**
 * @brief Creates a new virtual machine
 * @param size the size of the memory
 */
Virtual_Machine *vm_create(int size);

/**
 * @brief Get the register state
 * 
 * @param vm the machine to get the register state from
 * @param register_number  the register number
 */
UINT16 get_register(Virtual_Machine *vm, int register_number);

/**
 * @brief Set the register state
 * 
 * @param vm the machine to set the register state to
 * @param register_number the register number
 * @param value the value to set
 */
void write_register(Virtual_Machine *vm, int register_number, UINT16 value);

/**
 * @brief Get the value of a memory address
 * 
 * @param vm the machine to get the memory address from
 * @param address the address to get the value from
 */
UINT16 get_memory(Virtual_Machine *vm, int address);

/**
 * @brief Writing to a specific memory address
 * 
 * @param vm the machine to write to
 * @param address the address to write to
 * @param value the value to write
 */
void write_memory(Virtual_Machine *vm, int address, UINT16 value);

/**
 * @brief Running the virtual machine
 * @param vm the virtual machine to run
 */
void run_vm(Virtual_Machine *vm, std::vector<Label> labels);

/**
 * @brief Running exactly one instruction
 * 
 * @param vm the machine
 * @param instruction the instruction to run
 */
void step_vm(Virtual_Machine *vm, std::vector<Label> labels);

/**
 * @brief Logging all registers
 * @param vm the vm from which to get the registers
 */
void log_registers(Virtual_Machine *vm);