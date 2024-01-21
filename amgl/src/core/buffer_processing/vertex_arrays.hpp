#pragma once
#include "amgl/amgl.hpp"

#include "core/context_processing/context.hpp"
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

        memory_mapping mem_mappings[context::MAX_VERTEX_ATTRIB_BINDINGS] {};
        enum_t types[context::MAX_VERTEX_ATTRIB_BINDINGS] {};
        std::bitset<context::MAX_VERTEX_ATTRIB_BINDINGS> normalized_flags {};
        std::bitset<context::MAX_VERTEX_ATTRIB_BINDINGS> enable_flags {};
    };

    class vertex_arrays
    {
        friend class buffer_mng;
    public:
        vertex_arrays() = default;
        vertex_arrays(uint32_t size);

        // Returns 'id' in the internal range [0, UINT32_MAX - 1]
        uint32_t create_array() noexcept;
        // Takes 'id' in the internal range [0, UINT32_MAX - 1]
        void free_array(uint32_t id) noexcept;

        // Takes 'id' in the internal range [0, UINT32_MAX - 1]
        bool is_vertex_array_exist(uint32_t id) const noexcept;

        // Takes 'buffer' and 'vertex_array' in the internal range [0, UINT32_MAX - 1]
        // Doesn't check 'target', 'buffer' and 'vertex_array' validity
        void bind_buffer_unsafe(uint32_t vertex_array, enum_t target, uint32_t buffer) noexcept;

    private:
        void resize_buffers(uint32_t size) noexcept;

    private:
        std::vector<attribute_layout> m_layouts;
        std::vector<uint32_t> m_vbo_ids;
        std::vector<uint32_t> m_ebo_ids;

        id_pool m_id_pool;
    };
}