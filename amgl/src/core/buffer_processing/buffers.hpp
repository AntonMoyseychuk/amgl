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
        using memory_block = std::vector<byte_t>;

    public:
        buffers() = default;
        buffers(uint32_t size);

        uint32_t create_id() noexcept;
        void free_id(uint32_t id) noexcept;

        void allocate_memory_block(uint32_t id, size_t size) noexcept;
        void deallocate_memory_block(uint32_t id) noexcept;

        const memory_block* get_memory_block(uint32_t id) const noexcept;
        memory_block* get_memory_block(uint32_t id) noexcept;

    private:
        std::vector<memory_block> m_memory_blocks;
        id_pool m_id_pool;
    };
}