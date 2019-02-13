#include <stdlib.h>
#include <string.h>
#include <scic/errno.h>
#include <scic/vector.h>
#include <scic/vector/_private/error.h>


vector_t *
vector_filter(vector_t *vector, vector_filter_fn_t f, size_t result_size)
{
        iterator_t iterator, last;
        size_t index = 0;
        vector_t *result;
        void *x;
        
        result = malloc(sizeof(vector_t));

        VECTOR_MALLOC_VAL(result, NULL);

        vector_setup(result, vector->capacity, result_size);

        iterator = vector_begin(vector);
	last = vector_end(vector);

	for (; !iterator_equals(&iterator, &last); iterator_increment(&iterator))
        {
                x = iterator_get(&iterator);
                
                if (f(x, index++, vector))
                {
                        vector_push_back(result, x);
                }
	}

        return result;
}


vector_t *
vector_map(vector_t *vector, vector_map_fn_t f, size_t result_size)
{
        iterator_t iterator, last;
        size_t index = 0;
        vector_t *result;
        void *m;

        m = malloc(result_size);

        VECTOR_MALLOC_VAL(m, NULL);
        
        result = malloc(sizeof(vector_t));

        VECTOR_MALLOC_VAL(result, NULL);

        vector_setup(result, vector->capacity, result_size);

        iterator = vector_begin(vector);
	last = vector_end(vector);

	for (; !iterator_equals(&iterator, &last); iterator_increment(&iterator))
        {
                memset(m, 0, result_size);

                f(m, iterator_get(&iterator), index++, vector);

                vector_push_back(result, m);
	}

        return result;
}


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