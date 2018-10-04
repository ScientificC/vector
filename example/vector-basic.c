#include <stdio.h>
#include <scic/vector.h>

int
main(int argc, const char *argv[])
{
        vector_t
} vector;
        int x, y, sum;

        /* Choose initial capacity */
        /* Specify the size of the elements you want to store once */
        vector_setup(&vector, 10, sizeof(int));

        x = 6, y = 9;
        vector_push_back(&vector, &x);
        vector_insert(&vector, 0, &y);
        vector_assign(&vector, 0, &y);

        x = *(int *)vector_get(&vector, 0);
        y = *(int *)vector_back(&vector);
        x = VECTOR_GET_AS(int, &vector, 1);

        for (size_t i = 0; i < vector.size; i++)
                printf("Number %d at position %d\n", VECTOR_GET_AS(int, &vector, i), i);

        /* Memory management interface */
        vector_resize(&vector, 10);
        vector_reserve(&vector, 100);

        vector_clear(&vector);
        vector_destroy(&vector);
