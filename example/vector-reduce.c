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
        vector_filter_fn_t is_positive;
        vector_map_fn_t inc;
        vector_reduce_fn_t sum;
        vector_t v, *incs, *positive_nums;

        double x = -2.0, y = 3.0, z = 4.0, initial = 0.0;
        void *result;

        vector_setup(&v, 2, sizeof(double));

        vector_push_back(&v, &x);
        vector_push_back(&v, &y);
        vector_push_back(&v, &z);

        is_positive = lambda(bool, (const void *x, size_t i, vector_t *xs) {
                double _x = CAST_TO(double, x);

                return _x >= 0.0;
        });

        inc = lambda(void, (const void *r, const void *x, size_t i, vector_t *xs) {
                double _r = CAST_TO(double, r);
                double _x = CAST_TO(double, x);

                CAST_TO(double, r) = _x + 1.0;
        });

        sum = lambda(void, (void *r, const void *x, size_t i, vector_t *xs)
        {
                /* Get real values from memory */               
                double _r = CAST_TO(double, r);
                double _x = CAST_TO(double, x);

                CAST_TO(double, r) = _r + _x;
        });

        positive_nums = vector_filter(&v, is_positive, sizeof(double));

        incs = vector_map(positive_nums, inc, sizeof(double));

        result = vector_reduce(incs, sum, &initial, sizeof(double));

        printf("Sum: %g\n", CAST_TO(double, result));

        vector_destroy(&v);
        vector_destroy(positive_nums);
        vector_destroy(incs);

        return 0;
}
