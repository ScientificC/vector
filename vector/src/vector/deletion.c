#include <stdlib.h>
#include <string.h>
#include <scic/errno.h>
#include <scic/vector.h>

#define _SCIC_VECTOR_COMMON_H_ 1

#include <scic/vector/_common/bool.h>
#include <scic/vector/_private/error.h>


int 
vector_pop_back(vector_t *vector) 
{
	VECTOR_NULL_POINTER(vector);
	
    if (vector->size <= 0) {
        SCIC_ERROR(
            "cannot call `vector_pop_back` function when vector structure is empty",
            SCIC_EBADLEN 
        );
    }

	--vector->size;

#ifndef VECTOR_NO_SHRINK
	if (_vector_should_shrink(vector)) 
    {
		_vector_adjust_capacity(vector);
	}
#endif

	return SCIC_SUCCESS;
}


int 
vector_pop_front(vector_t *vector) 
{
	return vector_erase(vector, 0);
}


int 
vector_erase(vector_t *vector, size_t index) 
{
    VECTOR_NULL_POINTER(vector);
    VECTOR_INVALID_INDEX(vector, index);
	VECTOR_INVALID_ELEM_SIZE(vector);

	/* Just overwrite */
	_vector_move_left(vector, index);

#ifndef VECTOR_NO_SHRINK
	if (--vector->size == vector->capacity / 4) 
    {
		_vector_adjust_capacity(vector);
	}
#endif

	return SCIC_SUCCESS;
}


int 
vector_clear(vector_t *vector) 
{
	return vector_resize(vector, 0);
}