#ifndef SCIC_VECTOR_H
#define SCIC_VECTOR_H

#include <stdbool.h>
#include <stddef.h>

#define VECTOR_MINIMUM_CAPACITY 2
#define VECTOR_GROWTH_FACTOR 2
#define VECTOR_SHRINK_THRESHOLD (1 / 4)

#define VECTOR_UNINITIALIZED NULL
#define VECTOR_INITIALIZER { 0, 0, 0, VECTOR_UNINITIALIZED }


/*
 * Structures
 */

typedef struct _vector_t {
	size_t size;
	size_t capacity;
	size_t element_size;

	void *data;
} vector_t;

typedef struct _iterator_t {
	void *pointer;
	size_t element_size;
} iterator_t;

/*
 * Behaviour
 */

/* Constructor */
int vector_setup(vector_t *vector, size_t capacity, size_t element_size);

/* Copy Constructor */
int vector_copy(vector_t *destination, vector_t *source);

/* Copy Assignment */
int vector_copy_assign(vector_t *destination, vector_t *source);

/* Move Constructor */
int vector_move(vector_t *destination, vector_t *source);

/* Move Assignment */
int vector_move_assign(vector_t *destination, vector_t *source);

int vector_swap(vector_t *destination, vector_t *source);

/* Destructor */
int vector_destroy(vector_t *vector);

/* Insertion */
int vector_push_back(vector_t *vector, void *element);
int vector_push_front(vector_t *vector, void *element);
int vector_insert(vector_t *vector, size_t index, void *element);
int vector_assign(vector_t *vector, size_t index, void *element);

/* Deletion */
int vector_pop_back(vector_t *vector);
int vector_pop_front(vector_t *vector);
int vector_erase(vector_t *vector, size_t index);
int vector_clear(vector_t *vector);

/* Lookup */
void *vector_get(vector_t *vector, size_t index);
const void *vector_const_get(const vector_t *vector, size_t index);
void *vector_front(vector_t *vector);
void *vector_back(vector_t *vector);
#define VECTOR_GET_AS(type, vector_pointer, index) \
	*((type*)vector_get((vector_pointer), (index)))

/* Information */
bool vector_is_initialized(const vector_t *vector);
size_t vector_byte_size(const vector_t *vector);
size_t vector_free_space(const vector_t *vector);
bool vector_is_empty(const vector_t *vector);

/* Memory management */
int vector_resize(vector_t *vector, size_t new_size);
int vector_reserve(vector_t *vector, size_t minimum_capacity);
int vector_shrink_to_fit(vector_t *vector);

/* Iterators */
iterator_t vector_begin(vector_t *vector);
iterator_t vector_end(vector_t *vector);
iterator_t vector_iterator(vector_t *vector, size_t index);

void *iterator_get(iterator_t *iterator);
#define ITERATOR_GET_AS(type, iterator) *((type*)iterator_get((iterator)))

int iterator_erase(vector_t *vector, iterator_t *iterator);

void iterator_increment(iterator_t *iterator);
void iterator_decrement(iterator_t *iterator);

void *iterator_next(iterator_t *iterator);
void *iterator_previous(iterator_t *iterator);

bool iterator_equals(iterator_t *first, iterator_t *second);
bool iterator_is_before(iterator_t *first, iterator_t *second);
bool iterator_is_after(iterator_t *first, iterator_t *second);

size_t iterator_index(vector_t *vector, iterator_t *iterator);

#define VECTOR_FOR_EACH(vector_pointer, iterator_name)                             \
	for (iterator_t(iterator_name) = vector_begin((vector_pointer)),               \
			end = vector_end((vector_pointer));                                    \
			 !iterator_equals(&(iterator_name), &end);                             \
			 iterator_increment(&(iterator_name)))

/*
 * Private
 */

#define MAX(a, b) ((a) > (b) ? (a) : (b))

bool _vector_should_grow(vector_t *vector);
bool _vector_should_shrink(vector_t *vector);

size_t _vector_free_bytes(const vector_t *vector);
void *_vector_offset(vector_t *vector, size_t index);
const void *_vector_const_offset(const vector_t *vector, size_t index);

void _vector_assign(vector_t *vector, size_t index, void *element);

int _vector_move_right(vector_t *vector, size_t index);
void _vector_move_left(vector_t *vector, size_t index);

int _vector_adjust_capacity(vector_t *vector);
int _vector_reallocate(vector_t *vector, size_t new_capacity);

void _vector_swap(size_t *first, size_t *second);

#endif
