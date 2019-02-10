#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <scic/vector.h>

#define lambda(ret_t, body) ({            \
        ret_t anon_fn_name body;          \
        anon_fn_name;                     \
})

int
main(int argc, char const *argv[])
{
        vector_reduce_fn_t sum;
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
