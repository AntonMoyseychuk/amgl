#pragma once
#include "amgl/amgl.hpp"
#include "core/utils/type_traits.hpp"

#include "core/math/common.hpp"


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


    template <size_t bit>
    struct bit_val_wrapper
    {
        static constexpr size_t value = bit;
    };

    template <typename... bits>
    struct pixel_format_base
    {
        constexpr pixel_format_base() = default;

        static constexpr inline size_t TOTAL_BITS_COUNT = math::sum(bits::value...);
        static constexpr inline size_t COMPONENTS_COUNT = sizeof...(bits);
        static constexpr inline size_t BITS_PER_COMPONENT[COMPONENTS_COUNT] = { bits::value... };
    };

    template <typename implicit_t, typename internal_t, size_t... bits>
    struct pixel_format : pixel_format_base<bit_val_wrapper<bits>...>
    {
        AM_STATIC_ASSERT_MSG(sizeof...(bits) < 0u, "invalid pixel components count");
    };

    template <typename implicit_t, typename internal_t, size_t bits0, size_t bits1, size_t bits2, size_t bits3>
    struct pixel_format<implicit_t, internal_t, bits0, bits1, bits2, bits3> 
        : pixel_format_base<bit_val_wrapper<bits0>, bit_val_wrapper<bits1>, bit_val_wrapper<bits2>, bit_val_wrapper<bits3>>
    {
        using base_type = pixel_format_base<bit_val_wrapper<bits0>, bit_val_wrapper<bits1>, bit_val_wrapper<bits2>, bit_val_wrapper<bits3>>;
        using base_type::COMPONENTS_COUNT;
        
        using imlicit_type = implicit_t;
        using internal_type = internal_t;

        constexpr pixel_format(internal_type r, internal_type g, internal_type b, internal_type a) : r(r), g(g), b(b), a(a) {}
        constexpr pixel_format() : pixel_format(0, 0, 0, 0) {}

        void set(size_t index, internal_type value) noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            switch (index) {
                case 0: r = value; break;
                case 1: g = value; break;
                case 2: b = value; break;
                case 3: a = value; break;
            };
        }

        void set_rev(size_t index, internal_type value) noexcept
        {
            set(COMPONENTS_COUNT - 1u - index, value);
        }

        internal_type get(size_t index) const noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            switch (index) {
                case 0: return r;
                case 1: return g;
                case 2: return b;
                case 3: return a;
                default: return (internal_type)0;
            };
        }

        internal_type get_rev(size_t index) const noexcept
        {
            return get(COMPONENTS_COUNT - 1u - index);
        }

        union 
        {
            struct
            {
                internal_type r : bits0;
                internal_type g : bits1;
                internal_type b : bits2;
                internal_type a : bits3;
            };

            struct 
            {
                internal_type a_rev : bits0;
                internal_type b_rev : bits1;
                internal_type g_rev : bits2;
                internal_type r_rev : bits3;
            };
        };
    };

    template <typename implicit_t, typename internal_t, size_t bits0, size_t bits1, size_t bits2>
    struct pixel_format<implicit_t, internal_t, bits0, bits1, bits2> 
        : pixel_format_base<bit_val_wrapper<bits0>, bit_val_wrapper<bits1>, bit_val_wrapper<bits2>>
    {
        using base_type = pixel_format_base<bit_val_wrapper<bits0>, bit_val_wrapper<bits1>, bit_val_wrapper<bits2>>;
        using base_type::COMPONENTS_COUNT;
        
        using imlicit_type = implicit_t;
        using internal_type = internal_t;

        constexpr pixel_format(internal_type r, internal_type g, internal_type b) : r(r), g(g), b(b) {}
        constexpr pixel_format() : pixel_format(0, 0, 0) {}

        void set(size_t index, internal_type value) noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            switch (index) {
                case 0: r = value; break;
                case 1: g = value; break;
                case 2: b = value; break;
            };
        }

        void set_rev(size_t index, internal_type value) noexcept
        {
            set(COMPONENTS_COUNT - 1u - index, value);
        }

        internal_type get(size_t index) const noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            switch (index) {
                case 0: return r;
                case 1: return g;
                case 2: return b;
                default: return (internal_type)0;
            };
        }

        internal_type get_rev(size_t index) const noexcept
        {
            return get(COMPONENTS_COUNT - 1u - index);
        }

        union 
        {
            struct
            {
                internal_type r : bits0;
                internal_type g : bits1;
                internal_type b : bits2;
            };

            struct 
            {
                internal_type b_rev : bits0;
                internal_type g_rev : bits1;
                internal_type r_rev : bits2;
            };
        };
    };

    template <typename implicit_t, typename internal_t, size_t bits0, size_t bits1>
    struct pixel_format<implicit_t, internal_t, bits0, bits1> : pixel_format_base<bit_val_wrapper<bits0>, bit_val_wrapper<bits1>>
    {
        using base_type = pixel_format_base<bit_val_wrapper<bits0>, bit_val_wrapper<bits1>>;
        using base_type::COMPONENTS_COUNT;
        
        using imlicit_type = implicit_t;
        using internal_type = internal_t;

        constexpr pixel_format(internal_type r, internal_type g) : r(r), g(g) {}
        constexpr pixel_format() : pixel_format(0, 0) {}

        void set(size_t index, internal_type value) noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            switch (index) {
                case 0: r = value; break;
                case 1: g = value; break;
            };
        }

        void set_rev(size_t index, internal_type value) noexcept
        {
            set(COMPONENTS_COUNT - 1u - index, value);
        }

        internal_type get(size_t index) const noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            switch (index) {
                case 0: return r;
                case 1: return g;
                default: return (internal_type)0;
            };
        }

        internal_type get_rev(size_t index) const noexcept
        {
            return get(COMPONENTS_COUNT - 1u - index);
        }

        union 
        {
            struct
            {
                internal_type r : bits0;
                internal_type g : bits1;
            };

            struct 
            {
                internal_type g_rev : bits0;
                internal_type r_rev : bits1;
            };

            internal_type packed;
        };
    };

    template <typename implicit_t, typename internal_t, size_t bits0>
    struct pixel_format<implicit_t, internal_t, bits0> : pixel_format_base<bit_val_wrapper<bits0>>
    {
        using base_type = pixel_format_base<bit_val_wrapper<bits0>>;
        using base_type::TOTAL_BITS_COUNT;
        
        using imlicit_type = implicit_t;
        using internal_type = internal_t;

        constexpr pixel_format(internal_type r) : r(r) {}
        constexpr pixel_format() : pixel_format(0) {}

        void set(size_t index, internal_type value) noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            switch (index) {
                case 0: r = value; break;
            };
        }

        void set_rev(size_t index, internal_type value) noexcept
        {
            set(COMPONENTS_COUNT - 1u - index, value);
        }

        internal_type get(size_t index) const noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            switch (index) {
                case 0: return r;
                default: return (internal_type)0;
            };
        }

        internal_type get_rev(size_t index) const noexcept
        {
            return get(COMPONENTS_COUNT - 1u - index);
        }

        union 
        {
            internal_type r : bits0;

            internal_type r_rev : bits0;
        };
    };
 
    using fmt_red               = pixel_format<uint8_t, uint8_t, 8>;
    using fmt_red_integer       = pixel_format<uint8_t, uint8_t, 8>;
    using fmt_rg                = pixel_format<uint8_t, uint8_t, 8, 8>;
    using fmt_rg_integer        = pixel_format<uint8_t, uint8_t, 8, 8>;
    using fmt_rgb               = pixel_format<uint8_t, uint32_t, 8, 8, 8>;
    using fmt_rgb_integer       = pixel_format<uint8_t, uint32_t, 8, 8, 8>;
    using fmt_rgba              = pixel_format<uint8_t, uint8_t, 8, 8, 8, 8>;
    using fmt_rgba_integer      = pixel_format<uint8_t, uint8_t, 8, 8, 8, 8>;
    using fmt_bgr               = pixel_format<uint8_t, uint32_t, 8, 8, 8>;
    using fmt_bgr_integer       = pixel_format<uint8_t, uint32_t, 8, 8, 8>;
    using fmt_bgra              = pixel_format<uint8_t, uint8_t, 8, 8, 8, 8>;
    using fmt_bgra_integer      = pixel_format<uint8_t, uint8_t, 8, 8, 8, 8>;

    using fmt_stencil_index     = pixel_format<uint8_t, uint8_t, 8>;
 
    using fmt_depth_component   = pixel_format<uint8_t, uint8_t, 8>;
    using fmt_depth_component16 = pixel_format<uint16_t, uint16_t, 16>;
    using fmt_depth_component24 = pixel_format<uint32_t, uint32_t, 24>;
    using fmt_depth_component32 = pixel_format<uint32_t, uint32_t, 32>;
 
    using fmt_depth_stencil     = pixel_format<uint8_t, uint8_t, 8, 8>;

    using fmt_srgb              = fmt_rgb;
    using fmt_srgb_alpha        = fmt_rgba;

    using fmt_r3_g3_b2          = pixel_format<uint8_t, uint8_t, 3, 3, 2>;
 
    using fmt_r8                = pixel_format<uint8_t, uint8_t, 8>;
    using fmt_r8_snorm          = pixel_format<int8_t, uint8_t, 8>;
    using fmt_r16               = pixel_format<uint16_t, uint16_t, 16>;
    using fmt_r16_snorm         = pixel_format<int16_t, uint16_t, 16>;
    using fmt_rg8               = pixel_format<uint8_t, uint8_t, 8, 8>;
    using fmt_rg8_snorm         = pixel_format<int8_t, uint8_t, 8, 8>;
    using fmt_rg16              = pixel_format<uint16_t, uint16_t, 16, 16>;
    using fmt_rg16_snorm        = pixel_format<int16_t, uint16_t, 16, 16>;
    using fmt_rgb8              = pixel_format<uint8_t, uint32_t, 8, 8, 8>;
    using fmt_rgb8_snorm        = pixel_format<int8_t, uint32_t, 8, 8, 8>;
    using fmt_rgb10             = pixel_format<uint16_t, uint32_t, 10, 10, 10>;
    using fmt_rgb16             = pixel_format<uint16_t, uint32_t, 16, 16, 16>;
    using fmt_rgb16_snorm       = pixel_format<int16_t, uint32_t, 16, 16, 16>;
    using fmt_rgba2             = pixel_format<uint8_t, uint8_t, 2, 2, 2, 2>;
    using fmt_rgba4             = pixel_format<uint8_t, uint8_t, 4, 4, 4, 4>;
    using fmt_rgb5_a1           = pixel_format<uint8_t, uint16_t, 5, 5, 5, 1>;
    using fmt_rgba8             = pixel_format<uint8_t, uint16_t, 8, 8, 8, 8>;
    using fmt_rgba8_snorm       = pixel_format<int8_t, uint8_t, 8, 8, 8, 8>;
    using fmt_rgb10_a2          = pixel_format<uint16_t, uint32_t, 10, 10, 10, 2>;
    using fmt_rgb10_a2ui        = fmt_rgb10_a2;
    using fmt_rgba12            = pixel_format<uint16_t, uint64_t, 12, 12, 12, 12>;
    using fmt_rgba16            = pixel_format<uint16_t, uint16_t, 16, 16, 16, 16>;
    using fmt_srgb8             = pixel_format<uint8_t, uint32_t, 8, 8, 8>;
    using fmt_srgb8_alpha8      = pixel_format<uint8_t, uint8_t, 8, 8, 8, 8>;

    using fmt_r16f              = pixel_format<half_float::half, uint16_t, 16>;
    using fmt_rg16f             = pixel_format<half_float::half, uint16_t, 16, 16>;
    using fmt_rgb16f            = pixel_format<half_float::half, uint32_t, 16, 16, 16>;
    using fmt_rgba16f           = pixel_format<half_float::half, uint16_t, 16, 16, 16, 16>;
    using fmt_r32f              = pixel_format<float, uint32_t, 32>;
    using fmt_rg32f             = pixel_format<float, uint32_t, 32, 32>;
    using fmt_rgb32f            = pixel_format<float, uint64_t, 32, 32, 32>;
    using fmt_rgba32f           = pixel_format<float, uint32_t, 32, 32, 32, 32>;
    using fmt_r11f_g11f_b10f    = pixel_format<float, uint32_t, 11, 11, 10>;
    using fmt_r8i               = pixel_format<int8_t, uint8_t, 8>;
    using fmt_r8ui              = pixel_format<uint8_t, uint8_t, 8>;
    using fmt_r16i              = pixel_format<int16_t, uint16_t, 16>;
    using fmt_r16ui             = pixel_format<uint16_t, uint16_t, 16>;
    using fmt_r32i              = pixel_format<int32_t, uint32_t, 32>;
    using fmt_r32ui             = pixel_format<uint32_t, uint32_t, 32>;
    using fmt_rg8i              = pixel_format<int8_t, uint8_t, 8, 8>;
    using fmt_rg8ui             = pixel_format<uint8_t, uint8_t, 8, 8>;
    using fmt_rg16i             = pixel_format<int16_t, uint16_t, 16, 16>;
    using fmt_rg16ui            = pixel_format<uint16_t, uint16_t, 16, 16>;
    using fmt_rg32i             = pixel_format<int32_t, uint32_t, 32, 32>;
    using fmt_rg32ui            = pixel_format<uint32_t, uint32_t, 32, 32>;
    using fmt_rgb8i             = pixel_format<int8_t, uint32_t, 8, 8, 8>;
    using fmt_rgb8ui            = pixel_format<uint8_t, uint32_t, 8, 8, 8>;
    using fmt_rgb16i            = pixel_format<int16_t, uint32_t, 16, 16, 16>;
    using fmt_rgb16ui           = pixel_format<uint16_t, uint32_t, 16, 16, 16>;
    using fmt_rgb32i            = pixel_format<int32_t, uint64_t, 32, 32, 32>;
    using fmt_rgb32ui           = pixel_format<uint32_t, uint64_t, 32, 32, 32>;
    using fmt_rgba8i            = pixel_format<int8_t, uint8_t, 8, 8, 8, 8>;
    using fmt_rgba8ui           = pixel_format<uint8_t, uint8_t, 8, 8, 8, 8>;
    using fmt_rgba16i           = pixel_format<int16_t, uint16_t, 16, 16, 16, 16>;
    using fmt_rgba16ui          = pixel_format<uint16_t, uint16_t, 16, 16, 16, 16>;
    using fmt_rgba32i           = pixel_format<int32_t, uint32_t, 32, 32, 32, 32>;
    using fmt_rgba32ui          = pixel_format<uint32_t, uint32_t, 32, 32, 32, 32>;

    AM_STATIC_ASSERT(sizeof(fmt_red)               == 1u);
    AM_STATIC_ASSERT(sizeof(fmt_red_integer)       == 1u);
    AM_STATIC_ASSERT(sizeof(fmt_rg)                == 2u);
    AM_STATIC_ASSERT(sizeof(fmt_rg_integer)        == 2u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb)               == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb_integer)       == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba)              == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba_integer)      == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_bgr)               == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_bgr_integer)       == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_bgra)              == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_bgra_integer)      == 4u);

    AM_STATIC_ASSERT(sizeof(fmt_stencil_index)     == 1u);
    AM_STATIC_ASSERT(sizeof(fmt_depth_component)   == 1u);
    AM_STATIC_ASSERT(sizeof(fmt_depth_component16) == 2u);
    AM_STATIC_ASSERT(sizeof(fmt_depth_component24) == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_depth_component32) == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_depth_stencil)     == 2u);
  
    AM_STATIC_ASSERT(sizeof(fmt_srgb)              == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_srgb_alpha)        == 4u);

    AM_STATIC_ASSERT(sizeof(fmt_r3_g3_b2)          == 1u);

    AM_STATIC_ASSERT(sizeof(fmt_r8)                == 1u);
    AM_STATIC_ASSERT(sizeof(fmt_r8_snorm)          == 1u);
    AM_STATIC_ASSERT(sizeof(fmt_r16)               == 2u);
    AM_STATIC_ASSERT(sizeof(fmt_r16_snorm)         == 2u);
    AM_STATIC_ASSERT(sizeof(fmt_rg8)               == 2u);
    AM_STATIC_ASSERT(sizeof(fmt_rg16)              == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rg16_snorm)        == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb8)              == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb8_snorm)        == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb10)             == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb16)             == 8u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb16_snorm)       == 8u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba2)             == 1u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba4)             == 2u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb5_a1)           == 2u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba8)             == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba8_snorm)       == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb10_a2)          == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb10_a2ui)        == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba12)            == 8u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba16)            == 8u);
    AM_STATIC_ASSERT(sizeof(fmt_srgb8)             == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_srgb8_alpha8)      == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_r16f)              == 2u);
    AM_STATIC_ASSERT(sizeof(fmt_rg16f)             == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb16f)            == 8u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba16f)           == 8u);
    AM_STATIC_ASSERT(sizeof(fmt_r32f)              == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rg32f)             == 8u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb32f)            == 16u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba32f)           == 16u);
    AM_STATIC_ASSERT(sizeof(fmt_r11f_g11f_b10f)    == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_r8i)               == 1u);
    AM_STATIC_ASSERT(sizeof(fmt_r8ui)              == 1u);
    AM_STATIC_ASSERT(sizeof(fmt_r16i)              == 2u);
    AM_STATIC_ASSERT(sizeof(fmt_r16ui)             == 2u);
    AM_STATIC_ASSERT(sizeof(fmt_r32i)              == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_r32ui)             == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rg8i)              == 2u);
    AM_STATIC_ASSERT(sizeof(fmt_rg8ui)             == 2u);
    AM_STATIC_ASSERT(sizeof(fmt_rg16i)             == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rg16ui)            == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rg32i)             == 8u);
    AM_STATIC_ASSERT(sizeof(fmt_rg32ui)            == 8u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb8i)             == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb8ui)            == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb16i)            == 8u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb16ui)           == 8u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb32i)            == 16u);
    AM_STATIC_ASSERT(sizeof(fmt_rgb32ui)           == 16u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba8i)            == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba8ui)           == 4u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba16i)           == 8u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba16ui)          == 8u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba32i)           == 16u);
    AM_STATIC_ASSERT(sizeof(fmt_rgba32ui)          == 16u);


    /// @brief  
    /// @return Pixel size in bytes or 0 if 'internal_format' is invalid
    inline constexpr size_t get_internal_fmt_pixel_size(enum_t internal_format) noexcept
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