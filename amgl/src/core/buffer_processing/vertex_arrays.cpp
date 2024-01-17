#include "pch.hpp"
#include "vertex_arrays.hpp"

namespace amgl
{
    vertex_arrays::vertex_arrays(uint32_t size)
        : m_vbo_ids(size), m_ebo_ids(size), m_layouts(size)
    {
    }
    
    
    uint32_t vertex_arrays::create_id() noexcept
    {
        AM_ASSERT(detail::are_equal(m_layouts.size(), m_vbo_ids.size(), m_ebo_ids.size()));
        const size_t buffer_size = m_vbo_ids.size();

        const uint32_t internal_id = m_id_pool.generate_id();
        if (internal_id >= buffer_size) {
            resize_buffers(static_cast<size_t>(buffer_size* 1.5f) + 1u);
        }
        return conv_internal_to_user_range(internal_id);
    }
    
    
    void vertex_arrays::free_id(uint32_t id) noexcept
    {
        const uint32_t internal_id = conv_user_to_inernal_range(id);
        m_id_pool.free_id(internal_id);
    }
    

    void vertex_arrays::bind_buffer_unsafe(uint32_t vertex_array, enum_t target, uint32_t buffer) noexcept
    {
        switch (target) {
        case AMGL_ARRAY_BUFFER:
            m_vbo_ids[vertex_array] = buffer;
            break;
        case AMGL_ELEMENT_ARRAY_BUFFER:
            m_ebo_ids[vertex_array] = buffer;
            break;
        }
    }

    void vertex_arrays::resize_buffers(uint32_t size) noexcept
    {
        m_layouts.resize(size);
        m_vbo_ids.resize(size);
        m_ebo_ids.resize(size);
    }
}