// #include "pch.hpp"
// #include "rgba8.hpp"

// #include "core/textures/texture_data_converting/texture_formats.hpp"
// #include "core/textures/texture_data_converting/texture_types.hpp"

// #include "convert.hpp"


// namespace amgl
// {
//     namespace detail
//     {
//         template <typename type> 
//         void to_rgba32f(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2, size_t shift3) noexcept
//         {
//             fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
//             const type* _src = (const type*)src;

//             _dst->r = convert_arithmetic<decltype(_dst->r), type>(0.0f, 1.0f, _src[shift0]);
//             _dst->g = convert_arithmetic<decltype(_dst->g), type>(0.0f, 1.0f, _src[shift1]);
//             _dst->b = convert_arithmetic<decltype(_dst->b), type>(0.0f, 1.0f, _src[shift2]);
//             _dst->a = convert_arithmetic<decltype(_dst->a), type>(0.0f, 1.0f, _src[shift3]);
//         };

//         template <typename type> 
//         void to_rgba32f(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2) noexcept
//         {
//             fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
//             const type* _src = (const type*)src;

//             _dst->r = convert_arithmetic<decltype(_dst->r), type>(0.0f, 1.0f, _src[shift0]);
//             _dst->g = convert_arithmetic<decltype(_dst->g), type>(0.0f, 1.0f, _src[shift1]);
//             _dst->b = convert_arithmetic<decltype(_dst->b), type>(0.0f, 1.0f, _src[shift2]);
//             _dst->a = 1.0f;
//         };

//         template <typename type> 
//         void to_rgba32f(void *dst, const void *src, size_t shift0, size_t shift1) noexcept
//         {
//             fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
//             const type* _src = (const type*)src;

//             _dst->r = convert_arithmetic<decltype(_dst->r), type>(0.0f, 1.0f, _src[shift0]);
//             _dst->g = convert_arithmetic<decltype(_dst->g), type>(0.0f, 1.0f, _src[shift1]);
//             _dst->b = 0.0f;
//             _dst->a = 1.0f;
//         };

//         template <typename type> 
//         void to_rgba32f(void *dst, const void *src, size_t shift0) noexcept
//         {
//             fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
//             const type* _src = (const type*)src;

//             _dst->r = convert_arithmetic<decltype(_dst->r), type>(0.0f, 1.0f, _src[shift0]);
//             _dst->g = 0.0f;
//             _dst->b = 0.0f;
//             _dst->a = 1.0f;
//         };

//         template <> 
//         void to_rgba32f<float>(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2, size_t shift3) noexcept
//         {
//             fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
//             const float* _src = (const float*)src;
            
//             _dst->r = _src[shift0];
//             _dst->g = _src[shift1];
//             _dst->b = _src[shift2];
//             _dst->a = _src[shift3];
//         };

//         template <> 
//         void to_rgba32f<float>(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2) noexcept
//         {
//             fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
//             const float* _src = (const float*)src;

//             _dst->r = _src[shift0];
//             _dst->g = _src[shift1];
//             _dst->b = _src[shift2];
//             _dst->a = 1.0f;
//         };

//         template <> 
//         void to_rgba32f<float>(void *dst, const void *src, size_t shift0, size_t shift1) noexcept
//         {
//             fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
//             const float* _src = (const float*)src;

//             _dst->r = _src[shift0];
//             _dst->g = _src[shift1];
//             _dst->b = 0.0f;
//             _dst->a = 1.0f;
//         };

//         template <> 
//         void to_rgba32f<float>(void *dst, const void *src, size_t shift0) noexcept
//         {
//             fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
//             const float* _src = (const float*)src;

//             _dst->r = _src[shift0];
//             _dst->g = 0.0f;
//             _dst->b = 0.0f;
//             _dst->a = 1.0f;
//         };


//         template <typename packed_type> 
//         void packed_to_rgba32f(void *dst, const void *src) noexcept
//         {
//             fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
//             const packed_type* _src = (const packed_type*)src;

//             using val_type = typename packed_type::value_type;

//             float t = inverse_lerp<val_type, float>(
//                 min_bit_value<val_type>(packed_type::R_BITS_COUNT), max_bit_value<val_type>(packed_type::R_BITS_COUNT), _src->r);
//             _dst->r = lerp<fmt_rgba32f::value_type>(0.0f, 1.0f, t);

//             t = inverse_lerp<val_type, float>(
//                 min_bit_value<val_type>(packed_type::G_BITS_COUNT), max_bit_value<val_type>(packed_type::G_BITS_COUNT), _src->g);
//             _dst->g = lerp<fmt_rgba32f::value_type>(0.0f, 1.0f, t);

//             t = inverse_lerp<val_type, float>(
//                 min_bit_value<val_type>(packed_type::B_BITS_COUNT), max_bit_value<val_type>(packed_type::B_BITS_COUNT), _src->b);
//             _dst->b = lerp<fmt_rgba32f::value_type>(0.0f, 1.0f, t);

//             t = inverse_lerp<val_type, float>(
//                 min_bit_value<val_type>(packed_type::A_BITS_COUNT), max_bit_value<val_type>(packed_type::A_BITS_COUNT), _src->a);
//             _dst->a = lerp<fmt_rgba32f::value_type>(0.0f, 1.0f, t);
//         };


//         template <> 
//         void packed_to_rgba32f<type_int_2_10_10_10_rev>(void *dst, const void *src) noexcept
//         {
//             using packed_type = type_int_2_10_10_10_rev;

//             fmt_rgba32f* _dst = (fmt_rgba32f*)dst;
//             const packed_type* _src = (const packed_type*)src;

//             float t = math::inverse_lerp<packed_type::value_type, float>(
//                 MATH_MIN_SIGNED_BIT_VALUE(packed_type::R_BITS_COUNT), MATH_MAX_SIGNED_BIT_VALUE(packed_type::R_BITS_COUNT), _src->r);
//             _dst->r = math::lerp<fmt_rgba32f::value_type>(0, 255, t);

//             t = math::inverse_lerp<packed_type::value_type, float>(
//                 MATH_MIN_SIGNED_BIT_VALUE(packed_type::G_BITS_COUNT), MATH_MAX_SIGNED_BIT_VALUE(packed_type::G_BITS_COUNT), _src->g);
//             _dst->g = math::lerp<fmt_rgba32f::value_type>(0, 255, t);

//             t = math::inverse_lerp<packed_type::value_type, float>(
//                 MATH_MIN_SIGNED_BIT_VALUE(packed_type::B_BITS_COUNT), MATH_MAX_SIGNED_BIT_VALUE(packed_type::B_BITS_COUNT), _src->b);
//             _dst->b = math::lerp<fmt_rgba32f::value_type>(0, 255, t);

//             t = math::inverse_lerp<packed_type::value_type, float>(
//                 MATH_MIN_SIGNED_BIT_VALUE(packed_type::A_BITS_COUNT), MATH_MAX_SIGNED_BIT_VALUE(packed_type::A_BITS_COUNT), _src->a);
//             _dst->a = math::lerp<fmt_rgba32f::value_type>(0, 255, t);
//         };


//         template<typename... shift_types>
//         static void type_to_rgba32f(void *dst, enum_t type, const void *src, shift_types&&... shifts) noexcept
//         {
//             switch (type) {
//                 case AMGL_UNSIGNED_BYTE:                to_rgba32f<uint8_t>(dst, src, std::forward<shift_types>(shifts)...);    break;
//                 case AMGL_BYTE:                         to_rgba32f<int8_t>(dst, src, std::forward<shift_types>(shifts)...);     break;
//                 case AMGL_UNSIGNED_SHORT:               to_rgba32f<uint16_t>(dst, src, std::forward<shift_types>(shifts)...);   break;
//                 case AMGL_SHORT:                        to_rgba32f<int16_t>(dst, src, std::forward<shift_types>(shifts)...);    break;
//                 case AMGL_UNSIGNED_INT:                 to_rgba32f<uint32_t>(dst, src, std::forward<shift_types>(shifts)...);   break;
//                 case AMGL_INT:                          to_rgba32f<int32_t>(dst, src, std::forward<shift_types>(shifts)...);    break;
//                 case AMGL_FLOAT:                        to_rgba32f<float>(dst, src, std::forward<shift_types>(shifts)...);      break;
//                 case AMGL_INT_2_10_10_10_REV:           AM_NOT_IMPLEMENTED;
//                 case AMGL_UNSIGNED_INT_10_10_10_2:      AM_NOT_IMPLEMENTED;
//                 case AMGL_UNSIGNED_INT_2_10_10_10_REV:  AM_NOT_IMPLEMENTED;
//                 case AMGL_UNSIGNED_SHORT_4_4_4_4:       AM_NOT_IMPLEMENTED;
//                 case AMGL_UNSIGNED_SHORT_4_4_4_4_REV:   AM_NOT_IMPLEMENTED;
//                 case AMGL_UNSIGNED_SHORT_5_5_5_1:       AM_NOT_IMPLEMENTED;
//                 case AMGL_UNSIGNED_SHORT_1_5_5_5_REV:   AM_NOT_IMPLEMENTED;
//                 case AMGL_UNSIGNED_INT_8_8_8_8:         AM_NOT_IMPLEMENTED;
//                 case AMGL_UNSIGNED_INT_8_8_8_8_REV:     AM_NOT_IMPLEMENTED;
//             }
//         }


//         void format_type_to_rgba32f(void *dst, enum_t format, enum_t type, const void *src) noexcept
//         {
//             switch (format) {
//                 case AMGL_RED:
//                 case AMGL_RED_INTEGER:      type_to_rgba32f(dst, type, src, 0); break;
                
//                 case AMGL_RG:
//                 case AMGL_RG_INTEGER:       type_to_rgba32f(dst, type, src, 0, 1); break;
               
//                 case AMGL_RGB:
//                 case AMGL_RGB_INTEGER:      type_to_rgba32f(dst, type, src, 0, 1, 2); break;
                
//                 case AMGL_RGBA:
//                 case AMGL_RGBA_INTEGER:     type_to_rgba32f(dst, type, src, 0, 1, 2, 3); break;

//                 case AMGL_BGR:
//                 case AMGL_BGR_INTEGER:      type_to_rgba32f(dst, type, src, 2, 1, 0); break;
                
//                 case AMGL_BGRA:
//                 case AMGL_BGRA_INTEGER:     type_to_rgba32f(dst, type, src, 3, 2, 1, 0); break;
//             }
//         }
//     }
// }