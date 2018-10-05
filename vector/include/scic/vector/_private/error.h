#ifndef SCIC_VECTOR_PRIVATE_ERROR_H
#define SCIC_VECTOR_PRIVATE_ERROR_H

#include <scic/errno.h>

/*
 * Error handlers with SCIC error return statement
 *
 */

#define VECTOR_NULL_POINTER(_pointer) do {                                 \
        if ((_pointer) == NULL)                                            \
                SCIC_ERROR(                                                \
                        "failed to allocate space for vector data",        \
                        SCIC_ENOMEM                                        \
                );                                                         \
} while (0)

#define VECTOR_MALLOC(_pointer) do {                                       \
        if ((_pointer) == NULL)                                            \
                SCIC_ERROR(                                                \
                        "failed to allocate space for vector data",        \
                        SCIC_ENOMEM                                        \
                );                                                         \
} while (0)

#define VECTOR_INVALID_INDEX(_vector_pointer, _index) do {                 \
        if ((_index) >= (_vector_pointer)->size)                           \
                SCIC_ERROR(                                                \
                        "failed to access to invalid index",               \
                        SCIC_EINVAL                                        \
                );                                                         \
} while (0)

#define VECTOR_INVALID_VECTOR_SIZE(_vector_pointer) do {                   \
        if (!(_vector_pointer)->size)                                      \
                SCIC_ERROR(                                                \
                        "failed access to empty array",                    \
                        SCIC_EINVAL                                        \
                );                                                         \
} while (0)

/*
 * VAL error handlers
 */

#define VECTOR_NULL_POINTER_VAL(_pointer, _val) do {                       \
        if ((_pointer) == NULL)                                            \
                SCIC_ERROR_VAL(                                            \
                        "failed to allocate space for vector data",        \
                        SCIC_ENOMEM,                                       \
                        _val                                               \
                );                                                         \
} while (0)

#define VECTOR_MALLOC_VAL(_pointer, _val) do {                             \
        if ((_pointer) == NULL)                                            \
                SCIC_ERROR_VAL(                                            \
                        "failed to allocate space for vector data",        \
                        SCIC_ENOMEM,                                       \
                        _val                                               \
                );                                                         \
} while (0)

#define VECTOR_INVALID_INDEX_VAL(_vector_pointer, _index, _val) do {       \
        if ((_index) > (_vector_pointer)->size)                            \
                SCIC_ERROR_VAL(                                            \
                        "failed to access to invalid index",               \
                        SCIC_EINVAL,                                       \
                        _val                                               \
                );                                                         \
} while (0)

#define VECTOR_INVALID_VECTOR_SIZE_VAL(_vector_pointer, _val) do {         \
        if (!(_vector_pointer)->size)                                      \
                SCIC_ERROR_VAL(                                            \
                        "failed access to empty array",                    \
                        SCIC_EINVAL,                                       \
                        _val                                               \
                );                                                         \
} while (0)

#define VECTOR_INVALID_ELEM_SIZE_COMPARISON_VAL(_f, _s, _val) do {         \
        if ((_f)->element_size != (_s)->element_size)                      \
                SCIC_ERROR_VAL(                                            \
                        "the elem size is not valid",                      \
                        SCIC_EINVAL,                                       \
                        _val                                               \
                );                                                         \
} while (0)

/*
 * VOID error handlers
 */

#define VECTOR_NULL_ITERATOR_POINTER_VOID(_pointer) do {                   \
        if ((_pointer) == NULL)                                            \
                SCIC_ERROR_VOID(                                           \
                        "failed to allocate space for iterator",           \
                        SCIC_ENOMEM                                        \
                );                                                         \
} while (0)

#endif
