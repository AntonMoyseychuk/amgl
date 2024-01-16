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
        RETURN_IF(!buffers);

        for (uint32_t i = 0u; i < n; ++i) {
            buffers[i] = m_buffers.create_id();
        }
    }


    void buffer_mng::delete_buffers(uint32_t n, const uint32_t *buffers) noexcept
    {
        RETURN_IF(!buffers);

        for (uint32_t i = 0u; i < n; ++i) {
            
            m_buffers.free_id(buffers[i]);
        }
    }
    

    void buffer_mng::bind_buffer(enum_t target, uint32_t buffer) noexcept
    {
        CHECK_BUFFER_TARGET_VALIDITY(target);
        CHECK_BUFFER_VALIDITY(buffer);

        gs_context_mng.bind_target_buffer_unsafe(target, conv_user_to_inernal_range(buffer));
    }
}