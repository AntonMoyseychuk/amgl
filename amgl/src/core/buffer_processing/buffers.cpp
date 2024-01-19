#include "pch.hpp"
#include "buffers.hpp"

namespace amgl
{
    buffers::buffers(uint32_t size)
    {
        resize_buffers(size);
    }


    uint32_t buffers::create_id() noexcept
    {
        const uint32_t id = m_id_pool.generate_id();
        if (id >= m_memory_blocks.size()) {
            resize_buffers(static_cast<size_t>(m_memory_blocks.size() * 1.5f) + 1u);
        }
        return id;
    }


    void buffers::free_id(uint32_t id) noexcept
    {
        deallocate_memory_block(id);
        m_id_pool.free_id(id);
    }


    void buffers::reallocate_memory_block(uint32_t id, size_t size) noexcept
    {
        AM_ASSERT(id < m_memory_blocks.size());
        m_memory_blocks[id].resize(size);
    }


    void buffers::deallocate_memory_block(uint32_t id) noexcept
    {
        AM_ASSERT(id < m_memory_blocks.size());

        m_memory_blocks[id].clear();
        m_memory_blocks[id].shrink_to_fit();
    }

    
    void buffers::shrink_buffer_to_size(uint32_t id, size_t size) noexcept
    {
        AM_ASSERT(id < m_memory_blocks.size());
        m_memory_blocks[id].resize(size);
        m_memory_blocks[id].shrink_to_fit();
    }

    
    const buffers::memory_block& buffers::get_memory_block(uint32_t id) const noexcept
    {
        AM_ASSERT(id < m_memory_blocks.size());
        return m_memory_blocks[id];
    }


    buffers::memory_block& buffers::get_memory_block(uint32_t id) noexcept
    {
        AM_ASSERT(id < m_memory_blocks.size());
        return m_memory_blocks[id];
    }

    
    void *buffers::map_buffer(uint32_t id) noexcept
    {
        AM_ASSERT(id < m_memory_blocks.size());
        AM_ASSERT(id < m_map_states.size());

        m_map_states[id] = true;
        return m_memory_blocks[id].data();
    }

    
    void buffers::unmap_buffer(uint32_t id) noexcept
    {
        AM_ASSERT(id < m_map_states.size());
        m_map_states[id] = false;
    }

    
    bool buffers::is_buffer_mapped(uint32_t id) const noexcept
    {
        AM_ASSERT(id < m_memory_blocks.size());
        return m_map_states[id];
    }


    bool buffers::is_buffer_exist(uint32_t id) const noexcept
    {
        return id == AM_DEFAULT_INTERNAL_ID || m_id_pool.is_busy(id);
    }
    

    void buffers::resize_buffers(uint32_t size) noexcept
    {
        m_memory_blocks.resize(size);
        m_map_states.resize(size);
    }
}