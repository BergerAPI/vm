#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// A vector is a dynamic list of objects.
typedef struct
{
    void **data;
    size_t size;
    size_t capacity;
} vector;

/**
 * Creating a vector.
 * @param initial_size 
 * @return vector* 
 */
vector *vector_new(size_t initial_size);

/**
 * Getting an element from a vector.
 * @param vector 
 */
void *vector_at(vector *v, int index);

/**
 * Pushing to the vector.
 * @param v 
 * @param element 
 */
void push_back(vector *v, void *element);

/**
 * Clearing the vector.
 * @param v 
 */
void free_vector(vector *v);