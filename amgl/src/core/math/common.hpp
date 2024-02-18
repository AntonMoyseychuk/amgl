#pragma once
#include <type_traits>

namespace amgl
{
    namespace math
    {
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


        template<typename type>
        constexpr inline double inverse_lerp(const type& left, const type& right, const type& value) noexcept
        {   
            return static_cast<double>(value - left) / (right - left);
        }

        template<typename type>
        constexpr inline type lerp(const type& left, const type& right, float t) noexcept
        {   
            return left + t * (right - left);
        }


        template<typename type>
        constexpr inline type clamp(const type& left, const type& right, const type& value) noexcept
        {   
            return min(value, max(value, left));
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