#include "pch.hpp"
#include "buffers.hpp"

namespace amgl
{
    buffers::buffers(uint32_t size)
        : m_memory_blocks(size)
    {
    }

    uint32_t buffers::create_id() noexcept
    {
        const uint32_t internal_id = m_id_pool.generate_id();
        if (internal_id >= m_memory_blocks.size()) {
            resize_buffers(static_cast<size_t>(m_memory_blocks.size() * 1.5f) + 1u);
        }
        return conv_internal_to_user_range(internal_id);
    }

    void buffers::free_id(uint32_t id) noexcept
    {
        deallocate_memory_block(id);

        const uint32_t internal_id = conv_user_to_inernal_range(id);
        m_id_pool.free_id(internal_id);
    }

    void buffers::allocate_memory_block(uint32_t id, size_t size) noexcept
    {
        RETURN_IF(is_default_id_user_range(id));

        const uint32_t internal_id = conv_user_to_inernal_range(id);
        AM_ASSERT(internal_id < m_memory_blocks.size());

        m_memory_blocks[internal_id].resize(size);
    }

    void buffers::deallocate_memory_block(uint32_t id) noexcept
    {
        RETURN_IF(is_default_id_user_range(id));

        const uint32_t internal_id = conv_user_to_inernal_range(id);
        AM_ASSERT(internal_id < m_memory_blocks.size());

        m_memory_blocks[internal_id].clear();
        m_memory_blocks[internal_id].shrink_to_fit();
    }

    const buffers::memory_block *buffers::get_memory_block(uint32_t id) const noexcept
    {
        RETURN_IF(is_default_id_user_range(id), nullptr);

        const uint32_t internal_id = conv_user_to_inernal_range(id);
        AM_ASSERT(internal_id < m_memory_blocks.size());

        return &m_memory_blocks[internal_id];
    }

    buffers::memory_block *buffers::get_memory_block(uint32_t id) noexcept
    {
        RETURN_IF(is_default_id_user_range(id), nullptr);

        const uint32_t internal_id = conv_user_to_inernal_range(id);
        AM_ASSERT(internal_id < m_memory_blocks.size());

        return &m_memory_blocks[internal_id];
    }

    bool buffers::is_buffer_mapped(uint32_t id) const noexcept
    {
        RETURN_IF(is_default_id_user_range(id), false);

        const uint32_t internal_id = conv_user_to_inernal_range(id);
        AM_ASSERT(internal_id < m_map_states.size());

        return m_map_states[internal_id];
    }

    void buffers::resize_buffers(uint32_t size) noexcept
    {
        m_memory_blocks.resize(size);
        m_map_states.resize(size);
    }
}