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


        template<typename type, typename return_type = double, typename = std::enable_if_t<std::is_floating_point_v<return_type>>>
        inline constexpr return_type inverse_lerp(const type& left, const type& right, const type& value) noexcept
        {   
            return static_cast<return_type>(value - left) / (right - left);
        }

        template<typename type>
        inline constexpr type lerp(const type& left, const type& right, float t) noexcept
        {   
            return left + t * (right - left);
        }


        template<typename type>
        inline constexpr type clamp(const type& left, const type& right, const type& value) noexcept
        {   
            return min(right, max(value, left));
        }


        template <typename type>
        inline constexpr type pow(type value, size_t power) noexcept
        {
            type result = static_cast<type>(1);
            for (size_t i = 0; i < power; ++i) {
                result *= value;
            }
            return result;
        }
        

        template <typename type>
        inline constexpr type max_bit_value(size_t bits) noexcept
        {
            if constexpr (std::is_unsigned_v<type>) {
                return pow<type>(2, bits) - 1;
            } else {
                return pow<type>(2, bits - 1) - 1;
            }
        }
        
        template <typename type>
        inline constexpr type min_bit_value(size_t bits) noexcept
        {
            if constexpr (std::is_unsigned_v<type>) {
                return static_cast<type>(0);
            } else {
                return -pow<type>(2, bits - 1);
            }
        }
    }
}