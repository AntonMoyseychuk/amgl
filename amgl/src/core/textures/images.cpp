#include "pch.hpp"
#include "images.hpp"


namespace amgl
{
    images::images(size_t size)
    {
        resize(size);
    }

    
    uint32_t images::create_image() noexcept
    {
        const size_t size  = m_memory_blocks.size();

        AM_ASSERT(detail::are_equal(size, m_widths.size(), m_heights.size(), m_depths.size(), m_targets.size()));

        const uint32_t id = m_id_pool.generate_id();
        if (id >= size) {
            resize(static_cast<size_t>(size * 1.5f) + 1u);
        }
        return id;
    }

    
    void images::free_image(uint32_t id) noexcept
    {
        set(id, AMGL_NONE, 0u, 0u, 0u, AMGL_NONE, AMGL_NONE);
        
        m_memory_blocks[id].resize(0);
        m_memory_blocks[id].shrink_to_fit();

        m_id_pool.free_id(id);
    }

    
    bool images::is_image_exist(uint32_t id) const noexcept
    {
        return id == AM_DEFAULT_KERNEL_ID || m_id_pool.is_busy(id);
    }

    
    void images::set(uint32_t id, enum_t target, uint32_t width, uint32_t height, uint32_t depth, enum_t internal_format, enum_t format) noexcept
    {
        m_widths[id]           = width;
        m_heights[id]          = height;
        m_depths[id]           = depth;
        m_internal_formats[id] = internal_format;
        m_formats[id]          = format;
        m_targets[id]          = target;
    }

    
    void images::resize(size_t size) noexcept
    {
        m_memory_blocks.resize(size);
        m_widths.resize(size, 0u);
        m_heights.resize(size, 0u);
        m_depths.resize(size, 0u);
        m_internal_formats.resize(size, AMGL_NONE);
        m_formats.resize(size, AMGL_NONE);
        m_targets.resize(size, AMGL_NONE);
    }
}