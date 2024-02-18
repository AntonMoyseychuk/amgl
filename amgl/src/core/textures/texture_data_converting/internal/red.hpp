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


        template<typename packed_type>
        static inline void packed_type_to_red(void *dst, const void *src) noexcept
        {
            ((fmt_red*)dst)->r = ((packed_type*)src)->r;
        }

        template<>
        inline void packed_type_to_red<type_int_2_10_10_10_rev>(void *dst, const void *src) noexcept
        {
            const int32_t red = ((const type_int_2_10_10_10_rev*)src)->r;

            const float t = math::inverse_lerp<int32_t>(MIN_SIGNED_BIT_VALUE(10), MAX_UNSIGNED_BIT_VALUE(10), red);
            ((fmt_red*)dst)->r = math::lerp<uint8_t>(0, 255, t);
        }

        template<>
        inline void packed_type_to_red<type_uint_10_10_10_2>(void *dst, const void *src) noexcept
        {
            const type_uint_10_10_10_2* _src = (const type_uint_10_10_10_2*)src;

            const float t = math::inverse_lerp<uint32_t>(MIN_UNSIGNED_BIT_VALUE(10), MAX_UNSIGNED_BIT_VALUE(10), _src->r);
            ((fmt_red*)dst)->r = math::lerp<uint8_t>(0, 255, t);
        }

        template<>
        inline void packed_type_to_red<type_uint_2_10_10_10_rev>(void *dst, const void *src) noexcept
        {
            const type_uint_2_10_10_10_rev* _src = (const type_uint_2_10_10_10_rev*)src;

            const float t = math::inverse_lerp<uint32_t>(MIN_UNSIGNED_BIT_VALUE(10), MAX_UNSIGNED_BIT_VALUE(10), _src->r);
            ((fmt_red*)dst)->r = math::lerp<uint8_t>(0, 255, t);
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
                case AMGL_INT_2_10_10_10_REV:          packed_type_to_red<type_int_2_10_10_10_rev>(dst, src);  break;
                case AMGL_UNSIGNED_INT_10_10_10_2:     packed_type_to_red<type_uint_10_10_10_2>(dst, src);     break;
                case AMGL_UNSIGNED_INT_2_10_10_10_REV: packed_type_to_red<type_uint_2_10_10_10_rev>(dst, src); break;
                case AMGL_UNSIGNED_BYTE_3_3_2:         packed_type_to_red<type_ubyte_3_3_2>(dst, src);         break;
                case AMGL_UNSIGNED_BYTE_2_3_3_REV:     packed_type_to_red<type_ubyte_2_3_3_rev>(dst, src);     break;
                case AMGL_UNSIGNED_SHORT_5_6_5:        packed_type_to_red<type_ushort_5_6_5>(dst, src);        break;
                case AMGL_UNSIGNED_SHORT_5_6_5_REV:    packed_type_to_red<type_ushort_5_6_5_rev>(dst, src);    break;
                case AMGL_UNSIGNED_SHORT_4_4_4_4:      packed_type_to_red<type_ushort_4_4_4_4>(dst, src);      break;
                case AMGL_UNSIGNED_SHORT_4_4_4_4_REV:  packed_type_to_red<type_ushort_4_4_4_4_rev>(dst, src);  break;
                case AMGL_UNSIGNED_SHORT_5_5_5_1:      packed_type_to_red<type_ushort_5_5_5_1>(dst, src);      break;
                case AMGL_UNSIGNED_SHORT_1_5_5_5_REV:  packed_type_to_red<type_ushort_1_5_5_5_rev>(dst, src);  break;
                case AMGL_UNSIGNED_INT_8_8_8_8:        packed_type_to_red<type_uint_8_8_8_8>(dst, src);        break;
                case AMGL_UNSIGNED_INT_8_8_8_8_REV:    packed_type_to_red<type_uint_8_8_8_8_rev>(dst, src);    break;
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
                // case AMGL_STENCIL_INDEX:
                // case AMGL_DEPTH_COMPONENT:
                // case AMGL_DEPTH_STENCIL:
            }
        }
    } 
}