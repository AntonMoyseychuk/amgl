#include "pch.hpp"
#include "vertex_arrays.hpp"

namespace amgl
{
    vertex_arrays::vertex_arrays(uint32_t size)
    {
        resize(size);
    }
    
    
    uint32_t vertex_arrays::create_array() noexcept
    {
        AM_ASSERT(detail::are_equal(m_attributes.size(), m_vbo_ids.size(), m_ebo_ids.size()));
        const size_t buffer_size = m_vbo_ids.size();

        const uint32_t id = m_id_pool.generate_id();
        if (id >= buffer_size) {
            resize(static_cast<size_t>(buffer_size* 1.5f) + 1u);
        }
        return id;
    }
    
    
    void vertex_arrays::free_array(uint32_t id) noexcept
    {
        m_id_pool.free_id(id);
    }

    
    bool vertex_arrays::is_vertex_array_exist(uint32_t id) const noexcept
    {
        return id == AM_DEFAULT_KERNEL_ID || m_id_pool.is_busy(id);
    }

    
    void vertex_arrays::bind_buffer(uint32_t vertex_array, enum_t target, uint32_t buffer) noexcept
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

    
    void vertex_arrays::set_attribute_desc(uint32_t vertex_array, uint32_t index, size_t size, enum_t type, bool normalized, size_t stride, const void *pointer) noexcept
    {
        attributes::layout_desc& desc = m_attributes[vertex_array].layout_descs[index];
        desc.size       = size;
        desc.stride     = stride;
        desc.pointer    = uintptr_t(pointer);
        desc.type       = type;
        desc.normalized = normalized;
    }

    
    void vertex_arrays::resize(size_t size) noexcept
    {
        m_attributes.resize(size);
        m_attributes_enable_flags.resize(size);
        
        m_vbo_ids.resize(size, AM_DEFAULT_KERNEL_ID);
        m_ebo_ids.resize(size, AM_DEFAULT_KERNEL_ID);
        m_id_pool.reserve(size);
    }
}