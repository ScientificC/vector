#include <stdlib.h>
#include <string.h>
#include <scic/errno.h>
#include <scic/vector.h>

#define _SCIC_COMMON_H_ 1

#include <scic/vector/_common/bool.h>
#include <scic/vector/_private/error.h>


int
vector_push_back(vector_t *vector, void *elem)
{
    int errno;

    VECTOR_NULL_POINTER(vector);

    if (_vector_should_grow(vector)) 
    {
        if ((errno = _vector_adjust_capacity(vector)) != SCIC_SUCCESS) 
        {
            return errno;
        }
    }

    _vector_assign(vector, vector->size, elem);
    ++vector->size;

    return SCIC_SUCCESS;
}


int
vector_push_front(vector_t *vector, void *element)
{
    return vector_insert(vector, 0, element);
}


int 
vector_insert(vector_t *vector, size_t index, void *element) 
{
	void *offset;
    int errno;

    VECTOR_NULL_POINTER(vector);
    VECTOR_INVALID_INDEX(vector, index);
    VECTOR_INVALID_ELEM_SIZE(vector);

	if (_vector_should_grow(vector)) 
    {
		if ((errno = _vector_adjust_capacity(vector)) != SCIC_SUCCESS) 
        {
			return errno;
		}
	}

	/* Move other elements to the right */
	if ((errno = _vector_move_right(vector, index)) != SCIC_SUCCESS) 
    {
		return errno;
	}

	/* Insert the element */
	offset = _vector_offset(vector, index);

	memcpy(offset, element, vector->element_size);
	++vector->size;

	return SCIC_SUCCESS;
}


int 
vector_assign(vector_t *vector, size_t index, void *element) 
{
	VECTOR_NULL_POINTER(vector);
    VECTOR_INVALID_INDEX(vector, index);
    VECTOR_INVALID_ELEM_SIZE(vector);

	_vector_assign(vector, index, element);

	return SCIC_SUCCESS;
}