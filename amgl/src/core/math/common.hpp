#pragma once
#include <type_traits>

namespace amgl
{
    namespace math
    {
        #define MATH_TYPE_MIN(type)                  std::numeric_limits<type>::lowest()
        #define MATH_TYPE_MAX(type)                  std::numeric_limits<type>::max()

        #define MATH_MAX_SIGNED_BIT_VALUE(bits)      (amgl::math::pow(2, bits - 1) - 1)
        #define MATH_MIN_SIGNED_BIT_VALUE(bits)      -amgl::math::pow(2, bits - 1)

        #define MATH_MAX_UNSIGNED_BIT_VALUE(bits)    (amgl::math::pow(2, bits) - 1)
        #define MATH_MIN_UNSIGNED_BIT_VALUE(bits)    0u


        #if defined(min) || defined(MIN)
            #undef min
            #undef MIN
        #endif

        #if defined(max) || defined(MAX)
            #undef max
            #undef MAX
        #endif

        template <typename type>
        inline constexpr const type& min(const type& a, const type& b) noexcept
        {
            return a < b ? a : b;
        }

        template <typename type>
        inline constexpr const type& max(const type& a, const type& b) noexcept
        {
            return a > b ? a : b;
        }


        template<typename type, typename return_type = double, typename = std::enable_if_t<std::is_floating_point_v<return_type>>>
        constexpr inline return_type inverse_lerp(const type& left, const type& right, const type& value) noexcept
        {   
            return static_cast<return_type>(value - left) / (right - left);
        }

        template<typename type>
        constexpr inline type lerp(const type& left, const type& right, float t) noexcept
        {   
            return left + t * (right - left);
        }


        template<typename type>
        constexpr inline type clamp(const type& left, const type& right, const type& value) noexcept
        {   
            return min(right, max(value, left));
        }


        template <typename type, typename = std::enable_if_t<std::is_arithmetic_v<type>>>
        inline constexpr type pow(type value, size_t power) noexcept
        {
            type result = static_cast<type>(1);
            for (size_t i = 0; i < power; ++i) {
                result *= value;
            }
            return result;
        }


        /// @brief Checks if 'value' belongs to [left, right)
        template <typename type>
        inline constexpr bool is_in_range(const type& value, const type& left, const type& right) noexcept
        {
            return value >= left && value < right;
        }


        /// @brief Checks if value is equal to arg
        template<typename type0, typename type1>
        inline constexpr bool is_one_of(const type0& value, const type1& arg) noexcept
        {
            return value == arg;
        }

        /// @brief Checks if value is one of args
        template<typename type0, typename type1, typename... Args>
        inline constexpr bool is_one_of(const type0& value, const type1& arg0, Args&&... args) noexcept
        {
            return value == arg0 || is_one_of(value, std::forward<Args>(args)...);
        }


        /// @brief Checks if value is equal to arg
        template<typename type0, typename type1>
        inline constexpr bool are_equal(const type0& value, const type1& arg) noexcept
        {
            return value == arg;
        }

        /// @brief Checks if all args are equal
        template<typename type0, typename type1, typename... Args>
        inline constexpr bool are_equal(const type0& value, const type1& arg0, Args&&... args) noexcept
        {
            return value == arg0 && are_equal(value, std::forward<Args>(args)...);
        }
    }
}