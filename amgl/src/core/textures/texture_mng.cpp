#include "pch.hpp"
#include "texture_mng.hpp"

#include "core/core.hpp"
#include "core/utils/util_func.hpp"

#include "core/context/context_mng.hpp"
#include "core/buffers/buffer_mng.hpp"


static_assert(AM_INIT_TEX_COUNT > 0, "AM_INIT_TEXTURE_COUNT must be greater than 0");


namespace amgl
{
    static context_mng& gs_context_mng = context_mng::instance();
    static buffer_mng& gs_buffer_mng = buffer_mng::instance();


    #define CHECK_TEXTURE_TARGET_VALIDITY(target, error_flag, ...)                          \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(target,                                     \
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
            AMGL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY), error_flag, gs_context_mng, __VA_ARGS__)


    #define CHECK_TEXTURE_FORMAT_VALIDITY(format, error_flag, ...)                          \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(format,                                     \
            AMGL_RED,                                                                       \
            AMGL_RG,                                                                        \
            AMGL_RGB,                                                                       \
            AMGL_RGBA,                                                                      \
            AMGL_BGR,                                                                       \
            AMGL_RED_INTEGER,                                                               \
            AMGL_RG_INTEGER,                                                                \
            AMGL_RGB_INTEGER,                                                               \
            AMGL_BGR_INTEGER,                                                               \
            AMGL_RGBA_INTEGER,                                                              \
            AMGL_BGRA_INTEGER,                                                              \
            AMGL_STENCIL_INDEX,                                                             \
            AMGL_DEPTH_COMPONENT,                                                           \
            AMGL_DEPTH_STENCIL), error_flag, gs_context_mng, __VA_ARGS__)


    #define CHECK_TEXTURE_TYPE_VALIDITY(type, error_flag, ...)                              \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(type,                                       \
            AMGL_UNSIGNED_BYTE,                                                             \
            AMGL_BYTE,                                                                      \
            AMGL_UNSIGNED_SHORT,                                                            \
            AMGL_SHORT,                                                                     \
            AMGL_UNSIGNED_INT,                                                              \
            AMGL_INT,                                                                       \
            AMGL_FLOAT,                                                                     \
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
            AMGL_UNSIGNED_INT_2_10_10_10_REV), error_flag, gs_context_mng, __VA_ARGS__)


    #define CHECK_TEXTURE_INTERNAL_FORMAT_VALIDITY(internal_format, error_flag, ...)        \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(internal_format,                            \
            AMGL_DEPTH_COMPONENT,                                                           \
            AMGL_DEPTH_STENCIL,                                                             \
            AMGL_RED,                                                                       \
            AMGL_RG,                                                                        \
            AMGL_RGB,                                                                       \
            AMGL_RGBA,                                                                      \
            AMGL_R8,                                                                        \
            AMGL_R8_SNORM,                                                                  \
            AMGL_R16,                                                                       \
            AMGL_R16_SNORM,                                                                 \
            AMGL_RG8,                                                                       \
            AMGL_RG8_SNORM,                                                                 \
            AMGL_RG16,                                                                      \
            AMGL_RG16_SNORM,                                                                \
            AMGL_R3_G3_B2,                                                                  \
            AMGL_RGB4,                                                                      \
            AMGL_RGB5,                                                                      \
            AMGL_RGB8,                                                                      \
            AMGL_RGB8_SNORM,                                                                \
            AMGL_RGB10,                                                                     \
            AMGL_RGB12,                                                                     \
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
            AMGL_RGB9_E5,                                                                   \
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
            AMGL_RGBA32UI), error_flag, gs_context_mng, __VA_ARGS__)


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


    // Doesn't check 'type' validity
    // Returns 0 if 'type' is invalid
    static inline uint32_t texture_type_in_bytes(enum_t type) noexcept
    {
        switch (type) {
            case AMGL_UNSIGNED_BYTE:                    return 1u;
            case AMGL_BYTE:                             return 1u;
            case AMGL_UNSIGNED_SHORT:                   return 2u;
            case AMGL_SHORT:                            return 2u;
            case AMGL_UNSIGNED_INT:                     return 4u;
            case AMGL_INT:                              return 4u;
            case AMGL_FLOAT:                            return 4u;
            case AMGL_UNSIGNED_BYTE_3_3_2:              return 1u;
            case AMGL_UNSIGNED_BYTE_2_3_3_REV:          return 1u;
            case AMGL_UNSIGNED_SHORT_5_6_5:             return 2u;
            case AMGL_UNSIGNED_SHORT_5_6_5_REV:         return 2u;
            case AMGL_UNSIGNED_SHORT_4_4_4_4:           return 2u;
            case AMGL_UNSIGNED_SHORT_4_4_4_4_REV:       return 2u;
            case AMGL_UNSIGNED_SHORT_5_5_5_1:           return 2u;
            case AMGL_UNSIGNED_SHORT_1_5_5_5_REV:       return 2u;
            case AMGL_UNSIGNED_INT_8_8_8_8:             return 4u;
            case AMGL_UNSIGNED_INT_8_8_8_8_REV:         return 4u;
            case AMGL_UNSIGNED_INT_10_10_10_2:          return 4u;
            case AMGL_UNSIGNED_INT_2_10_10_10_REV:      return 4u;
            default:                                    return 0u;
        }
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
        // Not implemented yet
        // const uint32_t max_texture_level = log2(width) + 1u;
        // CHECK_TEXTURE_LOD_VALIDITY(level, max_texture_level, AMGL_INVALID_VALUE);

        AM_SET_ERROR_FLAG_IF(width > context::MAX_TEXTURE_SIZE, AMGL_INVALID_VALUE, gs_context_mng);
        AM_SET_ERROR_FLAG_IF(border != 0, AMGL_INVALID_VALUE, gs_context_mng);
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(target, AMGL_TEXTURE_1D, AMGL_PROXY_TEXTURE_1D), AMGL_INVALID_ENUM, gs_context_mng);

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

        AM_SET_ERROR_FLAG_IF(format != AMGL_RGB && detail::is_one_of(
            type, 
            AMGL_UNSIGNED_BYTE_3_3_2, 
            AMGL_UNSIGNED_BYTE_2_3_3_REV, 
            AMGL_UNSIGNED_SHORT_5_6_5, 
            AMGL_UNSIGNED_SHORT_5_6_5_REV), AMGL_INVALID_OPERATION, gs_context_mng);

        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(format, AMGL_RGBA) && detail::is_one_of(
            type, 
            AMGL_UNSIGNED_SHORT_4_4_4_4,
            AMGL_UNSIGNED_SHORT_4_4_4_4_REV,
            AMGL_UNSIGNED_SHORT_5_5_5_1,
            AMGL_UNSIGNED_SHORT_1_5_5_5_REV,
            AMGL_UNSIGNED_INT_8_8_8_8,
            AMGL_UNSIGNED_INT_8_8_8_8_REV,
            AMGL_UNSIGNED_INT_10_10_10_2,
            AMGL_UNSIGNED_INT_2_10_10_10_REV), AMGL_INVALID_OPERATION , gs_context_mng);

        static context& cont = gs_context_mng.get_context();
        const uint32_t binded_pubo_user_range = CONV_KERNEL_TO_USER_SPACE(cont.buf_bindings.pubo[0].buffer);
        if (!AM_IS_DEFAULT_ID_USER_SPACE(binded_pubo_user_range)) {
            AM_SET_ERROR_FLAG_IF(gs_buffer_mng.is_buffer_mapped(binded_pubo_user_range), AMGL_INVALID_OPERATION , gs_context_mng);
            
            const uint32_t type_size_in_bytes = texture_type_in_bytes(type);
            const size_t pubo_size = gs_buffer_mng.get_buffer_size(binded_pubo_user_range);
            AM_SET_ERROR_FLAG_IF(pubo_size % type_size_in_bytes != 0, AMGL_INVALID_OPERATION, gs_context_mng);
        }

        CHECK_TEXTURE_FORMAT_VALIDITY(format, AMGL_INVALID_ENUM);
        CHECK_TEXTURE_TYPE_VALIDITY(type, AMGL_INVALID_ENUM);
        CHECK_TEXTURE_INTERNAL_FORMAT_VALIDITY(internal_format, AMGL_INVALID_VALUE);

        
    }

    
    texture_mng::texture_mng(size_t preallocation_size)
    {
        resize(preallocation_size);
    }

    
    void texture_mng::resize(size_t size) noexcept
    {
        m_textures.resize(size);
    }
}