#include <stdlib.h>
#include <scic/vector.h>

#include <scic/vector/_private/error.h>

int
scic_vector_resize(scic_vector_t *vector, size_t new_size) 
{
	if (new_size <= vector->capacity * SCIC_VECTOR_SHRINK_THRESHOLD) 
    {
		vector->size = new_size;

		if (_scic_vector_reallocate(vector, new_size * SCIC_VECTOR_GROWTH_FACTOR) == SCIC_ENOMEM) 
        {
			return SCIC_ENOMEM;
		}
	} 
    else if (new_size > vector->capacity) 
    {
		if (_scic_vector_reallocate(vector, new_size * SCIC_VECTOR_GROWTH_FACTOR) == SCIC_ENOMEM) 
        {
			return SCIC_ENOMEM;
		}
	}

	vector->size = new_size;

	return SCIC_SUCCESS;
}


int
scic_vector_reserve(scic_vector_t *vector, size_t minimum_capacity) 
{
	if (minimum_capacity > vector->capacity) 
    {
		if (_scic_vector_reallocate(vector, minimum_capacity) == SCIC_ENOMEM) 
        {
			return SCIC_ENOMEM;
		}
	}

	return SCIC_SUCCESS;
}


int
scic_vector_shrink_to_fit(scic_vector_t *vector) 
{
	return _scic_vector_reallocate(vector, vector->size);
}