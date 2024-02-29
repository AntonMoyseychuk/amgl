#pragma once
#include "core/math/common.hpp"
#include "core/utils/util_func.hpp"
#include "core/core.hpp"

#include <type_traits>

namespace amgl
{
    namespace detail
    {
        /// @brief
        /// @param value Floating point value in [0, 1] range
        template <typename type, typename = std::enable_if_t<std::is_integral_v<type>>>
        type float_to_integer(type min, type max, float value) noexcept
        {
            AM_ASSERT(min < max);
            AM_ASSERT(value >= 0.0f && value <= 1.0f);

            return math::lerp(min, max, value);
        }

        /// @brief Converts 'value' to [min(type), max(type)] range
        /// @param value Floating point value in [0, 1] range
        template <typename type, typename = std::enable_if_t<std::is_integral_v<type>>>
        type float_to_integer(float value) noexcept
        {
            return float_to_integer(std::numeric_limits<type>::lowest(), std::numeric_limits<type>::max(), value);
        }


        /// @brief
        /// @return Value in [0, 1] range 
        template <typename type, typename = std::enable_if_t<std::is_integral_v<type>>>
        float integer_to_float(type min, type max, type value) noexcept
        {
            AM_ASSERT(min < max);

            return math::inverse_lerp(min, max, value);
        }

        /// @brief
        /// @return Value in [0, 1] range 
        template <typename type, typename = std::enable_if_t<std::is_integral_v<type>>>
        float integer_to_float(type value) noexcept
        {
            return math::inverse_lerp(std::numeric_limits<type>::lowest(), std::numeric_limits<type>::max(), value);
        }


        // template <typename dst_type, typename src_type>
        // inline dst_type convert_integral(dst_type dst_min, dst_type dst_max, src_type src) noexcept
        // {
        //     using namespace math;

        //     const float t = inverse_lerp<src_type, float>(min_value<src_type>(), max_value<src_type>(), src);
        //     return lerp<dst_type>(dst_min, dst_max, t);
        // }

        // template <typename dst_type, typename src_type>
        // inline dst_type convert_float(dst_type dst_min, dst_type dst_max, src_type src) noexcept
        // {
        //     const float t = math::clamp<src_type>(0.0, 1.0, src);
        //     return math::lerp<dst_type>(dst_min, dst_max, t);
        // }

        // template <typename dst_type, typename src_type>
        // inline dst_type convert_arithmetic(dst_type dst_min, dst_type dst_max, src_type src) noexcept
        // {
        //     if (std::is_same_v<dst_type, src_type>) {
        //         return math::clamp<dst_type>(dst_min, dst_max, src);
        //     }

        //     const bool is_src_floating_type = std::is_floating_point_v<src_type>;
        //     const bool is_dst_floating_type = std::is_floating_point_v<dst_type>;
            
        //     if (is_dst_floating_type && is_src_floating_type || !is_dst_floating_type && !is_src_floating_type) {
        //         return math::clamp<dst_type>(dst_min, dst_max, src);
        //     } else if (is_dst_floating_type && !is_src_floating_type) {
        //         return convert_integral<dst_type, src_type>(dst_min, dst_max, src);
        //     } else if () {
        //         return convert_float<dst_type, src_type>(dst_min, dst_max, src);
        //     }
        // }

        // template <typename dst_type, typename src_type>
        // inline dst_type convert_arithmetic(src_type src) noexcept
        // {
        //     if (std::is_same_v<dst_type, src_type>) {
        //         return src;
        //     }

        //     const bool is_src_floating_type = std::is_floating_point_v<src_type>;
        //     const bool is_dst_floating_type = std::is_floating_point_v<dst_type>;
            
        //     static constexpr auto dst_min = math::min_value<dst_type>();
        //     static constexpr auto dst_max = math::max_value<dst_type>();

        //     if (is_dst_floating_type && is_src_floating_type) {
        //         return math::clamp(dst_min, dst_max, src);
        //     } else if (is_dst_floating_type && !is_src_floating_type) {
        //         return convert_integral<dst_type, src_type>(dst_min, dst_max, src);
        //     } else {
        //         return convert_float<dst_type, src_type>(dst_min, dst_max, src);
        //     }
        // }
    }
}