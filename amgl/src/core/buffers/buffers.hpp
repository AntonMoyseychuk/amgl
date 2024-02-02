#pragma once
#include "amgl/amgl.hpp"

#include "core/utils/id_pool.hpp"

#include <vector>


namespace amgl
{
    class buffers
    {
        friend class buffer_mng;
    public:
        using memory_block = std::vector<ubyte_t>;

    public:
        buffers() = default;
        buffers(uint32_t size);

        // RETURNS: ID in the kernel range [0, UINT32_MAX - 1]
        uint32_t create_buffer() noexcept;
        // NOTE: Takes 'id' in the kernel range [0, UINT32_MAX - 1]
        void free_buffer(uint32_t id) noexcept;

        // NOTE: Takes 'id' in the kernel range [0, UINT32_MAX - 1]
        void reallocate_memory_block(uint32_t id, size_t size) noexcept;
        // NOTE: Takes 'id' in the kernel range [0, UINT32_MAX - 1]
        void deallocate_memory_block(uint32_t id) noexcept;
        // NOTE: Takes 'id' in the kernel range [0, UINT32_MAX - 1]
        void shrink_buffer_to_size(uint32_t id, size_t size) noexcept;

        // NOTE: Takes 'id' in the kernel range [0, UINT32_MAX - 1]
        const memory_block& get_memory_block(uint32_t id) const noexcept;
        // NOTE: Takes 'id' in the kernel range [0, UINT32_MAX - 1]
        memory_block& get_memory_block(uint32_t id) noexcept;

        // NOTE: Takes 'id' in the kernel range [0, UINT32_MAX - 1]
        void* map_buffer(uint32_t id) noexcept;
        // NOTE: Takes 'id' in the kernel range [0, UINT32_MAX - 1]
        void unmap_buffer(uint32_t id) noexcept;

        // NOTE: Takes 'id' in the kernel range [0, UINT32_MAX - 1]
        bool is_buffer_mapped(uint32_t id) const noexcept;

        // NOTE: Takes 'id' in the kernel range [0, UINT32_MAX - 1]
        bool is_buffer_exist(uint32_t id) const noexcept;

    private:
        void resize(uint32_t size) noexcept;

    private:
        std::vector<memory_block> m_memory_blocks;
        std::vector<bool> m_map_states;
        
        id_pool m_id_pool;
    };
}