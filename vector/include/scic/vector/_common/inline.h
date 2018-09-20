#ifndef _SCIC_COMMON_H_
#error "Never use <scic/vector/_common/inline.h> directly; include <cml.h> instead."
#endif

#ifndef SCIC_INLINE_H
#define SCIC_INLINE_H

#ifdef _MSC_VER
        #define __SCIC_INLINE __forceinline
#else
        #define __SCIC_INLINE inline __attribute((always_inline))
#endif

/* Use `extern inline` for C99 or later */
#ifdef PREDEF_STANDARD_C99
        #define __SCIC_EXTERN_INLINE extern __SCIC_INLINE
#else
        #undef __SCIC_INLINE

        #define __SCIC_INLINE
        #define __SCIC_EXTERN_INLINE
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER) || defined(WIN32)
        #define __SCIC_API __declspec(dllexport)
#endif

#endif
