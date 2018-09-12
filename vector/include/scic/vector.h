#ifndef SCIC_VECTOR_H
#define SCIC_VECTOR_H

#include <stdbool.h>
#include <stddef.h>

#define SCIC_VECTOR_MINIMUM_CAPACITY 2
#define SCIC_VECTOR_GROWTH_FACTOR 2
#define SCIC_VECTOR_SHRINK_THRESHOLD (1 / 4)

#define SCIC_VECTOR_UNINITIALIZED NULL
#define SCIC_VECTOR_INITIALIZER { 0, 0, 0, SCIC_VECTOR_UNINITIALIZED }

/*
 * Structures
 */

typedef struct _scic_vector_t {
	size_t size;
	size_t capacity;
	size_t element_size;

	void *data;
} scic_vector_t;

typedef struct _scic_iterator_t {
	void *pointer;
	size_t element_size;
} scic_iterator_t;

/*
 * Behaviour
 */

/* Constructor */
int scic_vector_setup(scic_vector_t *vector, size_t capacity, size_t element_size);

/* Copy Constructor */
int scic_vector_copy(scic_vector_t *destination, scic_vector_t *source);

/* Copy Assignment */
int scic_vector_copy_assign(scic_vector_t *destination, scic_vector_t *source);

/* Move Constructor */
int scic_vector_move(scic_vector_t *destination, scic_vector_t *source);

/* Move Assignment */
int scic_vector_move_assign(scic_vector_t *destination, scic_vector_t *source);

int scic_vector_swap(scic_vector_t *destination, scic_vector_t *source);

/* Destructor */
int scic_vector_destroy(scic_vector_t *vector);

/* Insertion */
int scic_vector_push_back(scic_vector_t *vector, void *element);
int scic_vector_push_front(scic_vector_t *vector, void *element);
int scic_vector_insert(scic_vector_t *vector, size_t index, void *element);
int scic_vector_assign(scic_vector_t *vector, size_t index, void *element);

/* Deletion */
int scic_vector_pop_back(scic_vector_t *vector);
int scic_vector_pop_front(scic_vector_t *vector);
int scic_vector_erase(scic_vector_t *vector, size_t index);
int scic_vector_clear(scic_vector_t *vector);

/* Lookup */
void *vector_get(scic_vector_t *vector, size_t index);
const void *vector_const_get(const scic_vector_t *vector, size_t index);
void *vector_front(scic_vector_t *vector);
void *vector_back(scic_vector_t *vector);
#define SCIC_VECTOR_GET_AS(type, scic_vector_pointer, index) \
	*((type*)vector_get((vector_pointer), (index)))

/* Information */
bool scic_vector_is_initialized(const scic_vector_t *vector);
size_t scic_vector_byte_size(const scic_vector_t *vector);
size_t scic_vector_free_space(const scic_vector_t *vector);
bool scic_vector_is_empty(const scic_vector_t *vector);

/* Memory management */
int scic_vector_resize(scic_vector_t *vector, size_t new_size);
int scic_vector_reserve(scic_vector_t *vector, size_t minimum_capacity);
int scic_vector_shrink_to_fit(scic_vector_t *vector);

/* Iterators */
scic_iterator_t scic_vector_begin(scic_vector_t *vector);
scic_iterator_t scic_vector_end(scic_vector_t *vector);
scic_iterator_t scic_vector_iterator(scic_vector_t *vector, size_t index);

void *iterator_get(scic_iterator_t *iterator);
#define ITERATOR_GET_AS(type, iterator) *((type*)iterator_get((iterator)))

int iterator_erase(scic_vector_t *vector, scic_iterator_t *iterator);

void iterator_increment(scic_iterator_t *iterator);
void iterator_decrement(scic_iterator_t *iterator);

void *iterator_next(scic_iterator_t *iterator);
void *iterator_previous(scic_iterator_t *iterator);

bool iterator_equals(scic_iterator_t *first, scic_iterator_t *second);
bool iterator_is_before(scic_iterator_t *first, scic_iterator_t *second);
bool iterator_is_after(scic_iterator_t *first, scic_iterator_t *second);

size_t iterator_index(scic_vector_t *vector, scic_iterator_t *iterator);

#define SCIC_VECTOR_FOR_EACH(vector_pointer, iterator_name)                  \
	for (scic_iterator_t(iterator_name) = scic_vector_begin((vector_pointer)),      \
			end = scic_vector_end((vector_pointer));                                    \
			 !iterator_equals(&(iterator_name), &end);                             \
			 iterator_increment(&(iterator_name)))

/*
 * Private
 */

#define MAX(a, b) ((a) > (b) ? (a) : (b))

bool _vector_should_grow(scic_vector_t *vector);
bool _vector_should_shrink(scic_vector_t *vector);

size_t _vector_free_bytes(const scic_vector_t *vector);
void *_vector_offset(scic_vector_t *vector, size_t index);
const void *_vector_const_offset(const scic_vector_t *vector, size_t index);

void _vector_assign(scic_vector_t *vector, size_t index, void *element);

int _vector_move_right(scic_vector_t *vector, size_t index);
void _vector_move_left(scic_vector_t *vector, size_t index);

int _vector_adjust_capacity(scic_vector_t *vector);
int _vector_reallocate(scic_vector_t *vector, size_t new_capacity);

void _vector_swap(size_t *first, size_t *second);

#endif
