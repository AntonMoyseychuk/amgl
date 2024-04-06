#pragma once
#include "core/utils/type_traits.hpp"

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

        template <typename type, typename... Args>
        inline constexpr const type min(const type& a, const type& b, Args&&... args) noexcept
        {
            if constexpr (sizeof...(Args)) {
                return min(a < b ? a : b, std::forward<Args>(args)...);
            } else {
                return a < b ? a : b;
            }
        }

        template <typename type, typename... Args>
        inline constexpr const type max(const type& a, const type& b, Args&&... args) noexcept
        {
            if constexpr (sizeof...(Args)) {
                return max(a > b ? a : b, std::forward<Args>(args)...);
            } else {
                return a > b ? a : b;
            }
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
        

        template <typename type, typename... Args>
        constexpr inline auto sum(type&& arg0, Args&&... args) noexcept
        {
            if constexpr (sizeof...(Args)) {
                return arg0 + sum(std::forward<Args>(args)...);
            } else {
                return arg0;
            }
        }
    }
}