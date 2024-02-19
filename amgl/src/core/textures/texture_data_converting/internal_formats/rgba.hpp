#pragma once
#include "core/math/common.hpp"

namespace amgl
{
    namespace detail
    {
        template <typename type, size_t component_shift0, size_t component_shift1, size_t component_shift2, size_t component_shift3,
            typename = std::enable_if_t<std::is_integral_v<type> && 
            amgl::math::is_in_range(component_shift0, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift1, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift2, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift3, (size_t)0, (size_t)5)>
        >
        inline void integer_type_1_to_rgba(void *dst, const void *src) noexcept
        {
            fmt_rgba* _dst  = (fmt_rgba*)dst;

            _dst->r = math::clamp<type>((type)0, (type)255, *((const type*)src + component_shift0));
            _dst->g = 0;
            _dst->b = 0;
            _dst->a = 1;
        }

        template <typename type, size_t component_shift0, size_t component_shift1, size_t component_shift2, size_t component_shift3,
            typename = std::enable_if_t<std::is_integral_v<type> && 
            amgl::math::is_in_range(component_shift0, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift1, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift2, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift3, (size_t)0, (size_t)5)>
        >
        inline void integer_type_2_to_rgba(void *dst, const void *src) noexcept
        {
            fmt_rgba* _dst   = (fmt_rgba*)dst;
            const type* _src = (type*)src;

            _dst->r = math::clamp<type>((type)0, (type)255, *(_src + component_shift0));
            _dst->g = math::clamp<type>((type)0, (type)255, *(_src + component_shift1));
            _dst->b = 0;
            _dst->a = 1;
        }

        template <typename type, size_t component_shift0, size_t component_shift1, size_t component_shift2, size_t component_shift3,
            typename = std::enable_if_t<std::is_integral_v<type> && 
            amgl::math::is_in_range(component_shift0, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift1, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift2, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift3, (size_t)0, (size_t)5)>
        >
        inline void integer_type_3_to_rgba(void *dst, const void *src) noexcept
        {
            fmt_rgba* _dst   = (fmt_rgba*)dst;
            const type* _src = (type*)src;

            _dst->r = math::clamp<type>((type)0, (type)255, *(_src + component_shift0));
            _dst->g = math::clamp<type>((type)0, (type)255, *(_src + component_shift1));
            _dst->b = math::clamp<type>((type)0, (type)255, *(_src + component_shift2));
            _dst->a = 1;
        } 

        template <typename type, size_t component_shift0, size_t component_shift1, size_t component_shift2, size_t component_shift3,
            typename = std::enable_if_t<std::is_integral_v<type> && 
            amgl::math::is_in_range(component_shift0, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift1, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift2, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift3, (size_t)0, (size_t)5)>
        >
        inline void integer_type_4_to_rgba(void *dst, const void *src) noexcept
        {
            fmt_rgba* _dst   = (fmt_rgba*)dst;
            const type* _src = (type*)src;

            _dst->r = math::clamp<type>((type)0, (type)255, *(_src + component_shift0));
            _dst->g = math::clamp<type>((type)0, (type)255, *(_src + component_shift1));
            _dst->b = math::clamp<type>((type)0, (type)255, *(_src + component_shift2));
            _dst->a = math::clamp<type>((type)0, (type)255, *(_src + component_shift3));
        } 

        template <typename type, size_t component_shift0, size_t component_shift1, size_t component_shift2, size_t component_shift3,
            typename = std::enable_if_t<std::is_floating_point_v<type> && 
            amgl::math::is_in_range(component_shift0, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift1, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift2, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift3, (size_t)0, (size_t)5)>
        >
        inline void floating_type_1_to_rgba(void *dst, const void *src) noexcept
        {
            fmt_rgba* _dst   = (fmt_rgba*)dst;
            const type* _src = (type*)src;

            const type red = math::clamp((type)0, (type)1, *(_src + component_shift0));

            _dst->r = math::lerp<type>((type)0, (type)255, red);
            _dst->g = 0;
            _dst->b = 0;
            _dst->a = 1;
        } 

        template <typename type, size_t component_shift0, size_t component_shift1, size_t component_shift2, size_t component_shift3,
            typename = std::enable_if_t<std::is_floating_point_v<type> && 
            amgl::math::is_in_range(component_shift0, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift1, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift2, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift3, (size_t)0, (size_t)5)>
        >
        inline void floating_type_2_to_rgba(void *dst, const void *src) noexcept
        {
            fmt_rgba* _dst   = (fmt_rgba*)dst;
            const type* _src = (type*)src;

            const type red = math::clamp((type)0, (type)1,  *(_src + component_shift0));
            const type green = math::clamp((type)0, (type)1, *(_src + component_shift1));

            _dst->r = math::lerp<type>((type)0, (type)255, red);
            _dst->g = math::lerp<type>((type)0, (type)255, green);
            _dst->b = 0;
            _dst->a = 1;
        } 

        template <typename type, size_t component_shift0, size_t component_shift1, size_t component_shift2, size_t component_shift3,
            typename = std::enable_if_t<std::is_floating_point_v<type> && 
            amgl::math::is_in_range(component_shift0, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift1, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift2, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift3, (size_t)0, (size_t)5)>
        >
        inline void floating_type_3_to_rgba(void *dst, const void *src) noexcept
        {
            fmt_rgba* _dst   = (fmt_rgba*)dst;
            const type* _src = (type*)src;

            const type red = math::clamp((type)0, (type)1,  *(_src + component_shift0));
            const type green = math::clamp((type)0, (type)1, *(_src + component_shift1));
            const type blue = math::clamp((type)0, (type)1, *(_src + component_shift2));

            _dst->r = math::lerp<type>((type)0, (type)255, red);
            _dst->g = math::lerp<type>((type)0, (type)255, green);
            _dst->b = math::lerp<type>((type)0, (type)255, blue);
            _dst->a = 1;
        } 

        template <typename type, size_t component_shift0, size_t component_shift1, size_t component_shift2, size_t component_shift3,
            typename = std::enable_if_t<std::is_floating_point_v<type> && 
            amgl::math::is_in_range(component_shift0, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift1, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift2, (size_t)0, (size_t)5) &&
            amgl::math::is_in_range(component_shift3, (size_t)0, (size_t)5)>
        >
        inline void floating_type_4_to_rgba(void *dst, const void *src) noexcept
        {
            fmt_rgba* _dst   = (fmt_rgba*)dst;
            const type* _src = (type*)src;

            const type red = math::clamp((type)0, (type)1,  *(_src + component_shift0));
            const type green = math::clamp((type)0, (type)1, *(_src + component_shift1));
            const type blue = math::clamp((type)0, (type)1, *(_src + component_shift2));
            const type alpha = math::clamp((type)0, (type)1, *(_src + component_shift3));

            _dst->r = math::lerp<type>((type)0, (type)255, red);
            _dst->g = math::lerp<type>((type)0, (type)255, green);
            _dst->b = math::lerp<type>((type)0, (type)255, blue);
            _dst->a = math::lerp<type>((type)0, (type)255, alpha);
        } 

        template<typename packed_type>
        inline void packed_type_to_rgba(void *dst, const void *src) noexcept
        {   
            fmt_rgba* _dst          = (fmt_rgba*)dst;
            const packed_type* _src = (packed_type*)src;

            _dst->r = _src->r;
            _dst->g = _src->g;
            _dst->b = _src->b;
            _dst->a = _src->a;
        }

        template<typename packed_type, typename internal_type>
        inline void variety_10_10_10_2_to_rgba(void *dst, const void *src) noexcept
        {   
            fmt_rgba* _dst          = (fmt_rgba*)dst;
            const packed_type* _src = (packed_type*)src;

            const float red = math::inverse_lerp<internal_type, float>(MATH_MIN_SIGNED_BIT_VALUE(10), MATH_MAX_UNSIGNED_BIT_VALUE(10), _src->r);
            const float green = math::inverse_lerp<internal_type, float>(MATH_MIN_SIGNED_BIT_VALUE(10), MATH_MAX_UNSIGNED_BIT_VALUE(10), _src->g);
            const float blue = math::inverse_lerp<internal_type, float>(MATH_MIN_SIGNED_BIT_VALUE(10), MATH_MAX_UNSIGNED_BIT_VALUE(10), _src->b);
            const float alpha = math::inverse_lerp<internal_type, float>(MATH_MIN_SIGNED_BIT_VALUE(2), MATH_MAX_UNSIGNED_BIT_VALUE(2), _src->a);

            _dst->r = math::lerp<uint8_t>(0, 255, red);
            _dst->g = math::lerp<uint8_t>(0, 255, green);
            _dst->b = math::lerp<uint8_t>(0, 255, blue);
            _dst->a = math::lerp<uint8_t>(0, 255, alpha);
        }


        template<>
        inline void packed_type_to_rgba<type_int_2_10_10_10_rev>(void *dst, const void *src) noexcept
        {
            variety_10_10_10_2_to_rgba<type_int_2_10_10_10_rev, int32_t>(dst, src);
        }

        template<>
        inline void packed_type_to_rgba<type_uint_10_10_10_2>(void *dst, const void *src) noexcept
        {
            variety_10_10_10_2_to_rgba<type_uint_10_10_10_2, int32_t>(dst, src);
        }

        template<>
        inline void packed_type_to_rgba<type_uint_2_10_10_10_rev>(void *dst, const void *src) noexcept
        {
            variety_10_10_10_2_to_rgba<type_uint_2_10_10_10_rev, int32_t>(dst, src);
        }

        // __VA_ARGS__ = components shifts
        #define type_to_rgba(dst, type, src, components, ...)                                                                        \
            switch(type) {                                                                                                           \
                case AMGL_BYTE:                        integer_type_##components##_to_rgba<int8_t, __VA_ARGS__>(dst, src);   break;  \
                case AMGL_UNSIGNED_BYTE:               integer_type_##components##_to_rgba<uint8_t, __VA_ARGS__>(dst, src);  break;  \
                case AMGL_SHORT:                       integer_type_##components##_to_rgba<int16_t, __VA_ARGS__>(dst, src);  break;  \
                case AMGL_UNSIGNED_SHORT:              integer_type_##components##_to_rgba<uint16_t, __VA_ARGS__>(dst, src); break;  \
                case AMGL_INT:                         integer_type_##components##_to_rgba<int32_t, __VA_ARGS__>(dst, src);  break;  \
                case AMGL_UNSIGNED_INT:                integer_type_##components##_to_rgba<uint32_t, __VA_ARGS__>(dst, src); break;  \
                case AMGL_FLOAT:                       floating_type_##components##_to_rgba<float, __VA_ARGS__>(dst, src);   break;  \
                case AMGL_DOUBLE:                      floating_type_##components##_to_rgba<double, __VA_ARGS__>(dst, src);  break;  \
                case AMGL_INT_2_10_10_10_REV:          packed_type_to_rgba<type_int_2_10_10_10_rev>(dst, src);               break;  \
                case AMGL_UNSIGNED_INT_10_10_10_2:     packed_type_to_rgba<type_uint_10_10_10_2>(dst, src);                  break;  \
                case AMGL_UNSIGNED_INT_2_10_10_10_REV: packed_type_to_rgba<type_uint_2_10_10_10_rev>(dst, src);              break;  \
                case AMGL_UNSIGNED_SHORT_4_4_4_4:      packed_type_to_rgba<type_ushort_4_4_4_4>(dst, src);                   break;  \
                case AMGL_UNSIGNED_SHORT_4_4_4_4_REV:  packed_type_to_rgba<type_ushort_4_4_4_4_rev>(dst, src);               break;  \
                case AMGL_UNSIGNED_SHORT_5_5_5_1:      packed_type_to_rgba<type_ushort_5_5_5_1>(dst, src);                   break;  \
                case AMGL_UNSIGNED_SHORT_1_5_5_5_REV:  packed_type_to_rgba<type_ushort_1_5_5_5_rev>(dst, src);               break;  \
                case AMGL_UNSIGNED_INT_8_8_8_8:        packed_type_to_rgba<type_uint_8_8_8_8>(dst, src);                     break;  \
                case AMGL_UNSIGNED_INT_8_8_8_8_REV:    packed_type_to_rgba<type_uint_8_8_8_8_rev>(dst, src);                 break;  \
            }

        inline void format_type_to_rgba(void *dst, enum_t format, enum_t type, const void *src) noexcept
        {
            switch (format) {
                case AMGL_RED:                  type_to_rgba(dst, type, src, 1, 0, 1, 2, 3); break;
                case AMGL_RG:                   type_to_rgba(dst, type, src, 2, 0, 1, 2, 3); break;
                case AMGL_RGB:                  type_to_rgba(dst, type, src, 3, 0, 1, 2, 3); break;
                case AMGL_RGBA:                 type_to_rgba(dst, type, src, 4, 0, 1, 2, 3); break;
                case AMGL_RED_INTEGER:          type_to_rgba(dst, type, src, 1, 0, 1, 2, 3); break;
                case AMGL_RG_INTEGER:           type_to_rgba(dst, type, src, 2, 0, 1, 2, 3); break;
                case AMGL_RGB_INTEGER:          type_to_rgba(dst, type, src, 3, 0, 1, 2, 3); break;
                case AMGL_RGBA_INTEGER:         type_to_rgba(dst, type, src, 4, 0, 1, 2, 3); break;
                case AMGL_BGR:                  type_to_rgba(dst, type, src, 3, 2, 1, 0, 3); break;
                case AMGL_BGRA:                 type_to_rgba(dst, type, src, 4, 2, 1, 0, 3); break;
                case AMGL_BGR_INTEGER:          type_to_rgba(dst, type, src, 3, 2, 1, 0, 3); break;
                case AMGL_BGRA_INTEGER:         type_to_rgba(dst, type, src, 4, 2, 1, 0, 3); break;
            }
        }
    } 
}