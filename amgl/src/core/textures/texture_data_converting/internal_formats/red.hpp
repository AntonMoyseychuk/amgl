#pragma once
#include "core/math/common.hpp"

namespace amgl
{
    namespace detail
    {
        template <typename type, typename = std::enable_if_t<std::is_integral_v<type>>>
        static inline void integer_type_to_red(void *dst, const void *src) noexcept
        {
            ((fmt_red*)dst)->r = math::clamp<type>((type)0, (type)255, *(const type*)src);
        } 

        template <typename type, typename = std::enable_if_t<std::is_same_v<type, float> || std::is_same_v<type, double>>>
        static inline void floating_type_to_red(void *dst, const void *src) noexcept
        {
            const type value = math::clamp((type)0, (type)1, *(const type*)src);
            ((fmt_red*)dst)->r = math::lerp<type>((type)0, (type)255, value);
        }

        static inline void red_type_to_red(void *dst, enum_t type, const void *src) noexcept
        {
            switch(type) {
                case AMGL_BYTE:                        integer_type_to_red<int8_t>(dst, src);                  break;
                case AMGL_UNSIGNED_BYTE:               integer_type_to_red<uint8_t>(dst, src);                 break;
                case AMGL_SHORT:                       integer_type_to_red<int16_t>(dst, src);                 break;
                case AMGL_UNSIGNED_SHORT:              integer_type_to_red<uint16_t>(dst, src);                break;
                case AMGL_INT:                         integer_type_to_red<int32_t>(dst, src);                 break;
                case AMGL_UNSIGNED_INT:                integer_type_to_red<uint32_t>(dst, src);                break;
                case AMGL_FLOAT:                       floating_type_to_red<float>(dst, src);                  break;
                case AMGL_DOUBLE:                      floating_type_to_red<double>(dst, src);                 break;
            }
        }

        static inline void format_type_to_red(void *dst, enum_t format, enum_t type, const void *src) noexcept
        {
            switch (format) {
                case AMGL_RED:                  red_type_to_red(dst, type, src);
                // case AMGL_RG:
                // case AMGL_RGB:
                // case AMGL_RGBA:
                // case AMGL_RED_INTEGER:
                // case AMGL_RG_INTEGER:
                // case AMGL_RGB_INTEGER:
                // case AMGL_RGBA_INTEGER:
                // case AMGL_BGR:
                // case AMGL_BGRA:
                // case AMGL_BGR_INTEGER:
                // case AMGL_BGRA_INTEGER:
            }
        }
    } 
}