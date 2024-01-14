#include "pch.hpp"
#include "vertex_arrays.hpp"

namespace amgl
{
    #define ENSURE_BUFFER_SIZES_SAMENESS() AM_ASSERT(m_layouts.size() == m_vbo_ids.size() == m_ebo_ids.size())

    vertex_arrays::vertex_arrays(uint32_t size)
        : m_vbo_ids(size), m_ebo_ids(size), m_layouts(size)
    {
    }
    
    uint32_t vertex_arrays::create_id() noexcept
    {
        const uint32_t internal_id = m_id_pool.generate_id();

        ENSURE_BUFFER_SIZES_SAMENESS();
        const size_t buffer_size = m_vbo_ids.size();
        if (internal_id >= buffer_size) {
            resize_buffers(static_cast<size_t>(buffer_size* 1.5f) + 1u);
        }
        return detail::conv_internal_to_user_range(internal_id);
    }
    
    void vertex_arrays::free_id(uint32_t id) noexcept
    {
        const uint32_t internal_id = detail::conv_user_to_inernal_range(id);
        m_id_pool.free_id(internal_id);
    }
    
    void vertex_arrays::resize_buffers(uint32_t size) noexcept
    {
        m_layouts.resize(size);
        m_vbo_ids.resize(size);
        m_ebo_ids.resize(size);
    }
}