#pragma once

#if defined(_DEBUG) || defined(DEBUG) || !defined(NDEBUG)
    #define AM_DEBUG
#else
    #define AM_RELEASE
#endif

#define AM_DEFAULT_USER_ID 0U
#define AM_DEFAULT_KERNEL_ID UINT32_MAX

#define AM_IS_DEFAULT_ID_USER_SPACE(id)    (id == AM_DEFAULT_USER_ID)
#define AM_IS_DEFAULT_ID_KERNEL_SPACE(id)  (id == AM_DEFAULT_KERNEL_ID)

// Converts id from kernel [0, UINT32_MAX - 1] to user [1, UINT32_MAX] range
#define CONV_KERNEL_TO_USER_RANGE(id) ((uint32_t)id + (uint32_t)1)
// Converts id from user [1, UINT32_MAX] to kernel [0, UINT32_MAX - 1] range
#define CONV_USER_TO_KERNEL_RANGE(id) ((uint32_t)id - (uint32_t)1)

#ifdef AM_DEBUG
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


#define AM_SET_ERROR_FLAG_IF(condition, error, context_manager, ...)    \
    if (condition) {                                                    \
        (context_manager).update_error_flag(error);                     \
        return __VA_ARGS__;                                             \
    }


#define AM_RETURN_IF(condition, ...)    \
    if (condition) {                    \
        return __VA_ARGS__;             \
    }


#define AM_CONTINUE_IF(condition)       \
    if (condition) {                    \
        continue;                       \
    }


namespace amgl
{
    namespace detail
    {
        // Checks if value belongs to [left, right)
        template <typename type>
        inline constexpr bool is_in_range(const type& value, const type& left, const type& right) noexcept
        {
            return value >= left && value < right;
        }


        template<typename type0, typename type1, typename... Args>
        inline constexpr bool is_one_of(const type0& value, const type1& arg0, Args&&... args) noexcept
        {
            return value == arg0 || is_one_of(value, std::forward<Args>(args)...);
        }

        template<typename type0, typename type1>
        inline constexpr bool is_one_of(const type0& value, const type1& arg) noexcept
        {
            return value == arg;
        }


        template<typename type0, typename type1, typename... Args>
        inline constexpr bool are_equal(const type0& value, const type1& arg0, Args&&... args) noexcept
        {
            return value == arg0 && are_equal(value, std::forward<Args>(args)...);
        }

        template<typename type0, typename type1>
        inline constexpr bool are_equal(const type0& value, const type1& arg) noexcept
        {
            return value == arg;
        }
        

        inline constexpr bool are_memory_regions_overlap(const void* region0, size_t size0, const void* region1, size_t size1) noexcept
        {
            return is_in_range(uintptr_t(region0), uintptr_t(region1), uintptr_t(region1) + size1) ||
                is_in_range(uintptr_t(region1), uintptr_t(region0), uintptr_t(region0) + size0);
        }
    }
}