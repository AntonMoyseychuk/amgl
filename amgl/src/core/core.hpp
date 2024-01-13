#pragma once

#if defined(_DEBUG) || defined(DEBUG) || !defined(NDEBUG)
    #include <cstdio>
    #include "debugbreak/debugbreak.h"
    
    #define AM_ASSERT_MSG(expr, ...)                        \
        {                                                   \
            if(!(expr)) {                                   \
                printf_s(__FILE__ " (%d): ", __LINE__);     \
                printf_s(__VA_ARGS__);                      \
                debug_break();                              \
            }                                               \
        }
    #define AM_ASSERT(expr) AM_ASSERT_MSG(expr, #expr " failed")

#else
    #define AM_ASSERT_MSG(expr, ...)
    #define AM_ASSERT(expr)
#endif