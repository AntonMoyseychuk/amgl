#include "pch.hpp"
#include "texture_mng.hpp"

#include "core/core.hpp"

static_assert(AM_INIT_TEX_COUNT > 0, "AM_INIT_TEXTURE_COUNT must be greater than 0");


namespace amgl
{
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

    
    texture_mng::texture_mng(size_t preallocation_size)
    {
        resize(preallocation_size);
    }

    
    void texture_mng::resize(size_t size) noexcept
    {
        m_textures.resize(size);
    }
}