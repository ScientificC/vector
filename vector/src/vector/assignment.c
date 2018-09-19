#include <stdlib.h>
#include <string.h>
#include <scic/errno.h>
#include <scic/vector.h>
#include <scic/vector/_private/error.h>


int
scic_vector_setup(scic_vector_t *vector, size_t capacity, size_t element_size)
{
        VECTOR_NULL_POINTER_ERROR(vector);

        vector->size = 0;
        vector->capacity = MAX(SCIC_VECTOR_MINIMUM_CAPACITY, capacity);
        vector->element_size = element_size;
        vector->data = malloc(vector->capacity * element_size);

        VECTOR_MALLOC_ERROR(vector->data);

        return SCIC_SUCCESS;
}


int
scic_vector_copy(scic_vector_t *destination, scic_vector_t *source)
{
        VECTOR_NULL_POINTER_ERROR(source);
        VECTOR_NULL_POINTER_ERROR(destination);

        if (scic_vector_is_initialized(destination)) return SCIC_FAILURE;
        if (!scic_vector_is_initialized(source)) return SCIC_FAILURE;

        destination->size = source->size;
        destination->capacity = source->size * 2;
        destination->element_size = source->element_size;

        /* Note that we are not necessarily allocating the same capacity */
        destination->data = malloc(source->capacity * destination->element_size);

        VECTOR_MALLOC_ERROR(destination->data);

        memcpy(destination->data, source->data, scic_vector_byte_size(source));

        return SCIC_SUCCESS;
}


int
scic_vector_copy_assign(scic_vector_t *destination, scic_vector_t *source)
{
        VECTOR_NULL_POINTER_ERROR(source);
        VECTOR_NULL_POINTER_ERROR(destination);

        if (scic_vector_is_initialized(destination)) return SCIC_FAILURE;
        if (!scic_vector_is_initialized(source)) return SCIC_FAILURE;

        scic_vector_destroy(destination);

        return scic_vector_copy(destination, source);
}


int
scic_vector_move(scic_vector_t *destination, scic_vector_t *source)
{
        VECTOR_NULL_POINTER_ERROR(source);
        VECTOR_NULL_POINTER_ERROR(destination);

        *destination = *source;
        source->data = NULL;

        return SCIC_SUCCESS;
}


int
scic_vector_move_assign(scic_vector_t *destination, scic_vector_t *source)
{
        scic_vector_swap(destination, source);

        return scic_vector_destroy(source);
}


int
scic_vector_swap(scic_vector_t *destination, scic_vector_t *source)
{
        void *temp;

        VECTOR_MALLOC_ERROR(source);
        VECTOR_MALLOC_ERROR(destination);

        if (!scic_vector_is_initialized(destination)) return SCIC_FAILURE;
        if (!scic_vector_is_initialized(source)) return SCIC_FAILURE;

        _vector_swap(&destination->size, &source->size);
        _vector_swap(&destination->capacity, &source->capacity);
        _vector_swap(&destination->element_size, &source->element_size);

        temp = destination->data;
        destination->data = source->data;
        source->data = temp;

        return SCIC_SUCCESS;
}


int
scic_vector_destroy(scic_vector_t *vector)
{
        VECTOR_NULL_POINTER_ERROR(vector);

        free(vector->data);

        vector->data = NULL;

        return SCIC_SUCCESS;
}
