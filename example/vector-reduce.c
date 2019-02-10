#include <stdlib.h>
#include <stdio.h>
#include <scic/vector.h>

#define CAST_TO(_type, _x) *((_type *) _x)

#define lambda(ret_t, body) ({            \
        ret_t anon_fn_name body;          \
        anon_fn_name;                     \
})

typedef void (*reduce_fn_t)(void *, const void *, vector_t *, size_t i);

void
vector_reduce(vector_t *vector, void *result, reduce_fn_t f)
{
        iterator_t iterator, last;
        size_t index = 0;

        iterator = vector_begin(vector);
	last = vector_end(vector);

	for (; !iterator_equals(&iterator, &last); iterator_increment(&iterator)) {
		f(result, iterator_get(&iterator), vector, index++);
	};
}

int
main(int argc, char const *argv[])
{
        vector_t v;

        vector_setup(&v, 2, sizeof(double));

        double x = 2, y = 3, result = 0.0;

        vector_push_back(&v, &x);
        vector_push_back(&v, &y);

        vector_reduce(&v, &result, lambda(void, (void *r, const void *x, vector_t *xs, size_t i)
        {
                /* Get real values from memory */                
                double _r = CAST_TO(double, r); 
                double _x = CAST_TO(double, x);

                CAST_TO(double, r) = _r + _x;
        }));

        printf("Sum: %g\n", result);

        return 0;
}
