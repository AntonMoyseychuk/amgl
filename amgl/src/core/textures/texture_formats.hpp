#pragma once
#include "core/core.hpp"

#include <cstdint>

namespace amgl
{
    template <typename type, size_t r_bits>
    AM_PACKED_STRUCT_BEGIN struct fmt_r_t
    {
        constexpr fmt_r_t() : r(0) {}
        constexpr explicit fmt_r_t(type r) : r(r) {}

        static constexpr size_t R_BITS_COUNT = r_bits;

        type r : r_bits;
    } AM_PACKED_STRUCT_END;

    template <typename type, size_t r_bits, size_t g_bits>
    AM_PACKED_STRUCT_BEGIN struct fmt_rg_t
    {
        constexpr fmt_rg_t() : r(0), g(0) {}
        constexpr fmt_rg_t(type r, type g) : r(r), g(g) {}

        static constexpr size_t R_BITS_COUNT = r_bits;
        static constexpr size_t G_BITS_COUNT = g_bits;

        type r : r_bits;
        type g : g_bits;
    } AM_PACKED_STRUCT_END;

    template <typename type, size_t r_bits, size_t g_bits, size_t b_bits, size_t dummy_bits>
    AM_PACKED_STRUCT_BEGIN struct fmt_rgb_t
    {
        constexpr fmt_rgb_t() : r(0), g(0), b(0) {}
        constexpr fmt_rgb_t(type r, type g, type b) : r(r), g(g), b(b) {}

        static constexpr size_t R_BITS_COUNT = r_bits;
        static constexpr size_t G_BITS_COUNT = g_bits;
        static constexpr size_t B_BITS_COUNT = b_bits;
        static constexpr size_t DUMMY_BITS_COUNT = dummy_bits;

        type r      : r_bits;
        type g      : g_bits;
        type b      : b_bits;
        type        : dummy_bits;
    } AM_PACKED_STRUCT_END;

    template <typename type, size_t b_bits, size_t g_bits, size_t r_bits, size_t dummy_bits>
    AM_PACKED_STRUCT_BEGIN struct fmt_bgr_t
    {
        constexpr fmt_bgr_t() : b(0), g(0), r(0) {}
        constexpr fmt_bgr_t(type b, type g, type r) : b(b), g(g), r(r) {}

        static constexpr size_t R_BITS_COUNT        = r_bits;
        static constexpr size_t G_BITS_COUNT        = g_bits;
        static constexpr size_t B_BITS_COUNT        = b_bits;
        static constexpr size_t DUMMY_BITS_COUNT    = dummy_bits;

        type b      : b_bits;
        type g      : g_bits;
        type r      : r_bits;
        type        : dummy_bits;
    } AM_PACKED_STRUCT_END;

    template <typename type, size_t r_bits, size_t g_bits, size_t b_bits, size_t a_bits>
    AM_PACKED_STRUCT_BEGIN struct fmt_rgba_t
    {
        constexpr fmt_rgba_t() : r(0), g(0), b(0), a(0) {}
        constexpr fmt_rgba_t(type r, type g, type b, type a) : r(r), g(g), b(b), a(a) {}

        static constexpr size_t R_BITS_COUNT = r_bits;
        static constexpr size_t G_BITS_COUNT = g_bits;
        static constexpr size_t B_BITS_COUNT = b_bits;
        static constexpr size_t A_BITS_COUNT = a_bits;

        type r : r_bits;
        type g : g_bits;
        type b : b_bits;
        type a : a_bits;
    } AM_PACKED_STRUCT_END;

    template <typename type, size_t b_bits, size_t g_bits, size_t r_bits, size_t a_bits>
    AM_PACKED_STRUCT_BEGIN struct fmt_bgra_t
    {
        constexpr fmt_bgra_t() : b(0), g(0), r(0), a(0) {}
        constexpr fmt_bgra_t(type b, type g, type r, type a) : b(b), g(g), r(r), a(a) {}

        static constexpr size_t R_BITS_COUNT = r_bits;
        static constexpr size_t G_BITS_COUNT = g_bits;
        static constexpr size_t B_BITS_COUNT = b_bits;
        static constexpr size_t A_BITS_COUNT = a_bits;

        type b : b_bits;
        type g : g_bits;
        type r : r_bits;
        type a : a_bits;
    } AM_PACKED_STRUCT_END;

    template <typename type, size_t stencil_bits>
    AM_PACKED_STRUCT_BEGIN struct fmt_stencil_index_t
    {
        constexpr fmt_stencil_index_t() : stencil(0) {}
        constexpr fmt_stencil_index_t(type stencil) : stencil(stencil) {}

        static constexpr size_t STENCIL_BITS_COUNT = stencil_bits;

        type stencil : stencil_bits;
    } AM_PACKED_STRUCT_END;

    template <typename type, size_t depth_bits>
    AM_PACKED_STRUCT_BEGIN struct fmt_depth_component_t
    {
        constexpr fmt_depth_component_t() : depth(0) {}
        constexpr fmt_depth_component_t(type depth) : depth(depth) {}

        static constexpr size_t DEPTH_BITS_COUNT = depth_bits;

        type depth : depth_bits;
    } AM_PACKED_STRUCT_END;

    template <typename depth_type, size_t depth_bits, typename stencil_type, size_t stencil_bits>
    AM_PACKED_STRUCT_BEGIN struct fmt_depth_stencil_t : fmt_depth_component_t<depth_type, depth_bits>, fmt_stencil_index_t<stencil_type, stencil_bits>
    {
    } AM_PACKED_STRUCT_END;

    using fmt_red               = fmt_r_t<uint8_t, 8>;
    using fmt_red_integer       = fmt_red;
    using fmt_rg                = fmt_rg_t<uint8_t, 8, 8>;
    using fmt_rg_integer        = fmt_rg;
    using fmt_rgb               = fmt_rgb_t<uint8_t, 8, 8, 8, 8>;
    using fmt_rgb_integer       = fmt_rgb;
    using fmt_rgba              = fmt_rgba_t<uint8_t, 8, 8, 8, 8>;
    using fmt_rgba_integer      = fmt_rgba;
    using fmt_bgr               = fmt_bgr_t<uint8_t, 8, 8, 8, 8>;
    using fmt_bgr_integer       = fmt_bgr;
    using fmt_bgra              = fmt_bgra_t<uint8_t, 8, 8, 8, 8>;
    using fmt_bgra_integer      = fmt_bgra;

    using fmt_stencil_index     = fmt_stencil_index_t<uint8_t, 8>;
    
    using fmt_depth_component   = fmt_depth_component_t<uint8_t, 8>;
    using fmt_depth_component16 = fmt_depth_component_t<uint16_t, 16>;
    using fmt_depth_component24 = fmt_depth_component_t<uint32_t, 24>;
    using fmt_depth_component32 = fmt_depth_component_t<uint32_t, 32>;
    
    using fmt_depth_stencil     = fmt_depth_stencil_t<uint8_t, 8, uint8_t, 8>;

    using fmt_srgb              = fmt_rgb;
    using fmt_srgb_alpha        = fmt_rgba;

    using fmt_r3_g3_b2          = fmt_rgb_t<uint8_t, 3, 3, 2, 0>;
    
    using fmt_r8                = fmt_r_t<uint8_t, 8>;
    using fmt_r8_snorm          = fmt_r_t<int8_t, 8>;
    using fmt_r16               = fmt_r_t<uint16_t, 16>;
    using fmt_r16_snorm         = fmt_r_t<int16_t, 16>;
    using fmt_rg8               = fmt_rg_t<uint8_t, 8, 8>;
    using fmt_rg8_snorm         = fmt_rg_t<int8_t, 8, 8>;
    using fmt_rg16              = fmt_rg_t<uint16_t, 16, 16>;
    using fmt_rg16_snorm        = fmt_rg_t<int16_t, 16, 16>;
    using fmt_rgb8              = fmt_rgb_t<uint8_t, 8, 8, 8, 8>;
    using fmt_rgb8_snorm        = fmt_rgb_t<int8_t, 8, 8, 8, 8>;
    using fmt_rgb10             = fmt_rgb_t<uint32_t, 10, 10, 10, 2>;
    using fmt_rgb16             = fmt_rgb_t<uint16_t, 16, 16, 16, 16>;
    using fmt_rgb16_snorm       = fmt_rgb_t<int16_t, 16, 16, 16, 16>;
    using fmt_rgba2             = fmt_rgba_t<uint8_t, 2, 2, 2, 2>;
    using fmt_rgba4             = fmt_rgba_t<uint8_t, 4, 4, 4, 4>;
    using fmt_rgb5_a1           = fmt_rgba_t<uint16_t, 5, 5, 5, 1>;
    using fmt_rgba8             = fmt_rgba_t<uint8_t, 8, 8, 8, 8>;
    using fmt_rgba8_snorm       = fmt_rgba_t<int8_t, 8, 8, 8, 8>;
    using fmt_rgb10_a2          = fmt_rgba_t<uint32_t, 10, 10, 10, 2>;
    using fmt_rgb10_a2ui        = fmt_rgb10_a2;
    using fmt_rgba12            = fmt_rgba_t<uint16_t, 12, 12, 12, 12>;
    using fmt_rgba16            = fmt_rgba_t<uint16_t, 16, 16, 16, 16>;
    using fmt_srgb8             = fmt_rgb8;
    using fmt_srgb8_alpha8      = fmt_rgba8;


    constexpr size_t s = sizeof(fmt_rgb10);

    // struct fmt_red
    // {
    //     uint8_t r = 0;
    // };
    // struct fmt_red_integer : fmt_red
    // {
    // };
    // struct fmt_rg
    // {
    //     uint8_t r = 0;
    //     uint8_t g = 0;
    // };
    // struct fmt_rg_integer : fmt_rg
    // {
    // };
    // struct fmt_rgb
    // {
    //     uint8_t r = 0;
    //     uint8_t g = 0;
    //     uint8_t b = 0;
    //     uint8_t dummy = 0;
    // };
    // struct fmt_rgb_integer : fmt_rgb
    // {
    // };
    // struct fmt_rgba
    // {
    //     uint8_t r = 0;
    //     uint8_t g = 0;
    //     uint8_t b = 0;
    //     uint8_t a = 0;
    // };
    // struct fmt_rgba_integer : fmt_rgba
    // {
    // };
    // struct fmt_bgr
    // {
    //     uint8_t b = 0;
    //     uint8_t g = 0;
    //     uint8_t r = 0;
    //     uint8_t dummy = 0;
    // };
    // struct fmt_bgr_integer : fmt_bgr
    // {
    // };
    // struct fmt_bgra
    // {
    //     uint8_t b = 0;
    //     uint8_t g = 0;
    //     uint8_t r = 0;
    //     uint8_t a = 0;
    // };
    // struct fmt_bgra_integer : fmt_bgra
    // {
    // };
    // struct fmt_srgb : fmt_rgb
    // {
    // };
    // struct fmt_srgb_alpha : fmt_rgba
    // {
    // };
    // struct fmt_depth_component16
    // {
    //     uint16_t depth = 0;
    // };
    // struct fmt_depth_component24
    // {
    //     constexpr fmt_depth_component24() : depth(0), dummy(0) {}
    //     uint32_t depth : 24;
    //     uint32_t dummy : 8;
    // };
    // struct fmt_depth_component32
    // {
    //     uint32_t depth = 0;
    // };
    // struct fmt_r8
    // {
    //     uint8_t r = 0;
    // };
    // struct fmt_r8_snorm
    // {
    //     int8_t r = 0;
    // };
    // struct fmt_r16
    // {
    //     uint16_t r = 0;
    // };
    // struct fmt_r16_snorm
    // {
    //     int16_t r = 0;
    // };
    // struct fmt_rg8
    // {
    //     uint8_t r = 0;
    //     uint8_t g = 0;
    // };
    // struct fmt_rg8_snorm
    // {
    //     int8_t r = 0;
    //     int8_t g = 0;
    // };
    // struct fmt_rg16
    // {
    //     uint16_t r = 0;
    //     uint16_t g = 0;
    // };
    // struct fmt_rg16_snorm
    // {
    //     int16_t r = 0;
    //     int16_t g = 0;
    // };
    // struct fmt_r3_g3_b2
    // {
    //     constexpr fmt_r3_g3_b2() : r(0), g(0), b(3) {}
    //     uint8_t r : 3;
    //     uint8_t g : 3;
    //     uint8_t b : 2;
    //     uint8_t : 0;
    // };
    // struct fmt_rgb8
    // {
    //     uint8_t r = 0;
    //     uint8_t g = 0;
    //     uint8_t b = 0;
    // };
    // struct fmt_rgb8_snorm
    // {
    //     int8_t r = 0;
    //     int8_t g = 0;
    //     int8_t b = 0;
    // };


    //     AMGL_R16F,                                                                      \
    //     AMGL_RG16F,                                                                     \
    //     AMGL_RGB16F,                                                                    \
    //     AMGL_RGBA16F,                                                                   \
    //     AMGL_R32F,                                                                      \
    //     AMGL_RG32F,                                                                     \
    //     AMGL_RGB32F,                                                                    \
    //     AMGL_RGBA32F,                                                                   \
    //     AMGL_R11F_G11F_B10F,                                                            \
    //     AMGL_R8I,                                                                       \
    //     AMGL_R8UI,                                                                      \
    //     AMGL_R16I,                                                                      \
    //     AMGL_R16UI,                                                                     \
    //     AMGL_R32I,                                                                      \
    //     AMGL_R32UI,                                                                     \
    //     AMGL_RG8I,                                                                      \
    //     AMGL_RG8UI,                                                                     \
    //     AMGL_RG16I,                                                                     \
    //     AMGL_RG16UI,                                                                    \
    //     AMGL_RG32I,                                                                     \
    //     AMGL_RG32UI,                                                                    \
    //     AMGL_RGB8I,                                                                     \
    //     AMGL_RGB8UI,                                                                    \
    //     AMGL_RGB16I,                                                                    \
    //     AMGL_RGB16UI,                                                                   \
    //     AMGL_RGB32I,                                                                    \
    //     AMGL_RGB32UI,                                                                   \
    //     AMGL_RGBA8I,                                                                    \
    //     AMGL_RGBA8UI,                                                                   \
    //     AMGL_RGBA16I,                                                                   \
    //     AMGL_RGBA16UI,                                                                  \
    //     AMGL_RGBA32I,                                                                   \
    //     AMGL_RGBA32UI
}