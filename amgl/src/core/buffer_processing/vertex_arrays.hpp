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
        attribute_layout() 
            : mem_mappings(), types(), normalized_flags(), enable_flags()
        {
            std::fill_n(types.begin(), types.size(), AMGL_FLOAT);
        }

        struct memory_mapping
        {
            uintptr_t pointer = 0u;
            size_t stride     = 0u;
            size_t size       = 4u;
        };

        std::array<memory_mapping, context::MAX_VERTEX_ATTRIB_BINDINGS> mem_mappings;
        std::array<enum_t, context::MAX_VERTEX_ATTRIB_BINDINGS> types;
        std::bitset<context::MAX_VERTEX_ATTRIB_BINDINGS> normalized_flags;
        std::bitset<context::MAX_VERTEX_ATTRIB_BINDINGS> enable_flags;
    };

    class vertex_arrays
    {
        friend class buffer_mng;
    public:
        vertex_arrays() = default;
        vertex_arrays(uint32_t size);

        // RETURNS: Vertex array ID in the internal range [0, UINT32_MAX - 1]
        uint32_t create_array() noexcept;
        // NOTE: Takes 'id' in the internal range [0, UINT32_MAX - 1]
        void free_array(uint32_t id) noexcept;

        // NOTE: Takes 'id' in the internal range [0, UINT32_MAX - 1]
        bool is_vertex_array_exist(uint32_t id) const noexcept;

        // NOTE: Takes 'vertex_array' and 'buffer' in the internal range [0, UINT32_MAX - 1]
        // NOTE: Doesn't check 'target', 'buffer' and 'vertex_array' validity
        void bind_buffer_unsafe(uint32_t vertex_array, enum_t target, uint32_t buffer) noexcept;

        // NOTE: Takes 'vertex_array' in the internal range [0, UINT32_MAX - 1]
        // NOTE: Doesn't check 'vertex_array', 'index', 'size', 'type', 'stride' and 'pointer' validity
        void set_layout(uint32_t vertex_array, uint32_t index, size_t size, enum_t type, bool normalized, size_t stride, const void* pointer) noexcept;
        // NOTE: Takes 'vertex_array' in the internal range [0, UINT32_MAX - 1]
        // NOTE: Doesn't check 'size' validity
        void set_layout_size(uint32_t vertex_array, uint32_t index, size_t size) noexcept;
        // NOTE: Takes 'vertex_array' in the internal range [0, UINT32_MAX - 1]
        // NOTE: Doesn't check 'vertex_array', 'index' and 'stride' validity
        void set_layout_stride(uint32_t vertex_array, uint32_t index, size_t stride) noexcept;
        // NOTE: Takes 'vertex_array' in the internal range [0, UINT32_MAX - 1]
        // NOTE: Doesn't check 'vertex_array', 'index' and 'pointer' validity
        void set_layout_pointer(uint32_t vertex_array, uint32_t index, const void* pointer) noexcept;
        // NOTE: Takes 'vertex_array' in the internal range [0, UINT32_MAX - 1]
        // NOTE: Doesn't check 'vertex_array', 'index' and 'type' validity
        void set_layout_type(uint32_t vertex_array, uint32_t index, enum_t type) noexcept;
        // NOTE: Takes 'vertex_array' in the internal range [0, UINT32_MAX - 1]
        // NOTE: Doesn't check 'vertex_array', 'index' and 'normalized' validity
        void set_layout_normalized(uint32_t vertex_array, uint32_t index, bool normalized) noexcept;

    private:
        void resize_buffers(uint32_t size) noexcept;

    private:
        std::vector<attribute_layout> m_layouts;
        std::vector<uint32_t> m_vbo_ids;
        std::vector<uint32_t> m_ebo_ids;

        id_pool m_id_pool;
    };
}