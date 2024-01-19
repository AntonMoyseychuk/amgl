#include "pch.hpp"
#include "buffer_mng.hpp"

#include "core/context_processing/context_mng.hpp"

namespace amgl
{
    static context_mng& gs_context_mng = context_mng::instance();


    #define CHECK_BUFFER_TARGET_VALIDITY(target, error_flag)        \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(target,                  \
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
            AMGL_UNIFORM_BUFFER), error_flag, gs_context_mng)


    #define CHECK_BUFFER_USAGE_VALIDITY(usage, error_flag)          \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(usage,                   \
            AMGL_STREAM_DRAW,                                       \
            AMGL_STREAM_READ,                                       \
            AMGL_STREAM_COPY,                                       \
            AMGL_STATIC_DRAW,                                       \
            AMGL_STATIC_READ,                                       \
            AMGL_STATIC_COPY,                                       \
            AMGL_DYNAMIC_DRAW,                                      \
            AMGL_DYNAMIC_READ,                                      \
            AMGL_DYNAMIC_COPY), error_flag, gs_context_mng)


    // Takes 'buffer' in the internal range [0, UINT32_MAX - 1]
    #define CHECK_BUFFER_VALIDITY(buffer, error_flag) \
        AM_SET_ERROR_FLAG_IF(!m_buffers.is_buffer_exist(buffer), error_flag, gs_context_mng)

    // Takes 'buffer' in the internal range [0, UINT32_MAX - 1]
    #define CHECK_BUFFER_NOT_DEFAULT(buffer, error_flag) \
        AM_SET_ERROR_FLAG_IF(is_default_id_internal_range(buffer), error_flag, gs_context_mng)

    // Takes 'buffer' in the internal range [0, UINT32_MAX - 1]
    #define CHECK_BUFFER_NOT_MAPPED(buffer, error_flag) \
        AM_SET_ERROR_FLAG_IF(m_buffers.is_buffer_mapped(buffer), error_flag, gs_context_mng)

    // Takes 'vao' in the internal range [0, UINT32_MAX - 1]
    #define CHECK_VAO_VALIDITY(vao, error_flag) \
        AM_SET_ERROR_FLAG_IF(!m_vertex_arrays.is_vertex_array_exist(vao), error_flag, gs_context_mng)

    // Takes 'vao' in the internal range [0, UINT32_MAX - 1]
    #define CHECK_VAO_NOT_DEFAULT(vao, error_flag) \
        AM_SET_ERROR_FLAG_IF(is_default_id_internal_range(vao), error_flag, gs_context_mng)


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

    
    void buffer_mng::invalidate_buffer_data(uint32_t buffer) noexcept
    {
        const uint32_t internal_id = conv_user_to_inernal_range(buffer);
        CHECK_BUFFER_VALIDITY(internal_id, AMGL_INVALID_VALUE);
        CHECK_BUFFER_NOT_MAPPED(internal_id, AMGL_INVALID_OPERATION);
            
        m_buffers.deallocate_memory_block(internal_id);
    }

    
    void buffer_mng::delete_buffers(uint32_t n, const uint32_t *buffers) noexcept
    {
        AM_RETURN_IF(!buffers);

        for (uint32_t i = 0u; i < n; ++i) {
            const uint32_t internal_id = conv_user_to_inernal_range(buffers[i]);
            AM_CONTINUE_IF(is_default_id_internal_range(internal_id) || !m_buffers.is_buffer_exist(internal_id));

            const int32_t target = gs_context_mng.get_binding_target(buffers[i]);
            if (target != AMGL_NONE) {
                gs_context_mng.bind_target_buffer_unsafe(target, AM_DEFAULT_USER_ID);
            }
            m_buffers.free_id(internal_id);
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
            memcpy_s(m_buffers.get_memory_block(internal_id).data(), size, data, size);
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

        buffers::memory_block& mem_block = m_buffers.get_memory_block(internal_id);

        const size_t buffer_size = mem_block.size();
        AM_SET_ERROR_FLAG_IF(offset + size > buffer_size, AMGL_INVALID_VALUE, gs_context_mng);

        AM_RETURN_IF(data == nullptr);

        byte_t* dst = mem_block.data() + offset;
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

        buffers::memory_block& read_mem_block = m_buffers.get_memory_block(internal_read_id);
        buffers::memory_block& write_mem_block = m_buffers.get_memory_block(internal_write_id);
        AM_SET_ERROR_FLAG_IF(read_offset + size > read_mem_block.size() || write_offset + size > write_mem_block.size(), 
            AMGL_INVALID_VALUE, gs_context_mng);

        AM_SET_ERROR_FLAG_IF(internal_read_id == internal_write_id || 
            detail::are_memory_regions_overlap(read_mem_block.data(), size, write_mem_block.data(), size), AMGL_INVALID_VALUE, gs_context_mng);
        
        memcpy_s(write_mem_block.data() + write_offset, write_mem_block.size(), read_mem_block.data() + read_offset, size);
    }

    
    void buffer_mng::get_buffer_sub_data(enum_t target, size_t offset, size_t size, void *data) noexcept
    {
        CHECK_BUFFER_TARGET_VALIDITY(target, AMGL_INVALID_ENUM);

        const uint32_t buffer = gs_context_mng.get_binding(target);
        get_named_buffer_sub_data(buffer, offset, size, data);
    }

    
    void buffer_mng::get_named_buffer_sub_data(uint32_t buffer, size_t offset, size_t size, void *data) noexcept
    {
        const uint32_t internal_id = conv_user_to_inernal_range(buffer);
        CHECK_BUFFER_VALIDITY(internal_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_DEFAULT(internal_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_MAPPED(internal_id, AMGL_INVALID_OPERATION);

        buffers::memory_block& mem_block = m_buffers.get_memory_block(internal_id);

        const size_t buffer_size = mem_block.size();
        AM_SET_ERROR_FLAG_IF(offset + size > buffer_size, AMGL_INVALID_VALUE, gs_context_mng);

        AM_RETURN_IF(data == nullptr);

        const byte_t* src = mem_block.data() + offset;
        memcpy(data, src, size);
    }

    
    void buffer_mng::set_vertex_attrib_array_state(uint32_t index, bool enabled) noexcept
    {
        const uint32_t vao_user_range = conv_internal_to_user_range(gs_context_mng.get_context().bindings.vao);
        set_vertex_array_attrib_state(vao_user_range, index, enabled);
    }

    
    void buffer_mng::set_vertex_array_attrib_state(uint32_t vaobj, uint32_t index, bool enabled) noexcept
    {
        AM_ASSERT_MSG(false, "VAOs are not implemented yet");

        const uint32_t internal_id = conv_user_to_inernal_range(vaobj);

        CHECK_VAO_VALIDITY(internal_id, AMGL_INVALID_OPERATION);
        CHECK_VAO_NOT_DEFAULT(internal_id, AMGL_INVALID_OPERATION);

        AM_SET_ERROR_FLAG_IF(index >= context::MAX_VERTEX_ATTRIBS_COUNT, AMGL_INVALID_VALUE, gs_context_mng);

        AM_ASSERT(internal_id < m_vertex_arrays.m_layouts.size());
        m_vertex_arrays.m_layouts[internal_id].enable_flags.set(index, enabled);
    }


    bool buffer_mng::is_buffer(uint32_t buffer) noexcept
    {
        AM_RETURN_IF(is_default_id_user_range(buffer), false);

        return m_buffers.is_buffer_exist(conv_user_to_inernal_range(buffer));
    }
}