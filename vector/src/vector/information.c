#include <stdlib.h>
#include <scic/vector.h>


bool
vector_is_initialized(const vector_t* vector)
{
        return vector->data != NULL;
}


size_t
vector_byte_size(const vector_t* vector)
{
        return vector->size * vector->element_size;
}


size_t
vector_free_space(const vector_t* vector)
{
        return vector->capacity - vector->size;
}


bool
vector_is_empty(const vector_t* vector)
{
        return vector->size == 0;
}
