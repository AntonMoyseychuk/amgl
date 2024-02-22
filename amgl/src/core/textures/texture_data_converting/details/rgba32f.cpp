#include "pch.hpp"
#include "rgba8.hpp"

#include "core/textures/texture_data_converting/texture_formats.hpp"
#include "core/textures/texture_data_converting/texture_types.hpp"

#include "core/math/common.hpp"


namespace amgl
{
    namespace detail
    {
        #define CONVERT_INTEGRAL(src_type, src, dst)                                                                \
        {                                                                                                           \
            dst = math::inverse_lerp<src_type, float>(MATH_TYPE_MIN(src_type), MATH_TYPE_MAX(src_type), src);       \
        }


        template <typename type> 
        void convert_to_rgba32f(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2, size_t shift3) noexcept
        {
            fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
            const type* _src = (const type*)src;

            CONVERT_INTEGRAL(type, _src[shift0], _dst->r);
            CONVERT_INTEGRAL(type, _src[shift1], _dst->g);
            CONVERT_INTEGRAL(type, _src[shift2], _dst->b);
            CONVERT_INTEGRAL(type, _src[shift3], _dst->a);
        };

        template <typename type> 
        void convert_to_rgba32f(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2) noexcept
        {
            fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
            const type* _src = (const type*)src;

            CONVERT_INTEGRAL(type, _src[shift0], _dst->r);
            CONVERT_INTEGRAL(type, _src[shift1], _dst->g);
            CONVERT_INTEGRAL(type, _src[shift2], _dst->b);
            _dst->a = 1.0f;
        };

        template <typename type> 
        void convert_to_rgba32f(void *dst, const void *src, size_t shift0, size_t shift1) noexcept
        {
            fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
            const type* _src = (const type*)src;

            CONVERT_INTEGRAL(type, _src[shift0], _dst->r);
            CONVERT_INTEGRAL(type, _src[shift1], _dst->g);
            _dst->b = 0.0f;
            _dst->a = 1.0f;
        };

        template <typename type> 
        void convert_to_rgba32f(void *dst, const void *src, size_t shift0) noexcept
        {
            fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
            const type* _src = (const type*)src;

            CONVERT_INTEGRAL(type, _src[shift0], _dst->r);
            _dst->g = 0.0f;
            _dst->b = 0.0f;
            _dst->a = 1.0f;
        };

        template <> 
        void convert_to_rgba32f<float>(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2, size_t shift3) noexcept
        {
            fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
            const float* _src = (const float*)src;
            
            _dst->r = _src[shift0];
            _dst->g = _src[shift1];
            _dst->b = _src[shift2];
            _dst->a = _src[shift3];
        };

        template <> 
        void convert_to_rgba32f<float>(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2) noexcept
        {
            fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
            const float* _src = (const float*)src;

            _dst->r = _src[shift0];
            _dst->g = _src[shift1];
            _dst->b = _src[shift2];
            _dst->a = 1.0f;
        };

        template <> 
        void convert_to_rgba32f<float>(void *dst, const void *src, size_t shift0, size_t shift1) noexcept
        {
            fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
            const float* _src = (const float*)src;

            _dst->r = _src[shift0];
            _dst->g = _src[shift1];
            _dst->b = 0.0f;
            _dst->a = 1.0f;
        };

        template <> 
        void convert_to_rgba32f<float>(void *dst, const void *src, size_t shift0) noexcept
        {
            fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
            const float* _src = (const float*)src;

            _dst->r = _src[shift0];
            _dst->g = 0.0f;
            _dst->b = 0.0f;
            _dst->a = 1.0f;
        };


        static void red_type_to_rgba32f(void *dst, enum_t type, const void *src) noexcept
        {
            switch (type) {
                case AMGL_UNSIGNED_BYTE:    convert_to_rgba32f<uint8_t>(dst, src, 0);     break;
                case AMGL_BYTE:             convert_to_rgba32f<int8_t>(dst, src, 0);      break;
                case AMGL_UNSIGNED_SHORT:   convert_to_rgba32f<uint16_t>(dst, src, 0);    break;
                case AMGL_SHORT:            convert_to_rgba32f<int16_t>(dst, src, 0);     break;
                case AMGL_UNSIGNED_INT:     convert_to_rgba32f<uint32_t>(dst, src, 0);    break;
                case AMGL_INT:              convert_to_rgba32f<int32_t>(dst, src, 0);     break;
                case AMGL_FLOAT:            convert_to_rgba32f<float>(dst, src, 0);       break;
            }
        }


        static void rg_type_to_rgba32f(void *dst, enum_t type, const void *src) noexcept
        {
            switch (type) {
                case AMGL_UNSIGNED_BYTE:    convert_to_rgba32f<uint8_t>(dst, src, 0, 1);     break;
                case AMGL_BYTE:             convert_to_rgba32f<int8_t>(dst, src, 0, 1);      break;
                case AMGL_UNSIGNED_SHORT:   convert_to_rgba32f<uint16_t>(dst, src, 0, 1);    break;
                case AMGL_SHORT:            convert_to_rgba32f<int16_t>(dst, src, 0, 1);     break;
                case AMGL_UNSIGNED_INT:     convert_to_rgba32f<uint32_t>(dst, src, 0, 1);    break;
                case AMGL_INT:              convert_to_rgba32f<int32_t>(dst, src, 0, 1);     break;
                case AMGL_FLOAT:            convert_to_rgba32f<float>(dst, src, 0, 1);       break;
            }
        }


        static void rgb_type_to_rgba32f(void *dst, enum_t type, const void *src) noexcept
        {
            switch (type) {
                case AMGL_UNSIGNED_BYTE:    convert_to_rgba32f<uint8_t>(dst, src, 0, 1, 2);     break;
                case AMGL_BYTE:             convert_to_rgba32f<int8_t>(dst, src, 0, 1, 2);      break;
                case AMGL_UNSIGNED_SHORT:   convert_to_rgba32f<uint16_t>(dst, src, 0, 1, 2);    break;
                case AMGL_SHORT:            convert_to_rgba32f<int16_t>(dst, src, 0, 1, 2);     break;
                case AMGL_UNSIGNED_INT:     convert_to_rgba32f<uint32_t>(dst, src, 0, 1, 2);    break;
                case AMGL_INT:              convert_to_rgba32f<int32_t>(dst, src, 0, 1, 2);     break;
                case AMGL_FLOAT:            convert_to_rgba32f<float>(dst, src, 0, 1, 2);       break;
            }
        }


        static void rgba_type_to_rgba32f(void *dst, enum_t type, const void *src) noexcept
        {
            switch (type) {
                case AMGL_UNSIGNED_BYTE:    convert_to_rgba32f<uint8_t>(dst, src, 0, 1, 2, 3);     break;
                case AMGL_BYTE:             convert_to_rgba32f<int8_t>(dst, src, 0, 1, 2, 3);      break;
                case AMGL_UNSIGNED_SHORT:   convert_to_rgba32f<uint16_t>(dst, src, 0, 1, 2, 3);    break;
                case AMGL_SHORT:            convert_to_rgba32f<int16_t>(dst, src, 0, 1, 2, 3);     break;
                case AMGL_UNSIGNED_INT:     convert_to_rgba32f<uint32_t>(dst, src, 0, 1, 2, 3);    break;
                case AMGL_INT:              convert_to_rgba32f<int32_t>(dst, src, 0, 1, 2, 3);     break;
                case AMGL_FLOAT:            convert_to_rgba32f<float>(dst, src, 0, 1, 2, 3);       break;
            }
        }


        static void bgr_type_to_rgba32f(void *dst, enum_t type, const void *src) noexcept
        {
            switch (type) {
                case AMGL_UNSIGNED_BYTE:    convert_to_rgba32f<uint8_t>(dst, src, 2, 1, 0);     break;
                case AMGL_BYTE:             convert_to_rgba32f<int8_t>(dst, src, 2, 1, 0);      break;
                case AMGL_UNSIGNED_SHORT:   convert_to_rgba32f<uint16_t>(dst, src, 2, 1, 0);    break;
                case AMGL_SHORT:            convert_to_rgba32f<int16_t>(dst, src, 2, 1, 0);     break;
                case AMGL_UNSIGNED_INT:     convert_to_rgba32f<uint32_t>(dst, src, 2, 1, 0);    break;
                case AMGL_INT:              convert_to_rgba32f<int32_t>(dst, src, 2, 1, 0);     break;
                case AMGL_FLOAT:            convert_to_rgba32f<float>(dst, src, 2, 1, 0);       break;
            }
        }


        static void bgra_type_to_rgba32f(void *dst, enum_t type, const void *src) noexcept
        {
            switch (type) {
                case AMGL_UNSIGNED_BYTE:    convert_to_rgba32f<uint8_t>(dst, src, 2, 1, 0, 3);     break;
                case AMGL_BYTE:             convert_to_rgba32f<int8_t>(dst, src, 2, 1, 0, 3);      break;
                case AMGL_UNSIGNED_SHORT:   convert_to_rgba32f<uint16_t>(dst, src, 2, 1, 0, 3);    break;
                case AMGL_SHORT:            convert_to_rgba32f<int16_t>(dst, src, 2, 1, 0, 3);     break;
                case AMGL_UNSIGNED_INT:     convert_to_rgba32f<uint32_t>(dst, src, 2, 1, 0, 3);    break;
                case AMGL_INT:              convert_to_rgba32f<int32_t>(dst, src, 2, 1, 0, 3);     break;
                case AMGL_FLOAT:            convert_to_rgba32f<float>(dst, src, 2, 1, 0, 3);       break;
            }
        }


        void format_type_to_rgba32f(void *dst, enum_t format, enum_t type, const void *src) noexcept
        {
            switch (format) {
                case AMGL_RED:
                case AMGL_RED_INTEGER:      red_type_to_rgba32f(dst, type, src); break;
                
                case AMGL_RG:
                case AMGL_RG_INTEGER:       rg_type_to_rgba32f(dst, type, src); break;
               
                case AMGL_RGB:
                case AMGL_RGB_INTEGER:      rgb_type_to_rgba32f(dst, type, src); break;
                
                case AMGL_RGBA:
                case AMGL_RGBA_INTEGER:     rgba_type_to_rgba32f(dst, type, src); break;

                case AMGL_BGR:
                case AMGL_BGR_INTEGER:      bgr_type_to_rgba32f(dst, type, src); break;
                
                case AMGL_BGRA:
                case AMGL_BGRA_INTEGER:     bgra_type_to_rgba32f(dst, type, src); break;
            }
        }
    }
}