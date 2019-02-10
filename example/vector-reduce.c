#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <scic/vector.h>
#include <scic/vector/_private/error.h>

#define CAST_TO(_type, _x) *((_type *) _x)

#define lambda(ret_t, body) ({            \
        ret_t anon_fn_name body;          \
        anon_fn_name;                     \
})

typedef void (*reduce_fn_t)(void *, const void *, size_t, vector_t *);

void *
vector_reduce(vector_t *vector, reduce_fn_t f, void *initial_value)
{
        iterator_t iterator, last;
        size_t index = 0;
        void *result;

        VECTOR_NULL_POINTER_VAL(initial_value, NULL);
        
        result = malloc(vector->element_size);

        VECTOR_MALLOC_VAL(result, NULL);

        memcpy(result, initial_value, vector->element_size);

        iterator = vector_begin(vector);
	last = vector_end(vector);

	for (; !iterator_equals(&iterator, &last); iterator_increment(&iterator))
        {
		f(result, iterator_get(&iterator), index++, vector);
	}

        return result;
}

int
main(int argc, char const *argv[])
{
        reduce_fn_t sum;
        vector_t v;

        double x = 2, y = 3, initial = 0.0;
        void *result;

        vector_setup(&v, 2, sizeof(double));

        vector_push_back(&v, &x);
        vector_push_back(&v, &y);

        sum = lambda(void, (void *r, const void *x, size_t i, vector_t *xs)
        {
                /* Get real values from memory */               
                double _r = CAST_TO(double, r);
                double _x = CAST_TO(double, x);

                CAST_TO(double, r) = _r + _x;
        });

        result = vector_reduce(&v, sum, &initial);

        printf("Sum: %g\n", CAST_TO(double, result));

        return 0;
}
