#include <stdlib.h>
#include <scic/errno.h>
#include <scic/vector.h>

#define _SCIC_COMMON_H_ 1

#include <scic/vector/_common/bool.h>
#include <scic/vector/_private/error.h>


int
vector_push_back(vector_t *vector, void *elem)
{
    VECTOR_NULL_POINTER(vector);

    if (_vector_should_grow(vector)) 
    {
        int error;
        
        if ((error = _vector_adjust_capacity(vector)) != SCIC_SUCCESS) 
        {
            return error;
        }
    }

    _vector_assign(vector, vector->size, elem);
    ++vector->size;

    return SCIC_SUCCESS;
}

int
vector_push_front(vector_t *vector, void *elem)
{
    return vector_insert(vector, 0, element);
}