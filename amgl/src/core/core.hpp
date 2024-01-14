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
        inline constexpr bool is_one_of(const T0& value, const T1& arg0, Args&&... args) noexcept
        {
            return value == arg0 || is_one_of(value, std::forward<Args>(args)...);
        }

        template<typename T0, typename T1>
        inline constexpr bool is_one_of(const T0& value, const T1& arg) noexcept
        {
            return value == arg;
        }

        template<typename T0, typename T1, typename... Args>
        inline constexpr bool are_equal(const T0& value, const T1& arg0, Args&&... args) noexcept
        {
            return value == arg0 && are_equal(value, std::forward<Args>(args)...);
        }

        template<typename T0, typename T1>
        inline constexpr bool are_equal(const T0& value, const T1& arg) noexcept
        {
            return value == arg;
        }
    }
}