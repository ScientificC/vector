#include <stdlib.h>
#include <scic/errno.h>
#include <scic/vector.h>

#include <scic/vector/_private/error.h>

int
vector_resize(vector_t *vector, size_t new_size)
{
        int errno;

        if (new_size <= vector->capacity * VECTOR_SHRINK_THRESHOLD) {
                vector->size = new_size;

                errno = _vector_reallocate(vector,
                                           new_size * VECTOR_GROWTH_FACTOR);

                if (errno != SCIC_SUCCESS)
                        return errno;

        } else if (new_size > vector->capacity) {
                errno = _vector_reallocate(vector,
                                           new_size * VECTOR_GROWTH_FACTOR);

                if (errno != SCIC_SUCCESS)
                        return errno;
        }

        vector->size = new_size;

        return SCIC_SUCCESS;
}

int
vector_reserve(vector_t *vector, size_t minimum_capacity)
{
        if (minimum_capacity > vector->capacity) {
                int errno = _vector_reallocate(vector, minimum_capacity);

                if (errno != SCIC_SUCCESS)
                        return errno;
        }

        return SCIC_SUCCESS;
}

int
vector_shrink_to_fit(vector_t *vector)
{
        return _vector_reallocate(vector, vector->size);
}
