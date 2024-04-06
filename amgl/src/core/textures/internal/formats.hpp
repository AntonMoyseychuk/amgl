#pragma once
#include "amgl/amgl.hpp"
#include "core/utils/type_traits.hpp"

#include "converting/integer_float_mapping.hpp"


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

    template <enum_t format, typename implicit_t, typename internal_t, size_t... bits>
    struct pixel_format : pixel_format_base<bit_val_wrapper<bits>...>
    {
        AM_STATIC_ASSERT_MSG(sizeof...(bits) < 0u, "invalid pixel components count");
    };

    template <enum_t format, typename implicit_t, typename internal_t, size_t bits0, size_t bits1, size_t bits2, size_t bits3>
    struct pixel_format<format, implicit_t, internal_t, bits0, bits1, bits2, bits3> 
        : pixel_format_base<bit_val_wrapper<bits0>, bit_val_wrapper<bits1>, bit_val_wrapper<bits2>, bit_val_wrapper<bits3>>
    {
        using base_type = pixel_format_base<bit_val_wrapper<bits0>, bit_val_wrapper<bits1>, bit_val_wrapper<bits2>, bit_val_wrapper<bits3>>;
        using base_type::COMPONENTS_COUNT;
        
        using implicit_type = implicit_t;
        using internal_type = internal_t;

        static constexpr enum_t AMGL_FORMAT = format;

        constexpr pixel_format(implicit_type r, implicit_type g, implicit_type b, implicit_type a) 
            : r(*reinterpret_cast<internal_type*>(&r)), 
            g(*reinterpret_cast<internal_type*>(&g)), 
            b(*reinterpret_cast<internal_type*>(&b)), 
            a(*reinterpret_cast<internal_type*>(&a)) 
        {}
        constexpr pixel_format(implicit_type val) 
            : pixel_format(val, val, val, val) {}
        constexpr pixel_format() 
            : pixel_format(0, 0, 0, 0) {}

        void set(size_t index, implicit_type value) noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            switch (index) {
                case 0: r = *reinterpret_cast<internal_type*>(&value); break;
                case 1: g = *reinterpret_cast<internal_type*>(&value); break;
                case 2: b = *reinterpret_cast<internal_type*>(&value); break;
                case 3: a = *reinterpret_cast<internal_type*>(&value); break;
            };
        }

        void set_rev(size_t index, implicit_type value) noexcept
        {
            set(COMPONENTS_COUNT - 1u - index, value);
        }

        implicit_type get(size_t index) const noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            internal_type result = 0; 

            switch (index) {
                case 0: result = r; break;
                case 1: result = g; break;
                case 2: result = b; break;
                case 3: result = a; break;
            };

            return *reinterpret_cast<implicit_type*>(&result);
        }

        implicit_type get_rev(size_t index) const noexcept
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

    template <enum_t format, typename implicit_t, typename internal_t, size_t bits0, size_t bits1, size_t bits2>
    struct pixel_format<format, implicit_t, internal_t, bits0, bits1, bits2> 
        : pixel_format_base<bit_val_wrapper<bits0>, bit_val_wrapper<bits1>, bit_val_wrapper<bits2>>
    {
        using base_type = pixel_format_base<bit_val_wrapper<bits0>, bit_val_wrapper<bits1>, bit_val_wrapper<bits2>>;
        using base_type::COMPONENTS_COUNT;
        
        using implicit_type = implicit_t;
        using internal_type = internal_t;

        static constexpr enum_t AMGL_FORMAT = format;

        constexpr pixel_format(implicit_type r, implicit_type g, implicit_type b) 
            : r(*reinterpret_cast<internal_type*>(&r)), 
            g(*reinterpret_cast<internal_type*>(&g)), 
            b(*reinterpret_cast<internal_type*>(&b))
        {}
        constexpr pixel_format(implicit_type val) 
            : pixel_format(val, val, val) {}
        constexpr pixel_format() 
            : pixel_format(0, 0, 0) {}

        void set(size_t index, implicit_type value) noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            switch (index) {
                case 0: r = *reinterpret_cast<internal_type*>(&value); break;
                case 1: g = *reinterpret_cast<internal_type*>(&value); break;
                case 2: b = *reinterpret_cast<internal_type*>(&value); break;
            };
        }

        void set_rev(size_t index, implicit_type value) noexcept
        {
            set(COMPONENTS_COUNT - 1u - index, value);
        }

        implicit_type get(size_t index) const noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            internal_type result = 0; 

            switch (index) {
                case 0: result = r; break;
                case 1: result = g; break;
                case 2: result = b; break;
            };

            return *reinterpret_cast<implicit_type*>(&result);
        }

        implicit_type get_rev(size_t index) const noexcept
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

    template <enum_t format, typename implicit_t, typename internal_t, size_t bits0, size_t bits1>
    struct pixel_format<format, implicit_t, internal_t, bits0, bits1> : pixel_format_base<bit_val_wrapper<bits0>, bit_val_wrapper<bits1>>
    {
        using base_type = pixel_format_base<bit_val_wrapper<bits0>, bit_val_wrapper<bits1>>;
        using base_type::COMPONENTS_COUNT;
        
        using implicit_type = implicit_t;
        using internal_type = internal_t;

        static constexpr enum_t AMGL_FORMAT = format;

        constexpr pixel_format(implicit_type r, implicit_type g) 
            : r(*reinterpret_cast<internal_type*>(&r)), 
            g(*reinterpret_cast<internal_type*>(&g))
        {}
        constexpr pixel_format(implicit_t val) 
            : pixel_format(val, val) {}
        constexpr pixel_format() 
            : pixel_format(0, 0) {}

        void set(size_t index, implicit_type value) noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            switch (index) {
                case 0: r = *reinterpret_cast<internal_type*>(&value); break;
                case 1: g = *reinterpret_cast<internal_type*>(&value); break;
            };
        }

        void set_rev(size_t index, implicit_type value) noexcept
        {
            set(COMPONENTS_COUNT - 1u - index, value);
        }

        implicit_type get(size_t index) const noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            internal_type result = 0; 

            switch (index) {
                case 0: result = r; break;
                case 1: result = g; break;
            };

            return *reinterpret_cast<implicit_type*>(&result);
        }

        implicit_type get_rev(size_t index) const noexcept
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
        };
    };

    template <enum_t format, typename implicit_t, typename internal_t, size_t bits0>
    struct pixel_format<format, implicit_t, internal_t, bits0> : pixel_format_base<bit_val_wrapper<bits0>>
    {
        using base_type = pixel_format_base<bit_val_wrapper<bits0>>;
        using base_type::COMPONENTS_COUNT;
        
        using implicit_type = implicit_t;
        using internal_type = internal_t;

        static constexpr enum_t AMGL_FORMAT = format;

        constexpr pixel_format(implicit_type r) 
            : r(*reinterpret_cast<internal_type*>(&r))
        {}
        constexpr pixel_format() 
            : pixel_format(0) {}

        void set(size_t index, implicit_type value) noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            switch (index) {
                case 0: r = *reinterpret_cast<internal_type*>(&value); break;
            };
        }

        void set_rev(size_t index, implicit_type value) noexcept
        {
            set(COMPONENTS_COUNT - 1u - index, value);
        }

        implicit_type get(size_t index) const noexcept
        {
            AM_ASSERT_MSG(index < COMPONENTS_COUNT, "index must be 0 <= index < %u", COMPONENTS_COUNT);
            
            internal_type result = 0; 

            switch (index) {
                case 0: result = r; break;
            };

            return *reinterpret_cast<implicit_type*>(&result);
        }

        implicit_type get_rev(size_t index) const noexcept
        {
            return get(COMPONENTS_COUNT - 1u - index);
        }

        union 
        {
            internal_type r : bits0;

            internal_type r_rev : bits0;
        };
    };
    
    /*------------------- Texture Internal Formats -------------------*/
    using fmt_red               = pixel_format<AMGL_RED, uint8_t, uint8_t, 8>;
    using fmt_red_integer       = pixel_format<AMGL_RED_INTEGER, uint8_t, uint8_t, 8>;
    using fmt_rg                = pixel_format<AMGL_RG, uint8_t, uint8_t, 8, 8>;
    using fmt_rg_integer        = pixel_format<AMGL_RG_INTEGER, uint8_t, uint8_t, 8, 8>;
    using fmt_rgb               = pixel_format<AMGL_RGB, uint8_t, uint32_t, 8, 8, 8>;
    using fmt_rgb_integer       = pixel_format<AMGL_RGB_INTEGER, uint8_t, uint32_t, 8, 8, 8>;
    using fmt_rgba              = pixel_format<AMGL_RGBA, uint8_t, uint8_t, 8, 8, 8, 8>;
    using fmt_rgba_integer      = pixel_format<AMGL_RGBA_INTEGER, uint8_t, uint8_t, 8, 8, 8, 8>;
    using fmt_bgr               = pixel_format<AMGL_BGR, uint8_t, uint32_t, 8, 8, 8>;
    using fmt_bgr_integer       = pixel_format<AMGL_BGR_INTEGER, uint8_t, uint32_t, 8, 8, 8>;
    using fmt_bgra              = pixel_format<AMGL_BGRA, uint8_t, uint8_t, 8, 8, 8, 8>;
    using fmt_bgra_integer      = pixel_format<AMGL_BGRA_INTEGER, uint8_t, uint8_t, 8, 8, 8, 8>;

    using fmt_stencil_index     = pixel_format<AMGL_STENCIL_INDEX, uint8_t, uint8_t, 8>;
 
    using fmt_depth_component   = pixel_format<AMGL_DEPTH_COMPONENT, uint8_t, uint8_t, 8>;
    using fmt_depth_component16 = pixel_format<AMGL_DEPTH_COMPONENT16, uint16_t, uint16_t, 16>;
    using fmt_depth_component24 = pixel_format<AMGL_DEPTH_COMPONENT24, uint32_t, uint32_t, 24>;
    using fmt_depth_component32 = pixel_format<AMGL_DEPTH_COMPONENT32, uint32_t, uint32_t, 32>;
 
    using fmt_depth_stencil     = pixel_format<AMGL_DEPTH_STENCIL, uint8_t, uint8_t, 8, 8>;

    using fmt_srgb              = pixel_format<AMGL_SRGB, uint8_t, uint32_t, 8, 8, 8>;
    using fmt_srgb_alpha        = pixel_format<AMGL_SRGB_ALPHA, uint8_t, uint8_t, 8, 8, 8, 8>;

    using fmt_r3_g3_b2          = pixel_format<AMGL_R3_G3_B2, uint8_t, uint8_t, 3, 3, 2>;
 
    using fmt_r8                = pixel_format<AMGL_R8, uint8_t, uint8_t, 8>;
    using fmt_r8_snorm          = pixel_format<AMGL_R8_SNORM, int8_t, int8_t, 8>;
    using fmt_r16               = pixel_format<AMGL_R16, uint16_t, uint16_t, 16>;
    using fmt_r16_snorm         = pixel_format<AMGL_R16_SNORM, int16_t, int16_t, 16>;
    using fmt_rg8               = pixel_format<AMGL_RG8, uint8_t, uint8_t, 8, 8>;
    using fmt_rg8_snorm         = pixel_format<AMGL_RG8_SNORM, int8_t, int8_t, 8, 8>;
    using fmt_rg16              = pixel_format<AMGL_RG16, uint16_t, uint16_t, 16, 16>;
    using fmt_rg16_snorm        = pixel_format<AMGL_RG16_SNORM, int16_t, int16_t, 16, 16>;
    using fmt_rgb8              = pixel_format<AMGL_RGB8, uint8_t, uint32_t, 8, 8, 8>;
    using fmt_rgb8_snorm        = pixel_format<AMGL_RGB8_SNORM, int8_t, int32_t, 8, 8, 8>;
    using fmt_rgb10             = pixel_format<AMGL_RGB10, uint16_t, uint32_t, 10, 10, 10>;
    using fmt_rgb16             = pixel_format<AMGL_RGB16, uint16_t, uint32_t, 16, 16, 16>;
    using fmt_rgb16_snorm       = pixel_format<AMGL_RGB16_SNORM, int16_t, int32_t, 16, 16, 16>;
    using fmt_rgba2             = pixel_format<AMGL_RGBA2, uint8_t, uint8_t, 2, 2, 2, 2>;
    using fmt_rgba4             = pixel_format<AMGL_RGBA4, uint8_t, uint8_t, 4, 4, 4, 4>;
    using fmt_rgb5_a1           = pixel_format<AMGL_RGB5_A1, uint8_t, uint16_t, 5, 5, 5, 1>;
    using fmt_rgba8             = pixel_format<AMGL_RGBA8, uint8_t, uint8_t, 8, 8, 8, 8>;
    using fmt_rgba8_snorm       = pixel_format<AMGL_RGBA8_SNORM, int8_t, int8_t, 8, 8, 8, 8>;
    using fmt_rgb10_a2          = pixel_format<AMGL_RGB10_A2, uint16_t, uint32_t, 10, 10, 10, 2>;
    using fmt_rgb10_a2ui        = pixel_format<AMGL_RGB10_A2UI, uint16_t, uint32_t, 10, 10, 10, 2>;
    using fmt_rgba12            = pixel_format<AMGL_RGBA12, uint16_t, uint64_t, 12, 12, 12, 12>;
    using fmt_rgba16            = pixel_format<AMGL_RGBA16, uint16_t, uint16_t, 16, 16, 16, 16>;
    using fmt_srgb8             = pixel_format<AMGL_SRGB8, uint8_t, uint32_t, 8, 8, 8>;
    using fmt_srgb8_alpha8      = pixel_format<AMGL_SRGB8_ALPHA8, uint8_t, uint8_t, 8, 8, 8, 8>;

    using fmt_r16f              = pixel_format<AMGL_R16F, half_float::half, int16_t, 16>;
    using fmt_rg16f             = pixel_format<AMGL_RG16F, half_float::half, int16_t, 16, 16>;
    using fmt_rgb16f            = pixel_format<AMGL_RGB16F, half_float::half, int32_t, 16, 16, 16>;
    using fmt_rgba16f           = pixel_format<AMGL_RGBA16F, half_float::half, int16_t, 16, 16, 16, 16>;
    using fmt_r32f              = pixel_format<AMGL_R32F, float, int32_t, 32>;
    using fmt_rg32f             = pixel_format<AMGL_RG32F, float, int32_t, 32, 32>;
    using fmt_rgb32f            = pixel_format<AMGL_RGB32F, float, int64_t, 32, 32, 32>;
    using fmt_rgba32f           = pixel_format<AMGL_RGBA32F, float, int32_t, 32, 32, 32, 32>;
    using fmt_r11f_g11f_b10f    = pixel_format<AMGL_R11F_G11F_B10F, float, int32_t, 11, 11, 10>;
    using fmt_r8i               = pixel_format<AMGL_R8I, int8_t, int8_t, 8>;
    using fmt_r8ui              = pixel_format<AMGL_R8UI, uint8_t, uint8_t, 8>;
    using fmt_r16i              = pixel_format<AMGL_R16I, int16_t, int16_t, 16>;
    using fmt_r16ui             = pixel_format<AMGL_R16UI, uint16_t, uint16_t, 16>;
    using fmt_r32i              = pixel_format<AMGL_R32I, int32_t, int32_t, 32>;
    using fmt_r32ui             = pixel_format<AMGL_R32UI, uint32_t, uint32_t, 32>;
    using fmt_rg8i              = pixel_format<AMGL_RG8I, int8_t, int8_t, 8, 8>;
    using fmt_rg8ui             = pixel_format<AMGL_RG8UI, uint8_t, uint8_t, 8, 8>;
    using fmt_rg16i             = pixel_format<AMGL_RG16I, int16_t, int16_t, 16, 16>;
    using fmt_rg16ui            = pixel_format<AMGL_RG16UI, uint16_t, uint16_t, 16, 16>;
    using fmt_rg32i             = pixel_format<AMGL_RG32I, int32_t, int32_t, 32, 32>;
    using fmt_rg32ui            = pixel_format<AMGL_RG32UI, uint32_t, uint32_t, 32, 32>;
    using fmt_rgb8i             = pixel_format<AMGL_RGB8I, int8_t, int32_t, 8, 8, 8>;
    using fmt_rgb8ui            = pixel_format<AMGL_RGB8UI, uint8_t, uint32_t, 8, 8, 8>;
    using fmt_rgb16i            = pixel_format<AMGL_RGB16I, int16_t, int32_t, 16, 16, 16>;
    using fmt_rgb16ui           = pixel_format<AMGL_RGB16UI, uint16_t, uint32_t, 16, 16, 16>;
    using fmt_rgb32i            = pixel_format<AMGL_RGB32I, int32_t, int64_t, 32, 32, 32>;
    using fmt_rgb32ui           = pixel_format<AMGL_RGB32UI, uint32_t, uint64_t, 32, 32, 32>;
    using fmt_rgba8i            = pixel_format<AMGL_RGBA8I, int8_t, int8_t, 8, 8, 8, 8>;
    using fmt_rgba8ui           = pixel_format<AMGL_RGBA8UI, uint8_t, uint8_t, 8, 8, 8, 8>;
    using fmt_rgba16i           = pixel_format<AMGL_RGBA16I, int16_t, int16_t, 16, 16, 16, 16>;
    using fmt_rgba16ui          = pixel_format<AMGL_RGBA16UI, uint16_t, uint16_t, 16, 16, 16, 16>;
    using fmt_rgba32i           = pixel_format<AMGL_RGBA32I, int32_t, int32_t, 32, 32, 32, 32>;
    using fmt_rgba32ui          = pixel_format<AMGL_RGBA32UI, uint32_t, uint32_t, 32, 32, 32, 32>;
    
    /*------------------- Input Formats -------------------*/
    using in_fmt_r_ubyte    = fmt_r8ui;
    using in_fmt_r_byte     = fmt_r8i;
    using in_fmt_r_ushort   = fmt_r16ui;
    using in_fmt_r_short    = fmt_r16i;
    using in_fmt_r_uint     = fmt_r32ui;
    using in_fmt_r_int      = fmt_r32i;
    using in_fmt_r_float    = fmt_r32f;
    
    using in_fmt_rg_ubyte    = fmt_rg8ui;
    using in_fmt_rg_byte     = fmt_rg8i;
    using in_fmt_rg_ushort   = fmt_rg16ui;
    using in_fmt_rg_short    = fmt_rg16i;
    using in_fmt_rg_uint     = fmt_rg32ui;
    using in_fmt_rg_int      = fmt_rg32i;
    using in_fmt_rg_float    = fmt_rg32f;

    using in_fmt_rgb_ubyte    = pixel_format<AMGL_RGB8UI, uint8_t, uint8_t, 8, 8, 8>;
    using in_fmt_rgb_byte     = pixel_format<AMGL_RGB8I, int8_t, int8_t, 8, 8, 8>;
    using in_fmt_rgb_ushort   = pixel_format<AMGL_RGB16UI, uint16_t, uint16_t, 16, 16, 16>;
    using in_fmt_rgb_short    = pixel_format<AMGL_RGB16I, int16_t, int16_t, 16, 16, 16>;
    using in_fmt_rgb_uint     = pixel_format<AMGL_RGB32UI, uint32_t, uint32_t, 32, 32, 32>;
    using in_fmt_rgb_int      = pixel_format<AMGL_RGB32I, int32_t, int32_t, 32, 32, 32>;
    using in_fmt_rgb_float    = pixel_format<AMGL_RGB32F, float, int32_t, 32, 32, 32>;

    using in_fmt_rgba_ubyte    = fmt_rgba8ui;
    using in_fmt_rgba_byte     = fmt_rgba8i;
    using in_fmt_rgba_ushort   = fmt_rgba16ui;
    using in_fmt_rgba_short    = fmt_rgba16i;
    using in_fmt_rgba_uint     = fmt_rgba32ui;
    using in_fmt_rgba_int      = fmt_rgba32i;
    using in_fmt_rgba_float    = fmt_rgba32f;


    template <typename fmt>
    struct fmt_min_max_default
    {
        AM_STATIC_ASSERT_MSG(sizeof(fmt) < 0, "Invalid fmt type");
    };

    #define _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt, min_val, max_val, default_val)  \
        template <>                                                                 \
        struct fmt_min_max_default<fmt> {                                           \
            static inline const fmt min = min_val;                                  \
            static inline const fmt max = max_val;                                  \
            static inline const fmt def = default_val;                              \
        }

    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_red,               fmt_red(0),                 fmt_red(UINT8_MAX),                 fmt_red(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_red_integer,       fmt_red_integer(0),         fmt_red_integer(UINT8_MAX),         fmt_red_integer(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rg,                fmt_rg(0),                  fmt_rg(UINT8_MAX),                  fmt_rg(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rg_integer,        fmt_rg_integer(0),          fmt_rg_integer(UINT8_MAX),          fmt_rg_integer(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb,               fmt_rgb(0),                 fmt_rgb(UINT8_MAX),                 fmt_rgb(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb_integer,       fmt_rgb_integer(0),         fmt_rgb_integer(UINT8_MAX),         fmt_rgb_integer(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba,              fmt_rgba(0),                fmt_rgba(UINT8_MAX),                fmt_rgba(0, 0, 0, UINT8_MAX));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba_integer,      fmt_rgba_integer(0),        fmt_rgba_integer(UINT8_MAX),        fmt_rgba_integer(0, 0, 0, UINT8_MAX));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_bgr,               fmt_bgr(0),                 fmt_bgr(UINT8_MAX),                 fmt_bgr(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_bgr_integer,       fmt_bgr_integer(0),         fmt_bgr_integer(UINT8_MAX),         fmt_bgr_integer(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_bgra,              fmt_bgra(0),                fmt_bgra(UINT8_MAX),                fmt_bgra(0, 0, 0, UINT8_MAX));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_bgra_integer,      fmt_bgra_integer(0),        fmt_bgra_integer(UINT8_MAX),        fmt_bgra_integer(0, 0, 0, UINT8_MAX));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_stencil_index,     fmt_stencil_index(0),       fmt_stencil_index(UINT8_MAX),       fmt_stencil_index(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_depth_component,   fmt_depth_component(0),     fmt_depth_component(UINT8_MAX),     fmt_depth_component(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_depth_component16, fmt_depth_component16(0),   fmt_depth_component16(UINT16_MAX),  fmt_depth_component16(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_depth_component24, fmt_depth_component24(0),   fmt_depth_component24(0xffffffu),   fmt_depth_component24(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_depth_component32, fmt_depth_component32(0),   fmt_depth_component32(UINT32_MAX),  fmt_depth_component32(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_depth_stencil,     fmt_depth_stencil(0),       fmt_depth_stencil(UINT8_MAX),       fmt_depth_stencil(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_srgb,              fmt_srgb(0),                fmt_srgb(UINT8_MAX),                fmt_srgb(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_srgb_alpha,        fmt_srgb_alpha(0),          fmt_srgb_alpha(UINT8_MAX),          fmt_srgb_alpha(0, 0, 0, UINT8_MAX));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_r3_g3_b2,          fmt_r3_g3_b2(0),            fmt_r3_g3_b2(7, 7, 3),              fmt_r3_g3_b2(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_r8,                fmt_r8(0),                  fmt_r8(UINT8_MAX),                  fmt_r8(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_r8_snorm,          fmt_r8_snorm(INT8_MIN),     fmt_r8_snorm(INT8_MAX),             fmt_r8_snorm(INT8_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_r16,               fmt_r16(0),                 fmt_r16(UINT16_MAX),                fmt_r16(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_r16_snorm,         fmt_r16_snorm(INT16_MIN),   fmt_r16_snorm(INT16_MAX),           fmt_r16_snorm(INT16_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rg8,               fmt_rg8(0),                 fmt_rg8(UINT8_MAX),                 fmt_rg8(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rg8_snorm,         fmt_rg8_snorm(INT8_MIN),    fmt_rg8_snorm(INT8_MAX),            fmt_rg8_snorm(INT8_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rg16,              fmt_rg16(0),                fmt_rg16(UINT16_MAX),               fmt_rg16(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rg16_snorm,        fmt_rg16_snorm(INT16_MIN),  fmt_rg16_snorm(INT16_MAX),          fmt_rg16_snorm(INT16_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb8,              fmt_rgb8(0),                fmt_rgb8(UINT8_MAX),                fmt_rgb8(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb8_snorm,        fmt_rgb8_snorm(INT8_MIN),   fmt_rgb8_snorm(INT8_MAX),           fmt_rgb8_snorm(INT8_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb10,             fmt_rgb10(0),               fmt_rgb10(1023),                    fmt_rgb10(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb16,             fmt_rgb16(0),               fmt_rgb16(UINT16_MAX),              fmt_rgb16(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb16_snorm,       fmt_rgb16_snorm(INT16_MIN), fmt_rgb16_snorm(INT16_MAX),         fmt_rgb16_snorm(INT16_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba2,             fmt_rgba2(0),               fmt_rgba2(3),                       fmt_rgba2(0, 0, 0, 3));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba4,             fmt_rgba4(0),               fmt_rgba4(15),                      fmt_rgba4(0, 0, 0, 15));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb5_a1,           fmt_rgb5_a1(0),             fmt_rgb5_a1(31, 31, 31, 1),         fmt_rgb5_a1(0, 0, 0, 1));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba8,             fmt_rgba8(0),               fmt_rgba8(UINT8_MAX),               fmt_rgba8(0, 0, 0, UINT8_MAX));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba8_snorm,       fmt_rgba8_snorm(INT8_MIN),  fmt_rgba8_snorm(INT8_MAX),          fmt_rgba8_snorm(INT8_MIN, INT8_MIN, INT8_MIN, INT8_MAX));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb10_a2,          fmt_rgb10_a2(0),            fmt_rgb10_a2(1023, 1023, 1023, 3),  fmt_rgb10_a2(0, 0, 0, 3));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb10_a2ui,        fmt_rgb10_a2ui(0),          fmt_rgb10_a2ui(1023, 1023, 1023, 3), fmt_rgb10_a2ui(0, 0, 0, 3));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba12,            fmt_rgba12(0),              fmt_rgba12(4095),                   fmt_rgba12(0, 0, 0, 4095));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba16,            fmt_rgba16(0),              fmt_rgba16(UINT16_MAX),             fmt_rgba16(0, 0, 0, UINT16_MAX));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_srgb8,             fmt_srgb8(0),               fmt_srgb8(UINT8_MAX),               fmt_srgb8(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_srgb8_alpha8,      fmt_srgb8_alpha8(0),        fmt_srgb8_alpha8(UINT8_MAX),        fmt_srgb8_alpha8(0, 0, 0, UINT8_MAX));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_r16f,              fmt_r16f(half_float::half(0.0f)),       fmt_r16f(half_float::half(1.0f)),       fmt_r16f(half_float::half(1.0f)));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rg16f,             fmt_rg16f(half_float::half(0.0f)),      fmt_rg16f(half_float::half(1.0f)),      fmt_rg16f(half_float::half(0.0f)));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb16f,            fmt_rgb16f(half_float::half(0.0f)),     fmt_rgb16f(half_float::half(1.0f)),     fmt_rgb16f(half_float::half(0.0f)));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba16f,           fmt_rgba16f(half_float::half(0.0f)),    fmt_rgba16f(half_float::half(1.0f)),    fmt_rgba16f(half_float::half(0.0f), half_float::half(0.0f), half_float::half(0.0f), half_float::half(1.0f)));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_r32f,              fmt_r32f(0.0f),             fmt_r32f(1.0f),                     fmt_r32f(0.0f));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rg32f,             fmt_rg32f(0.0f),            fmt_rg32f(1.0f),                    fmt_rg32f(0.0f));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb32f,            fmt_rgb32f(0.0f),           fmt_rgb32f(1.0f),                   fmt_rgb32f(0.0f));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba32f,           fmt_rgba32f(0.0f),          fmt_rgba32f(1.0f),                  fmt_rgba32f(0.0f, 0.0f, 0.0f, 1.0f));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_r11f_g11f_b10f,    fmt_r11f_g11f_b10f(0.0f),   fmt_r11f_g11f_b10f(1.0f),           fmt_r11f_g11f_b10f(0.0f));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_r8i,               fmt_r8i(INT8_MIN),          fmt_r8i(INT8_MAX),                  fmt_r8i(INT8_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_r8ui,              fmt_r8ui(0),                fmt_r8ui(UINT8_MAX),                fmt_r8ui(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_r16i,              fmt_r16i(INT16_MIN),        fmt_r16i(INT16_MAX),                fmt_r16i(INT16_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_r16ui,             fmt_r16ui(0),               fmt_r16ui(UINT16_MAX),              fmt_r16ui(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_r32i,              fmt_r32i(INT32_MIN),        fmt_r32i(INT32_MAX),                fmt_r32i(INT32_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_r32ui,             fmt_r32ui(0),               fmt_r32ui(UINT32_MAX),              fmt_r32ui(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rg8i,              fmt_rg8i(INT8_MIN),         fmt_rg8i(INT8_MAX),                 fmt_rg8i(INT8_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rg8ui,             fmt_rg8ui(0),               fmt_rg8ui(UINT8_MAX),               fmt_rg8ui(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rg16i,             fmt_rg16i(INT16_MIN),       fmt_rg16i(INT16_MAX),               fmt_rg16i(INT16_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rg16ui,            fmt_rg16ui(0),              fmt_rg16ui(UINT16_MAX),             fmt_rg16ui(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rg32i,             fmt_rg32i(INT32_MIN),       fmt_rg32i(INT32_MAX),               fmt_rg32i(INT32_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rg32ui,            fmt_rg32ui(0),              fmt_rg32ui(UINT32_MAX),             fmt_rg32ui(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb8i,             fmt_rgb8i(INT8_MIN),        fmt_rgb8i(INT8_MAX),                fmt_rgb8i(INT8_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb8ui,            fmt_rgb8ui(0),              fmt_rgb8ui(UINT8_MAX),              fmt_rgb8ui(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb16i,            fmt_rgb16i(INT16_MIN),      fmt_rgb16i(INT16_MAX),              fmt_rgb16i(INT16_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb16ui,           fmt_rgb16ui(0),             fmt_rgb16ui(UINT16_MAX),            fmt_rgb16ui(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb32i,            fmt_rgb32i(INT32_MIN),      fmt_rgb32i(INT32_MAX),              fmt_rgb32i(INT32_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgb32ui,           fmt_rgb32ui(0),             fmt_rgb32ui(UINT32_MAX),            fmt_rgb32ui(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba8i,            fmt_rgba8i(INT8_MIN),       fmt_rgba8i(INT8_MAX),               fmt_rgba8i(INT8_MIN, INT8_MIN, INT8_MIN, INT8_MAX));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba8ui,           fmt_rgba8ui(0),             fmt_rgba8ui(UINT8_MAX),             fmt_rgba8ui(0, 0, 0, UINT8_MAX));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba16i,           fmt_rgba16i(INT16_MIN),     fmt_rgba16i(INT16_MAX),             fmt_rgba16i(INT16_MIN, INT16_MIN, INT16_MIN, INT16_MAX));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba16ui,          fmt_rgba16ui(0),            fmt_rgba16ui(UINT16_MAX),           fmt_rgba16ui(0, 0, 0, UINT16_MAX));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba32i,           fmt_rgba32i(INT32_MIN),     fmt_rgba32i(INT32_MAX),             fmt_rgba32i(INT32_MIN, INT32_MIN, INT32_MIN, INT32_MAX));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(fmt_rgba32ui,          fmt_rgba32ui(0),            fmt_rgba32ui(UINT32_MAX),           fmt_rgba32ui(0, 0, 0, UINT32_MAX));
    
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(in_fmt_rgb_ubyte,      in_fmt_rgb_ubyte(0),        in_fmt_rgb_ubyte(UINT8_MAX),        in_fmt_rgb_ubyte(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(in_fmt_rgb_byte,       in_fmt_rgb_byte(INT8_MIN),  in_fmt_rgb_byte(INT8_MAX),          in_fmt_rgb_byte(INT8_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(in_fmt_rgb_ushort,     in_fmt_rgb_ushort(0),       in_fmt_rgb_ushort(UINT16_MAX),      in_fmt_rgb_ushort(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(in_fmt_rgb_short,      in_fmt_rgb_short(INT16_MIN),in_fmt_rgb_short(INT16_MAX),        in_fmt_rgb_short(INT16_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(in_fmt_rgb_uint,       in_fmt_rgb_uint(0),         in_fmt_rgb_uint(UINT32_MAX),        in_fmt_rgb_uint(0));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(in_fmt_rgb_int,        in_fmt_rgb_int(INT32_MIN),  in_fmt_rgb_int(INT32_MAX),          in_fmt_rgb_int(INT32_MIN));
    _DECLARE_FMT_MIN_MAX_DEFAULT_VALUE(in_fmt_rgb_float,      in_fmt_rgb_float(0.0f),     in_fmt_rgb_float(1.0f),             in_fmt_rgb_float(0.0f));


    template <enum_t format, enum_t type>
    struct fmt_from_enum
    {
        using fmt_type = void;
    };

    #define _DECLARE_FMT_FROM_ENUM_SPEC(format, type, out_type) \
        template <>                                             \
        struct fmt_from_enum<format, type>                      \
        {                                                       \
            using fmt_type = out_type;                          \
        }
    
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RED, AMGL_BYTE, in_fmt_r_byte);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RED, AMGL_UNSIGNED_BYTE, in_fmt_r_ubyte);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RED, AMGL_SHORT, in_fmt_r_short);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RED, AMGL_UNSIGNED_SHORT, in_fmt_r_ushort);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RED, AMGL_INT, in_fmt_r_int);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RED, AMGL_UNSIGNED_INT, in_fmt_r_uint);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RED, AMGL_FLOAT, in_fmt_r_float);

    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RG, AMGL_BYTE, in_fmt_rg_byte);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RG, AMGL_UNSIGNED_BYTE, in_fmt_rg_ubyte);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RG, AMGL_SHORT, in_fmt_rg_short);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RG, AMGL_UNSIGNED_SHORT, in_fmt_rg_ushort);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RG, AMGL_INT, in_fmt_rg_int);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RG, AMGL_UNSIGNED_INT, in_fmt_rg_uint);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RG, AMGL_FLOAT, in_fmt_rg_float);

    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RGB, AMGL_BYTE, in_fmt_rgb_byte);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RGB, AMGL_UNSIGNED_BYTE, in_fmt_rgb_ubyte);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RGB, AMGL_SHORT, in_fmt_rgb_short);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RGB, AMGL_UNSIGNED_SHORT, in_fmt_rgb_ushort);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RGB, AMGL_INT, in_fmt_rgb_int);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RGB, AMGL_UNSIGNED_INT, in_fmt_rgb_uint);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RGB, AMGL_FLOAT, in_fmt_rgb_float);

    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RGBA, AMGL_BYTE, in_fmt_rgba_byte);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RGBA, AMGL_UNSIGNED_BYTE, in_fmt_rgba_ubyte);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RGBA, AMGL_SHORT, in_fmt_rgba_short);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RGBA, AMGL_UNSIGNED_SHORT, in_fmt_rgba_ushort);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RGBA, AMGL_INT, in_fmt_rgba_int);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RGBA, AMGL_UNSIGNED_INT, in_fmt_rgba_uint);
    _DECLARE_FMT_FROM_ENUM_SPEC(AMGL_RGBA, AMGL_FLOAT, in_fmt_rgba_float);

    template<enum_t format, enum_t type>
    using fmt_from_enum_t = typename fmt_from_enum<format, type>::fmt_type;


    template <enum_t internal_format>
    struct internal_fmt_from_enum
    {
        using fmt_type = void;
    };

    #define _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(internal_format, out_type) \
        template <>                                                         \
        struct internal_fmt_from_enum<internal_format>                      \
        {                                                                   \
            using fmt_type = out_type;                                      \
        }

    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RED, fmt_red);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RG, fmt_rg);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB, fmt_rgb);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA, fmt_rgba);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RED_INTEGER, fmt_red_integer);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RG_INTEGER, fmt_rg_integer);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB_INTEGER, fmt_rgb_integer);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA_INTEGER, fmt_rgba_integer);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_STENCIL_INDEX, fmt_stencil_index);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_DEPTH_COMPONENT, fmt_depth_component);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_DEPTH_STENCIL, fmt_depth_stencil);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_SRGB, fmt_srgb);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_SRGB_ALPHA, fmt_srgb_alpha);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_DEPTH_COMPONENT16, fmt_depth_component16);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_DEPTH_COMPONENT24, fmt_depth_component24);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_DEPTH_COMPONENT32, fmt_depth_component32);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_R8, fmt_r8);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_R8_SNORM, fmt_r8_snorm);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_R16, fmt_r16);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_R16_SNORM, fmt_r16_snorm);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RG8, fmt_rg8);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RG8_SNORM, fmt_rg8_snorm);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RG16, fmt_rg16);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RG16_SNORM, fmt_rg16_snorm);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_R3_G3_B2, fmt_r3_g3_b2);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB8, fmt_rgb8);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB10, fmt_rgb10);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB8_SNORM, fmt_rgb8_snorm);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB16, fmt_rgb16);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB16_SNORM, fmt_rgb16_snorm);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA2, fmt_rgba2);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA4, fmt_rgba4);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB5_A1, fmt_rgb5_a1);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA8, fmt_rgba8);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA8_SNORM, fmt_rgba8_snorm);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB10_A2, fmt_rgb10_a2);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB10_A2UI, fmt_rgb10_a2ui);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA12, fmt_rgba12);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA16, fmt_rgba16);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_SRGB8, fmt_srgb8);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_SRGB8_ALPHA8, fmt_srgb8_alpha8);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_R16F, fmt_r16f);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RG16F, fmt_rg16f);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB16F, fmt_rgb16f);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA16F, fmt_rgba16f);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_R32F, fmt_r32f);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RG32F, fmt_rg32f);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB32F, fmt_rgb32f);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA32F, fmt_rgba32f);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_R11F_G11F_B10F, fmt_r11f_g11f_b10f);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_R8I, fmt_r8i);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_R8UI, fmt_r8ui);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_R16I, fmt_r16i);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_R16UI, fmt_r16ui);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_R32I, fmt_r32i);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_R32UI, fmt_r32ui);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RG8I, fmt_rg8i);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RG8UI, fmt_rg8ui);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RG16I, fmt_rg16i);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RG16UI, fmt_rg16ui);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RG32I, fmt_rg32i);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RG32UI, fmt_rg32ui);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB8I, fmt_rgb8i);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB8UI, fmt_rgb8ui);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB16I, fmt_rgb16i);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB16UI, fmt_rgb16ui);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB32I, fmt_rgb32i);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGB32UI, fmt_rgb32ui);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA8I, fmt_rgba8i);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA8UI, fmt_rgba8ui);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA16I, fmt_rgba16i);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA16UI, fmt_rgba16ui);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA32I, fmt_rgba32i);
    _DECLARE_INTERNAL_FMT_FROM_ENUM_SPEC(AMGL_RGBA32UI, fmt_rgba32ui);

    template<enum_t internal_format>
    using internal_fmt_from_enum_t = typename internal_fmt_from_enum<internal_format>::fmt_type;


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
    
    AM_STATIC_ASSERT(sizeof(in_fmt_r_ubyte)        == 1u);
    AM_STATIC_ASSERT(sizeof(in_fmt_r_byte)         == 1u);
    AM_STATIC_ASSERT(sizeof(in_fmt_r_ushort)       == 2u);
    AM_STATIC_ASSERT(sizeof(in_fmt_r_short)        == 2u);
    AM_STATIC_ASSERT(sizeof(in_fmt_r_uint)         == 4u);
    AM_STATIC_ASSERT(sizeof(in_fmt_r_int)          == 4u);
    AM_STATIC_ASSERT(sizeof(in_fmt_r_float)        == 4u);
    
    AM_STATIC_ASSERT(sizeof(in_fmt_rg_ubyte)        == 2u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rg_byte)         == 2u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rg_ushort)       == 4u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rg_short)        == 4u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rg_uint)         == 8u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rg_int)          == 8u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rg_float)        == 8u);

    AM_STATIC_ASSERT(sizeof(in_fmt_rgb_ubyte)        == 3u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rgb_byte)         == 3u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rgb_ushort)       == 6u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rgb_short)        == 6u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rgb_uint)         == 12u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rgb_int)          == 12u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rgb_float)        == 12u);

    AM_STATIC_ASSERT(sizeof(in_fmt_rgba_ubyte)        == 4u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rgba_byte)         == 4u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rgba_ushort)       == 8u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rgba_short)        == 8u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rgba_uint)         == 16u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rgba_int)          == 16u);
    AM_STATIC_ASSERT(sizeof(in_fmt_rgba_float)        == 16u);
}