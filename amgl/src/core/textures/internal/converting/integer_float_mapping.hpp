#pragma once
#include "core/math/common.hpp"
#include "core/core.hpp"

#include "core/utils/type_traits.hpp"

namespace amgl
{
    namespace detail
    {
        /// @brief
        /// @param value Floating point value in [0, 1] range
        template <typename type, typename = std::enable_if_t<std::is_integral_v<type>>>
        inline constexpr type float_to_integer(type min, type max, float value) noexcept
        {
            AM_ASSERT(min < max);
            AM_ASSERT(value >= 0.0f && value <= 1.0f);

            return math::lerp(min, max, value);
        }

        /// @brief Converts 'value' to [min(type), max(type)] range
        /// @param value Floating point value in [0, 1] range
        template <typename type, typename = std::enable_if_t<std::is_integral_v<type>>>
        inline constexpr type float_to_integer(float value) noexcept
        {
            return float_to_integer(std::numeric_limits<type>::lowest(), std::numeric_limits<type>::max(), value);
        }


        /// @brief
        /// @return Value in [0, 1] range 
        template <typename type, typename = std::enable_if_t<std::is_integral_v<type>>>
        inline constexpr float integer_to_float(type min, type max, type value) noexcept
        {
            AM_ASSERT(min < max);

            return math::inverse_lerp(min, max, value);
        }

        /// @brief
        /// @return Value in [0, 1] range 
        template <typename type, typename = std::enable_if_t<std::is_integral_v<type>>>
        inline constexpr float integer_to_float(type value) noexcept
        {
            return math::inverse_lerp(std::numeric_limits<type>::lowest(), std::numeric_limits<type>::max(), value);
        }

        
        template <typename type_in, typename type_out = type_in>
        inline constexpr type_out map(const type_out& out_min, const type_out& out_max, 
            const type_in& in_min, const type_in& in_max, const type_in& value) noexcept
        {
            return math::lerp(out_min, out_max, math::inverse_lerp(in_min, in_max, value));
        }


        // template <typename type>
        // inline constexpr type max_bit_value(size_t bits) noexcept
        // {
        //     if constexpr (std::is_unsigned_v<type>) {
        //         return pow<type>(2, bits) - 1;
        //     } else {
        //         return pow<type>(2, bits - 1) - 1;
        //     }
        // }
        //
        // template <typename type>
        // inline constexpr type min_bit_value(size_t bits) noexcept
        // {
        //     if constexpr (std::is_unsigned_v<type>) {
        //         return static_cast<type>(0);
        //     } else {
        //         return -pow<type>(2, bits - 1);
        //     }
        // }
    }
}