#include <stdlib.h>
#include <string.h>
#include <scic/errno.h>
#include <scic/vector.h>
#include <scic/vector/_private/error.h>

void *
vector_reduce(vector_t *vector, vector_reduce_fn_t f, void *initial_value, size_t result_size)
{
        iterator_t iterator, last;
        size_t index = 0;
        void *result;

        VECTOR_NULL_POINTER_VAL(initial_value, NULL);
        
        result = malloc(result_size);

        VECTOR_MALLOC_VAL(result, NULL);

        memcpy(result, initial_value, result_size);

        iterator = vector_begin(vector);
	last = vector_end(vector);

	for (; !iterator_equals(&iterator, &last); iterator_increment(&iterator))
        {
		f(result, iterator_get(&iterator), index++, vector);
	}

        return result;
}