#pragma once
#include "amgl/amgl.hpp"

#include "core/context/context.hpp"
#include "core/utils/id_pool.hpp"

#include <vector>
#include <bitset>

namespace amgl
{      
    class vertex_arrays
    {
        friend class buffer_mng;
    public:
        vertex_arrays() = default;
        vertex_arrays(uint32_t size);

        /// @brief 
        /// @return Vertex array ID in the kernel range [0, UINT32_MAX - 1]
        uint32_t create_array() noexcept;

        /// @brief 
        /// @param id Vertex array object in the kernel range [0, UINT32_MAX - 1]
        void free_array(uint32_t id) noexcept;

        /// @brief 
        /// @param id Vertex array object in the kernel range [0, UINT32_MAX - 1]
        bool is_vertex_array_exist(uint32_t id) const noexcept;

        /// @brief 
        /// @param vertex_array Vertex array object in the kernel range [0, UINT32_MAX - 1]
        /// @param target Buffer target
        /// @param buffer Buffer object in the kernel range [0, UINT32_MAX - 1]
        /// @note Doesn't check 'vertex_array', 'target' and 'buffer' validity 
        void bind_buffer(uint32_t vertex_array, enum_t target, uint32_t buffer) noexcept;

        /// @brief 
        /// @param vertex_array Vertex array object in the kernel range [0, UINT32_MAX - 1]
        /// @param index Attribute index
        /// @param size Componets count
        /// @param type Type of component
        /// @param normalized Normalize flag
        /// @param stride Stride to same component
        /// @param pointer Stride to first component
        /// @note Doesn't check 'vertex_array', 'index', 'size', 'type', 'stride' and 'pointer' validity
        void set_attribute_desc(uint32_t vertex_array, uint32_t index, size_t size, enum_t type, 
            bool normalized, size_t stride, const void* pointer) noexcept;

    private:
        void resize(size_t size) noexcept;

    private:
        struct attributes
        {
            using enable_flags_storage = std::bitset<context::MAX_VERTEX_ATTRIB_BINDINGS>;

            struct layout_desc
            {
                uintptr_t pointer = 0u;
                size_t stride     = 0u;
                size_t size       = 4u;
                enum_t type       = AMGL_FLOAT;
                bool normalized   = false;
            };

            std::array<layout_desc, context::MAX_VERTEX_ATTRIB_BINDINGS> layout_descs;
        };

    private:
        std::vector<attributes> m_attributes;
        std::vector<attributes::enable_flags_storage> m_attributes_enable_flags;

        std::vector<uint32_t> m_vbo_ids;
        std::vector<uint32_t> m_ebo_ids;

        id_pool m_id_pool;
    };
}