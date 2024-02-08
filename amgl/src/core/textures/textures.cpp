#include "pch.hpp"
#include "textures.hpp"


namespace amgl
{
    textures::textures(size_t size)
    {
        resize(size);
    }

    
    uint32_t textures::create_texture() noexcept
    {
        const size_t size  = m_memory_blocks.size();

        AM_ASSERT(detail::are_equal(size, m_widths.size(), m_heights.size(), m_depths.size(), m_targets.size()));

        const uint32_t id = m_id_pool.generate_id();
        if (id >= size) {
            resize(static_cast<size_t>(size * 1.5f) + 1u);
        }
        return id;
    }

    
    void textures::free_texture(uint32_t id) noexcept
    {
        m_targets[id] = AMGL_NONE;
        m_widths[id]  = 0u;
        m_heights[id] = 0u;
        m_depths[id]  = 0u;
        
        // deallocate memory

        m_id_pool.free_id(id);
    }

    
    bool textures::is_texture_exist(uint32_t id) const noexcept
    {
        return id == AM_DEFAULT_KERNEL_ID || m_id_pool.is_busy(id);
    }

    
    void textures::resize(size_t size) noexcept
    {
        m_memory_blocks.resize(size);
        m_widths.resize(size, 0u);
        m_heights.resize(size, 1u);
        m_depths.resize(size, 1u);
        m_formats.resize(size, AMGL_NONE);
        m_types.resize(size, AMGL_NONE);
        m_targets.resize(size, AMGL_NONE);
    }
}