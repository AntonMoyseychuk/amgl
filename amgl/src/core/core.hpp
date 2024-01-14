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

namespace amgl
{
    namespace detail
    {
        template<typename T0, typename T1, typename... Args>
        inline constexpr bool is_one_of(const T0& value0, const T1& value1, Args&&... list) noexcept
        {
            return value0 == value1 && is_one_of(value0, std::forward<Args>(list)...);
        }

        template<typename T>
        inline constexpr bool is_one_of(const T& value) noexcept
        {
            return true;
        }
    }
}