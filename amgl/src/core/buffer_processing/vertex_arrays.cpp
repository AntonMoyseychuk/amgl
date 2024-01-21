#include "pch.hpp"
#include "vertex_arrays.hpp"

namespace amgl
{
    vertex_arrays::vertex_arrays(uint32_t size)
    {
        resize_buffers(size);
    }
    
    
    uint32_t vertex_arrays::create_array() noexcept
    {
        AM_ASSERT(detail::are_equal(m_layouts.size(), m_vbo_ids.size(), m_ebo_ids.size()));
        const size_t buffer_size = m_vbo_ids.size();

        const uint32_t id = m_id_pool.generate_id();
        if (id >= buffer_size) {
            resize_buffers(static_cast<size_t>(buffer_size* 1.5f) + 1u);
        }
        return id;
    }
    
    
    void vertex_arrays::free_array(uint32_t id) noexcept
    {
        m_id_pool.free_id(id);
    }

    
    bool vertex_arrays::is_vertex_array_exist(uint32_t id) const noexcept
    {
        return id == AM_DEFAULT_INTERNAL_ID || m_id_pool.is_busy(id);
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

    
    void vertex_arrays::set_layout(uint32_t vertex_array, uint32_t index, size_t size, enum_t type, bool normalized, size_t stride, const void *pointer) noexcept
    {
        attribute_layout& layout = m_layouts[vertex_array];

        attribute_layout::memory_mapping& mm = layout.mem_mappings[index];
        mm.size     = size;
        mm.stride   = stride;
        mm.pointer  = (uintptr_t)pointer;

        layout.types[index]                 = type;
        layout.normalized_flags[index]      = normalized;
    }

    
    void vertex_arrays::set_layout_size(uint32_t vertex_array, uint32_t index, size_t size) noexcept
    {
        m_layouts[vertex_array].mem_mappings[index].size = size;
    }


    void vertex_arrays::set_layout_stride(uint32_t vertex_array, uint32_t index, size_t stride) noexcept
    {
        m_layouts[vertex_array].mem_mappings[index].stride = stride;
    }

    
    void vertex_arrays::set_layout_pointer(uint32_t vertex_array, uint32_t index, const void *pointer) noexcept
    {
        m_layouts[vertex_array].mem_mappings[index].pointer = (uintptr_t)pointer;
    }

    
    void vertex_arrays::set_layout_type(uint32_t vertex_array, uint32_t index, enum_t type) noexcept
    {
        m_layouts[vertex_array].types[index] = type;
    }

    
    void vertex_arrays::set_layout_normalized(uint32_t vertex_array, uint32_t index, bool normalized) noexcept
    {
        m_layouts[vertex_array].normalized_flags[index] = normalized;
    }

    
    void vertex_arrays::resize_buffers(uint32_t size) noexcept
    {
        m_layouts.resize(size);
        m_vbo_ids.resize(size, AM_DEFAULT_INTERNAL_ID);
        m_ebo_ids.resize(size, AM_DEFAULT_INTERNAL_ID);
    }
}