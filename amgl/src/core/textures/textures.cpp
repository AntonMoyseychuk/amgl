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
        const size_t storages_size  = m_memory_blocks.size();
        const size_t widths_size    = m_widths.size();
        const size_t heights_size   = m_heights.size();
        const size_t depths_size    = m_depths.size();
        const size_t targets_size   = m_targets.size();

        AM_ASSERT(detail::are_equal(storages_size, widths_size, heights_size, depths_size, targets_size));

        const uint32_t id = m_id_pool.generate_id();
        if (id >= storages_size) {
            resize(static_cast<size_t>(storages_size * 1.5f) + 1u);
        }
        return id;
    }

    
    void textures::free_texture(uint32_t id) noexcept
    {
        m_id_pool.free_id(id);
    }

    
    bool textures::is_texture_exist(uint32_t id) const noexcept
    {
        return id == AM_DEFAULT_KERNEL_ID || m_id_pool.is_busy(id);
    }

    
    void textures::resize(size_t size) noexcept
    {
        m_memory_blocks.resize(size);
        m_widths.resize(size);
        m_heights.resize(size);
        m_depths.resize(size);
        m_targets.resize(size);
    }
}