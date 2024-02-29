// #include "pch.hpp"
// #include "rgba8.hpp"

// #include "core/textures/texture_data_converting/texture_formats.hpp"
// #include "core/textures/texture_data_converting/texture_input_data_types.hpp"

// #include "convert.hpp"


// namespace amgl
// {
//     namespace detail
//     {
//         template <typename type> 
//         static void to_rgba8(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2, size_t shift3) noexcept
//         {
//             fmt_rgba8* _dst = (fmt_rgba8*)dst;
//             const type* _src = (const type*)src;

//             _dst->r = convert_arithmetic<decltype(_dst->r), type>(0, 255, _src[shift0]);
//             _dst->g = convert_arithmetic<decltype(_dst->g), type>(0, 255, _src[shift1]);
//             _dst->b = convert_arithmetic<decltype(_dst->b), type>(0, 255, _src[shift2]);
//             _dst->a = convert_arithmetic<decltype(_dst->a), type>(0, 255, _src[shift3]);
//         };

//         template <typename type> 
//         static void to_rgba8(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2) noexcept
//         {
//             fmt_rgba8* _dst = (fmt_rgba8*)dst;
//             const type* _src = (const type*)src;

//             _dst->r = convert_arithmetic<decltype(_dst->r), type>(0, 255, _src[shift0]);
//             _dst->g = convert_arithmetic<decltype(_dst->g), type>(0, 255, _src[shift1]);
//             _dst->b = convert_arithmetic<decltype(_dst->b), type>(0, 255, _src[shift2]);
//             _dst->a = 255;
//         };

//         template <typename type> 
//         static void to_rgba8(void *dst, const void *src, size_t shift0, size_t shift1) noexcept
//         {
//             fmt_rgba8* _dst = (fmt_rgba8*)dst;
//             const type* _src = (const type*)src;

//             _dst->r = convert_arithmetic<decltype(_dst->r), type>(0, 255, _src[shift0]);
//             _dst->g = convert_arithmetic<decltype(_dst->g), type>(0, 255, _src[shift1]);
//             _dst->b = 0;
//             _dst->a = 255;
//         };

//         template <typename type> 
//         static void to_rgba8(void *dst, const void *src, size_t shift0) noexcept
//         {
//             fmt_rgba8* _dst = (fmt_rgba8*)dst;
//             const type* _src = (const type*)src;

//             _dst->r = convert_arithmetic<decltype(_dst->r), type>(0, 255, _src[shift0]);
//             _dst->g = 0;
//             _dst->b = 0;
//             _dst->a = 255;
//         };

//         template <> 
//         void to_rgba8<uint8_t>(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2, size_t shift3) noexcept
//         {
//             fmt_rgba8* _dst = (fmt_rgba8*)dst;
//             const uint8_t* _src = (const uint8_t*)src;
           
//             _dst->r = _src[shift0];
//             _dst->g = _src[shift1];
//             _dst->b = _src[shift2];
//             _dst->a = _src[shift3];
//         };

//         template <> 
//         void to_rgba8<uint8_t>(void *dst, const void *src, size_t shift0, size_t shift1, size_t shift2) noexcept
//         {
//             fmt_rgba8* _dst = (fmt_rgba8*)dst;
//             const uint8_t* _src = (const uint8_t*)src;

//             _dst->r = _src[shift0];
//             _dst->g = _src[shift1];
//             _dst->b = _src[shift2];
//             _dst->a = 255;
//         };

//         template <> 
//         void to_rgba8<uint8_t>(void *dst, const void *src, size_t shift0, size_t shift1) noexcept
//         {
//             fmt_rgba8* _dst = (fmt_rgba8*)dst;
//             const uint8_t* _src = (const uint8_t*)src;

//             _dst->r = _src[shift0];
//             _dst->g = _src[shift1];
//             _dst->b = 0;
//             _dst->a = 255;
//         };

//         template <> 
//         void to_rgba8<uint8_t>(void *dst, const void *src, size_t shift0) noexcept
//         {
//             fmt_rgba8* _dst = (fmt_rgba8*)dst;
//             const uint8_t* _src = (const uint8_t*)src;

//             _dst->r = _src[shift0];
//             _dst->g = 0;
//             _dst->b = 0;
//             _dst->a = 255;
//         };


//         template<typename... shift_types>
//         static void type_to_rgba8(void *dst, enum_t type, const void *src, shift_types&&... shifts) noexcept
//         {
//             switch (type) {
//                 case AMGL_UNSIGNED_BYTE:                to_rgba8<uint8_t>(dst, src, std::forward<shift_types>(shifts)...);    break;
//                 case AMGL_BYTE:                         to_rgba8<int8_t>(dst, src, std::forward<shift_types>(shifts)...);     break;
//                 case AMGL_UNSIGNED_SHORT:               to_rgba8<uint16_t>(dst, src, std::forward<shift_types>(shifts)...);   break;
//                 case AMGL_SHORT:                        to_rgba8<int16_t>(dst, src, std::forward<shift_types>(shifts)...);    break;
//                 case AMGL_UNSIGNED_INT:                 to_rgba8<uint32_t>(dst, src, std::forward<shift_types>(shifts)...);   break;
//                 case AMGL_INT:                          to_rgba8<int32_t>(dst, src, std::forward<shift_types>(shifts)...);    break;
//                 case AMGL_FLOAT:                        to_rgba8<float>(dst, src, std::forward<shift_types>(shifts)...);      break;
//                 case AMGL_UNSIGNED_BYTE_3_3_2:          AM_NOT_IMPLEMENTED;
//                 case AMGL_UNSIGNED_BYTE_2_3_3_REV:      AM_NOT_IMPLEMENTED;
//                 case AMGL_UNSIGNED_SHORT_5_6_5:         AM_NOT_IMPLEMENTED;
//                 case AMGL_UNSIGNED_SHORT_5_6_5_REV:     AM_NOT_IMPLEMENTED;
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
        
        
//         void format_type_to_rgba8(void *dst, enum_t format, enum_t type, const void *src) noexcept
//         {
//             switch (format) {
//                 case AMGL_RED:
//                 case AMGL_RED_INTEGER:      type_to_rgba8(dst, type, src, 0); break;
               
//                 case AMGL_RG:
//                 case AMGL_RG_INTEGER:       type_to_rgba8(dst, type, src, 0, 1); break;
              
//                 case AMGL_RGB:
//                 case AMGL_RGB_INTEGER:      type_to_rgba8(dst, type, src, 0, 1, 2); break;
               
//                 case AMGL_RGBA:
//                 case AMGL_RGBA_INTEGER:     type_to_rgba8(dst, type, src, 0, 1, 2, 3); break;
        
//                 case AMGL_BGR:
//                 case AMGL_BGR_INTEGER:      type_to_rgba8(dst, type, src, 2, 1, 0); break;
               
//                 case AMGL_BGRA:
//                 case AMGL_BGRA_INTEGER:     type_to_rgba8(dst, type, src, 3, 2, 1, 0); break;
//             }
//         }
//     }
// }