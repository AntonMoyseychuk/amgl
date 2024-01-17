#include "pch.hpp"
#include "buffer_mng.hpp"

#include "core/context_processing/context_mng.hpp"

namespace amgl
{
    static context_mng& gs_context_mng = context_mng::instance();

    #define CHECK_BUFFER_TARGET_VALIDITY(target)                    \
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
            gs_context_mng.update_error_flag(AMGL_INVALID_ENUM);    \
            return;                                                 \
        }


    // Takes 'buffer' in the internal range [0, UINT32_MAX - 1]
    #define CHECK_BUFFER_VALIDITY(buffer)                                               \
        if (!m_buffers.is_buffer_exist(buffer) && !is_default_id_user_range(buffer)) {  \
            gs_context_mng.update_error_flag(AMGL_INVALID_VALUE);                       \
            return;                                                                     \
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

            const int32_t target = gs_context_mng.get_binding_type(buffers[i]);
            if (target != AMGL_NONE) {
                gs_context_mng.bind_target_buffer_unsafe(target, AM_DEFAULT_USER_ID);
            }
            m_buffers.free_id(conv_user_to_inernal_range(buffers[i]));
        }
    }
    

    void buffer_mng::bind_buffer(enum_t target, uint32_t buffer) noexcept
    {
        CHECK_BUFFER_TARGET_VALIDITY(target);
        
        const uint32_t internal_id = conv_user_to_inernal_range(buffer);
        CHECK_BUFFER_VALIDITY(internal_id);

        gs_context_mng.bind_target_buffer_unsafe(target, buffer);

        const uint32_t vao = conv_user_to_inernal_range(gs_context_mng.get_binding(AMGL_VERTEX_ARRAY_BINDING));
        if (vao != AM_DEFAULT_INTERNAL_ID) {
            m_vertex_arrays.bind_buffer_unsafe(vao, target, internal_id);
        }
    }
    
    
    bool buffer_mng::is_buffer(uint32_t buffer) noexcept
    {
        AM_RETURN_IF(is_default_id_user_range(buffer), false);

        return m_buffers.is_buffer_exist(conv_user_to_inernal_range(buffer));
    }
}