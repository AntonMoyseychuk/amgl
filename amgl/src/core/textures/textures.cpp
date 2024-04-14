#include "pch.hpp"
#include "textures.hpp"

namespace amgl
{
    texture_descs::texture_descs(size_t size)
    {
        resize(size);
    }
    
    
    void texture_descs::set(uint32_t texture, enum_t target, enum_t internal_format, bool interpret_as_integer) noexcept
    {
        m_internal_formats[texture] = internal_format;
        m_targets[texture]          = target;
        m_are_integers[texture]     = interpret_as_integer;
    }
    
    
    void texture_descs::resize(size_t size) noexcept
    {
        m_internal_formats.resize(size, AMGL_NONE);
        m_targets.resize(size, AMGL_NONE);
        m_are_integers.resize(size, false);
    }
    
    
    LOD_root::LOD_root(size_t size)
    {
        resize(size);
    }
    
    
    void LOD_root::resize(size_t size) noexcept
    {
        m_images.resize(size);
    }
    
    
    textures::textures(size_t size)
    {
        resize(size);
    }
    
    
    uint32_t textures::create_texture() noexcept
    {
        const size_t size = get_count();

        const uint32_t texture = m_id_pool.generate_id();
        if (texture >= size) {
            resize(static_cast<size_t>(size * 1.5f) + 1u);
        }

        return texture;
    }

    
    void textures::free_texture(uint32_t texture) noexcept
    {
        m_LOD_roots.at(texture).m_images.free_all();
        m_tex_descs.set(texture, AMGL_NONE, AMGL_NONE, false);

        m_id_pool.free_id(texture);
    }

    
    bool textures::is_texture_exist(uint32_t texture) const noexcept
    {
        return texture == AM_DEFAULT_KERNEL_ID || m_id_pool.is_busy(texture);
    }

    
    void textures::resize(size_t size) noexcept
    {
        m_LOD_roots.resize(size);
        m_tex_descs.resize(size);
    }
}