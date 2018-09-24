#include <stdlib.h>
#include <scic/errno.h>
#include <scic/vector.h>

#define _SCIC_VECTOR_COMMON_H_ 1

#include <scic/vector/_common/bool.h>
#include <scic/vector/_private/error.h>


void *
vector_get(vector_t *vector, size_t index) 
{
	VECTOR_NULL_POINTER_VAL(vector, NULL);
	VECTOR_INVALID_INDEX_VAL(vector, index, NULL);
	VECTOR_INVALID_ELEM_SIZE_VAL(vector, NULL);

	return _vector_offset(vector, index);
}


const void *
vector_const_get(const vector_t *vector, size_t index) 
{
	VECTOR_NULL_POINTER_VAL(vector, NULL);
	VECTOR_INVALID_INDEX_VAL(vector, index, NULL);
	VECTOR_INVALID_ELEM_SIZE_VAL(vector, NULL);

	return _vector_const_offset(vector, index);
}


void *
vector_front(vector_t *vector) 
{
	return vector_get(vector, 0);
}


void *
vector_back(vector_t *vector) 
{
	return vector_get(vector, vector->size - 1);
}