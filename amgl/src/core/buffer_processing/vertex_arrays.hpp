#pragma once
#include "amgl/amgl.hpp"

#include "core/state_processing/context.hpp"
#include "core/utils/id_pool.hpp"

#include <vector>
#include <bitset>

namespace amgl
{
    struct attribute_layout
    {
        struct memory_mapping
        {
            uintptr_t pointer = 0u;
            size_t stride     = 0u;
            size_t size       = 0u;
        };

        memory_mapping mem_mappings[context::MAX_VERTEX_ATTRIBS_COUNT] {};
        enum_t types[context::MAX_VERTEX_ATTRIBS_COUNT] {};
        std::bitset<context::MAX_VERTEX_ATTRIBS_COUNT> normalized_flags {};
        std::bitset<context::MAX_VERTEX_ATTRIBS_COUNT> enable_flags {};
    };

    class vertex_arrays
    {
    public:
        vertex_arrays() = default;
        vertex_arrays(uint32_t size);

        uint32_t create_id() noexcept;
        void free_id(uint32_t id) noexcept;

    private:
        void resize_buffers(uint32_t size) noexcept;

    private:
        std::vector<attribute_layout> m_layouts;
        std::vector<uint32_t> m_vbo_ids;
        std::vector<uint32_t> m_ebo_ids;

        id_pool m_id_pool;
    };
}