#include "pch.hpp"
#include "buffer_mng.hpp"


AM_STATIC_ASSERT_MSG(AM_INIT_BUFF_COUNT > 0, "AM_INIT_BUFF_COUNT must be greater than 0");


namespace amgl
{
    static context_mng& gs_context_mng = context_mng::instance();


    #define CHECK_BUFFER_TARGET_VALIDITY(target, error_flag, ...)           \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(target,                     \
            AMGL_ARRAY_BUFFER,                                              \
            AMGL_ATOMIC_COUNTER_BUFFER,                                     \
            AMGL_COPY_READ_BUFFER,                                          \
            AMGL_COPY_WRITE_BUFFER,                                         \
            AMGL_DISPATCH_INDIRECT_BUFFER,                                  \
            AMGL_DRAW_INDIRECT_BUFFER,                                      \
            AMGL_ELEMENT_ARRAY_BUFFER,                                      \
            AMGL_PIXEL_PACK_BUFFER,                                         \
            AMGL_PIXEL_UNPACK_BUFFER,                                       \
            AMGL_QUERY_BUFFER,                                              \
            AMGL_SHADER_STORAGE_BUFFER,                                     \
            AMGL_TEXTURE_BUFFER,                                            \
            AMGL_TRANSFORM_FEEDBACK_BUFFER,                                 \
            AMGL_UNIFORM_BUFFER), error_flag, gs_context_mng, __VA_ARGS__)


    #define CHECK_BUFFER_USAGE_VALIDITY(usage, error_flag, ...)             \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(usage,                      \
            AMGL_STREAM_DRAW,                                               \
            AMGL_STREAM_READ,                                               \
            AMGL_STREAM_COPY,                                               \
            AMGL_STATIC_DRAW,                                               \
            AMGL_STATIC_READ,                                               \
            AMGL_STATIC_COPY,                                               \
            AMGL_DYNAMIC_DRAW,                                              \
            AMGL_DYNAMIC_READ,                                              \
            AMGL_DYNAMIC_COPY), error_flag, gs_context_mng, __VA_ARGS__)


    #define CHECK_BUFFER_ACCESS_VALIDITY(access, error_flag, ...)           \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(access,                     \
            AMGL_READ_ONLY,                                                 \
            AMGL_WRITE_ONLY,                                                \
            AMGL_READ_WRITE), error_flag, gs_context_mng, __VA_ARGS__)


    // Takes 'buffer' in the kernel range [0, UINT32_MAX - 1]
    #define CHECK_BUFFER_VALIDITY(buffer, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(!m_buffers.is_buffer_exist(buffer), error_flag, gs_context_mng, __VA_ARGS__)

    // Takes 'buffer' in the kernel range [0, UINT32_MAX - 1]
    #define CHECK_BUFFER_NOT_DEFAULT(buffer, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(buffer), error_flag, gs_context_mng, __VA_ARGS__)

    // Takes 'buffer' in the kernel range [0, UINT32_MAX - 1]
    #define CHECK_BUFFER_NOT_MAPPED(buffer, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(m_buffers.is_buffer_mapped(buffer), error_flag, gs_context_mng, __VA_ARGS__)

    // Takes 'vao' in the kernel range [0, UINT32_MAX - 1]
    #define CHECK_VAO_VALIDITY(vao, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(!m_vertex_arrays.is_vertex_array_exist(vao), error_flag, gs_context_mng, __VA_ARGS__)

    // Takes 'vao' in the kernel range [0, UINT32_MAX - 1]
    #define CHECK_VAO_NOT_DEFAULT(vao, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(vao), error_flag, gs_context_mng, __VA_ARGS__)


    buffer_mng::buffer_mng(size_t preallocation_size)
        : m_buffers(preallocation_size), m_vertex_arrays(preallocation_size)
    {
    }


    void buffer_mng::gen_buffers(uint32_t n, uint32_t *buffers) noexcept
    {
        AM_RETURN_IF(!buffers);

        for (uint32_t i = 0u; i < n; ++i) {
            buffers[i] = CONV_KERNEL_TO_USER_SPACE(m_buffers.create_buffer());
        }
    }

    
    void buffer_mng::invalidate_buffer_data(uint32_t buffer) noexcept
    {
        const uint32_t kernel_id = CONV_USER_TO_KERNEL_SPACE(buffer);
        CHECK_BUFFER_VALIDITY(kernel_id, AMGL_INVALID_VALUE);
        CHECK_BUFFER_NOT_MAPPED(kernel_id, AMGL_INVALID_OPERATION);
            
        m_buffers.deallocate_memory_block(kernel_id);
    }

    
    void buffer_mng::delete_buffers(uint32_t n, const uint32_t *buffers) noexcept
    {
        AM_RETURN_IF(!buffers);

        for (uint32_t i = 0u; i < n; ++i) {
            const uint32_t kernel_id = CONV_USER_TO_KERNEL_SPACE(buffers[i]);
            AM_CONTINUE_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(kernel_id) || !m_buffers.is_buffer_exist(kernel_id));
            
            m_buffers.unmap_buffer(kernel_id);
            m_buffers.free_buffer(kernel_id);
        }
    }
    

    void buffer_mng::bind_buffer(enum_t target, uint32_t buffer) noexcept
    {
        CHECK_BUFFER_TARGET_VALIDITY(target, AMGL_INVALID_ENUM);
        
        const uint32_t kernel_buf_id = CONV_USER_TO_KERNEL_SPACE(buffer);
        CHECK_BUFFER_VALIDITY(kernel_buf_id, AMGL_INVALID_VALUE);

        gs_context_mng.bind_target_buffer(target, kernel_buf_id, 0);

        const uint32_t kernel_vao_id = gs_context_mng.get_binded_vertex_array();
        if (!AM_IS_DEFAULT_ID_KERNEL_SPACE(kernel_vao_id)) {
            m_vertex_arrays.bind_buffer(kernel_vao_id, target, kernel_buf_id);
        }
    }

    
    void buffer_mng::bind_buffer_base(enum_t target, uint32_t index, uint32_t buffer) noexcept
    {
        bind_buffer_range(target, index, buffer, nullptr, nullptr);
    }

    
    void buffer_mng::bind_buffers_base(enum_t target, uint32_t first, size_t count, const uint32_t *buffers) noexcept
    {
        for (size_t i = 0; i < count; ++i) {
            const uint32_t buff = buffers != nullptr ? buffers[i] : AM_DEFAULT_USER_ID;
            bind_buffer_base(target, first + i, buff);
        }
    }

    
    void buffer_mng::bind_buffer_range(enum_t target, uint32_t index, uint32_t buffer, const size_t* offset, const size_t* size) noexcept
    {
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(target, AMGL_ATOMIC_COUNTER_BUFFER, AMGL_SHADER_STORAGE_BUFFER,
            AMGL_TRANSFORM_FEEDBACK_BUFFER, AMGL_UNIFORM_BUFFER), AMGL_INVALID_ENUM, gs_context_mng);
        
        const uint32_t kernel_buf_id = CONV_USER_TO_KERNEL_SPACE(buffer);
        CHECK_BUFFER_VALIDITY(kernel_buf_id, AMGL_INVALID_OPERATION);

        buffer_range range;

        if (!AM_IS_DEFAULT_ID_KERNEL_SPACE(kernel_buf_id)) {
            const size_t buffer_size = m_buffers.get_memory_block(kernel_buf_id).size();

            if (offset != nullptr && size != nullptr) {
                AM_SET_ERROR_FLAG_IF(*offset + *size > buffer_size, AMGL_INVALID_VALUE, gs_context_mng);
            }

            if (offset != nullptr && size != nullptr) {
                range.offset = *offset;
                range.size = *size;
            } else {
                range.offset = 0u;
                range.size = buffer_size;
            }    
        }

        gs_context_mng.bind_target_buffer(target, kernel_buf_id, index);
        gs_context_mng.bind_target_buffer_range(target, index, range);
    }

    
    void buffer_mng::bind_buffers_range(enum_t target, uint32_t first, size_t count, const uint32_t *buffers, const size_t *offsets, const size_t *sizes) noexcept
    {
        for (size_t i = 0u; i < count; ++i) {
            if (buffers != nullptr) {
                bind_buffer_range(target, first + i, buffers[i], offsets + i, sizes + i);
            } else {
                bind_buffer_base(target, first + i, AM_DEFAULT_USER_ID);
            }
        }
    }

    
    void buffer_mng::buffer_data(enum_t target, size_t size, const void *data, enum_t usage) noexcept
    {
        CHECK_BUFFER_TARGET_VALIDITY(target, AMGL_INVALID_ENUM);
    
        const uint32_t user_buf_id = CONV_KERNEL_TO_USER_SPACE(gs_context_mng.get_binded_buffer(target, 0));
        named_buffer_data(user_buf_id, size, data, usage);
    }

    
    void buffer_mng::named_buffer_data(uint32_t buffer, size_t size, const void *data, enum_t usage) noexcept
    {
        CHECK_BUFFER_USAGE_VALIDITY(usage, AMGL_INVALID_ENUM);

        const uint32_t kernel_id = CONV_USER_TO_KERNEL_SPACE(buffer);
        CHECK_BUFFER_VALIDITY(kernel_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_DEFAULT(kernel_id, AMGL_INVALID_OPERATION);

        m_buffers.reallocate_memory_block(kernel_id, size);
        m_buffers.unmap_buffer(kernel_id);

        if (data != nullptr) {
            memcpy_s(m_buffers.get_memory_block(kernel_id).data(), size, data, size);
        }
    }

    
    void buffer_mng::buffer_sub_data(enum_t target, size_t offset, size_t size, const void *data) noexcept
    {
        CHECK_BUFFER_TARGET_VALIDITY(target, AMGL_INVALID_ENUM);

        const uint32_t user_buf_id = CONV_KERNEL_TO_USER_SPACE(gs_context_mng.get_binded_buffer(target, 0));
        named_buffer_sub_data(user_buf_id, offset, size, data);
    }


    void buffer_mng::named_buffer_sub_data(uint32_t buffer, size_t offset, size_t size, const void *data) noexcept
    {
        const uint32_t kernel_id = CONV_USER_TO_KERNEL_SPACE(buffer);
        CHECK_BUFFER_VALIDITY(kernel_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_DEFAULT(kernel_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_MAPPED(kernel_id, AMGL_INVALID_OPERATION);

        buffers::memory_block& mem_block = m_buffers.get_memory_block(kernel_id);

        const size_t buffer_size = mem_block.size();
        AM_SET_ERROR_FLAG_IF(offset + size > buffer_size, AMGL_INVALID_VALUE, gs_context_mng);

        AM_RETURN_IF(data == nullptr);

        ubyte_t* dst = mem_block.data() + offset;
        memcpy_s(dst, buffer_size, data, size);
    }

    
    void buffer_mng::copy_buffer_sub_data(enum_t read_target, enum_t write_target, size_t read_offset, size_t write_offset, size_t size) noexcept
    {
        CHECK_BUFFER_TARGET_VALIDITY(read_target, AMGL_INVALID_ENUM);
        CHECK_BUFFER_TARGET_VALIDITY(write_target, AMGL_INVALID_ENUM);

        const uint32_t user_read_buffer_id = CONV_KERNEL_TO_USER_SPACE(gs_context_mng.get_binded_buffer(read_target, 0));
        const uint32_t user_write_buffer_id = CONV_KERNEL_TO_USER_SPACE(gs_context_mng.get_binded_buffer(write_target, 0));
        copy_named_buffer_sub_data(user_read_buffer_id, user_write_buffer_id, read_offset, write_offset, size);
    }

    
    void buffer_mng::copy_named_buffer_sub_data(uint32_t read_buffer, uint32_t write_buffer, size_t read_offset, size_t write_offset, size_t size) noexcept
    {
        const uint32_t kernel_read_id = CONV_USER_TO_KERNEL_SPACE(read_buffer);
        CHECK_BUFFER_VALIDITY(kernel_read_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_DEFAULT(kernel_read_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_MAPPED(kernel_read_id, AMGL_INVALID_OPERATION);

        const uint32_t kernel_write_id = CONV_USER_TO_KERNEL_SPACE(write_buffer);
        CHECK_BUFFER_VALIDITY(kernel_write_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_DEFAULT(kernel_write_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_MAPPED(kernel_write_id, AMGL_INVALID_OPERATION);

        buffers::memory_block& read_mem_block = m_buffers.get_memory_block(kernel_read_id);
        buffers::memory_block& write_mem_block = m_buffers.get_memory_block(kernel_write_id);
        AM_SET_ERROR_FLAG_IF(read_offset + size > read_mem_block.size() || write_offset + size > write_mem_block.size(), 
            AMGL_INVALID_VALUE, gs_context_mng);

        const uintptr_t region0 = (uintptr_t)read_mem_block.data(), region1 = (uintptr_t)write_mem_block.data();
        const bool are_regions_overlaps = 
            detail::is_in_range(region0, region1, region1 + size) ||
            detail::is_in_range(region1, region0, region0 + size);
        AM_SET_ERROR_FLAG_IF(kernel_read_id == kernel_write_id || are_regions_overlaps, AMGL_INVALID_VALUE, gs_context_mng);
        
        memcpy_s(write_mem_block.data() + write_offset, write_mem_block.size(), read_mem_block.data() + read_offset, size);
    }

    
    void buffer_mng::get_buffer_sub_data(enum_t target, size_t offset, size_t size, void *data) noexcept
    {
        CHECK_BUFFER_TARGET_VALIDITY(target, AMGL_INVALID_ENUM);

        const uint32_t user_buf_id = CONV_KERNEL_TO_USER_SPACE(gs_context_mng.get_binded_buffer(target, 0));
        get_named_buffer_sub_data(user_buf_id, offset, size, data);
    }

    
    void buffer_mng::get_named_buffer_sub_data(uint32_t buffer, size_t offset, size_t size, void *data) noexcept
    {
        const uint32_t kernel_id = CONV_USER_TO_KERNEL_SPACE(buffer);
        CHECK_BUFFER_VALIDITY(kernel_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_DEFAULT(kernel_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_MAPPED(kernel_id, AMGL_INVALID_OPERATION);

        buffers::memory_block& mem_block = m_buffers.get_memory_block(kernel_id);

        const size_t buffer_size = mem_block.size();
        AM_SET_ERROR_FLAG_IF(offset + size > buffer_size, AMGL_INVALID_VALUE, gs_context_mng);

        AM_RETURN_IF(data == nullptr);

        const ubyte_t* src = mem_block.data() + offset;
        memcpy(data, src, size);
    }

    
    void buffer_mng::set_vertex_attrib_array_state(uint32_t index, bool enabled) noexcept
    {
        const uint32_t vao_user_range = CONV_KERNEL_TO_USER_SPACE(gs_context_mng.get_context().buf_bindings.vao);
        set_vertex_array_attrib_state(vao_user_range, index, enabled);
    }

    
    void buffer_mng::set_vertex_array_attrib_state(uint32_t vaobj, uint32_t index, bool enabled) noexcept
    {
        const uint32_t kernel_id = CONV_USER_TO_KERNEL_SPACE(vaobj);

        CHECK_VAO_VALIDITY(kernel_id, AMGL_INVALID_OPERATION);
        CHECK_VAO_NOT_DEFAULT(kernel_id, AMGL_INVALID_OPERATION);

        AM_SET_ERROR_FLAG_IF(index >= context::MAX_VERTEX_ATTRIB_BINDINGS, AMGL_INVALID_VALUE, gs_context_mng);

        AM_ASSERT(kernel_id < m_vertex_arrays.m_attributes.size());
        m_vertex_arrays.set_attribute_state(kernel_id, index, enabled);
    }

    
    void *buffer_mng::map_buffer(enum_t target, enum_t access) noexcept
    {
        CHECK_BUFFER_TARGET_VALIDITY(target, AMGL_INVALID_ENUM, nullptr);
        
        const uint32_t user_buf_id = CONV_KERNEL_TO_USER_SPACE(gs_context_mng.get_binded_buffer(target, 0));
        return map_named_buffer(user_buf_id, access);
    }

    
    void *buffer_mng::map_named_buffer(uint32_t buffer, enum_t access) noexcept
    {
        const uint32_t kernel_id = CONV_USER_TO_KERNEL_SPACE(buffer);
        CHECK_BUFFER_VALIDITY(kernel_id, AMGL_INVALID_OPERATION, nullptr);
        CHECK_BUFFER_NOT_DEFAULT(kernel_id, AMGL_INVALID_OPERATION, nullptr);
        
        CHECK_BUFFER_ACCESS_VALIDITY(access, AMGL_INVALID_ENUM, nullptr);

        return m_buffers.map_buffer(kernel_id);
    }

    
    void buffer_mng::unmap_buffer(enum_t target) noexcept
    {
        CHECK_BUFFER_TARGET_VALIDITY(target, AMGL_INVALID_ENUM);
        
        const uint32_t user_buf_id = CONV_KERNEL_TO_USER_SPACE(gs_context_mng.get_binded_buffer(target, 0));
        unmap_named_buffer(user_buf_id);
    }

    
    void buffer_mng::unmap_named_buffer(uint32_t buffer) noexcept
    {
        const uint32_t kernel_id = CONV_USER_TO_KERNEL_SPACE(buffer);
        CHECK_BUFFER_VALIDITY(kernel_id, AMGL_INVALID_OPERATION);
        CHECK_BUFFER_NOT_DEFAULT(kernel_id, AMGL_INVALID_OPERATION);

        AM_SET_ERROR_FLAG_IF(!m_buffers.is_buffer_mapped(kernel_id), AMGL_INVALID_OPERATION, gs_context_mng);

        m_buffers.unmap_buffer(kernel_id);
    }

    
    bool buffer_mng::is_buffer(uint32_t buffer) noexcept
    {
        AM_RETURN_IF(AM_IS_DEFAULT_ID_USER_SPACE(buffer), false);

        return m_buffers.is_buffer_exist(CONV_USER_TO_KERNEL_SPACE(buffer));
    }
    
    
    void buffer_mng::bind_vertex_array(uint32_t array) noexcept
    {
        const uint32_t kernel_vao_id = CONV_USER_TO_KERNEL_SPACE(array);
        CHECK_VAO_VALIDITY(kernel_vao_id, AMGL_INVALID_OPERATION);

        const uint32_t kernel_vbo_id = m_vertex_arrays.m_vbo_ids[kernel_vao_id];
        const uint32_t kernel_ebo_id = m_vertex_arrays.m_ebo_ids[kernel_vao_id];
        gs_context_mng.bind_vertex_array(kernel_vao_id, kernel_vbo_id, kernel_ebo_id, 0, 0);
    }
    
    
    void buffer_mng::delete_vertex_arrays(size_t n, const uint32_t *arrays) noexcept
    {
        AM_RETURN_IF(!arrays);

        for (uint32_t i = 0u; i < n; ++i) {
            const uint32_t kernel_vao_id = CONV_USER_TO_KERNEL_SPACE(arrays[i]);
            AM_CONTINUE_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(kernel_vao_id) || !m_vertex_arrays.is_vertex_array_exist(kernel_vao_id));

            if (gs_context_mng.get_binded_vertex_array() == kernel_vao_id) {
                gs_context_mng.bind_vertex_array(AM_DEFAULT_KERNEL_ID, AM_DEFAULT_KERNEL_ID, AM_DEFAULT_KERNEL_ID, 0, 0);
            } else {
                gs_context_mng.bind_vertex_array(AM_DEFAULT_KERNEL_ID);
            }
            m_vertex_arrays.free_array(kernel_vao_id);
        }
    }
    
    
    void buffer_mng::gen_vertex_arrays(size_t n, uint32_t *arrays) noexcept
    {
        AM_RETURN_IF(!arrays);

        for (uint32_t i = 0u; i < n; ++i) {
            arrays[i] = CONV_KERNEL_TO_USER_SPACE(m_vertex_arrays.create_array());
        }
    }
    
    
    bool buffer_mng::is_vertex_array(uint32_t array) noexcept
    {
        AM_RETURN_IF(AM_IS_DEFAULT_ID_USER_SPACE(array), false);

        return m_vertex_arrays.is_vertex_array_exist(CONV_USER_TO_KERNEL_SPACE(array));
    }
    
    
    void buffer_mng::vertex_attrib_pointer(uint32_t index, size_t size, enum_t type, bool normalized, size_t stride, const void *pointer) noexcept
    {
        AM_SET_ERROR_FLAG_IF(size == AMGL_BGRA && normalized == false, AMGL_INVALID_OPERATION, gs_context_mng);
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(size, 1, 2, 3, 4, AMGL_BGRA), AMGL_INVALID_VALUE, gs_context_mng);

        vertex_attrib_pointer_impl<
            AMGL_INT_2_10_10_10_REV, 
            AMGL_UNSIGNED_INT_2_10_10_10_REV,
            AMGL_BYTE, 
            AMGL_UNSIGNED_BYTE, 
            AMGL_SHORT, 
            AMGL_UNSIGNED_SHORT, 
            AMGL_INT, 
            AMGL_UNSIGNED_INT, 
            AMGL_FLOAT, 
            AMGL_DOUBLE>(index, size, type, normalized, stride, pointer);
    }
    
    
    void buffer_mng::vertex_attrib_I_pointer(uint32_t index, size_t size, enum_t type, size_t stride, const void *pointer) noexcept
    {
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(size, 1, 2, 3, 4), AMGL_INVALID_VALUE, gs_context_mng);

        vertex_attrib_pointer_impl<AMGL_BYTE, AMGL_UNSIGNED_BYTE, AMGL_SHORT, AMGL_UNSIGNED_SHORT, 
            AMGL_INT, AMGL_UNSIGNED_INT>(index, size, type, false, stride, pointer);
    }
    
    
    void buffer_mng::vertex_attrib_L_pointer(uint32_t index, size_t size, enum_t type, size_t stride, const void *pointer) noexcept
    {
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(size, 1, 2, 3, 4), AMGL_INVALID_VALUE, gs_context_mng);

        vertex_attrib_pointer_impl<AMGL_DOUBLE>(index, size, type, false, stride, pointer);
    }
}