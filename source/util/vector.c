#include "vector.h"

void *vector_at(vector *v, int index)
{
    if (index < 0 || index >= v->size)
    {
        error("vector_at: index out of bounds\n");
    }

    return v->data[index];
}

void push_back(vector *v, void *element)
{
    if (v->size == v->capacity)
    {
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity * sizeof(element));
    }

    v->data[v->size++] = element;
}

void free_vector(vector *v)
{
    free(v->data);
    free(v);
}

void *vector_pop_back(vector *v)
{
    if (v->size == 0)
    {
        error("vector_pop_back: stack underflow\n");
    }

    return v->data[--v->size];
}

vector *vector_new(size_t initial_size)
{
    vector *v = (vector *)malloc(sizeof(vector));
    v->data = malloc(initial_size * sizeof(void *));
    v->size = 0;
    v->capacity = initial_size;
    return v;
}