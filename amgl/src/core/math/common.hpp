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
    }
}