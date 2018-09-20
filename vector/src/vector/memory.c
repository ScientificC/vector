#include <stdlib.h>
#include <scic/errno.h>
#include <scic/vector.h>

#include <scic/vector/_private/error.h>

int
vector_resize(vector_t *vector, size_t new_size)
{
        if (new_size <= vector->capacity * VECTOR_SHRINK_THRESHOLD)
        {
                vector->size = new_size;

                if (_vector_reallocate(vector, new_size * VECTOR_GROWTH_FACTOR) == SCIC_ENOMEM)
                {
                        return SCIC_ENOMEM;
                }
        }
        else if (new_size > vector->capacity)
        {
                if (_vector_reallocate(vector, new_size * VECTOR_GROWTH_FACTOR) == SCIC_ENOMEM)
                {
                        return SCIC_ENOMEM;
                }
        }

        vector->size = new_size;

        return SCIC_SUCCESS;
}


int
vector_reserve(vector_t *vector, size_t minimum_capacity)
{
        if (minimum_capacity > vector->capacity)
        {
                if (_vector_reallocate(vector, minimum_capacity) == SCIC_ENOMEM)
                {
                        return SCIC_ENOMEM;
                }
        }

        return SCIC_SUCCESS;
}


int
vector_shrink_to_fit(vector_t *vector)
{
        return _vector_reallocate(vector, vector->size);
}