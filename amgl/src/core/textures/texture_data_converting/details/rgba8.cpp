#include "pch.hpp"
#include "rgba8.hpp"

#include "core/textures/texture_data_converting/texture_formats.hpp"
#include "core/textures/texture_data_converting/texture_types.hpp"

#include "core/math/common.hpp"


namespace amgl
{
    namespace detail
    {
        #define CONVERT_INTEGRAL(src_type, src, dst_type, dst)                                                          \
        {                                                                                                               \
            const float t = math::inverse_lerp<src_type, float>(MATH_TYPE_MIN(src_type), MATH_TYPE_MAX(src_type), src); \
            dst = math::lerp<dst_type>(0, 255, t);                                                                      \
        }

        #define CONVERT_FLOAT(src, dst_type, dst)                                                                   \
        {                                                                                                           \
            const float t = math::clamp<float>(0.0f, 1.0f, dst);                                                    \
            dst = math::lerp<dst_type>(0, 255, t);                                                                  \
        }


        template <typename type> 
        void convert_to_rgba8(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2, size_t shift3) noexcept
        {
            fmt_rgba8* _dst = (fmt_rgba8*)dst;
            const type* _src = (const type*)src;

            CONVERT_INTEGRAL(type, _src[shift0], fmt_rgba8::value_type, _dst->r);
            CONVERT_INTEGRAL(type, _src[shift1], fmt_rgba8::value_type, _dst->g);
            CONVERT_INTEGRAL(type, _src[shift2], fmt_rgba8::value_type, _dst->b);
            CONVERT_INTEGRAL(type, _src[shift3], fmt_rgba8::value_type, _dst->a);
        };

        template <typename type> 
        void convert_to_rgba8(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2) noexcept
        {
            fmt_rgba8* _dst = (fmt_rgba8*)dst;
            const type* _src = (const type*)src;

            CONVERT_INTEGRAL(type, _src[shift0], fmt_rgba8::value_type, _dst->r);
            CONVERT_INTEGRAL(type, _src[shift1], fmt_rgba8::value_type, _dst->g);
            CONVERT_INTEGRAL(type, _src[shift2], fmt_rgba8::value_type, _dst->b);
            _dst->a = 255;
        };

        template <typename type> 
        void convert_to_rgba8(void *dst, const void *src, size_t shift0, size_t shift1) noexcept
        {
            fmt_rgba8* _dst = (fmt_rgba8*)dst;
            const type* _src = (const type*)src;

            CONVERT_INTEGRAL(type, _src[shift0], fmt_rgba8::value_type, _dst->r);
            CONVERT_INTEGRAL(type, _src[shift1], fmt_rgba8::value_type, _dst->g);
            _dst->b = 0;
            _dst->a = 255;
        };

        template <typename type> 
        void convert_to_rgba8(void *dst, const void *src, size_t shift0) noexcept
        {
            fmt_rgba8* _dst = (fmt_rgba8*)dst;
            const type* _src = (const type*)src;

            CONVERT_INTEGRAL(type, _src[shift0], fmt_rgba8::value_type, _dst->r);
            _dst->g = 0;
            _dst->b = 0;
            _dst->a = 255;
        };

        template <> 
        void convert_to_rgba8<uint8_t>(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2, size_t shift3) noexcept
        {
            fmt_rgba8* _dst = (fmt_rgba8*)dst;
            const uint8_t* _src = (const uint8_t*)src;
            
            _dst->r = _src[shift0];
            _dst->g = _src[shift1];
            _dst->b = _src[shift2];
            _dst->a = _src[shift3];
        };

        template <> 
        void convert_to_rgba8<uint8_t>(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2) noexcept
        {
            fmt_rgba8* _dst = (fmt_rgba8*)dst;
            const uint8_t* _src = (const uint8_t*)src;

            _dst->r = _src[shift0];
            _dst->g = _src[shift1];
            _dst->b = _src[shift2];
            _dst->a = 255;
        };

        template <> 
        void convert_to_rgba8<uint8_t>(void *dst, const void *src, size_t shift0, size_t shift1) noexcept
        {
            fmt_rgba8* _dst = (fmt_rgba8*)dst;
            const uint8_t* _src = (const uint8_t*)src;

            _dst->r = _src[shift0];
            _dst->g = _src[shift1];
            _dst->b = 0;
            _dst->a = 255;
        };

        template <> 
        void convert_to_rgba8<uint8_t>(void *dst, const void *src, size_t shift0) noexcept
        {
            fmt_rgba8* _dst = (fmt_rgba8*)dst;
            const uint8_t* _src = (const uint8_t*)src;

            _dst->r = _src[shift0];
            _dst->g = 0;
            _dst->b = 0;
            _dst->a = 255;
        };

        template <> 
        void convert_to_rgba8<float>(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2, size_t shift3) noexcept
        {
            fmt_rgba8* _dst = (fmt_rgba8*)dst;
            const float* _src = (const float*)src;

            CONVERT_FLOAT(_src[shift0], fmt_rgba8::value_type, _dst->r);
            CONVERT_FLOAT(_src[shift1], fmt_rgba8::value_type, _dst->g);
            CONVERT_FLOAT(_src[shift2], fmt_rgba8::value_type, _dst->b);
            CONVERT_FLOAT(_src[shift3], fmt_rgba8::value_type, _dst->a);
        };

        template <> 
        void convert_to_rgba8<float>(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2) noexcept
        {
            fmt_rgba8* _dst = (fmt_rgba8*)dst;
            const float* _src = (const float*)src;

            CONVERT_FLOAT(_src[shift0], fmt_rgba8::value_type, _dst->r);
            CONVERT_FLOAT(_src[shift1], fmt_rgba8::value_type, _dst->g);
            CONVERT_FLOAT(_src[shift2], fmt_rgba8::value_type, _dst->b);
            _dst->a = 255;
        };

        template <> 
        void convert_to_rgba8<float>(void *dst, const void *src, size_t shift0, size_t shift1) noexcept
        {
            fmt_rgba8* _dst = (fmt_rgba8*)dst;
            const float* _src = (const float*)src;

            CONVERT_FLOAT(_src[shift0], fmt_rgba8::value_type, _dst->r);
            CONVERT_FLOAT(_src[shift1], fmt_rgba8::value_type, _dst->g);
            _dst->b = 0;
            _dst->a = 255;
        };

        template <> 
        void convert_to_rgba8<float>(void *dst, const void *src, size_t shift0) noexcept
        {
            fmt_rgba8* _dst = (fmt_rgba8*)dst;
            const float* _src = (const float*)src;

            CONVERT_FLOAT(_src[shift0], fmt_rgba8::value_type, _dst->r);
            _dst->g = 0;
            _dst->b = 0;
            _dst->a = 255;
        };


        template<typename... shift_types>
        static void type_to_rgba8(void *dst, enum_t type, const void *src, shift_types&&... shifts) noexcept
        {
            switch (type) {
                case AMGL_UNSIGNED_BYTE:    convert_to_rgba8<uint8_t>(dst, src, std::forward<shift_types>(shifts)...);    break;
                case AMGL_BYTE:             convert_to_rgba8<int8_t>(dst, src, std::forward<shift_types>(shifts)...);     break;
                case AMGL_UNSIGNED_SHORT:   convert_to_rgba8<uint16_t>(dst, src, std::forward<shift_types>(shifts)...);   break;
                case AMGL_SHORT:            convert_to_rgba8<int16_t>(dst, src, std::forward<shift_types>(shifts)...);    break;
                case AMGL_UNSIGNED_INT:     convert_to_rgba8<uint32_t>(dst, src, std::forward<shift_types>(shifts)...);   break;
                case AMGL_INT:              convert_to_rgba8<int32_t>(dst, src, std::forward<shift_types>(shifts)...);    break;
                case AMGL_FLOAT:            convert_to_rgba8<float>(dst, src, std::forward<shift_types>(shifts)...);      break;
            }
        }


        void format_type_to_rgba8(void *dst, enum_t format, enum_t type, const void *src) noexcept
        {
            switch (format) {
                case AMGL_RED:
                case AMGL_RED_INTEGER:      type_to_rgba8(dst, type, src, 0); break;
                
                case AMGL_RG:
                case AMGL_RG_INTEGER:       type_to_rgba8(dst, type, src, 0, 1); break;
               
                case AMGL_RGB:
                case AMGL_RGB_INTEGER:      type_to_rgba8(dst, type, src, 0, 1, 2); break;
                
                case AMGL_RGBA:
                case AMGL_RGBA_INTEGER:     type_to_rgba8(dst, type, src, 0, 1, 2, 3); break;

                case AMGL_BGR:
                case AMGL_BGR_INTEGER:      type_to_rgba8(dst, type, src, 2, 1, 0); break;
                
                case AMGL_BGRA:
                case AMGL_BGRA_INTEGER:     type_to_rgba8(dst, type, src, 3, 2, 1, 0); break;

                case AMGL_INT_2_10_10_10_REV:           AM_NOT_IMPLEMENTED;
                case AMGL_UNSIGNED_INT_10_10_10_2:      AM_NOT_IMPLEMENTED;
                case AMGL_UNSIGNED_INT_2_10_10_10_REV:  AM_NOT_IMPLEMENTED;
                case AMGL_UNSIGNED_BYTE_3_3_2:          AM_NOT_IMPLEMENTED;
                case AMGL_UNSIGNED_BYTE_2_3_3_REV:      AM_NOT_IMPLEMENTED;
                case AMGL_UNSIGNED_SHORT_5_6_5:         AM_NOT_IMPLEMENTED;
                case AMGL_UNSIGNED_SHORT_5_6_5_REV:     AM_NOT_IMPLEMENTED;
                case AMGL_UNSIGNED_SHORT_4_4_4_4:       AM_NOT_IMPLEMENTED;
                case AMGL_UNSIGNED_SHORT_4_4_4_4_REV:   AM_NOT_IMPLEMENTED;
                case AMGL_UNSIGNED_SHORT_5_5_5_1:       AM_NOT_IMPLEMENTED;
                case AMGL_UNSIGNED_SHORT_1_5_5_5_REV:   AM_NOT_IMPLEMENTED;
                case AMGL_UNSIGNED_INT_8_8_8_8:         AM_NOT_IMPLEMENTED;
                case AMGL_UNSIGNED_INT_8_8_8_8_REV:     AM_NOT_IMPLEMENTED;
            }
        }
    }
}