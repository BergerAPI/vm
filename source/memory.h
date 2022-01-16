#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#define UINT16 unsigned short

#define MB_TO_BYTES(size) (size * 1024 * 1024)
#define GB_TO_BYTES(size) (size * 1024 * 1024 * 1024)

/**
 * @brief Creating memory
 * 
 * @param size how much memory
 */
UINT16 *memory_allocate(int size);

/**
 * @brief Freeing some memory
 * 
 * @param memory the memory to free
 */
void free_memory(UINT16 *memory);