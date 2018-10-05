#include <stdio.h>
#include <scic/vector.h>
#include <float.h>

static size_t size = 5;

int
main(int argc, const char *argv[])
{
        iterator_t iterator, last;
        vector_t vector;
        int x, y;
        float w, sum;

        /* Choose initial capacity */
        /* Specify the size of the elements you want to store once */
        vector_setup(&vector, size, sizeof(float));

        for (size_t i = 0; i < size; i++) {
                w = (float) i;
                vector_push_back(&vector, &w);
        }

        printf("Length: %d - %.2f\n", vector.size, VECTOR_GET_AS(float, &vector, vector.size - 1));

        /* iterator support */
	iterator = vector_begin(&vector);
	last = vector_end(&vector);

	for (; !iterator_equals(&iterator, &last); iterator_increment(&iterator)) {
		*(float*) iterator_get(&iterator) += 1;
	}

	/* Or just use pretty macros */
	sum = 0;
        
	VECTOR_FOR_EACH(&vector, i, {
		sum += ITERATOR_GET_AS(float, &i);
	});

        printf("Sum: %.2f", sum);

        vector_clear(&vector);
        vector_destroy(&vector);
}
