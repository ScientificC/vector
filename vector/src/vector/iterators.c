#include <stdlib.h>
#include <scic/errno.h>
#include <scic/vector.h>

#define _SCIC_VECTOR_COMMON_H_ 1

#include <scic/vector/_common/bool.h>
#include <scic/vector/_private/error.h>

iterator_t
vector_begin(vector_t *vector)
{
	return vector_iterator(vector, 0);
}

iterator_t
vector_end(vector_t *vector)
{
	return vector_iterator(vector, vector->size);
}

iterator_t
vector_iterator(vector_t *vector, size_t index)
{
	iterator_t iterator = { NULL, 0 };

	VECTOR_NULL_POINTER_VAL(vector, iterator);
	VECTOR_INVALID_VECTOR_SIZE_VAL(vector, iterator);

        if (index > vector->size)
                SCIC_ERROR_VAL("failed to access to invalid index",
                           SCIC_EINVAL, iterator);

	iterator.pointer = _vector_offset(vector, index);
	iterator.element_size = vector->element_size;

	return iterator;
}

void *
iterator_get(iterator_t *iterator)
{
	return iterator->pointer;
}

int iterator_erase(vector_t *vector, iterator_t *iterator)
{
	size_t index = iterator_index(vector, iterator);
        int error = vector_erase(vector, index);

	if (error != SCIC_SUCCESS)
		return SCIC_SUCCESS;

	*iterator = vector_iterator(vector, index);

	return SCIC_SUCCESS;
}

void
iterator_increment(iterator_t *iterator)
{
	VECTOR_NULL_ITERATOR_POINTER_VOID(iterator);

	iterator->pointer += iterator->element_size;
}

void
iterator_decrement(iterator_t *iterator)
{
	VECTOR_NULL_ITERATOR_POINTER_VOID(iterator);

	iterator->pointer -= iterator->element_size;
}

void *
iterator_next(iterator_t *iterator)
{
	void *current = iterator->pointer;

	iterator_increment(iterator);

	return current;
}

void *
iterator_previous(iterator_t *iterator)
{
	void *current = iterator->pointer;

	iterator_decrement(iterator);

	return current;
}

bool
iterator_equals(iterator_t *first, iterator_t *second)
{
	VECTOR_INVALID_ELEM_SIZE_COMPARISON_VAL(first, second, false);

	return first->pointer == second->pointer;
}

bool
iterator_is_before(iterator_t *first, iterator_t *second)
{
	VECTOR_INVALID_ELEM_SIZE_COMPARISON_VAL(first, second, false);

	return first->pointer < second->pointer;
}

bool
iterator_is_after(iterator_t *first, iterator_t *second)
{
	VECTOR_INVALID_ELEM_SIZE_COMPARISON_VAL(first, second, false);

	return first->pointer > second->pointer;
}

size_t
iterator_index(vector_t *vector, iterator_t *iterator)
{
	VECTOR_NULL_POINTER(vector);
	VECTOR_NULL_ITERATOR_POINTER_VOID(iterator);

	return (iterator->pointer - vector->data) / vector->element_size;
}
