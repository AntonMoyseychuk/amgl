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
        switch (target)
        {
        case AMGL_ARRAY_BUFFER:
            m_context.bindings.vbo = buffer;
            break;
        case AMGL_ATOMIC_COUNTER_BUFFER:
            m_context.bindings.acbo = buffer;
            break;
        case AMGL_COPY_READ_BUFFER:
            m_context.bindings.crbo = buffer;
            break;
        case AMGL_COPY_WRITE_BUFFER:
            m_context.bindings.cwbo = buffer;
            break;
        case AMGL_DISPATCH_INDIRECT_BUFFER:
            m_context.bindings.dibo = buffer;
            break;
        case AMGL_DRAW_INDIRECT_BUFFER:
            m_context.bindings.dribo = buffer;
            break;
        case AMGL_ELEMENT_ARRAY_BUFFER:
            m_context.bindings.ebo = buffer;
            break;
        case AMGL_PIXEL_PACK_BUFFER:
            m_context.bindings.ppbo = buffer;
            break;
        case AMGL_PIXEL_UNPACK_BUFFER:
            m_context.bindings.pubo = buffer;
            break;
        case AMGL_QUERY_BUFFER:
            m_context.bindings.qbo = buffer;
            break;
        case AMGL_SHADER_STORAGE_BUFFER:
            m_context.bindings.ssbo = buffer;
            break;
        case AMGL_TEXTURE_BUFFER:
            m_context.bindings.tbo = buffer;
            break;
        case AMGL_TRANSFORM_FEEDBACK_BUFFER:
            m_context.bindings.tfbo = buffer;
            break;
        case AMGL_UNIFORM_BUFFER:
            m_context.bindings.ubo = buffer;
            break;
        };
    }
}