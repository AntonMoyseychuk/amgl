#pragma once

#define AM_DEFAULT_USER_ID 0U
#define AM_DEFAULT_INTERNAL_ID UINT32_MAX

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

#else
    #define AM_ASSERT_MSG(expr, ...)
    #define AM_ASSERT(expr)
#endif

#define AM_RETURN_IF(condition, ...)    \
    if (condition) {                    \
        return __VA_ARGS__;             \
    }

#define AM_CONTINUE_IF(condition)       \
    if (condition) {                    \
        continue;                       \
    }

#define AM_SET_ERROR_FLAG_IF(condition, error, context_manager, ...)    \
    if ((condition)) {                                                  \
        (context_manager).update_error_flag(error);                     \
        return __VA_ARGS__;                                             \
    }

#define AM_RETURN_VALUE_IF_FIND_ELEMENT(collection, element, return_value)  \
    for (const auto& elem : collection) {                                   \
        AM_RETURN_IF(elem == element, return_value);                        \
    }

namespace amgl
{
    // Converts id from internal [0, UINT32_MAX - 1] to user [1, UINT32_MAX] range
    inline constexpr uint32_t conv_internal_to_user_range(uint32_t id) noexcept { return id + 1; }
    // Converts id from user [1, UINT32_MAX] to internal [0, UINT32_MAX - 1] range
    inline constexpr uint32_t conv_user_to_inernal_range(uint32_t id) noexcept { return id - 1; }
        
    inline constexpr bool is_default_id_user_range(uint32_t id) noexcept { return id == AM_DEFAULT_USER_ID; }
    inline constexpr bool is_default_id_internal_range(uint32_t id) noexcept { return id == AM_DEFAULT_INTERNAL_ID; }
    

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