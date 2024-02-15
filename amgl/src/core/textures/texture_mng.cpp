#include "pch.hpp"
#include "texture_mng.hpp"
#include "texture_formats.hpp"

#include "core/core.hpp"
#include "core/utils/util_func.hpp"

#include "core/context/context_mng.hpp"
#include "core/buffers/buffer_mng.hpp"



static_assert(AM_INIT_TEX_COUNT > 0, "AM_INIT_TEXTURE_COUNT must be greater than 0");


namespace amgl
{
    static context_mng& gs_context_mng = context_mng::instance();
    static buffer_mng& gs_buffer_mng = buffer_mng::instance();


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

    #define TEXTURE_BASE_INTERNAL_FORMATS                                               \
        AMGL_RED,                                                                       \
        AMGL_RG,                                                                        \
        AMGL_RGB,                                                                       \
        AMGL_RGBA,                                                                      \
        AMGL_DEPTH_COMPONENT,                                                           \
        AMGL_DEPTH_STENCIL,                                                             \
        AMGL_SRGB,                                                                      \
        AMGL_SRGB_ALPHA

    #define TEXTURE_SIZED_INTERNAL_FORMATS                                              \
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
        /*AMGL_RGB4,                                                                      \
        AMGL_RGB5,*/                                                                      \
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
        AMGL_R16F,                                                                      \
        AMGL_RG16F,                                                                     \
        AMGL_RGB16F,                                                                    \
        AMGL_RGBA16F,                                                                   \
        AMGL_R32F,                                                                      \
        AMGL_RG32F,                                                                     \
        AMGL_RGB32F,                                                                    \
        AMGL_RGBA32F,                                                                   \
        AMGL_R11F_G11F_B10F,                                                            \
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
        AMGL_RGBA32UI

    #define TEXTURE_TARGETS                                                             \
        AMGL_TEXTURE_BUFFER,                                                            \
        AMGL_TEXTURE_1D,                                                                \
        AMGL_PROXY_TEXTURE_1D,                                                          \
        AMGL_TEXTURE_2D,                                                                \
        AMGL_PROXY_TEXTURE_2D,                                                          \
        AMGL_TEXTURE_3D,                                                                \
        AMGL_PROXY_TEXTURE_3D,                                                          \
        AMGL_TEXTURE_1D_ARRAY,                                                          \
        AMGL_PROXY_TEXTURE_1D_ARRAY,                                                    \
        AMGL_TEXTURE_2D_ARRAY,                                                          \
        AMGL_PROXY_TEXTURE_2D_ARRAY,                                                    \
        AMGL_TEXTURE_RECTANGLE,                                                         \
        AMGL_PROXY_TEXTURE_RECTANGLE,                                                   \
        AMGL_TEXTURE_CUBE_MAP,                                                          \
        AMGL_PROXY_TEXTURE_CUBE_MAP,                                                    \
        AMGL_TEXTURE_CUBE_MAP_ARRAY,                                                    \
        AMGL_PROXY_TEXTURE_CUBE_MAP_ARRAY,                                              \
        AMGL_TEXTURE_2D_MULTISAMPLE,                                                    \
        AMGL_PROXY_TEXTURE_2D_MULTISAMPLE,                                              \
        AMGL_TEXTURE_2D_MULTISAMPLE_ARRAY,                                              \
        AMGL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY

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
        AMGL_DEPTH_STENCIL                                                              \


    #define CHECK_TEXTURE_TARGET_VALIDITY(target, error_flag, ...)                      \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(target, TEXTURE_TARGETS),               \
            error_flag, gs_context_mng, __VA_ARGS__)


    #define CHECK_TEXTURE_FORMAT_VALIDITY(format, error_flag, ...)                      \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(format, TEXTURE_FORMATS),               \
            error_flag, gs_context_mng, __VA_ARGS__)


    #define CHECK_TEXTURE_TYPE_VALIDITY(type, error_flag, ...)                          \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(type,                                   \
            TEXTURE_PRIMITIVE_TYPES,                                                    \
            TEXTURE_PACKED_TYPES                                                        \
        ), error_flag, gs_context_mng, __VA_ARGS__)


    #define CHECK_TEXTURE_INTERNAL_FORMAT_VALIDITY(internal_format, error_flag, ...)    \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(internal_format,                        \
            TEXTURE_BASE_INTERNAL_FORMATS,                                              \
            TEXTURE_SIZED_INTERNAL_FORMATS                                              \
        ), error_flag, gs_context_mng, __VA_ARGS__)


    // Takes 'texture' in the kernel range [0, UINT32_MAX - 1]
    // Doesn't check 'target' validity
    #define CHECK_TARGET_COMPATIBILITY(target, texture, error_flag, ...)                                                    \
    {                                                                                                                       \
        const enum_t curr_target = m_textures.m_targets[texture];                                                           \
        AM_SET_ERROR_FLAG_IF(curr_target != AMGL_NONE && curr_target != target, error_flag, gs_context_mng, __VA_ARGS__);   \
    }

    // Takes 'texture' in the kernel range [0, UINT32_MAX - 1]
    #define CHECK_TEXTURE_VALIDITY(texture, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(!m_textures.is_texture_exist(texture), error_flag, gs_context_mng, __VA_ARGS__)

    // Takes 'texture' in the kernel range [0, UINT32_MAX - 1]
    #define CHECK_TEXTURE_NOT_DEFAULT(texture, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(texture), error_flag, gs_context_mng, __VA_ARGS__)

    #define CHECK_TEXTURE_LOD_VALIDITY(level, max_level, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(level > max_level, error_flag, gs_context_mng, __VA_ARGS__)


    /// @brief 
    /// @return Size in bytes or 0 if 'type' is invalid
    static constexpr inline size_t get_type_size(enum_t type) noexcept
    {
        switch (type) {
            case AMGL_UNSIGNED_BYTE:
            case AMGL_BYTE:
            case AMGL_UNSIGNED_BYTE_3_3_2:
            case AMGL_UNSIGNED_BYTE_2_3_3_REV:
                return 1u;

            case AMGL_UNSIGNED_SHORT:
            case AMGL_SHORT:
            case AMGL_UNSIGNED_SHORT_5_6_5:
            case AMGL_UNSIGNED_SHORT_5_6_5_REV:
            case AMGL_UNSIGNED_SHORT_4_4_4_4:
            case AMGL_UNSIGNED_SHORT_4_4_4_4_REV:
            case AMGL_UNSIGNED_SHORT_5_5_5_1:
            case AMGL_UNSIGNED_SHORT_1_5_5_5_REV:
                return 2u;

            case AMGL_UNSIGNED_INT:
            case AMGL_INT:
            case AMGL_FLOAT:
            case AMGL_UNSIGNED_INT_8_8_8_8:
            case AMGL_UNSIGNED_INT_8_8_8_8_REV:
            case AMGL_UNSIGNED_INT_10_10_10_2:
            case AMGL_UNSIGNED_INT_2_10_10_10_REV:
                return 4u;

            default:
                return 0u;
        }
    }


    /// @brief 
    /// @return Components count or 0 if 'format' is invalid
    static constexpr inline size_t get_components_count(enum_t format) noexcept
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
            // case AMGL_RGB4:
            // case AMGL_RGB5:
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

            default:
                return 0u;
        }
    }


    /// @brief  
    /// @return Pixel size in bytes or 0 if 'internal_format'
    static constexpr inline size_t get_bytes_per_pixel(enum_t internal_format) noexcept
    {
        using namespace detail;

        const size_t pixel_component_count = get_components_count(internal_format);

        // switch(internal_format) {
        //     case AMGL_RED:
        //     case AMGL_RG:
        //     case AMGL_RGB:
        //     case AMGL_RGBA:
        //     case AMGL_RED_INTEGER:
        //     case AMGL_RG_INTEGER:
        //     case AMGL_RGB_INTEGER:
        //     case AMGL_RGBA_INTEGER:
        //     case AMGL_BGR:
        //     case AMGL_BGRA:
        //     case AMGL_BGR_INTEGER:
        //     case AMGL_BGRA_INTEGER:
        //     case AMGL_STENCIL_INDEX:
        //     case AMGL_DEPTH_COMPONENT:
        //     case AMGL_DEPTH_STENCIL:
        //     case AMGL_SRGB:
        //     case AMGL_SRGB_ALPHA:
        //     case AMGL_DEPTH_COMPONENT16:
        //     case AMGL_DEPTH_COMPONENT24:
        //     case AMGL_DEPTH_COMPONENT32:
        //     case AMGL_R8:
        //     case AMGL_R8_SNORM:
        //     case AMGL_R16:
        //     case AMGL_R16_SNORM:
        //     case AMGL_RG8:
        //     case AMGL_RG8_SNORM:
        //     case AMGL_RG16:
        //     case AMGL_RG16_SNORM:
        //     case AMGL_R3_G3_B2:
        //     case AMGL_RGB8:
        //     case AMGL_RGB8_SNORM:
        //     case AMGL_RGB16:
        //     case AMGL_RGB16_SNORM:
        //     case AMGL_RGBA2:
        //     case AMGL_RGBA4:
        //     case AMGL_RGB5_A1:
        //     case AMGL_RGBA8:
        //     case AMGL_RGBA8_SNORM:
        //     case AMGL_RGB10_A2:
        //     case AMGL_RGB10_A2UI:
        //     case AMGL_RGBA12:
        //     case AMGL_RGBA16:
        //     case AMGL_SRGB8:
        //     case AMGL_SRGB8_ALPHA8:
        //     case AMGL_R16F:
        //     case AMGL_RG16F:
        //     case AMGL_RGB16F:
        //     case AMGL_RGBA16F:
        //     case AMGL_R32F:
        //     case AMGL_RG32F:
        //     case AMGL_RGB32F:
        //     case AMGL_RGBA32F:
        //     case AMGL_R11F_G11F_B10F:
        //     case AMGL_R8I:
        //     case AMGL_R8UI:
        //     case AMGL_R16I:
        //     case AMGL_R16UI:
        //     case AMGL_R32I:
        //     case AMGL_R32UI:
        //     case AMGL_RG8I:
        //     case AMGL_RG8UI:
        //     case AMGL_RG16I:
        //     case AMGL_RG16UI:
        //     case AMGL_RG32I:
        //     case AMGL_RG32UI:
        //     case AMGL_RGB8I:
        //     case AMGL_RGB8UI:
        //     case AMGL_RGB16I:
        //     case AMGL_RGB16UI:
        //     case AMGL_RGB32I:
        //     case AMGL_RGB32UI:
        //     case AMGL_RGBA8I:
        //     case AMGL_RGBA8UI:
        //     case AMGL_RGBA16I:
        //     case AMGL_RGBA16UI:
        //     case AMGL_RGBA32I:
        //     case AMGL_RGBA32UI:
        // };

        return 0u;
    }


    void texture_mng::gen_textures(size_t n, uint32_t* textures) noexcept
    {
        AM_RETURN_IF(!textures);

        for (uint32_t i = 0u; i < n; ++i) {
            textures[i] = CONV_KERNEL_TO_USER_SPACE(m_textures.create_texture());
        }
    }

    
    void texture_mng::delete_textures(size_t n, const uint32_t *textures) noexcept
    {
        AM_RETURN_IF(!textures);

        for (uint32_t i = 0u; i < n; ++i) {
            const uint32_t kernel_id = CONV_USER_TO_KERNEL_SPACE(textures[i]);
            AM_CONTINUE_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(kernel_id) || !m_textures.is_texture_exist(kernel_id));
            
            m_textures.free_texture(kernel_id);
        }
    }

    
    void texture_mng::bind_texture(enum_t target, uint32_t texture) noexcept
    {
        CHECK_TEXTURE_TARGET_VALIDITY(target, AMGL_INVALID_ENUM);

        const uint32_t kernel_tex_id = CONV_USER_TO_KERNEL_SPACE(texture);
        CHECK_TEXTURE_VALIDITY(kernel_tex_id, AMGL_INVALID_VALUE);

        if (!AM_IS_DEFAULT_ID_KERNEL_SPACE(kernel_tex_id)) {
            CHECK_TARGET_COMPATIBILITY(target, kernel_tex_id, AMGL_INVALID_OPERATION);
            m_textures.m_targets[kernel_tex_id] = target;
        }

        gs_context_mng.bind_target_texture(target, kernel_tex_id);
    }

    
    bool texture_mng::is_texture(uint32_t texture) noexcept
    {
        AM_RETURN_IF(AM_IS_DEFAULT_ID_USER_SPACE(texture), false);

        return m_textures.is_texture_exist(CONV_USER_TO_KERNEL_SPACE(texture));
    }

    
    void texture_mng::tex_image_1d(enum_t target, uint32_t level, enum_t internal_format, size_t width, 
        uint32_t border, enum_t format, enum_t type, const void *data) noexcept
    {
        static context& contxt = gs_context_mng.get_context();

        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(target, AMGL_TEXTURE_1D, AMGL_PROXY_TEXTURE_1D), AMGL_INVALID_ENUM, gs_context_mng);
        
        CHECK_TEXTURE_FORMAT_VALIDITY(format, AMGL_INVALID_ENUM);
        
        CHECK_TEXTURE_TYPE_VALIDITY(type, AMGL_INVALID_ENUM);
        
        const uint32_t max_texture_level = log2(width) + 1u;
        CHECK_TEXTURE_LOD_VALIDITY(level, max_texture_level, AMGL_INVALID_VALUE);
        
        CHECK_TEXTURE_INTERNAL_FORMAT_VALIDITY(internal_format, AMGL_INVALID_VALUE);

        AM_SET_ERROR_FLAG_IF(width > context::MAX_TEXTURE_SIZE, AMGL_INVALID_VALUE, gs_context_mng);
        
        AM_SET_ERROR_FLAG_IF(border != 0, AMGL_INVALID_VALUE, gs_context_mng);

        AM_SET_ERROR_FLAG_IF(detail::is_one_of(
            type, 
            AMGL_UNSIGNED_BYTE_3_3_2, 
            AMGL_UNSIGNED_BYTE_2_3_3_REV, 
            AMGL_UNSIGNED_SHORT_5_6_5, 
            AMGL_UNSIGNED_SHORT_5_6_5_REV) && format != AMGL_RGB, AMGL_INVALID_OPERATION, gs_context_mng);

        AM_SET_ERROR_FLAG_IF(detail::is_one_of(
            type, 
            AMGL_UNSIGNED_SHORT_4_4_4_4_REV,
            AMGL_UNSIGNED_SHORT_1_5_5_5_REV,
            AMGL_UNSIGNED_INT_8_8_8_8_REV,
            AMGL_UNSIGNED_INT_2_10_10_10_REV,
            AMGL_UNSIGNED_SHORT_4_4_4_4,
            AMGL_UNSIGNED_SHORT_5_5_5_1,
            AMGL_UNSIGNED_INT_8_8_8_8,
            AMGL_UNSIGNED_INT_10_10_10_2) && !detail::is_one_of(format, AMGL_RGBA, AMGL_BGRA), AMGL_INVALID_OPERATION, gs_context_mng);

        AM_SET_ERROR_FLAG_IF(format == AMGL_DEPTH_COMPONENT && !detail::is_one_of(
            internal_format, 
            AMGL_DEPTH_COMPONENT,
            AMGL_DEPTH_COMPONENT16,
            AMGL_DEPTH_COMPONENT24,
            AMGL_DEPTH_COMPONENT32), AMGL_INVALID_OPERATION , gs_context_mng);

        AM_SET_ERROR_FLAG_IF(detail::is_one_of(
            internal_format, 
            AMGL_DEPTH_COMPONENT,
            AMGL_DEPTH_COMPONENT16,
            AMGL_DEPTH_COMPONENT24,
            AMGL_DEPTH_COMPONENT32) && format != AMGL_DEPTH_COMPONENT, AMGL_INVALID_OPERATION , gs_context_mng);

        
        const uint32_t binded_pubo_user_range = CONV_KERNEL_TO_USER_SPACE(contxt.buf_bindings.pubo[0].buffer);
        if (!AM_IS_DEFAULT_ID_USER_SPACE(binded_pubo_user_range)) {
            AM_ASSERT_MSG(false, "Not impemented yet");

            // AM_SET_ERROR_FLAG_IF(gs_buffer_mng.is_buffer_mapped(binded_pubo_user_range), AMGL_INVALID_OPERATION , gs_context_mng);
            
            // const size_t pubo_size = gs_buffer_mng.get_buffer_size(binded_pubo_user_range);
            
            // AM_SET_ERROR_FLAG_IF(pubo_size > texture_buffer_size, AMGL_INVALID_OPERATION, gs_context_mng);

            // const uint32_t type_size_in_bytes = get_type_size(type);
            // AM_SET_ERROR_FLAG_IF(pubo_size % type_size_in_bytes != 0, AMGL_INVALID_OPERATION, gs_context_mng);
        } else {
            const uint32_t tex_kernel_range = gs_context_mng.get_binded_texture(target);
            
            if (!AM_IS_DEFAULT_ID_KERNEL_SPACE(tex_kernel_range)) {
                initialize_memory(tex_kernel_range, internal_format, format, type, width, data);

                m_textures.m_widths[tex_kernel_range]           = width;
                m_textures.m_heights[tex_kernel_range]          = 1u;
                m_textures.m_depths[tex_kernel_range]           = 1u;
                m_textures.m_internal_formats[tex_kernel_range] = internal_format;
                m_textures.m_types[tex_kernel_range]            = type;
                m_textures.m_targets[tex_kernel_range]          = target;
            }
        }
    }

    
    texture_mng::texture_mng(size_t preallocation_size)
    {
        resize(preallocation_size);
    }

    
    void texture_mng::initialize_memory(uint32_t texture, enum_t internal_format, 
        enum_t in_format, enum_t in_type, size_t pixel_count, const void *data)
    {
        using namespace detail;

        size_t tex_buffer_size = pixel_count * get_bytes_per_pixel(internal_format);
        
        
    }


    void texture_mng::initialize_memory(uint32_t texture, size_t size, const void *data)
    {
        textures::memory_block& mem_block = m_textures.m_memory_blocks[texture];
        
        mem_block.resize(size);
        if (data) {
            memcpy_s(mem_block.data(), size, data, size);
        }
    }

    
    void texture_mng::resize(size_t size) noexcept
    {
        m_textures.resize(size);
    }
}