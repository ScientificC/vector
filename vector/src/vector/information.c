#include <stdlib.h>
#include <scic/vector.h>


bool
scic_vector_is_initialized(const scic_vector_t* vector)
{
	return vector->data != NULL;
}


size_t
scic_vector_byte_size(const scic_vector_t* vector)
{
	return vector->size * vector->element_size;
}


size_t
scic_vector_free_space(const scic_vector_t* vector)
{
	return vector->capacity - vector->size;
}


bool
scic_vector_is_empty(const scic_vector_t* vector)
{
	return vector->size == 0;
}
