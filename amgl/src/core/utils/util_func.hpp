#pragma once
#include <cstdint>

namespace amgl
{
    namespace detail
    {
        /// @brief Checks if value belongs to [left, right)
        template <typename type>
        inline constexpr bool is_in_range(const type& value, const type& left, const type& right) noexcept
        {
            return value >= left && value < right;
        }


        /// @brief Checks if value is one of args
        template<typename type0, typename type1, typename... Args>
        inline constexpr bool is_one_of(const type0& value, const type1& arg0, Args&&... args) noexcept
        {
            return value == arg0 || is_one_of(value, std::forward<Args>(args)...);
        }

        /// @brief Checks if value is equal to arg
        template<typename type0, typename type1>
        inline constexpr bool is_one_of(const type0& value, const type1& arg) noexcept
        {
            return value == arg;
        }


        /// @brief Checks if all args are equal
        template<typename type0, typename type1, typename... Args>
        inline constexpr bool are_equal(const type0& value, const type1& arg0, Args&&... args) noexcept
        {
            return value == arg0 && are_equal(value, std::forward<Args>(args)...);
        }

        /// @brief Checks if value is equal to arg
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