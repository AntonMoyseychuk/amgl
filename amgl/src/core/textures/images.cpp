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

        AM_ASSERT(detail::are_equal(size, m_widths.size(), m_heights.size(), m_depths.size()));

        const uint32_t image = m_id_pool.generate_id();
        if (image >= size) {
            resize(static_cast<size_t>(size * 1.5f) + 1u);
        }
        return image;
    }

    
    void images::free_image(uint32_t image) noexcept
    {
        set(image, 0u, 0u, 0u);
        
        m_memory_blocks[image].resize(0);
        m_memory_blocks[image].shrink_to_fit();

        m_id_pool.free_id(image);
    }

    
    bool images::is_image_exist(uint32_t image) const noexcept
    {
        return image == AM_DEFAULT_KERNEL_ID || m_id_pool.is_busy(image);
    }

    
    void images::set(uint32_t image, uint32_t width, uint32_t height, uint32_t depth) noexcept
    {
        m_widths[image]           = width;
        m_heights[image]          = height;
        m_depths[image]           = depth;
        
    }

    
    void images::resize(size_t size) noexcept
    {
        m_memory_blocks.resize(size);
        m_widths.resize(size, 0u);
        m_heights.resize(size, 0u);
        m_depths.resize(size, 0u);
    }
    
    
    texture_descs::texture_descs(size_t size)
    {
        resize(size);
    }
    
    
    void texture_descs::set(uint32_t image, enum_t target, enum_t internal_format, bool interpret_as_integer) noexcept
    {
        m_internal_formats[image] = internal_format;
        m_targets[image]          = target;
        m_are_integers[image]     = interpret_as_integer;
    }
    
    
    void texture_descs::resize(size_t size) noexcept
    {
        m_internal_formats.resize(size, AMGL_NONE);
        m_targets.resize(size, AMGL_NONE);
        m_are_integers.resize(size, false);
    }
}