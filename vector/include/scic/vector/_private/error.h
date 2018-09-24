#ifndef SCIC_VECTOR_PRIVATE_ERROR_H
#define SCIC_VECTOR_PRIVATE_ERROR_H

#include <scic/errno.h>

/*
 * Error handlers with SCIC error return statement
 * 
 */

#define VECTOR_NULL_POINTER(_pointer)                                      \
        if (_pointer == NULL)                                              \
        {                                                                  \
                SCIC_ERROR(                                                \
                        "failed to allocate space for vector data",        \
                        SCIC_ENOMEM                                        \
                );                                                         \
        }

#define VECTOR_MALLOC(_pointer)                                            \
        if (_pointer == NULL)                                              \
        {                                                                  \
                SCIC_ERROR(                                                \
                        "failed to allocate space for vector data",        \
                        SCIC_ENOMEM                                        \
                );                                                         \
        }

#define VECTOR_INVALID_INDEX(_vector_pointer, _index)                      \
        if (_index >= _vector_pointer->size)                               \
        {                                                                  \
                SCIC_ERROR(                                                \
                        "failed to access to invalid index",               \
                        SCIC_EINVAL                                        \
                );                                                         \
        }

#define VECTOR_INVALID_ELEM_SIZE(_vector_pointer)                          \
        if (_vector_pointer->size == 0)                                    \
        {                                                                  \
                SCIC_ERROR(                                                \
                        "failed access to empty array",                    \
                        SCIC_EINVAL                                        \
                );                                                         \
        }


/*
 * VAL error handlers 
 * 
 */

#define VECTOR_NULL_POINTER_VAL(_pointer, _val)                            \
        if (_pointer == NULL)                                              \
        {                                                                  \
                SCIC_ERROR_VAL(                                            \
                        "failed to allocate space for vector data",        \
                        SCIC_ENOMEM,                                       \
                        _val                                               \
                );                                                         \
        }

#define VECTOR_MALLOC_VAL(_pointer, _val)                                  \
        if (_pointer == NULL)                                              \
        {                                                                  \
                SCIC_ERROR_VAL(                                            \
                        "failed to allocate space for vector data",        \
                        SCIC_ENOMEM,                                       \
                        _val                                               \
                );                                                         \
        }

#define VECTOR_INVALID_INDEX_VAL(_vector_pointer, _index, _val)            \
        if (_index >= _vector_pointer->size)                               \
        {                                                                  \
                SCIC_ERROR_VAL(                                            \
                        "failed to access to invalid index",               \
                        SCIC_EINVAL,                                       \
                        _val                                               \
                );                                                         \
        }

#define VECTOR_INVALID_ELEM_SIZE_VAL(_vector_pointer, _val)                \
        if (_vector_pointer->size == 0)                                    \
        {                                                                  \
                SCIC_ERROR_VAL(                                            \
                        "failed access to empty array",                    \
                        SCIC_EINVAL,                                       \
                        _val                                               \
                );                                                         \
        }

#endif
