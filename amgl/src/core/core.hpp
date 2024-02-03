#pragma once

#define AM_DEFAULT_USER_ID 0U
#define AM_DEFAULT_KERNEL_ID UINT32_MAX

#define AM_IS_DEFAULT_ID_USER_SPACE(id)    (id == AM_DEFAULT_USER_ID)
#define AM_IS_DEFAULT_ID_KERNEL_SPACE(id)  (id == AM_DEFAULT_KERNEL_ID)

// Converts id from kernel [0, UINT32_MAX - 1] to user [1, UINT32_MAX] range
#define CONV_KERNEL_TO_USER_RANGE(id) ((uint32_t)id + (uint32_t)1)
// Converts id from user [1, UINT32_MAX] to kernel [0, UINT32_MAX - 1] range
#define CONV_USER_TO_KERNEL_RANGE(id) ((uint32_t)id - (uint32_t)1)

#if AM_BUILD_DEBUG || AM_BUILD_RELEASE_WITH_DEBUG_INFO
    #include "debugbreak/debugbreak.h"
    #include <cstdio>
    
    #define AM_ASSERT_MSG(expr, ...)                         \
        {                                                    \
            if(!(expr)) {                                    \
                printf_s(__VA_ARGS__);                       \
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