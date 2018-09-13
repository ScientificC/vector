#ifndef SCIC_VECTOR_PRIVATE_ERROR_H
#define SCIC_VECTOR_PRIVATE_ERROR_H

#define VECTOR_NULL_POINTER_ERROR(_pointer)                                \
        if (_pointer == NULL)                                              \
        {                                                                  \
                SCIC_ERROR(                                                \
                        "failed to allocate space for vector data",        \
                        SCIC_ENOMEM                                        \
                        );                                                 \
        }


#define VECTOR_MALLOC_ERROR(_pointer)                                      \
        if (_pointer == NULL)                                              \
        {                                                                  \
                SCIC_ERROR(                                                \
                        "failed to allocate space for vector data",        \
                        SCIC_ENOMEM                                        \
                        );                                                 \
        }

#endif
