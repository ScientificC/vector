#ifndef SCIC_VECTOR_PRIVATE_ERROR_H
#define SCIC_VECTOR_PRIVATE_ERROR_H

#include <scic/errno.h>

#define VECTOR_NULL_POINTER(_pointer)                                      \
        if (_pointer == NULL)                                              \
        {                                                                  \
                SCIC_ERROR(                                                \
                        "failed to allocate space for vector data",        \
                        SCIC_ENOMEM                                        \
                        );                                                 \
        }

#define VECTOR_NULL_POINTER_VAL(_pointer)                                  \
        if (_pointer == NULL)                                              \
        {                                                                  \
                SCIC_ERROR_VAL(                                            \
                        "failed to allocate space for vector data",        \
                        SCIC_ENOMEM,                                       \
                        NULL                                               \
                        );                                                 \
        }

#define VECTOR_MALLOC(_pointer)                                            \
        if (_pointer == NULL)                                              \
        {                                                                  \
                SCIC_ERROR(                                                \
                        "failed to allocate space for vector data",        \
                        SCIC_ENOMEM                                        \
                        );                                                 \
        }

#define VECTOR_INVALID_INDEX_VAL(_vector_pointer, _index)                  \
        if (_index >= _vector_pointer->size)                               \
        {                                                                  \
                SCIC_ERROR_VAL(                                            \
                        "failed to access to invalid index",               \
                        SCIC_EINVAL,                                       \
                        NULL                                               \
                        );                                                 \
        }

#define VECTOR_INVALID_ELEM_SIZE_VAL(_vector_pointer)                      \
        if (_vector_pointer->size == 0)                                    \
        {                                                                  \
                SCIC_ERROR_VAL(                                            \
                        "failed access to empty array",                    \
                        SCIC_EINVAL,                                       \
                        NULL                                               \
                        );                                                 \
        }

#endif
