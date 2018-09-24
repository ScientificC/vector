#ifndef _SCIC_VECTOR_COMMON_H_
#error "Never use <scic/vector/_common/default.h> directly; include <cml.h> instead."
#endif

#ifndef SCIC_VECTOR_DEFAULT_H
#define SCIC_VECTOR_DEFAULT_H

/* Check C standard */
#ifdef __STDC__
        #define PREDEF_STANDARD_C89
        #ifdef __STDC_VERSION__
                #if __STDC_VERSION__ >= 199901L
                        #define PREDEF_STANDARD_C99
                        #if __STDC_VERSION__ >= 201112L
                                #define PREDEF_STANDARD_C11
                        #endif
                #endif
        #endif
#endif

#define __SCIC_VECTOR_BEGIN_DECLS
#define __SCIC_VECTOR_END_DECLS

#ifdef __cplusplus
        #undef __SCIC_VECTOR_BEGIN_DECLS
        #undef __SCIC_VECTOR_END_DECLS

        #define __SCIC_VECTOR_BEGIN_DECLS extern "C" {
        #define __SCIC_VECTOR_END_DECLS }

        #if __cplusplus >= 199901L
                #define PREDEF_STANDARD_CPP99
                #if __cplusplus >= 201112L
                        #define PREDEF_STANDARD_CPP11
                #endif
        #endif
#endif

#ifndef PREDEF_STANDARD_C11
        #undef __SCIC_VECTOR_NO_GENERIC
        #define __SCIC_VECTOR_NO_GENERIC
#endif

#define __SCIC_VECTOR_ARGS_FIRST(A, ...) A

#ifndef __SCIC_VECTOR_TYPE
        #define __SCIC_VECTOR_TYPE(__e, __t) \
        __builtin_types_compatible_p(__typeof(__e), __t)
#endif

#ifndef __SCIC_VECTOR_SAME_TYPE
        #define __SCIC_VECTOR_SAME_TYPE(__a, __b) \
        __builtin_types_compatible_p(__typeof(__a), __typeof(__b))
#endif

#if defined(SCIC_VECTOR_RANGE_CHECK_OFF) || !defined(SCIC_VECTOR_RANGE_CHECK)
#define SCIC_VECTOR_RANGE_CHECK 0  /* turn off range checking by default internally */
#endif

#define RETURN_IF_NULL(x) if (!x) { return; }

/* Quick boolean definition */
#ifdef SCIC_VECTOR_NO_STDBOOL
        #include <scic/vector/_common/bool.h>
#else
        #include <stdbool.h>
#endif

#ifndef mint_t
        #ifdef SCIC_VECTOR_NO_STDINT
                #define mint_t int
        #else
                #include <stdint.h>
                #define mint_t int32_t
        #endif
#endif

#endif
