#include <stdlib.h>
#include <string.h>
#include <scic/errno.h>
#include <scic/vector.h>

#define _SCIC_COMMON_H_ 1

#include <scic/vector/_common/bool.h>
#include <scic/vector/_private/error.h>


bool
_vector_should_grow(vector_t *vector)
{
        // TODO: assert(vector->size <= vector->capacity);

        return vector->size == vector->capacity;
}


bool
_vector_should_shrink(vector_t *vector)
{
        // TODO: assert(vector->size <= vector->capacity);

        return vector->size == vector->capacity * VECTOR_SHRINK_THRESHOLD;
}


size_t
_vector_free_bytes(const vector_t *vector)
{
        return vector_free_space(vector) * vector->element_size;
}


void *
_vector_offset(vector_t *vector, size_t index)
{
        return vector->data + (index * vector->element_size);
}


const void *
_vector_const_offset(const vector_t *vector, size_t index)
{
        return vector->data + (index * vector->element_size);
}


void
_vector_assign(vector_t *vector, size_t index, void *element)
{
        /* Insert the element */
        void *offset = _vector_offset(vector, index);
        memcpy(offset, element, vector->element_size);
}


int
_vector_move_right(vector_t *vector, size_t index)
{
        // TODO: assert(vector->size < vector->capacity);

        /* The location where to start to move from. */
        void *offset = _vector_offset(vector, index);

        /* How many to move to the right. */
        size_t elements_in_bytes = (vector->size - index) * vector->element_size;

#ifdef __STDC_LIB_EXT1__
        size_t right_capacity_in_bytes =
                (vector->capacity - (index + 1)) * vector->element_size;

        /* clang-format off */
        int return_code =  memmove_s(
                offset + vector->element_size,
                right_capacity_in_bytes,
                offset,
                elements_in_bytes
        );
        /* clang-format on */

        return return_code == 0 ? SCIC_SUCCESS : SCIC_FAILURE;

#else
        memmove(offset + vector->element_size, offset, elements_in_bytes);
        return SCIC_SUCCESS;
#endif
}


void
_vector_move_left(vector_t *vector, size_t index)
{
        size_t right_elements_in_bytes;
        void *offset;

        /* The offset into the memory */
        offset = _vector_offset(vector, index);

        /* How many to move to the left */
        right_elements_in_bytes = (vector->size - index - 1) * vector->element_size;

        memmove(offset, offset + vector->element_size, right_elements_in_bytes);
}


int
_vector_adjust_capacity(vector_t *vector)
{
        return
                _vector_reallocate(vector, MAX(1, vector->size * VECTOR_GROWTH_FACTOR));
}


int
_vector_reallocate(vector_t *vector, size_t new_capacity)
{
        void *old;
        size_t new_capacity_in_bytes;

        VECTOR_NULL_POINTER(vector);

        if (new_capacity < VECTOR_MINIMUM_CAPACITY)
        {
                if (vector->capacity <= VECTOR_MINIMUM_CAPACITY)
                {
                        return SCIC_SUCCESS;
                }

                new_capacity = VECTOR_MINIMUM_CAPACITY;
        }

        new_capacity_in_bytes = new_capacity * vector->element_size;
        old = vector->data;

        vector->data = malloc(new_capacity_in_bytes);
        VECTOR_MALLOC(vector->data);

#ifdef __STDC_LIB_EXT1__
        /* clang-format off */
        if (memcpy_s(vector->data,
                     new_capacity_in_bytes,
                     old,
                     vector_byte_size(vector)) != 0)
        {
                return SCIC_FAILURE;
        }
/* clang-format on */
#else
        memcpy(vector->data, old, vector_byte_size(vector));
#endif

        vector->capacity = new_capacity;

        free(old);

        return SCIC_SUCCESS;
}


void
_vector_swap(size_t *first, size_t *second)
{
        size_t temp = *first;

        *first = *second;
        *second = temp;
}