#include <stdio.h>
#include <scic/vector.h>
#include <float.h>

static size_t size = 1000000;

int
main(int argc, const char *argv[])
{
        vector_t vector;
        int x, y, sum;
        float w;

        /* Choose initial capacity of 10 */
        /* Specify the size of the elements you want to store once */
        vector_setup(&vector, size, sizeof(float));

        for (size_t i = 0; i < size; i++) {
                w = (float) i;
                vector_push_back(&vector, &w);
        }

        printf("Length: %d - %.2f\n", vector.size, VECTOR_GET_AS(float, &vector, vector.size - 1));

        vector_resize(&vector, size/2);

        printf("Length: %d - %.2f\n", vector.size, VECTOR_GET_AS(float, &vector, vector.size - 1));

        vector_resize(&vector, size*4);

        vector_clear(&vector);

        for (size_t i = 0; i < 4*size; i++) {
                w = (float) i;
                vector_push_back(&vector, &w);
        }

        printf("Length: %d - %.2f\n", vector.size, VECTOR_GET_AS(float, &vector, vector.size - 1));

        vector_clear(&vector);
        vector_destroy(&vector);
}
