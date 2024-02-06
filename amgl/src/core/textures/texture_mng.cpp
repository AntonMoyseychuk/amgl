#include "pch.hpp"
#include "texture_mng.hpp"

#include "core/core.hpp"
#include "core/context/context_mng.hpp"


static_assert(AM_INIT_TEX_COUNT > 0, "AM_INIT_TEXTURE_COUNT must be greater than 0");


namespace amgl
{
    static context_mng& gs_context_mng = context_mng::instance();


    #define CHECK_TEXTURE_TARGET_VALIDITY(target, error_flag, ...)                          \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(target,                                     \
            AMGL_TEXTURE_BUFFER,                                                            \
            AMGL_TEXTURE_1D,                                                                \
            AMGL_TEXTURE_2D,                                                                \
            AMGL_TEXTURE_3D,                                                                \
            AMGL_TEXTURE_1D_ARRAY,                                                          \
            AMGL_TEXTURE_2D_ARRAY,                                                          \
            AMGL_TEXTURE_RECTANGLE,                                                         \
            AMGL_TEXTURE_CUBE_MAP,                                                          \
            AMGL_TEXTURE_CUBE_MAP_ARRAY,                                                    \
            AMGL_TEXTURE_2D_MULTISAMPLE,                                                    \
            AMGL_TEXTURE_2D_MULTISAMPLE_ARRAY), error_flag, gs_context_mng, __VA_ARGS__)


    // Takes 'texture' in the kernel range [0, UINT32_MAX - 1]
    // Doesn't check 'target' validity
    #define CHECK_TARGET_COMPATIBILITY(target, texture, error_flag, ...)                                                    \
    {                                                                                                                       \
        const enum_t curr_target = m_textures.m_targets[texture].target;                                                    \
        AM_SET_ERROR_FLAG_IF(curr_target != AMGL_NONE && curr_target != target, error_flag, gs_context_mng, __VA_ARGS__);   \
    }

    // Takes 'texture' in the kernel range [0, UINT32_MAX - 1]
    #define CHECK_TEXTURE_VALIDITY(texture, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(!m_textures.is_texture_exist(texture), error_flag, gs_context_mng, __VA_ARGS__)

    // Takes 'texture' in the kernel range [0, UINT32_MAX - 1]
    #define CHECK_TEXTURE_NOT_DEFAULT(texture, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(texture), error_flag, gs_context_mng, __VA_ARGS__)


    void texture_mng::gen_textures(size_t n, uint32_t* textures) noexcept
    {
        AM_RETURN_IF(!textures);

        for (uint32_t i = 0u; i < n; ++i) {
            textures[i] = CONV_KERNEL_TO_USER_RANGE(m_textures.create_texture());
        }
    }

    
    void texture_mng::delete_textures(size_t n, const uint32_t *textures) noexcept
    {
        AM_RETURN_IF(!textures);

        for (uint32_t i = 0u; i < n; ++i) {
            const uint32_t kernel_id = CONV_USER_TO_KERNEL_RANGE(textures[i]);
            AM_CONTINUE_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(kernel_id) || !m_textures.is_texture_exist(kernel_id));
            
            m_textures.free_texture(kernel_id);
        }
    }

    
    void texture_mng::bind_texture(enum_t target, uint32_t texture) noexcept
    {
        CHECK_TEXTURE_TARGET_VALIDITY(target, AMGL_INVALID_ENUM);

        const uint32_t kernel_tex_id = CONV_USER_TO_KERNEL_RANGE(texture);
        CHECK_TEXTURE_VALIDITY(kernel_tex_id, AMGL_INVALID_VALUE);

        if (!AM_IS_DEFAULT_ID_KERNEL_SPACE(kernel_tex_id)) {
            CHECK_TARGET_COMPATIBILITY(target, kernel_tex_id, AMGL_INVALID_OPERATION);
            m_textures.m_targets[kernel_tex_id].target = target;
        }

        gs_context_mng.bind_target_texture(target, kernel_tex_id);
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