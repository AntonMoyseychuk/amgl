#pragma once

#if defined(_DEBUG) || defined(DEBUG) || !defined(NDEBUG)
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

    #define RETURN_IF(condition, ...)   \
        if (condition) {                \
            return __VA_ARGS__;         \
        }

#else
    #define AM_ASSERT_MSG(expr, ...)
    #define AM_ASSERT(expr)
#endif