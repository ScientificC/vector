#include <stdlib.h>
#include <string.h>
#include <scic/errno.h>
#include <scic/vector.h>
#include <scic/vector/_private/error.h>

int
vector_setup(vector_t *vector, size_t capacity, size_t element_size)
{
        VECTOR_NULL_POINTER(vector);

        vector->size = 0;
        vector->capacity = MAX(VECTOR_MINIMUM_CAPACITY, capacity);
        vector->element_size = element_size;
        vector->data = malloc(vector->capacity * element_size);

        VECTOR_MALLOC(vector->data);

        return SCIC_SUCCESS;
}

int
vector_copy(vector_t *destination, vector_t *source)
{
        VECTOR_NULL_POINTER(source);
        VECTOR_NULL_POINTER(destination);

        if (vector_is_initialized(destination)) return SCIC_FAILURE;
        if (!vector_is_initialized(source)) return SCIC_FAILURE;

        destination->size = source->size;
        destination->capacity = source->size * 2;
        destination->element_size = source->element_size;

        /* Note that we are not necessarily allocating the same capacity */
        destination->data = malloc(source->capacity * destination->element_size);

        VECTOR_MALLOC(destination->data);

        memcpy(destination->data, source->data, vector_byte_size(source));

        return SCIC_SUCCESS;
}

int
vector_copy_assign(vector_t *destination, vector_t *source)
{
        VECTOR_NULL_POINTER(source);
        VECTOR_NULL_POINTER(destination);

        if (vector_is_initialized(destination)) return SCIC_FAILURE;
        if (!vector_is_initialized(source)) return SCIC_FAILURE;

        vector_destroy(destination);

        return vector_copy(destination, source);
}

int
vector_move(vector_t *destination, vector_t *source)
{
        VECTOR_NULL_POINTER(source);
        VECTOR_NULL_POINTER(destination);

        *destination = *source;
        source->data = NULL;

        return SCIC_SUCCESS;
}

int
vector_move_assign(vector_t *destination, vector_t *source)
{
        vector_swap(destination, source);

        return vector_destroy(source);
}

int
vector_swap(vector_t *destination, vector_t *source)
{
        void *temp;

        VECTOR_MALLOC(source);
        VECTOR_MALLOC(destination);

        if (!vector_is_initialized(destination)) return SCIC_FAILURE;
        if (!vector_is_initialized(source)) return SCIC_FAILURE;

        _vector_swap(&destination->size, &source->size);
        _vector_swap(&destination->capacity, &source->capacity);
        _vector_swap(&destination->element_size, &source->element_size);

        temp = destination->data;
        destination->data = source->data;
        source->data = temp;

        return SCIC_SUCCESS;
}

int
vector_destroy(vector_t *vector)
{
        VECTOR_NULL_POINTER(vector);

        free(vector->data);

        vector->data = NULL;

        return SCIC_SUCCESS;
}
