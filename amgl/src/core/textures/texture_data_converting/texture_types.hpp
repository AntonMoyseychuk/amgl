#pragma once
#include "core/core.hpp"
#include "texture_formats.hpp"

#include <cstdint>


namespace amgl
{
    #define TEXTURE_PACKED_TYPES                                                        \
        AMGL_UNSIGNED_BYTE_3_3_2,                                                       \
        AMGL_UNSIGNED_BYTE_2_3_3_REV,                                                   \
        AMGL_UNSIGNED_SHORT_5_6_5,                                                      \
        AMGL_UNSIGNED_SHORT_5_6_5_REV,                                                  \
        AMGL_UNSIGNED_SHORT_4_4_4_4,                                                    \
        AMGL_UNSIGNED_SHORT_4_4_4_4_REV,                                                \
        AMGL_UNSIGNED_SHORT_5_5_5_1,                                                    \
        AMGL_UNSIGNED_SHORT_1_5_5_5_REV,                                                \
        AMGL_UNSIGNED_INT_8_8_8_8,                                                      \
        AMGL_UNSIGNED_INT_8_8_8_8_REV,                                                  \
        AMGL_UNSIGNED_INT_10_10_10_2,                                                   \
        AMGL_UNSIGNED_INT_2_10_10_10_REV

    #define TEXTURE_PRIMITIVE_TYPES                                                     \
        AMGL_UNSIGNED_BYTE,                                                             \
        AMGL_BYTE,                                                                      \
        AMGL_UNSIGNED_SHORT,                                                            \
        AMGL_SHORT,                                                                     \
        AMGL_UNSIGNED_INT,                                                              \
        AMGL_INT,                                                                       \
        AMGL_FLOAT

    #define TEXTURE_TYPES                                                               \
        TEXTURE_PACKED_TYPES, TEXTURE_PRIMITIVE_TYPES


    template <typename type, size_t a_bits, size_t b_bits, size_t g_bits, size_t r_bits, 
        typename = std::enable_if_t<std::is_arithmetic_v<type>>>
    AM_PACKED_STRUCT_BEGIN
    struct type_abgr_t
    {
        using value_type = type;

        constexpr type_abgr_t() : a(0), b(0), g(0), r(0) {}
        constexpr type_abgr_t(type r, type g, type b, type a) : a(a), b(b), g(g), r(r) {}

        static inline constexpr size_t a_max() noexcept { return static_cast<size_t>(math::pow(2, a_bits)) - 1u; }
        static inline constexpr size_t a_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t b_max() noexcept { return static_cast<size_t>(math::pow(2, b_bits)) - 1u; }
        static inline constexpr size_t b_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t g_max() noexcept { return static_cast<size_t>(math::pow(2, g_bits)) - 1u; }
        static inline constexpr size_t g_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t r_max() noexcept { return static_cast<size_t>(math::pow(2, r_bits)) - 1u; }
        static inline constexpr size_t r_min() noexcept { return std::numeric_limits<type>::lowest(); }

        static constexpr size_t A_BITS_COUNT = a_bits;
        static constexpr size_t B_BITS_COUNT = b_bits;
        static constexpr size_t G_BITS_COUNT = g_bits;
        static constexpr size_t R_BITS_COUNT = r_bits;

        type a : a_bits;
        type b : b_bits;
        type g : g_bits;
        type r : r_bits;
    }
    AM_PACKED_STRUCT_END

    using type_byte                 = int8_t;
    using type_ubyte                = uint8_t;
    using type_short                = int16_t;
    using type_ushort               = uint16_t;
    using type_int                  = int32_t;
    using type_uint                 = uint32_t;
    using type_float                = float;
    using type_double               = double;

    using type_int_2_10_10_10_rev   = type_abgr_t<int32_t, 2, 10, 10, 10>;
    using type_ushort_1_5_5_5_rev   = type_abgr_t<uint16_t, 1, 5, 5, 5>;
    using type_uint_8_8_8_8_rev     = type_abgr_t<uint32_t, 8, 8, 8, 8>;
    using type_uint_2_10_10_10_rev  = type_abgr_t<uint32_t, 2, 10, 10, 10>;

    using type_ushort_5_6_5         = fmt_rgb_t<uint16_t, 5, 6, 5, 0>;
    using type_ushort_5_6_5_rev     = fmt_bgr_t<uint16_t, 5, 6, 5, 0>;
    using type_ushort_4_4_4_4_rev   = fmt_bgra_t<uint16_t, 4, 4, 4, 4>;
    using type_ubyte_3_3_2          = fmt_bgr_t<uint8_t, 3, 3, 2, 0>;
    using type_ubyte_2_3_3_rev      = fmt_bgr_t<uint8_t, 2, 3, 3, 0>;
    using type_ushort_4_4_4_4       = fmt_rgba_t<uint16_t, 4, 4, 4, 4>;
    using type_ushort_5_5_5_1       = fmt_rgba_t<uint16_t, 5, 5, 5, 1>;
    using type_uint_8_8_8_8         = fmt_rgba_t<uint32_t, 8, 8, 8, 8>;
    using type_uint_10_10_10_2      = fmt_rgba_t<uint32_t, 10, 10, 10, 2>;

    static_assert(sizeof(type_byte)                 == 1u, "invalid type_byte size");
    static_assert(sizeof(type_ubyte)                == 1u, "invalid type_ubyte size");
    static_assert(sizeof(type_short)                == 2u, "invalid type_short size");
    static_assert(sizeof(type_ushort)               == 2u, "invalid type_ushort size");
    static_assert(sizeof(type_int)                  == 4u, "invalid type_int size");
    static_assert(sizeof(type_float)                == 4u, "invalid type_float size");
    static_assert(sizeof(type_double)               == 8u, "invalid type_double size");
    static_assert(sizeof(type_int_2_10_10_10_rev)   == 4u, "invalid type_int_2_10_10_10_rev size");
    static_assert(sizeof(type_ubyte_2_3_3_rev)      == 1u, "invalid type_ubyte_2_3_3_rev size");
    static_assert(sizeof(type_ushort_5_6_5)         == 2u, "invalid type_ushort_5_6_5 size");
    static_assert(sizeof(type_ushort_5_6_5_rev)     == 2u, "invalid type_ushort_5_6_5_rev size");
    static_assert(sizeof(type_ushort_4_4_4_4_rev)   == 2u, "invalid type_ushort_4_4_4_4_rev size");
    static_assert(sizeof(type_ushort_1_5_5_5_rev)   == 2u, "invalid type_ushort_1_5_5_5_rev size");
    static_assert(sizeof(type_uint_8_8_8_8_rev)     == 4u, "invalid type_uint_8_8_8_8_rev size");
    static_assert(sizeof(type_uint_2_10_10_10_rev)  == 4u, "invalid type_uint_2_10_10_10_rev size");
    static_assert(sizeof(type_ubyte_3_3_2)          == 1u, "invalid type_ubyte_3_3_2 size");
    static_assert(sizeof(type_ushort_4_4_4_4)       == 2u, "invalid type_ushort_4_4_4_4 size");
    static_assert(sizeof(type_uint_8_8_8_8)         == 4u, "invalid type_uint_8_8_8_8 size");
    static_assert(sizeof(type_uint_10_10_10_2)      == 4u, "invalid type_uint_10_10_10_2 size");


    /// @brief 
    /// @return Size in bytes or 0 if 'type' is invalid
    inline constexpr size_t get_type_size(enum_t type) noexcept
    {
        switch (type) {
            case AMGL_BYTE:                         return sizeof(type_byte);
            case AMGL_UNSIGNED_BYTE:                return sizeof(type_ubyte);
            case AMGL_SHORT:                        return sizeof(type_short);
            case AMGL_UNSIGNED_SHORT:               return sizeof(type_ushort);
            case AMGL_INT:                          return sizeof(type_int);
            case AMGL_UNSIGNED_INT:                 return sizeof(type_uint);
            case AMGL_FLOAT:                        return sizeof(type_float);
            case AMGL_DOUBLE:                       return sizeof(type_double);
            case AMGL_INT_2_10_10_10_REV:           return sizeof(type_int_2_10_10_10_rev);
            case AMGL_UNSIGNED_INT_10_10_10_2:      return sizeof(type_uint_10_10_10_2);
            case AMGL_UNSIGNED_INT_2_10_10_10_REV:  return sizeof(type_uint_2_10_10_10_rev);
            case AMGL_UNSIGNED_BYTE_3_3_2:          return sizeof(type_ubyte_3_3_2);
            case AMGL_UNSIGNED_BYTE_2_3_3_REV:      return sizeof(type_ubyte_2_3_3_rev);
            case AMGL_UNSIGNED_SHORT_5_6_5:         return sizeof(type_ushort_5_6_5);
            case AMGL_UNSIGNED_SHORT_5_6_5_REV:     return sizeof(type_ushort_5_6_5_rev);
            case AMGL_UNSIGNED_SHORT_4_4_4_4:       return sizeof(type_ushort_4_4_4_4);
            case AMGL_UNSIGNED_SHORT_4_4_4_4_REV:   return sizeof(type_ushort_4_4_4_4_rev);
            case AMGL_UNSIGNED_SHORT_5_5_5_1:       return sizeof(type_ushort_5_5_5_1);
            case AMGL_UNSIGNED_SHORT_1_5_5_5_REV:   return sizeof(type_ushort_1_5_5_5_rev);
            case AMGL_UNSIGNED_INT_8_8_8_8:         return sizeof(type_uint_8_8_8_8);
            case AMGL_UNSIGNED_INT_8_8_8_8_REV:     return sizeof(type_uint_8_8_8_8_rev);
        }

        return 0u;
    }
}