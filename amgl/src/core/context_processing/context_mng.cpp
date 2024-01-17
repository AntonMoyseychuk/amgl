#include "pch.hpp"
#include "context_mng.hpp"

#include "amgl/amgl.hpp"


namespace amgl
{
    void context_mng::update_error_flag(enum_t error) noexcept
    {
        AM_ASSERT(detail::is_one_of(error, AMGL_INVALID_ENUM, AMGL_INVALID_VALUE, AMGL_INVALID_OPERATION, 
            AMGL_STACK_OVERFLOW, AMGL_STACK_UNDERFLOW, AMGL_OUT_OF_MEMORY, AMGL_INVALID_FRAMEBUFFER_OPERATION));

        if (m_context.error_status == AMGL_NO_ERROR) {
            m_context.error_status = error;
        }
    }
    
    
    enum_t context_mng::get_error_flag_and_invalidate_state() noexcept
    {
        const enum_t error_status = m_context.error_status;
        m_context.error_status = AMGL_NO_ERROR;
        return error_status;
    }
    
    
    enum_t context_mng::get_error_flag() const noexcept
    {
        return m_context.error_status;
    }
    
    
    void context_mng::bind_target_buffer_unsafe(enum_t target, uint32_t buffer) noexcept
    {
        const uint32_t internal_id = conv_user_to_inernal_range(buffer);

        switch (target)
        {
        case AMGL_ARRAY_BUFFER:
            m_context.bindings.vbo = internal_id;
            break;
        case AMGL_ATOMIC_COUNTER_BUFFER:
            m_context.bindings.acbo = internal_id;
            break;
        case AMGL_COPY_READ_BUFFER:
            m_context.bindings.crbo = internal_id;
            break;
        case AMGL_COPY_WRITE_BUFFER:
            m_context.bindings.cwbo = internal_id;
            break;
        case AMGL_DISPATCH_INDIRECT_BUFFER:
            m_context.bindings.dibo = internal_id;
            break;
        case AMGL_DRAW_INDIRECT_BUFFER:
            m_context.bindings.dribo = internal_id;
            break;
        case AMGL_ELEMENT_ARRAY_BUFFER:
            m_context.bindings.ebo = internal_id;
            break;
        case AMGL_PIXEL_PACK_BUFFER:
            m_context.bindings.ppbo = internal_id;
            break;
        case AMGL_PIXEL_UNPACK_BUFFER:
            m_context.bindings.pubo = internal_id;
            break;
        case AMGL_QUERY_BUFFER:
            m_context.bindings.qbo = internal_id;
            break;
        case AMGL_SHADER_STORAGE_BUFFER:
            m_context.bindings.ssbo = internal_id;
            break;
        case AMGL_TEXTURE_BUFFER:
            m_context.bindings.tbo = internal_id;
            break;
        case AMGL_TRANSFORM_FEEDBACK_BUFFER:
            m_context.bindings.tfbo = internal_id;
            break;
        case AMGL_UNIFORM_BUFFER:
            m_context.bindings.ubo = internal_id;
            break;
        };
    }
    
    
    enum_t context_mng::get_binding_target(uint32_t binding) const noexcept
    {
        AM_RETURN_IF(is_default_id_user_range(binding), AMGL_NONE);

        const uint32_t internal_id = conv_user_to_inernal_range(binding);

        AM_RETURN_IF(m_context.bindings.vbo    == internal_id, AMGL_ARRAY_BUFFER);
        AM_RETURN_IF(m_context.bindings.ebo    == internal_id, AMGL_ELEMENT_ARRAY_BUFFER);
        AM_RETURN_IF(m_context.bindings.crbo   == internal_id, AMGL_COPY_READ_BUFFER);
        AM_RETURN_IF(m_context.bindings.cwbo   == internal_id, AMGL_COPY_WRITE_BUFFER);
        AM_RETURN_IF(m_context.bindings.ssbo   == internal_id, AMGL_SHADER_STORAGE_BUFFER);
        AM_RETURN_IF(m_context.bindings.ubo    == internal_id, AMGL_UNIFORM_BUFFER);
        AM_RETURN_IF(m_context.bindings.tbo    == internal_id, AMGL_TEXTURE_BUFFER);
        AM_RETURN_IF(m_context.bindings.tfbo   == internal_id, AMGL_TRANSFORM_FEEDBACK_BUFFER);
        AM_RETURN_IF(m_context.bindings.dribo  == internal_id, AMGL_DRAW_INDIRECT_BUFFER);
        AM_RETURN_IF(m_context.bindings.ppbo   == internal_id, AMGL_PIXEL_PACK_BUFFER);
        AM_RETURN_IF(m_context.bindings.pubo   == internal_id, AMGL_PIXEL_UNPACK_BUFFER);
        AM_RETURN_IF(m_context.bindings.qbo    == internal_id, AMGL_QUERY_BUFFER);
        AM_RETURN_IF(m_context.bindings.dibo   == internal_id, AMGL_DISPATCH_INDIRECT_BUFFER);
        AM_RETURN_IF(m_context.bindings.acbo   == internal_id, AMGL_ATOMIC_COUNTER_BUFFER);

        return AMGL_NONE;
    }

    uint32_t context_mng::get_binding(enum_t target) const noexcept
    {
        AM_RETURN_IF(target == AMGL_VERTEX_ARRAY_BINDING,      conv_internal_to_user_range(m_context.bindings.vao));
        AM_RETURN_IF(target == AMGL_ARRAY_BUFFER,              conv_internal_to_user_range(m_context.bindings.vbo));
        AM_RETURN_IF(target == AMGL_ELEMENT_ARRAY_BUFFER,      conv_internal_to_user_range(m_context.bindings.ebo));
        AM_RETURN_IF(target == AMGL_COPY_READ_BUFFER,          conv_internal_to_user_range(m_context.bindings.crbo));
        AM_RETURN_IF(target == AMGL_COPY_WRITE_BUFFER,         conv_internal_to_user_range(m_context.bindings.cwbo));
        AM_RETURN_IF(target == AMGL_SHADER_STORAGE_BUFFER,     conv_internal_to_user_range(m_context.bindings.ssbo));
        AM_RETURN_IF(target == AMGL_UNIFORM_BUFFER,            conv_internal_to_user_range(m_context.bindings.ubo));
        AM_RETURN_IF(target == AMGL_TEXTURE_BUFFER,            conv_internal_to_user_range(m_context.bindings.tbo));
        AM_RETURN_IF(target == AMGL_TRANSFORM_FEEDBACK_BUFFER, conv_internal_to_user_range(m_context.bindings.tfbo));
        AM_RETURN_IF(target == AMGL_DRAW_INDIRECT_BUFFER,      conv_internal_to_user_range(m_context.bindings.dribo));
        AM_RETURN_IF(target == AMGL_PIXEL_PACK_BUFFER,         conv_internal_to_user_range(m_context.bindings.ppbo));
        AM_RETURN_IF(target == AMGL_PIXEL_UNPACK_BUFFER,       conv_internal_to_user_range(m_context.bindings.pubo));
        AM_RETURN_IF(target == AMGL_QUERY_BUFFER,              conv_internal_to_user_range(m_context.bindings.qbo));
        AM_RETURN_IF(target == AMGL_DISPATCH_INDIRECT_BUFFER,  conv_internal_to_user_range(m_context.bindings.dibo));
        AM_RETURN_IF(target == AMGL_ATOMIC_COUNTER_BUFFER,     conv_internal_to_user_range(m_context.bindings.acbo));

        return AM_DEFAULT_USER_ID;
    }
}