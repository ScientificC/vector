#include <stdlib.h>
#include <scic/errno.h>
#include <scic/vector.h>

int
scic_vector_setup(scic_vector_t *vector, size_t capacity, size_t element_size)
{
        if (vector == NULL)
        {
              SCIC_ERROR_VAL(
                "failed to allocate space for vector struct",
                SCIC_ENOMEM,
                0
              );
        }

        vector->size = 0;
      	vector->capacity = MAX(SCIC_VECTOR_MINIMUM_CAPACITY, capacity);
      	vector->element_size = element_size;
      	vector->data = malloc(vector->capacity * element_size);

        if (vector->data == NULL) {
              SCIC_ERROR_VAL(
                "failed to allocate space for vector struct",
                SCIC_ENOMEM,
                0
              );
        }

        return SCIC_SUCCESS;
}
