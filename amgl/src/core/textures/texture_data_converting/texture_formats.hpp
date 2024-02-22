#pragma once
#include "amgl/amgl.hpp"

#include "core/core.hpp"
#include "half/half.hpp"

#include "core/math/common.hpp"

#include <cstdint>
#include <type_traits>

namespace amgl
{
    #define TEXTURE_FORMATS                                                             \
        AMGL_RED,                                                                       \
        AMGL_RG,                                                                        \
        AMGL_RGB,                                                                       \
        AMGL_BGR,                                                                       \
        AMGL_RGBA,                                                                      \
        AMGL_BGRA,                                                                      \
        AMGL_RED_INTEGER,                                                               \
        AMGL_RG_INTEGER,                                                                \
        AMGL_RGB_INTEGER,                                                               \
        AMGL_BGR_INTEGER,                                                               \
        AMGL_RGBA_INTEGER,                                                              \
        AMGL_BGRA_INTEGER,                                                              \
        AMGL_STENCIL_INDEX,                                                             \
        AMGL_DEPTH_COMPONENT,                                                           \
        AMGL_DEPTH_STENCIL


    #define TEXTURE_BASE_INTERNAL_FORMATS                                               \
        AMGL_RED,                                                                       \
        AMGL_RG,                                                                        \
        AMGL_RGB,                                                                       \
        AMGL_RGBA,                                                                      \
        AMGL_DEPTH_COMPONENT,                                                           \
        AMGL_DEPTH_STENCIL,                                                             \
        AMGL_SRGB,                                                                      \
        AMGL_SRGB_ALPHA

    #define TEXTURE_SIZED_INTEGRAL_INTERNAL_FORMATS                                     \
        AMGL_DEPTH_COMPONENT16,                                                         \
        AMGL_DEPTH_COMPONENT24,                                                         \
        AMGL_DEPTH_COMPONENT32,                                                         \
        AMGL_R8,                                                                        \
        AMGL_R8_SNORM,                                                                  \
        AMGL_R16,                                                                       \
        AMGL_R16_SNORM,                                                                 \
        AMGL_RG8,                                                                       \
        AMGL_RG8_SNORM,                                                                 \
        AMGL_RG16,                                                                      \
        AMGL_RG16_SNORM,                                                                \
        AMGL_R3_G3_B2,                                                                  \
        AMGL_RGB8,                                                                      \
        AMGL_RGB8_SNORM,                                                                \
        AMGL_RGB10,                                                                     \
        AMGL_RGB16,                                                                     \
        AMGL_RGB16_SNORM,                                                               \
        AMGL_RGBA2,                                                                     \
        AMGL_RGBA4,                                                                     \
        AMGL_RGB5_A1,                                                                   \
        AMGL_RGBA8,                                                                     \
        AMGL_RGBA8_SNORM,                                                               \
        AMGL_RGB10_A2,                                                                  \
        AMGL_RGB10_A2UI,                                                                \
        AMGL_RGBA12,                                                                    \
        AMGL_RGBA16,                                                                    \
        AMGL_SRGB8,                                                                     \
        AMGL_SRGB8_ALPHA8,                                                              \
        AMGL_R8I,                                                                       \
        AMGL_R8UI,                                                                      \
        AMGL_R16I,                                                                      \
        AMGL_R16UI,                                                                     \
        AMGL_R32I,                                                                      \
        AMGL_R32UI,                                                                     \
        AMGL_RG8I,                                                                      \
        AMGL_RG8UI,                                                                     \
        AMGL_RG16I,                                                                     \
        AMGL_RG16UI,                                                                    \
        AMGL_RG32I,                                                                     \
        AMGL_RG32UI,                                                                    \
        AMGL_RGB8I,                                                                     \
        AMGL_RGB8UI,                                                                    \
        AMGL_RGB16I,                                                                    \
        AMGL_RGB16UI,                                                                   \
        AMGL_RGB32I,                                                                    \
        AMGL_RGB32UI,                                                                   \
        AMGL_RGBA8I,                                                                    \
        AMGL_RGBA8UI,                                                                   \
        AMGL_RGBA16I,                                                                   \
        AMGL_RGBA16UI,                                                                  \
        AMGL_RGBA32I,                                                                   \
        AMGL_RGBA32UI,                                                                  \
        AMGL_R11F_G11F_B10F
    
    #define TEXTURE_SIZED_FLOATING_POINT_INTERNAL_FORMATS                               \
        AMGL_R16F,                                                                      \
        AMGL_RG16F,                                                                     \
        AMGL_RGB16F,                                                                    \
        AMGL_RGBA16F,                                                                   \
        AMGL_R32F,                                                                      \
        AMGL_RG32F,                                                                     \
        AMGL_RGB32F,                                                                    \
        AMGL_RGBA32F
        

    #define TEXTURE_SIZED_INTERNAL_FORMATS                                              \
        TEXTURE_SIZED_INTEGRAL_INTERNAL_FORMATS,                                        \
        TEXTURE_SIZED_FLOATING_POINT_INTERNAL_FORMATS


    #define TEXTURE_INTERNAL_FORMATS                                                    \
        TEXTURE_BASE_INTERNAL_FORMATS, TEXTURE_SIZED_INTERNAL_FORMATS


    template <typename type, size_t r_bits, typename = std::enable_if_t<std::is_integral_v<type>>>
    AM_PACKED_STRUCT_BEGIN
    struct fmt_r_t
    {
        using value_type = type;

        constexpr fmt_r_t() : r(0) {}
        constexpr explicit fmt_r_t(type r) : r(r) {}

        static constexpr size_t R_BITS_COUNT = r_bits;

        static inline constexpr size_t r_max() noexcept { return static_cast<size_t>(math::pow(2, r_bits)) - 1u; }
        static inline constexpr size_t r_min() noexcept { return std::numeric_limits<type>::lowest(); }

        type r : r_bits;
    }
    AM_PACKED_STRUCT_END


    template <typename type, size_t r_bits, size_t g_bits, typename = std::enable_if_t<std::is_integral_v<type>>>
    AM_PACKED_STRUCT_BEGIN 
    struct fmt_rg_t
    {
        using value_type = type;

        constexpr fmt_rg_t() : r(0), g(0) {}
        constexpr fmt_rg_t(type r, type g) : r(r), g(g) {}

        static constexpr size_t R_BITS_COUNT = r_bits;
        static constexpr size_t G_BITS_COUNT = g_bits;

        static inline constexpr size_t r_max() noexcept { return static_cast<size_t>(math::pow(2, r_bits)) - 1u; }
        static inline constexpr size_t g_max() noexcept { return static_cast<size_t>(math::pow(2, g_bits)) - 1u; }
        static inline constexpr size_t r_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t g_min() noexcept { return std::numeric_limits<type>::lowest(); }

        type r : r_bits;
        type g : g_bits;
    }
    AM_PACKED_STRUCT_END


    template <typename type, size_t r_bits, size_t g_bits, size_t b_bits, size_t dummy_bits, typename = std::enable_if_t<std::is_integral_v<type>>>
    AM_PACKED_STRUCT_BEGIN
    struct fmt_rgb_t
    {
        using value_type = type;

        constexpr fmt_rgb_t() : r(0), g(0), b(0) {}
        constexpr fmt_rgb_t(type r, type g, type b) : r(r), g(g), b(b) {}
    
        static constexpr size_t R_BITS_COUNT = r_bits;
        static constexpr size_t G_BITS_COUNT = g_bits;
        static constexpr size_t B_BITS_COUNT = b_bits;
        static constexpr size_t DUMMY_BITS_COUNT = dummy_bits;
    
        static inline constexpr size_t r_max() noexcept { return static_cast<size_t>(math::pow(2, r_bits)) - 1u; }
        static inline constexpr size_t g_max() noexcept { return static_cast<size_t>(math::pow(2, g_bits)) - 1u; }
        static inline constexpr size_t b_max() noexcept { return static_cast<size_t>(math::pow(2, b_bits)) - 1u; }
        static inline constexpr size_t r_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t g_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t b_min() noexcept { return std::numeric_limits<type>::lowest(); }

        type r      : r_bits;
        type g      : g_bits;
        type b      : b_bits;
        type        : dummy_bits;
    } 
    AM_PACKED_STRUCT_END


    template <typename type, size_t b_bits, size_t g_bits, size_t r_bits, size_t dummy_bits, typename = std::enable_if_t<std::is_integral_v<type>>>
    AM_PACKED_STRUCT_BEGIN 
    struct fmt_bgr_t
    {
        using value_type = type;

        constexpr fmt_bgr_t() : b(0), g(0), r(0) {}
        constexpr fmt_bgr_t(type b, type g, type r) : b(b), g(g), r(r) {}
    
        static constexpr size_t R_BITS_COUNT        = r_bits;
        static constexpr size_t G_BITS_COUNT        = g_bits;
        static constexpr size_t B_BITS_COUNT        = b_bits;
        static constexpr size_t DUMMY_BITS_COUNT    = dummy_bits;
    
        static inline constexpr size_t r_max() noexcept { return static_cast<size_t>(math::pow(2, r_bits)) - 1u; }
        static inline constexpr size_t g_max() noexcept { return static_cast<size_t>(math::pow(2, g_bits)) - 1u; }
        static inline constexpr size_t b_max() noexcept { return static_cast<size_t>(math::pow(2, b_bits)) - 1u; }
        static inline constexpr size_t r_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t g_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t b_min() noexcept { return std::numeric_limits<type>::lowest(); }

        type b      : b_bits;
        type g      : g_bits;
        type r      : r_bits;
        type        : dummy_bits;
    }
    AM_PACKED_STRUCT_END


    template <typename type, size_t r_bits, size_t g_bits, size_t b_bits, size_t a_bits, typename = std::enable_if_t<std::is_integral_v<type>>>
    AM_PACKED_STRUCT_BEGIN
    struct fmt_rgba_t
    {
        using value_type = type;

        constexpr fmt_rgba_t() : r(0), g(0), b(0), a(0) {}
        constexpr fmt_rgba_t(type r, type g, type b, type a) : r(r), g(g), b(b), a(a) {}

        static constexpr size_t R_BITS_COUNT = r_bits;
        static constexpr size_t G_BITS_COUNT = g_bits;
        static constexpr size_t B_BITS_COUNT = b_bits;
        static constexpr size_t A_BITS_COUNT = a_bits;

        static inline constexpr size_t r_max() noexcept { return static_cast<size_t>(math::pow(2, r_bits)) - 1u; }
        static inline constexpr size_t g_max() noexcept { return static_cast<size_t>(math::pow(2, g_bits)) - 1u; }
        static inline constexpr size_t b_max() noexcept { return static_cast<size_t>(math::pow(2, b_bits)) - 1u; }
        static inline constexpr size_t a_max() noexcept { return static_cast<size_t>(math::pow(2, a_bits)) - 1u; }
        static inline constexpr size_t r_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t g_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t b_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t a_min() noexcept { return std::numeric_limits<type>::lowest(); }

        type r : r_bits;
        type g : g_bits;
        type b : b_bits;
        type a : a_bits;
    }
    AM_PACKED_STRUCT_END


    template <typename type, size_t b_bits, size_t g_bits, size_t r_bits, size_t a_bits, typename = std::enable_if_t<std::is_integral_v<type>>>
    AM_PACKED_STRUCT_BEGIN
    struct fmt_bgra_t
    {
        using value_type = type;

        constexpr fmt_bgra_t() : b(0), g(0), r(0), a(0) {}
        constexpr fmt_bgra_t(type b, type g, type r, type a) : b(b), g(g), r(r), a(a) {}

        static constexpr size_t R_BITS_COUNT = r_bits;
        static constexpr size_t G_BITS_COUNT = g_bits;
        static constexpr size_t B_BITS_COUNT = b_bits;
        static constexpr size_t A_BITS_COUNT = a_bits;

        static inline constexpr size_t r_max() noexcept { return static_cast<size_t>(math::pow(2, r_bits)) - 1u; }
        static inline constexpr size_t g_max() noexcept { return static_cast<size_t>(math::pow(2, g_bits)) - 1u; }
        static inline constexpr size_t b_max() noexcept { return static_cast<size_t>(math::pow(2, b_bits)) - 1u; }
        static inline constexpr size_t a_max() noexcept { return static_cast<size_t>(math::pow(2, a_bits)) - 1u; }
        static inline constexpr size_t r_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t g_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t b_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t a_min() noexcept { return std::numeric_limits<type>::lowest(); }

        type b : b_bits;
        type g : g_bits;
        type r : r_bits;
        type a : a_bits;
    }
    AM_PACKED_STRUCT_END


    template <typename type, size_t stencil_bits, typename = std::enable_if_t<std::is_integral_v<type>>>
    AM_PACKED_STRUCT_BEGIN 
    struct fmt_stencil_index_t
    {
        using value_type = type;

        constexpr fmt_stencil_index_t() : stencil(0) {}
        constexpr fmt_stencil_index_t(type stencil) : stencil(stencil) {}

        static constexpr size_t STENCIL_BITS_COUNT = stencil_bits;

        static inline constexpr size_t stencil_max() noexcept { return static_cast<size_t>(math::pow(2, stencil_bits)) - 1u; }
        static inline constexpr size_t stencil_min() noexcept { return std::numeric_limits<type>::lowest(); }

        type stencil : stencil_bits;
    }
    AM_PACKED_STRUCT_END


    template <typename type, size_t depth_bits, typename = std::enable_if_t<std::is_integral_v<type>>>
    AM_PACKED_STRUCT_BEGIN
    struct fmt_depth_component_t
    {
        using value_type = type;

        constexpr fmt_depth_component_t() : depth(0) {}
        constexpr fmt_depth_component_t(type depth) : depth(depth) {}

        static constexpr size_t DEPTH_BITS_COUNT = depth_bits;

        static inline constexpr size_t depth_max() noexcept { return static_cast<size_t>(math::pow(2, depth_bits)) - 1u; }
        static inline constexpr size_t depth_min() noexcept { return std::numeric_limits<type>::lowest(); }

        type depth : depth_bits;
    }
    AM_PACKED_STRUCT_END


    template <typename type, size_t depth_bits, size_t stencil_bits, typename = std::enable_if_t<std::is_integral_v<type>>>
    AM_PACKED_STRUCT_BEGIN
    struct fmt_depth_stencil_t
    {
        using value_type = type;

        constexpr fmt_depth_stencil_t() : depth(0), stencil(0) {}
        constexpr fmt_depth_stencil_t(type depth, type stencil) : depth(depth), stencil(stencil) {}

        static constexpr size_t DEPTH_BITS_COUNT = depth_bits;
        static constexpr size_t STENCIL_BITS_COUNT = stencil_bits;

        static inline constexpr size_t depth_max() noexcept { return static_cast<size_t>(math::pow(2, depth_bits)) - 1u; }
        static inline constexpr size_t depth_min() noexcept { return std::numeric_limits<type>::lowest(); }
        static inline constexpr size_t stencil_max() noexcept { return static_cast<size_t>(math::pow(2, stencil_bits)) - 1u; }
        static inline constexpr size_t stencil_min() noexcept { return std::numeric_limits<type>::lowest(); }

        type depth : depth_bits;
        type stencil : stencil_bits;
    }
    AM_PACKED_STRUCT_END

    struct fmt_r16f_t
    {
        using value_type = half_float::half;

        fmt_r16f_t()
            : r(half_float::half_cast<half_float::half>(0.0f)) {}

        fmt_r16f_t(float r)
            : r(half_float::half_cast<half_float::half>(r)) {}

        fmt_r16f_t(half_float::half r)
            : r(r) {}

        static inline const half_float::half r_max() noexcept 
        { 
            static const half_float::half value = std::numeric_limits<half_float::half>::max();
            return value;
        }
        static inline const half_float::half r_min() noexcept
        {
            static const half_float::half value = std::numeric_limits<half_float::half>::lowest();
            return value;
        }

        half_float::half r;
    };


    struct fmt_rg16f_t : fmt_r16f_t
    {
        fmt_rg16f_t() : fmt_r16f_t(), 
            g(half_float::half_cast<half_float::half>(0.0f)) {}

        fmt_rg16f_t(float r, float g) : fmt_r16f_t(r), 
            g(half_float::half_cast<half_float::half>(g)) {}

        fmt_rg16f_t(half_float::half r, half_float::half g)
            : fmt_r16f_t(r), g(g) {}

        static inline const half_float::half g_max() noexcept { return r_max(); }
        static inline const half_float::half g_min() noexcept { return r_min(); }

        half_float::half g;
    };


    struct fmt_rgba16f_t : fmt_rg16f_t
    {
        fmt_rgba16f_t() : fmt_rg16f_t(0.0f, 0.0f),
            b(half_float::half_cast<half_float::half>(0.0f)),
            a(half_float::half_cast<half_float::half>(0.0f)) {}

        fmt_rgba16f_t(float r, float g, float b, float a) : fmt_rg16f_t(r, g),
            b(half_float::half_cast<half_float::half>(b)),
            a(half_float::half_cast<half_float::half>(a)) {}
        
        fmt_rgba16f_t(half_float::half r, half_float::half g, half_float::half b, half_float::half a) 
            : fmt_rg16f_t(r, g), b(b), a(a) {}

        static inline const half_float::half b_max() noexcept { return r_max(); }
        static inline const half_float::half b_min() noexcept { return r_min(); }
        static inline const half_float::half a_max() noexcept { return r_max(); }
        static inline const half_float::half a_min() noexcept { return r_min(); }

        half_float::half b;
        half_float::half a;
    };


    struct fmt_r32f_t
    {
        using value_type = float;

        constexpr fmt_r32f_t() : r(0.0f) {}
        constexpr fmt_r32f_t(float r) : r(r) {}

        static inline constexpr float r_max() noexcept { return std::numeric_limits<float>::max(); }
        static inline constexpr float r_min() noexcept { return std::numeric_limits<float>::lowest(); }

        float r;
    };


    struct fmt_rg32f_t : fmt_r32f_t
    {
        constexpr fmt_rg32f_t() : fmt_r32f_t(0.0f), g(0.0f) {}
        constexpr fmt_rg32f_t(float r, float g) : fmt_r32f_t(r), g(g) {}

        static inline constexpr float g_max() noexcept { return r_max(); }
        static inline constexpr float g_min() noexcept { return r_min(); }

        float g;
    };


    struct fmt_rgba32f_t : fmt_rg32f_t
    {
        constexpr fmt_rgba32f_t() : fmt_rg32f_t(0.0f, 0.0f), b(0.0f), a(0.0f) {}
        constexpr fmt_rgba32f_t(float r, float g, float b, float a) : fmt_rg32f_t(0.0f, 0.0f), b(b), a(a) {}

        static inline constexpr float b_max() noexcept { return r_max(); }
        static inline constexpr float b_min() noexcept { return r_min(); }
        static inline constexpr float a_max() noexcept { return r_max(); }
        static inline constexpr float a_min() noexcept { return r_min(); }

        float b, a;
    };


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
    
    using fmt_depth_stencil     = fmt_depth_stencil_t<uint8_t, 8, 8>;

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
    using fmt_rgba12            = fmt_rgba_t<uint64_t, 12, 12, 12, 28>;
    using fmt_rgba16            = fmt_rgba_t<uint16_t, 16, 16, 16, 16>;
    using fmt_srgb8             = fmt_rgb8;
    using fmt_srgb8_alpha8      = fmt_rgba8;

    using fmt_r16f              = fmt_r16f_t;
    using fmt_rg16f             = fmt_rg16f_t;
    using fmt_rgb16f            = fmt_rgba16f_t;
    using fmt_rgba16f           = fmt_rgba16f_t;
    using fmt_r32f              = fmt_r32f_t;
    using fmt_rg32f             = fmt_rg32f_t;
    using fmt_rgb32f            = fmt_rgba32f_t;
    using fmt_rgba32f           = fmt_rgba32f_t;
    using fmt_r11f_g11f_b10f    = fmt_rgb_t<uint32_t, 11, 11, 10, 0>;
    using fmt_r8i               = fmt_r_t<int8_t, 8>;
    using fmt_r8ui              = fmt_r_t<uint8_t, 8>;
    using fmt_r16i              = fmt_r_t<int16_t, 16>;
    using fmt_r16ui             = fmt_r_t<uint16_t, 16>;
    using fmt_r32i              = fmt_r_t<int32_t, 32>;
    using fmt_r32ui             = fmt_r_t<uint32_t, 32>;
    using fmt_rg8i              = fmt_rg_t<int8_t, 8, 8>;
    using fmt_rg8ui             = fmt_rg_t<uint8_t, 8, 8>;
    using fmt_rg16i             = fmt_rg_t<int16_t, 16, 16>;
    using fmt_rg16ui            = fmt_rg_t<uint16_t, 16, 16>;
    using fmt_rg32i             = fmt_rg_t<int32_t, 32, 32>;
    using fmt_rg32ui            = fmt_rg_t<uint32_t, 32, 32>;
    using fmt_rgb8i             = fmt_rgb_t<int8_t, 8, 8, 8, 8>;
    using fmt_rgb8ui            = fmt_rgb_t<uint8_t, 8, 8, 8, 8>;
    using fmt_rgb16i            = fmt_rgb_t<int16_t, 16, 16, 16, 16>;
    using fmt_rgb16ui           = fmt_rgb_t<uint16_t, 16, 16, 16, 16>;
    using fmt_rgb32i            = fmt_rgb_t<int32_t, 32, 32, 32, 32>;
    using fmt_rgb32ui           = fmt_rgb_t<uint32_t, 32, 32, 32, 32>;
    using fmt_rgba8i            = fmt_rgba_t<int8_t, 8, 8, 8, 8>;
    using fmt_rgba8ui           = fmt_rgba_t<uint8_t, 8, 8, 8, 8>;
    using fmt_rgba16i           = fmt_rgba_t<int16_t, 16, 16, 16, 16>;
    using fmt_rgba16ui          = fmt_rgba_t<uint16_t, 16, 16, 16, 16>;
    using fmt_rgba32i           = fmt_rgba_t<int32_t, 32, 32, 32, 32>;
    using fmt_rgba32ui          = fmt_rgba_t<uint32_t, 32, 32, 32, 32>;

    
    static_assert(sizeof(fmt_red)               == 1u, "invalid fmt_red size");
    static_assert(sizeof(fmt_red_integer)       == 1u, "invalid fmt_red_integer size");
    static_assert(sizeof(fmt_rg)                == 2u, "invalid fmt_rg size");
    static_assert(sizeof(fmt_rg_integer)        == 2u, "invalid fmt_rg_integer size");
    static_assert(sizeof(fmt_rgb)               == 4u, "invalid fmt_rgb size");
    static_assert(sizeof(fmt_rgb_integer)       == 4u, "invalid fmt_rgb_integer size");
    static_assert(sizeof(fmt_rgba)              == 4u, "invalid fmt_rgba size");
    static_assert(sizeof(fmt_rgba_integer)      == 4u, "invalid fmt_rgba_integer size");
    static_assert(sizeof(fmt_bgr)               == 4u, "invalid fmt_bgr size");
    static_assert(sizeof(fmt_bgr_integer)       == 4u, "invalid fmt_bgr_integer size");
    static_assert(sizeof(fmt_bgra)              == 4u, "invalid fmt_bgra size");
    static_assert(sizeof(fmt_bgra_integer)      == 4u, "invalid fmt_bgra_integer size");

    static_assert(sizeof(fmt_stencil_index)     == 1u, "invalid fmt_stencil_index size");
    static_assert(sizeof(fmt_depth_component)   == 1u, "invalid fmt_depth_component size");
    static_assert(sizeof(fmt_depth_component16) == 2u, "invalid fmt_depth_component16 size");
    static_assert(sizeof(fmt_depth_component24) == 4u, "invalid fmt_depth_component24 size");
    static_assert(sizeof(fmt_depth_component32) == 4u, "invalid fmt_depth_component32 size");
    static_assert(sizeof(fmt_depth_stencil)     == 2u, "invalid fmt_depth_stencil size");
    
    static_assert(sizeof(fmt_srgb)              == 4u, "invalid fmt_srgb size");
    static_assert(sizeof(fmt_srgb_alpha)        == 4u, "invalid fmt_srgb_alpha size");

    static_assert(sizeof(fmt_r3_g3_b2)          == 1u, "invalid fmt_r3_g3_b2 size");

    static_assert(sizeof(fmt_r8)                == 1u, "invalid fmt_r8 size");
    static_assert(sizeof(fmt_r8_snorm)          == 1u, "invalid fmt_r8_snorm size");
    static_assert(sizeof(fmt_r16)               == 2u, "invalid fmt_r16 size");
    static_assert(sizeof(fmt_r16_snorm)         == 2u, "invalid fmt_r16_snorm size");
    static_assert(sizeof(fmt_rg8)               == 2u, "invalid fmt_rg8 size");
    static_assert(sizeof(fmt_rg16)              == 4u, "invalid fmt_rg16 size");
    static_assert(sizeof(fmt_rg16_snorm)        == 4u, "invalid fmt_rg16_snorm size");
    static_assert(sizeof(fmt_rgb8)              == 4u, "invalid fmt_rgb8 size");
    static_assert(sizeof(fmt_rgb8_snorm)        == 4u, "invalid fmt_rgb8_snorm size");
    static_assert(sizeof(fmt_rgb10)             == 4u, "invalid fmt_rgb10 size");
    static_assert(sizeof(fmt_rgb16)             == 8u, "invalid fmt_rgb16 size");
    static_assert(sizeof(fmt_rgb16_snorm)       == 8u, "invalid fmt_rgb16_snorm size");
    static_assert(sizeof(fmt_rgba2)             == 1u, "invalid fmt_rgba2 size");
    static_assert(sizeof(fmt_rgba4)             == 2u, "invalid fmt_rgba4 size");
    static_assert(sizeof(fmt_rgb5_a1)           == 2u, "invalid fmt_rgb5_a1 size");
    static_assert(sizeof(fmt_rgba8)             == 4u, "invalid fmt_rgba8 size");
    static_assert(sizeof(fmt_rgba8_snorm)       == 4u, "invalid fmt_rgba8_snorm size");
    static_assert(sizeof(fmt_rgb10_a2)          == 4u, "invalid fmt_rgb10_a2 size");
    static_assert(sizeof(fmt_rgb10_a2ui)        == 4u, "invalid fmt_rgb10_a2ui size");
    static_assert(sizeof(fmt_rgba12)            == 8u, "invalid fmt_rgba12 size");
    static_assert(sizeof(fmt_rgba16)            == 8u, "invalid fmt_rgba16 size");
    static_assert(sizeof(fmt_srgb8)             == 4u, "invalid fmt_srgb8 size");
    static_assert(sizeof(fmt_srgb8_alpha8)      == 4u, "invalid fmt_srgb8_alpha8 size");
    static_assert(sizeof(fmt_r16f)              == 2u, "invalid fmt_r16f size");
    static_assert(sizeof(fmt_rg16f)             == 4u, "invalid fmt_rg16f size");
    static_assert(sizeof(fmt_rgb16f)            == 8u, "invalid fmt_rgb16f size");
    static_assert(sizeof(fmt_rgba16f)           == 8u, "invalid fmt_rgba16f size");
    static_assert(sizeof(fmt_r32f)              == 4u, "invalid fmt_r32f size");
    static_assert(sizeof(fmt_rg32f)             == 8u, "invalid fmt_rg32f size");
    static_assert(sizeof(fmt_rgb32f)            == 16u, "invalid fmt_rgb32f size");
    static_assert(sizeof(fmt_rgba32f)           == 16u, "invalid fmt_rgba32f size");
    static_assert(sizeof(fmt_r11f_g11f_b10f)    == 4u, "invalid fmt_r11f_g11f_b10f size");
    static_assert(sizeof(fmt_r8i)               == 1u, "invalid fmt_r8i size");
    static_assert(sizeof(fmt_r8ui)              == 1u, "invalid fmt_r8ui size");
    static_assert(sizeof(fmt_r16i)              == 2u, "invalid fmt_r16i size");
    static_assert(sizeof(fmt_r16ui)             == 2u, "invalid fmt_r16ui size");
    static_assert(sizeof(fmt_r32i)              == 4u, "invalid fmt_r32i size");
    static_assert(sizeof(fmt_r32ui)             == 4u, "invalid fmt_r32ui size");
    static_assert(sizeof(fmt_rg8i)              == 2u, "invalid fmt_rg8i size");
    static_assert(sizeof(fmt_rg8ui)             == 2u, "invalid fmt_rg8ui size");
    static_assert(sizeof(fmt_rg16i)             == 4u, "invalid fmt_rg16i size");
    static_assert(sizeof(fmt_rg16ui)            == 4u, "invalid fmt_rg16ui size");
    static_assert(sizeof(fmt_rg32i)             == 8u, "invalid fmt_rg32i size");
    static_assert(sizeof(fmt_rg32ui)            == 8u, "invalid fmt_rg32ui size");
    static_assert(sizeof(fmt_rgb8i)             == 4u, "invalid fmt_rgb8i size");
    static_assert(sizeof(fmt_rgb8ui)            == 4u, "invalid fmt_rgb8ui size");
    static_assert(sizeof(fmt_rgb16i)            == 8u, "invalid fmt_rgb16i size");
    static_assert(sizeof(fmt_rgb16ui)           == 8u, "invalid fmt_rgb16ui size");
    static_assert(sizeof(fmt_rgb32i)            == 16u, "invalid fmt_rgb32i size");
    static_assert(sizeof(fmt_rgb32ui)           == 16u, "invalid fmt_rgb32ui size");
    static_assert(sizeof(fmt_rgba8i)            == 4u, "invalid fmt_rgba8i size");
    static_assert(sizeof(fmt_rgba8ui)           == 4u, "invalid fmt_rgba8ui size");
    static_assert(sizeof(fmt_rgba16i)           == 8u, "invalid fmt_rgba16i size");
    static_assert(sizeof(fmt_rgba16ui)          == 8u, "invalid fmt_rgba16ui size");
    static_assert(sizeof(fmt_rgba32i)           == 16u, "invalid fmt_rgba32i size");
    static_assert(sizeof(fmt_rgba32ui)          == 16u, "invalid fmt_rgba32ui size");


    /// @brief 
    /// @return Components count or 0 if 'format' is invalid
    inline constexpr size_t get_components_count(enum_t format) noexcept
    {
        switch (format) {
            case AMGL_RED:
            case AMGL_DEPTH_COMPONENT:
            case AMGL_DEPTH_STENCIL:
            case AMGL_STENCIL_INDEX:
            case AMGL_RED_INTEGER:
            case AMGL_DEPTH_COMPONENT16:
            case AMGL_DEPTH_COMPONENT24:
            case AMGL_DEPTH_COMPONENT32:
            case AMGL_R8:
            case AMGL_R8_SNORM:
            case AMGL_R16:
            case AMGL_R16_SNORM:
            case AMGL_R16F:
            case AMGL_R32F:
            case AMGL_R8I:
            case AMGL_R8UI:
            case AMGL_R16I:
            case AMGL_R16UI:
            case AMGL_R32I:
            case AMGL_R32UI:
                return 1u;

            case AMGL_RG:
            case AMGL_RG_INTEGER:
            case AMGL_RG8:
            case AMGL_RG8_SNORM:
            case AMGL_RG16:
            case AMGL_RG16_SNORM:
            case AMGL_RG16F:
            case AMGL_RG32F:
            case AMGL_RG8I:
            case AMGL_RG8UI:
            case AMGL_RG16I:
            case AMGL_RG16UI:
            case AMGL_RG32I:
            case AMGL_RG32UI:
                return 2u;

            case AMGL_RGB:
            case AMGL_RGB8:
            case AMGL_RGB16F:
            case AMGL_RGB32F:
            case AMGL_RGB8UI:
            case AMGL_RGB32UI:
            case AMGL_RGB_INTEGER:
            case AMGL_BGR:
            case AMGL_BGR_INTEGER:
            case AMGL_R3_G3_B2:
            case AMGL_RGB8_SNORM:
            case AMGL_RGB10:
            case AMGL_RGB16_SNORM:
            case AMGL_RGBA2:
            case AMGL_SRGB:
            case AMGL_SRGB8:
            case AMGL_R11F_G11F_B10F:
            case AMGL_RGB8I:
            case AMGL_RGB16I:
            case AMGL_RGB16UI:
            case AMGL_RGB32I:
                return 3u;
                
            case AMGL_RGBA:
            case AMGL_RGB5_A1:
            case AMGL_RGBA4:
            case AMGL_RGBA8:
            case AMGL_RGB10_A2:
            case AMGL_RGB10_A2UI:
            case AMGL_RGBA12:
            case AMGL_RGBA16:
            case AMGL_SRGB_ALPHA:
            case AMGL_SRGB8_ALPHA8:
            case AMGL_RGBA16F:
            case AMGL_RGBA32F:
            case AMGL_RGBA8UI:
            case AMGL_RGBA32UI:
            case AMGL_RGBA_INTEGER:
            case AMGL_BGRA:
            case AMGL_BGRA_INTEGER:
            case AMGL_RGBA8_SNORM:
            case AMGL_RGBA8I:
            case AMGL_RGBA16I:
            case AMGL_RGBA16UI:
            case AMGL_RGBA32I:
                return 4u;
        }

        return 0u;
    }


    /// @brief  
    /// @return Pixel size in bytes or 0 if 'internal_format'
    inline constexpr size_t get_bytes_per_pixel(enum_t internal_format) noexcept
    {
        switch(internal_format) {
            case AMGL_RED:                  return sizeof(fmt_red);
            case AMGL_RED_INTEGER:          return sizeof(fmt_red_integer);
            case AMGL_RG:                   return sizeof(fmt_rg);
            case AMGL_RG_INTEGER:           return sizeof(fmt_rg_integer);
            case AMGL_RGB:                  return sizeof(fmt_rgb);
            case AMGL_RGB_INTEGER:          return sizeof(fmt_rgb_integer);
            case AMGL_RGBA:                 return sizeof(fmt_rgba);
            case AMGL_RGBA_INTEGER:         return sizeof(fmt_rgba_integer);
            case AMGL_BGR:                  return sizeof(fmt_bgr);
            case AMGL_BGR_INTEGER:          return sizeof(fmt_bgr_integer);
            case AMGL_BGRA:                 return sizeof(fmt_bgra);
            case AMGL_BGRA_INTEGER:         return sizeof(fmt_bgra_integer);
            case AMGL_STENCIL_INDEX:        return sizeof(fmt_stencil_index);
            case AMGL_DEPTH_COMPONENT:      return sizeof(fmt_depth_component);
            case AMGL_DEPTH_STENCIL:        return sizeof(fmt_depth_stencil);
            case AMGL_SRGB:                 return sizeof(fmt_srgb);
            case AMGL_SRGB_ALPHA:           return sizeof(fmt_srgb_alpha);
            case AMGL_DEPTH_COMPONENT16:    return sizeof(fmt_depth_component16);
            case AMGL_DEPTH_COMPONENT24:    return sizeof(fmt_depth_component24);
            case AMGL_DEPTH_COMPONENT32:    return sizeof(fmt_depth_component32);
            case AMGL_R8:                   return sizeof(fmt_r8);
            case AMGL_R8_SNORM:             return sizeof(fmt_r8_snorm);
            case AMGL_R16:                  return sizeof(fmt_r16);
            case AMGL_R16_SNORM:            return sizeof(fmt_r16_snorm);
            case AMGL_RG8:                  return sizeof(fmt_rg8);
            case AMGL_RG8_SNORM:            return sizeof(fmt_rg8_snorm);
            case AMGL_RG16:                 return sizeof(fmt_rg16);
            case AMGL_RG16_SNORM:           return sizeof(fmt_rg16_snorm);
            case AMGL_R3_G3_B2:             return sizeof(fmt_r3_g3_b2);
            case AMGL_RGB8:                 return sizeof(fmt_rgb8);
            case AMGL_RGB8_SNORM:           return sizeof(fmt_rgb8_snorm);
            case AMGL_RGB16:                return sizeof(fmt_rgb16);
            case AMGL_RGB16_SNORM:          return sizeof(fmt_rgb16_snorm);
            case AMGL_RGBA2:                return sizeof(fmt_rgba2);
            case AMGL_RGBA4:                return sizeof(fmt_rgba4);
            case AMGL_RGB5_A1:              return sizeof(fmt_rgb5_a1);
            case AMGL_RGBA8:                return sizeof(fmt_rgba8);
            case AMGL_RGBA8_SNORM:          return sizeof(fmt_rgba8_snorm);
            case AMGL_RGB10_A2:             return sizeof(fmt_rgb10_a2);
            case AMGL_RGB10_A2UI:           return sizeof(fmt_rgb10_a2ui);
            case AMGL_RGBA12:               return sizeof(fmt_rgba12);
            case AMGL_RGBA16:               return sizeof(fmt_rgba16);
            case AMGL_SRGB8:                return sizeof(fmt_srgb8);
            case AMGL_SRGB8_ALPHA8:         return sizeof(fmt_srgb8_alpha8);
            case AMGL_R16F:                 return sizeof(fmt_r16f);
            case AMGL_RG16F:                return sizeof(fmt_rg16f);
            case AMGL_RGB16F:               return sizeof(fmt_rgb16f);
            case AMGL_RGBA16F:              return sizeof(fmt_rgba16f);
            case AMGL_R32F:                 return sizeof(fmt_r32f);
            case AMGL_RG32F:                return sizeof(fmt_rg32f);
            case AMGL_RGB32F:               return sizeof(fmt_rgb32f);
            case AMGL_RGBA32F:              return sizeof(fmt_rgba32f);
            case AMGL_R11F_G11F_B10F:       return sizeof(fmt_r11f_g11f_b10f);
            case AMGL_R8I:                  return sizeof(fmt_r8i);
            case AMGL_R8UI:                 return sizeof(fmt_r8ui);
            case AMGL_R16I:                 return sizeof(fmt_r16i);
            case AMGL_R16UI:                return sizeof(fmt_r16ui);
            case AMGL_R32I:                 return sizeof(fmt_r32i);
            case AMGL_R32UI:                return sizeof(fmt_r32ui);
            case AMGL_RG8I:                 return sizeof(fmt_rg8i);
            case AMGL_RG8UI:                return sizeof(fmt_rg8ui);
            case AMGL_RG16I:                return sizeof(fmt_rg16i);
            case AMGL_RG16UI:               return sizeof(fmt_rg16ui);
            case AMGL_RG32I:                return sizeof(fmt_rg32i);
            case AMGL_RG32UI:               return sizeof(fmt_rg32ui);
            case AMGL_RGB8I:                return sizeof(fmt_rgb8i);
            case AMGL_RGB8UI:               return sizeof(fmt_rgb8ui);
            case AMGL_RGB16I:               return sizeof(fmt_rgb16i);
            case AMGL_RGB16UI:              return sizeof(fmt_rgb16ui);
            case AMGL_RGB32I:               return sizeof(fmt_rgb32i);
            case AMGL_RGB32UI:              return sizeof(fmt_rgb32ui);
            case AMGL_RGBA8I:               return sizeof(fmt_rgba8i);
            case AMGL_RGBA8UI:              return sizeof(fmt_rgba8ui);
            case AMGL_RGBA16I:              return sizeof(fmt_rgba16i);
            case AMGL_RGBA16UI:             return sizeof(fmt_rgba16ui);
            case AMGL_RGBA32I:              return sizeof(fmt_rgba32i);
            case AMGL_RGBA32UI:             return sizeof(fmt_rgba32ui);
        };

        return 0u;
    }
}