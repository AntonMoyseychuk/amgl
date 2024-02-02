#pragma once

#if defined(_DEBUG) || defined(DEBUG) || !defined(NDEBUG)
    #define AM_BUILD_DEBUG
#else
    #define AM_BUILD_RELEASE
#endif

static_assert(AM_INIT_BUFF_COUNT > 0, "AM_INIT_BUFF_COUNT must be greater than 0");

#define AM_DEFAULT_USER_ID 0U
#define AM_DEFAULT_KERNEL_ID UINT32_MAX

#define AM_IS_DEFAULT_ID_USER_SPACE(id)    (id == AM_DEFAULT_USER_ID)
#define AM_IS_DEFAULT_ID_KERNEL_SPACE(id)  (id == AM_DEFAULT_KERNEL_ID)

// Converts id from kernel [0, UINT32_MAX - 1] to user [1, UINT32_MAX] range
#define CONV_KERNEL_TO_USER_RANGE(id) ((uint32_t)id + (uint32_t)1)
// Converts id from user [1, UINT32_MAX] to kernel [0, UINT32_MAX - 1] range
#define CONV_USER_TO_KERNEL_RANGE(id) ((uint32_t)id - (uint32_t)1)

#ifdef AM_BUILD_DEBUG
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
#else
    #define AM_ASSERT_MSG(expr, ...)
    #define AM_ASSERT(expr)
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