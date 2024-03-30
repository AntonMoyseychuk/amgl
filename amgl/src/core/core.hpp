#pragma once

#define AM_DEFAULT_USER_ID 0U
#define AM_DEFAULT_KERNEL_ID UINT32_MAX


#define AM_IS_DEFAULT_ID_USER_SPACE(id)    (id == AM_DEFAULT_USER_ID)
#define AM_IS_DEFAULT_ID_KERNEL_SPACE(id)  (id == AM_DEFAULT_KERNEL_ID)


// Converts id from kernel [0, UINT32_MAX - 1] to user [1, UINT32_MAX] range
#define CONV_KERNEL_TO_USER_SPACE(id) ((uint32_t)id + (uint32_t)1)
// Converts id from user [1, UINT32_MAX] to kernel [0, UINT32_MAX - 1] range
#define CONV_USER_TO_KERNEL_SPACE(id) ((uint32_t)id - (uint32_t)1)


#ifdef _MSC_VER
    #define AM_FORCEINLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    #define AM_FORCEINLINE inline __attribute__((always_inline))
#else
    #define AM_FORCEINLINE inline
#endif


#if defined(_MSC_VER) && !defined(__clang__)
    #define AM_PACKED_STRUCT_BEGIN __pragma(pack(push,  1))
    #define AM_PACKED_STRUCT_END ; __pragma(pack(pop))
#elif defined(__GNUC__) || defined(__clang__)
    #define AM_PACKED_STRUCT_BEGIN
    #define AM_PACKED_STRUCT_END __attribute__((packed));
#else
    #error "Unknown compiler, cannot define PACKED_STRUCT"
#endif


#if AM_BUILD_DEBUG || AM_BUILD_RELEASE_WITH_DEBUG_INFO
    #include "debugbreak/debugbreak.h"
    #include <cstdio>
    
    #define AM_ASSERT_MSG(expr, format, ...)                 \
        {                                                    \
            if(!(expr)) {                                    \
                printf_s(format, __VA_ARGS__);               \
                printf_s("\n" __FILE__ " (%d)\n", __LINE__); \
                debug_break();                               \
            }                                                \
        }
    #define AM_ASSERT(expr) AM_ASSERT_MSG(expr, "\033[31m" #expr " failed\033[0m")
#elif AM_BUILD_RELEASE || AM_BUILD_RELEASE_MIN_SIZE
    #define AM_ASSERT_MSG(expr, ...)
    #define AM_ASSERT(expr)
#else
    #error invalid build type
#endif


#define AM_NOT_IMPLEMENTED AM_ASSERT_MSG(false, "Not implemented yet")


#if AM_DISABLE_ERROR_FLAGS
    #define AM_SET_ERROR_FLAG_IF(condition, error, context_manager, ...)
#else
    #define AM_SET_ERROR_FLAG_IF(condition, error, context_manager, ...)    \
        if (condition) {                                                    \
            (context_manager).update_error_flag(error);                     \
            return __VA_ARGS__;                                             \
        }
#endif


#define AM_RETURN_IF(condition, ...)    \
    if (condition) {                    \
        return __VA_ARGS__;             \
    }


#define AM_CONTINUE_IF(condition)       \
    if (condition) {                    \
        continue;                       \
    }

#define AM_STATIC_ASSERT_MSG(condition, msg) static_assert(condition, msg)
#define AM_STATIC_ASSERT(condition) static_assert(condition, "!(" #condition ")")