#include "pch.hpp"
#include "buffer_mng.hpp"

#include "core/context_processing/context_mng.hpp"

namespace amgl
{
    static context_mng& gs_context_mng = context_mng::instance();

    #define CHECK_BUFFER_TARGET_VALIDITY(target, error_flag)        \
        if(!detail::is_one_of(target,                               \
            AMGL_ARRAY_BUFFER,                                      \
            AMGL_ATOMIC_COUNTER_BUFFER,                             \
            AMGL_COPY_READ_BUFFER,                                  \
            AMGL_COPY_WRITE_BUFFER,                                 \
            AMGL_DISPATCH_INDIRECT_BUFFER,                          \
            AMGL_DRAW_INDIRECT_BUFFER,                              \
            AMGL_ELEMENT_ARRAY_BUFFER,                              \
            AMGL_PIXEL_PACK_BUFFER,                                 \
            AMGL_PIXEL_UNPACK_BUFFER,                               \
            AMGL_QUERY_BUFFER,                                      \
            AMGL_SHADER_STORAGE_BUFFER,                             \
            AMGL_TEXTURE_BUFFER,                                    \
            AMGL_TRANSFORM_FEEDBACK_BUFFER,                         \
            AMGL_UNIFORM_BUFFER)                                    \
        ) {                                                         \
            gs_context_mng.update_error_flag(error_flag);           \
            return;                                                 \
        }


    #define CHECK_BUFFER_USAGE_VALIDITY(usage, error_flag)          \
        if(!detail::is_one_of(usage,                                \
            AMGL_STREAM_DRAW,                                       \
            AMGL_STREAM_READ,                                       \
            AMGL_STREAM_COPY,                                       \
            AMGL_STATIC_DRAW,                                       \
            AMGL_STATIC_READ,                                       \
            AMGL_STATIC_COPY,                                       \
            AMGL_DYNAMIC_DRAW,                                      \
            AMGL_DYNAMIC_READ,                                      \
            AMGL_DYNAMIC_COPY)                                      \
        ) {                                                         \
            gs_context_mng.update_error_flag(error_flag);           \
            return;                                                 \
        }


    // Takes 'buffer' in the internal range [0, UINT32_MAX - 1]
    #define CHECK_BUFFER_VALIDITY(buffer, error_flag)               \
        if (!m_buffers.is_buffer_exist(buffer)) {                   \
            gs_context_mng.update_error_flag(error_flag);           \
            return;                                                 \
        }


    // Takes 'buffer' in the internal range [0, UINT32_MAX - 1]
    #define CHECK_BUFFER_NOT_DEFAULT(buffer, error_flag)            \
        if (is_default_id_internal_range(buffer)) {                 \
            gs_context_mng.update_error_flag(error_flag);           \
            return;                                                 \
        }

    // Takes 'buffer' in the internal range [0, UINT32_MAX - 1]
    #define CHECK_BUFFER_NOT_MAPPED(buffer, error_flag)             \
        if (m_buffers.is_buffer_mapped(buffer)) {                   \
            gs_context_mng.update_error_flag(error_flag);           \
            return;                                                 \
        }


    buffer_mng::buffer_mng(size_t preallocation_size)
        : m_buffers(preallocation_size), m_vertex_arrays(preallocation_size)
    {
    }


    void buffer_mng::gen_buffers(uint32_t n, uint32_t *buffers) noexcept
    {
        AM_RETURN_IF(!buffers);

        for (uint32_t i = 0u; i < n; ++i) {
            buffers[i] = conv_internal_to_user_range(m_buffers.create_id());
        }
    }


    void buffer_mng::delete_buffers(uint32_t n, const uint32_t *buffers) noexcept
    {
        AM_RETURN_IF(!buffers);

        for (uint32_t i = 0u; i < n; ++i) {
            if (is_default_id_user_range(buffers[i])) {
                continue;
            }

            const int32_t target = gs_context_mng.get_binding_target(buffers[i]);
            if (target != AMGL_NONE) {
                gs_context_mng.bind_target_buffer_unsafe(target, AM_DEFAULT_USER_ID);
            }
            m_buffers.free_id(conv_user_to_inernal_range(buffers[i]));
        }
    }
    

    void buffer_mng::bind_buffer(enum_t target, uint32_t buffer) noexcept
    {
        CHECK_BUFFER_TARGET_VALIDITY(target, AMGL_INVALID_ENUM);
        
        const uint32_t internal_id = conv_user_to_inernal_range(buffer);
        CHECK_BUFFER_VALIDITY(internal_id, AMGL_INVALID_VALUE);

        gs_context_mng.bind_target_buffer_unsafe(target, buffer);

        const uint32_t vao = conv_user_to_inernal_range(gs_context_mng.get_binding(AMGL_VERTEX_ARRAY_BINDING));
        if (vao != AM_DEFAULT_INTERNAL_ID) {
            m_vertex_arrays.bind_buffer_unsafe(vao, target, internal_id);
        }
    }

    
    void buffer_mng::buffer_data(enum_t target, size_t size, const void *data, enum_t usage) noexcept
    {
        CHECK_BUFFER_TARGET_VALIDITY(target, AMGL_INVALID_ENUM);
    
        const uint32_t buffer = gs_context_mng.get_binding(target);
        named_buffer_data(buffer, size, data, usage);
    }

    
    void buffer_mng::named_buffer_data(uint32_t buffer, size_t size, const void *data, enum_t usage) noexcept
    {
        CHECK_BUFFER_USAGE_VALIDITY(usage, AMGL_INVALID_ENUM);

        const uint32_t internal_id = conv_user_to_inernal_range(buffer);
        CHECK_BUFFER_VALIDITY(internal_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_DEFAULT(internal_id, AMGL_INVALID_OPERATION);

        m_buffers.reallocate_memory_block(internal_id, size);

        if (data != nullptr) {
            memcpy_s(m_buffers.m_memory_blocks[internal_id].data(), size, data, size);
        }
    }

    
    void buffer_mng::buffer_sub_data(enum_t target, size_t offset, size_t size, const void *data) noexcept
    {
        CHECK_BUFFER_TARGET_VALIDITY(target, AMGL_INVALID_ENUM);

        const uint32_t buffer = gs_context_mng.get_binding(target);
        named_buffer_sub_data(buffer, offset, size, data);
    }

    
    void buffer_mng::named_buffer_sub_data(uint32_t buffer, size_t offset, size_t size, const void *data) noexcept
    {
        const uint32_t internal_id = conv_user_to_inernal_range(buffer);
        CHECK_BUFFER_VALIDITY(internal_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_DEFAULT(internal_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_MAPPED(internal_id, AMGL_INVALID_OPERATION);

        const size_t buffer_size = m_buffers.m_memory_blocks[internal_id].size();
        if (offset + size >= buffer_size) {
            gs_context_mng.update_error_flag(AMGL_INVALID_VALUE);
            return;
        }

        if (data == nullptr) {
            return;
        }

        byte_t* dst = m_buffers.m_memory_blocks[internal_id].data() + offset;
        memcpy_s(dst, buffer_size, data, size);
    }

    
    void buffer_mng::copy_buffer_sub_data(enum_t read_target, enum_t write_target, size_t read_offset, size_t write_offset, size_t size) noexcept
    {
        CHECK_BUFFER_TARGET_VALIDITY(read_target, AMGL_INVALID_ENUM);
        CHECK_BUFFER_TARGET_VALIDITY(write_target, AMGL_INVALID_ENUM);

        const uint32_t read_buffer = gs_context_mng.get_binding(read_target);
        const uint32_t write_buffer = gs_context_mng.get_binding(write_target);
        copy_named_buffer_sub_data(read_buffer, write_buffer, read_offset, write_offset, size);
    }

    
    void buffer_mng::copy_named_buffer_sub_data(uint32_t read_buffer, uint32_t write_buffer, size_t read_offset, size_t write_offset, size_t size) noexcept
    {
        const uint32_t internal_read_id = conv_user_to_inernal_range(read_buffer);
        CHECK_BUFFER_VALIDITY(internal_read_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_DEFAULT(internal_read_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_MAPPED(internal_read_id, AMGL_INVALID_OPERATION);

        const uint32_t internal_write_id = conv_user_to_inernal_range(write_buffer);
        CHECK_BUFFER_VALIDITY(internal_write_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_DEFAULT(internal_write_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_MAPPED(internal_write_id, AMGL_INVALID_OPERATION);

        buffers::memory_block& read_mem_block = m_buffers.m_memory_blocks[internal_read_id];
        buffers::memory_block& write_mem_block = m_buffers.m_memory_blocks[internal_write_id];
        if (read_offset + size > read_mem_block.size() || write_offset + size > write_mem_block.size()) {
            gs_context_mng.update_error_flag(AMGL_INVALID_VALUE);
            return;
        }

        if (internal_read_id == internal_write_id || 
            detail::are_memory_regions_overlap(read_mem_block.data(), size, write_mem_block.data(), size)
        ) {
            gs_context_mng.update_error_flag(AMGL_INVALID_VALUE);
            return;
        }
        
        memcpy_s(write_mem_block.data() + write_offset, write_mem_block.size(), read_mem_block.data() + read_offset, size);
    }

    
    bool buffer_mng::is_buffer(uint32_t buffer) noexcept
    {
        AM_RETURN_IF(is_default_id_user_range(buffer), false);

        return m_buffers.is_buffer_exist(conv_user_to_inernal_range(buffer));
    }
}