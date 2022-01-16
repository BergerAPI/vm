#include "memory.h"

UINT16 *memory_allocate(int size)
{
    UINT16 *memory = (UINT16 *)malloc(size * sizeof(UINT16));

    if (memory == NULL)
    {
        printf("Error: memory allocation failed\n");
        exit(1);
    }

    return memory;
}

void free_memory(UINT16 *memory)
{
    free(memory);
}