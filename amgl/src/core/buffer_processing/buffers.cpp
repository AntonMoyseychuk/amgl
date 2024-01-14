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
            m_memory_blocks.resize(static_cast<size_t>(m_memory_blocks.size() * 1.5f) + 1u);
        }
        return conv_internal_to_user_range(internal_id);
    }

    void buffers::free_id(uint32_t id) noexcept
    {
        const uint32_t internal_id = conv_user_to_inernal_range(id);
        m_id_pool.free_id(internal_id);
    }

    void buffers::allocate_memory_block(uint32_t id, size_t size) noexcept
    {
        const uint32_t internal_id = conv_user_to_inernal_range(id);
        AM_ASSERT(internal_id < m_memory_blocks.size());

        m_memory_blocks[internal_id].resize(size);
    }

    void buffers::deallocate_memory_block(uint32_t id) noexcept
    {
        const uint32_t internal_id = conv_user_to_inernal_range(id);
        AM_ASSERT(internal_id < m_memory_blocks.size());

        m_memory_blocks[internal_id].clear();
        m_memory_blocks[internal_id].shrink_to_fit();
    }

    void buffers::invalidate_memory_block(uint32_t id) noexcept
    {
        const uint32_t internal_id = conv_user_to_inernal_range(id);
        m_memory_blocks[internal_id].clear();
    }

    const buffers::memory_block *buffers::get_memory_block(uint32_t id) const noexcept
    {
        const uint32_t internal_id = conv_user_to_inernal_range(id);
        return internal_id < m_memory_blocks.size() ? &m_memory_blocks[internal_id] : nullptr;
    }

    buffers::memory_block *buffers::get_memory_block(uint32_t id) noexcept
    {
        const uint32_t internal_id = conv_user_to_inernal_range(id);
        return internal_id < m_memory_blocks.size() ? &m_memory_blocks[internal_id] : nullptr;
    }
}