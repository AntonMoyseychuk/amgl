#pragma once
#include "buffers.hpp"
#include "vertex_arrays.hpp"

namespace amgl
{
    class buffer_mng
    {
    public:
        static buffer_mng& instance() noexcept
        {
            #ifdef AMGL_CFG_PREALLOCATION_SIZE
                static buffer_mng manager(AMGL_CFG_PREALLOCATION_SIZE);
            #else
                static buffer_mng manager;
            #endif
            return manager;
        }

        buffer_mng(const buffer_mng&) = delete;
        buffer_mng& operator=(const buffer_mng&) = delete;

        void gen_buffers(uint32_t n, uint32_t* buffers) noexcept;
        // Clears memory allocated for 'buffer' but doesn't free buffer id
        // Takes 'buffers' in the user range [1, UINT32_MAX]
        void invalidate_buffer_data(uint32_t buffer) noexcept;
        // Clears memory allocated for 'buffers' and buffers ids
        // Takes 'buffers' in the user range [1, UINT32_MAX]
        void delete_buffers(uint32_t n, const uint32_t* buffers) noexcept;

        // Takes 'buffer' in the user range [1, UINT32_MAX]
        void bind_buffer(enum_t target, uint32_t buffer) noexcept;

        // Takes 'buffer' in the user range [1, UINT32_MAX]
        void bind_buffer_base(enum_t target, uint32_t index, uint32_t buffer) noexcept;
        // Takes 'buffers' in the user range [1, UINT32_MAX]
        void bind_buffers_base(enum_t target, uint32_t first, size_t count, const uint32_t* buffers) noexcept;

        // Takes 'buffer' in the user range [1, UINT32_MAX]
        void bind_buffer_range(enum_t target, uint32_t index, uint32_t buffer, size_t offset, size_t size) noexcept;
        // Takes 'buffers' in the user range [1, UINT32_MAX]
        void bind_buffers_range(enum_t target, uint32_t first, size_t count, 
            const uint32_t *buffers, const size_t *offsets, const size_t *sizes) noexcept;

        void buffer_data(enum_t target, size_t size, const void *data, enum_t usage /* unused */) noexcept;
        // Takes 'buffer' in the user range [1, UINT32_MAX]
        void named_buffer_data(uint32_t buffer, size_t size, const void *data, enum_t usage /* unused */) noexcept;

        void buffer_sub_data(enum_t target, size_t offset, size_t size, const void *data) noexcept;
        // Takes 'buffer' in the user range [1, UINT32_MAX]
        void named_buffer_sub_data(uint32_t buffer, size_t offset, size_t size, const void *data) noexcept;

        void copy_buffer_sub_data(enum_t read_target, enum_t write_target, size_t read_offset, size_t write_offset, size_t size) noexcept;
        // Takes 'read_buffer' and 'write_buffer' in the user range [1, UINT32_MAX]
        void copy_named_buffer_sub_data(uint32_t read_buffer, uint32_t write_buffer, size_t read_offset, size_t write_offset, size_t size) noexcept;

        void get_buffer_sub_data(enum_t target, size_t offset, size_t size, void* data) noexcept;
        // Takes 'buffer' in the user range [1, UINT32_MAX]
        void get_named_buffer_sub_data(uint32_t buffer, size_t offset, size_t size, void* data) noexcept;

        void set_vertex_attrib_array_state(uint32_t index, bool enabled) noexcept;
        // Takes 'vaobj' in the user range [1, UINT32_MAX]
        void set_vertex_array_attrib_state(uint32_t vaobj, uint32_t index, bool enabled) noexcept;

        void* map_buffer(enum_t target, enum_t access /* unused */) noexcept;
        // Takes 'buffer' in the user range [1, UINT32_MAX]
        void* map_named_buffer(uint32_t buffer, enum_t access /* unused */) noexcept;
        void unmap_buffer(enum_t target) noexcept;
        // Takes 'buffer' in the user range [1, UINT32_MAX]
        void unmap_named_buffer(uint32_t buffer) noexcept;

        // Takes 'buffer' in the user range [1, UINT32_MAX]
        bool is_buffer(uint32_t buffer) noexcept;

        void gen_vertex_arrays(size_t n, uint32_t* arrays) noexcept;
        // Takes 'array' in the user range [1, UINT32_MAX]
        void bind_vertex_array(uint32_t array) noexcept;
        // Takes 'arrays' in the user range [1, UINT32_MAX]
        void delete_vertex_arrays(size_t n, const uint32_t* arrays) noexcept;
        // Takes 'array' in the user range [1, UINT32_MAX]
        bool is_vertex_array(uint32_t array) noexcept;

    private:
        buffer_mng() = default;
        buffer_mng(size_t preallocation_size);

    private:
        buffers m_buffers;
        vertex_arrays m_vertex_arrays;
    };
}