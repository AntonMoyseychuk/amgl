#include "pch.hpp"
#include "images.hpp"


namespace amgl
{
    images::images(size_t size)
    {
        resize(size);
    }

    
    void images::set(uint32_t image, uint32_t width, uint32_t height, uint32_t depth) noexcept
    {
        m_widths[image]  = width;
        m_heights[image] = height;
        m_depths[image]  = depth;
    }

    
    void images::free_all() noexcept
    {
        m_memory_blocks.resize(0u);
        m_memory_blocks.shrink_to_fit();
        m_widths.resize(0u);
        m_widths.shrink_to_fit();
        m_heights.resize(0u);
        m_heights.shrink_to_fit();
        m_depths.resize(0u);
        m_depths.shrink_to_fit();
    }

    
    void images::resize(size_t size) noexcept
    {
        m_memory_blocks.resize(size);
        m_widths.resize(size, 0u);
        m_heights.resize(size, 0u);
        m_depths.resize(size, 0u);
    }
}