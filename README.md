# vector

[![Build Status](https://travis-ci.org/ScientificC/vector.svg?branch=master)](https://travis-ci.org/ScientificC/vector) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

A pure C vector implementation with CMake build support

## Table of Contents

- [vector](#vector)
  - [Table of Contents](#table-of-contents)
  - [Using the Library](#using-the-library)
  - [Examples](#examples)
    - [Setup](#setup)
    - [Iterator](#iterator)
    - [Vector reduce](#vector-reduce)

## Using the Library

NOTE: This will install in /usr/local. You probably don't want that. But this is a quick start. The best thing to do is to combine this library with your other code into a larger CMake project/solution.

Install with [clib](https://github.com/clibs/clib):

```shell
$ clib install ScientificC/vector
```

or,

```shell
$ git clone https://github.com/ScientificC/vector.git
$ cd cml
$ mkdir build
$ cd build
$ cmake .. <build options>
$ make && make install
```

## Examples

### Setup

```c
#include <stdio.h>
#include <scic/vector.h>

int
main(int argc, const char *argv[])
{
        vector_t vector;
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
}
```

### Iterator

```c
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
```

### Vector reduce

```c
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

        double x = 2.0, y = 3.0, initial = 0.0;
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

        result = vector_reduce(&v, sum, &initial, sizeof(double));

        printf("Sum: %g\n", CAST_TO(double, result));

        return 0;
}
```
