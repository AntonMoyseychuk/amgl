#pragma once
#include "buffers.hpp"
#include "vertex_arrays.hpp"

#include "core/core.hpp"
#include "core/context/context_mng.hpp"

namespace amgl
{
    class buffer_mng
    {
    public:
        static buffer_mng& instance() noexcept
        {
            static buffer_mng manager(AM_INIT_BUFF_COUNT);
            return manager;
        }

        buffer_mng(const buffer_mng&) = delete;
        buffer_mng& operator=(const buffer_mng&) = delete;

        void gen_buffers(uint32_t n, uint32_t* buffers) noexcept;
        // Clears memory allocated for 'buffer' but doesn't free buffer id
        // NOTE: Takes 'buffers' in the user range [1, UINT32_MAX]
        void invalidate_buffer_data(uint32_t buffer) noexcept;
        // Clears memory allocated for 'buffers' and buffers ids
        // NOTE: Takes 'buffers' in the user range [1, UINT32_MAX]
        void delete_buffers(uint32_t n, const uint32_t* buffers) noexcept;

        // NOTE: Takes 'buffer' in the user range [1, UINT32_MAX]
        void bind_buffer(enum_t target, uint32_t buffer) noexcept;

        // NOTE: Takes 'buffer' in the user range [1, UINT32_MAX]
        void bind_buffer_base(enum_t target, uint32_t index, uint32_t buffer) noexcept;
        // NOTE: Takes 'buffers' in the user range [1, UINT32_MAX]
        void bind_buffers_base(enum_t target, uint32_t first, size_t count, const uint32_t* buffers) noexcept;

        // NOTE: Takes 'buffer' in the user range [1, UINT32_MAX]
        // NOTE: If 'offset' or 'size' are nullptr than 'offset' is considered to be zero and 'size' is the size of buffer
        void bind_buffer_range(enum_t target, uint32_t index, uint32_t buffer, const size_t* offset, const size_t* size) noexcept;
        // NOTE: Takes 'buffers' in the user range [1, UINT32_MAX]
        void bind_buffers_range(enum_t target, uint32_t first, size_t count, 
            const uint32_t *buffers, const size_t *offsets, const size_t *sizes) noexcept;

        void buffer_data(enum_t target, size_t size, const void *data, enum_t usage /* unused */) noexcept;
        // NOTE: Takes 'buffer' in the user range [1, UINT32_MAX]
        void named_buffer_data(uint32_t buffer, size_t size, const void *data, enum_t usage /* unused */) noexcept;

        void buffer_sub_data(enum_t target, size_t offset, size_t size, const void *data) noexcept;
        // NOTE: Takes 'buffer' in the user range [1, UINT32_MAX]
        void named_buffer_sub_data(uint32_t buffer, size_t offset, size_t size, const void *data) noexcept;

        void copy_buffer_sub_data(enum_t read_target, enum_t write_target, size_t read_offset, size_t write_offset, size_t size) noexcept;
        // NOTE: Takes 'read_buffer' and 'write_buffer' in the user range [1, UINT32_MAX]
        void copy_named_buffer_sub_data(uint32_t read_buffer, uint32_t write_buffer, size_t read_offset, size_t write_offset, size_t size) noexcept;

        void get_buffer_sub_data(enum_t target, size_t offset, size_t size, void* data) noexcept;
        // NOTE: Takes 'buffer' in the user range [1, UINT32_MAX]
        void get_named_buffer_sub_data(uint32_t buffer, size_t offset, size_t size, void* data) noexcept;

        void set_vertex_attrib_array_state(uint32_t index, bool enabled) noexcept;
        // NOTE: Takes 'vaobj' in the user range [1, UINT32_MAX]
        void set_vertex_array_attrib_state(uint32_t vaobj, uint32_t index, bool enabled) noexcept;

        void* map_buffer(enum_t target, enum_t access /* unused */) noexcept;
        // NOTE: Takes 'buffer' in the user range [1, UINT32_MAX]
        void* map_named_buffer(uint32_t buffer, enum_t access /* unused */) noexcept;
        void unmap_buffer(enum_t target) noexcept;
        // NOTE: Takes 'buffer' in the user range [1, UINT32_MAX]
        void unmap_named_buffer(uint32_t buffer) noexcept;

        // NOTE: Takes 'buffer' in the user range [1, UINT32_MAX]
        bool is_buffer(uint32_t buffer) noexcept;

        void gen_vertex_arrays(size_t n, uint32_t* arrays) noexcept;
        // NOTE: Takes 'array' in the user range [1, UINT32_MAX]
        void bind_vertex_array(uint32_t array) noexcept;
        // NOTE: Takes 'arrays' in the user range [1, UINT32_MAX]
        void delete_vertex_arrays(size_t n, const uint32_t* arrays) noexcept;
        // NOTE: Takes 'array' in the user range [1, UINT32_MAX]
        bool is_vertex_array(uint32_t array) noexcept;

        void vertex_attrib_pointer(uint32_t index, size_t size, enum_t type, bool normalized, size_t stride, const void* pointer) noexcept;
        void vertex_attrib_I_pointer(uint32_t index, size_t size, enum_t type, size_t stride, const void* pointer) noexcept;
        void vertex_attrib_L_pointer(uint32_t index, size_t size, enum_t type, size_t stride, const void* pointer) noexcept;

    private:
        buffer_mng() = default;
        buffer_mng(size_t preallocation_size);

        template <enum_t type0, enum_t... types>
        void vertex_attrib_pointer_impl(uint32_t index, size_t size, enum_t type, bool normalized, size_t stride, const void* pointer) noexcept
        {
            static context_mng& context_mng = context_mng::instance();

            AM_SET_ERROR_FLAG_IF(index >= context::MAX_VERTEX_ATTRIB_BINDINGS, AMGL_INVALID_VALUE, context_mng);    
            AM_SET_ERROR_FLAG_IF(!detail::is_one_of(size, 1, 2, 3, 4), AMGL_INVALID_VALUE, context_mng);
            AM_SET_ERROR_FLAG_IF(!detail::is_one_of(type, type0, std::forward<enum_t>(types)...), AMGL_INVALID_ENUM, context_mng);

            AM_SET_ERROR_FLAG_IF(detail::is_one_of(type, AMGL_INT_2_10_10_10_REV, AMGL_UNSIGNED_INT_2_10_10_10_REV) && size != 4, 
                AMGL_INVALID_OPERATION, context_mng);
            AM_SET_ERROR_FLAG_IF(type == AMGL_UNSIGNED_INT_10F_11F_11F_REV && size != 3, 
                AMGL_INVALID_OPERATION, context_mng);
            
            const uint32_t vao_kernel_id = context_mng.get_binded_vertex_array();
            // TODO: think about having an attribute layout as binding in context or something like that
            AM_SET_ERROR_FLAG_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(vao_kernel_id), AMGL_INVALID_VALUE, context_mng);
            
            const uint32_t vbo_kernel_id = m_vertex_arrays.m_vbo_ids[vao_kernel_id];
            AM_SET_ERROR_FLAG_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(vbo_kernel_id) && pointer != nullptr, AMGL_INVALID_OPERATION, context_mng);

            m_vertex_arrays.set_attribute_desc(vao_kernel_id, index, size, type, normalized, stride, pointer);
        }

    private:
        buffers m_buffers;
        vertex_arrays m_vertex_arrays;
    };
}