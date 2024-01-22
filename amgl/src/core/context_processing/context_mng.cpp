#include "pch.hpp"
#include "context_mng.hpp"

#include "amgl/amgl.hpp"


namespace amgl
{
    #define CHECK_BINDING_INDEX_VALIDITY(target, index, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(!detail::is_in_range((int32_t)index, (int32_t)0, get_target_bidning_points_count(target)), error_flag, *this, __VA_ARGS__)

    // Return -1 if target is not:
    // - AMGL_ARRAY_BUFFER
    // - AMGL_ATOMIC_COUNTER_BUFFER
    // - AMGL_COPY_READ_BUFFER
    // - AMGL_COPY_WRITE_BUFFER
    // - AMGL_DISPATCH_INDIRECT_BUFFER
    // - AMGL_DRAW_INDIRECT_BUFFER
    // - AMGL_ELEMENT_ARRAY_BUFFER
    // - AMGL_PIXEL_PACK_BUFFER
    // - AMGL_PIXEL_UNPACK_BUFFER
    // - AMGL_QUERY_BUFFER
    // - AMGL_SHADER_STORAGE_BUFFER
    // - AMGL_TEXTURE_BUFFER
    // - AMGL_TRANSFORM_FEEDBACK_BUFFER
    // - AMGL_UNIFORM_BUFFER
    static constexpr int32_t get_target_bidning_points_count(enum_t target) noexcept
    {
        switch (target) {
            case AMGL_ARRAY_BUFFER:                 return context::MAX_VERTEX_BUFFER_BINDINGS;
            case AMGL_ATOMIC_COUNTER_BUFFER:        return context::MAX_ATOMIC_COUNTER_BUFFER_BINDINGS;
            case AMGL_COPY_READ_BUFFER:             return context::MAX_COPY_READ_BUFFER_BINDINGS;
            case AMGL_COPY_WRITE_BUFFER:            return context::MAX_COPY_WRITE_BUFFER_BINDINGS;
            case AMGL_DISPATCH_INDIRECT_BUFFER:     return context::MAX_DISPATCH_INDIRECT_BUFFER_BINDINGS;
            case AMGL_DRAW_INDIRECT_BUFFER:         return context::MAX_DRAW_INDIRECT_BUFFER_BINDINGS;
            case AMGL_ELEMENT_ARRAY_BUFFER:         return context::MAX_ELEMENT_BUFFER_BINDINGS;
            case AMGL_PIXEL_PACK_BUFFER:            return context::MAX_PIXEL_PACK_BUFFER_BINDINGS;
            case AMGL_PIXEL_UNPACK_BUFFER:          return context::MAX_PIXEL_UNPACK_BUFFER_BINDINGS;
            case AMGL_QUERY_BUFFER:                 return context::MAX_QUERY_BUFFER_BINDINGS;
            case AMGL_SHADER_STORAGE_BUFFER:        return context::MAX_SHADER_STORAGE_BUFFER_BINDINGS;
            case AMGL_TEXTURE_BUFFER:               return context::MAX_TEXTURE_BUFFER_BINDINGS;
            case AMGL_TRANSFORM_FEEDBACK_BUFFER:    return context::MAX_TRANSFORM_FEEDBACK_BUFFER_BINDINGS;
            case AMGL_UNIFORM_BUFFER:               return context::MAX_UNIFORM_BUFFER_BINDINGS;  
            default:                                return -1;
        };
    }


    void context_mng::update_error_flag(enum_t error) const noexcept
    {
        AM_ASSERT(detail::is_one_of(error, AMGL_INVALID_ENUM, AMGL_INVALID_VALUE, AMGL_INVALID_OPERATION, 
            AMGL_STACK_OVERFLOW, AMGL_STACK_UNDERFLOW, AMGL_OUT_OF_MEMORY, AMGL_INVALID_FRAMEBUFFER_OPERATION));

        if (m_context.error_status == AMGL_NO_ERROR) {
            m_context.error_status = error;
        }
    }
    
    
    enum_t context_mng::get_error_flag_and_invalidate_state() const noexcept
    {
        const enum_t error_status = m_context.error_status;
        m_context.error_status = AMGL_NO_ERROR;
        return error_status;
    }
    
    
    enum_t context_mng::get_error_flag() const noexcept
    {
        return m_context.error_status;
    }

    
    void context_mng::bind_target_buffer_unsafe(enum_t target, uint32_t buffer, size_t binding_point) noexcept
    {
        CHECK_BINDING_INDEX_VALIDITY(target, binding_point, AMGL_INVALID_VALUE);

        const uint32_t internal_id = conv_user_to_inernal_range(buffer);

        switch (target) {
            case AMGL_ARRAY_BUFFER:                 m_context.bindings.vbo[binding_point].buffer   = internal_id; break;
            case AMGL_ATOMIC_COUNTER_BUFFER:        m_context.bindings.acbo[binding_point].buffer  = internal_id; break;
            case AMGL_COPY_READ_BUFFER:             m_context.bindings.crbo[binding_point].buffer  = internal_id; break;
            case AMGL_COPY_WRITE_BUFFER:            m_context.bindings.cwbo[binding_point].buffer  = internal_id; break;
            case AMGL_DISPATCH_INDIRECT_BUFFER:     m_context.bindings.dibo[binding_point].buffer  = internal_id; break;
            case AMGL_DRAW_INDIRECT_BUFFER:         m_context.bindings.dribo[binding_point].buffer = internal_id; break;
            case AMGL_ELEMENT_ARRAY_BUFFER:         m_context.bindings.ebo[binding_point].buffer   = internal_id; break;
            case AMGL_PIXEL_PACK_BUFFER:            m_context.bindings.ppbo[binding_point].buffer  = internal_id; break;
            case AMGL_PIXEL_UNPACK_BUFFER:          m_context.bindings.pubo[binding_point].buffer  = internal_id; break;
            case AMGL_QUERY_BUFFER:                 m_context.bindings.qbo[binding_point].buffer   = internal_id; break;
            case AMGL_SHADER_STORAGE_BUFFER:        m_context.bindings.ssbo[binding_point].buffer  = internal_id; break;
            case AMGL_TEXTURE_BUFFER:               m_context.bindings.tbo[binding_point].buffer   = internal_id; break;
            case AMGL_TRANSFORM_FEEDBACK_BUFFER:    m_context.bindings.tfbo[binding_point].buffer  = internal_id; break;
            case AMGL_UNIFORM_BUFFER:               m_context.bindings.ubo[binding_point].buffer   = internal_id; break;
        };
    }

    
    void context_mng::bind_vertex_array_unsafe(uint32_t array, uint32_t vbo, uint32_t ebo, size_t vbo_binding_point, size_t ebo_binding_poin) noexcept
    {
        CHECK_BINDING_INDEX_VALIDITY(AMGL_ARRAY_BUFFER, vbo_binding_point, AMGL_INVALID_VALUE);
        CHECK_BINDING_INDEX_VALIDITY(AMGL_ELEMENT_ARRAY_BUFFER, ebo_binding_poin, AMGL_INVALID_VALUE);

        m_context.bindings.vao                              = conv_user_to_inernal_range(array);
        m_context.bindings.vbo[vbo_binding_point].buffer    = conv_user_to_inernal_range(vbo);
        m_context.bindings.ebo[ebo_binding_poin].buffer     = conv_user_to_inernal_range(ebo);
    }


    uint32_t context_mng::get_binded_vertex_array() const noexcept
    {
        return conv_internal_to_user_range(m_context.bindings.vao);
    }

    
    enum_t context_mng::get_binding_target(uint32_t buffer) const noexcept
    {
        AM_RETURN_IF(is_default_id_user_range(buffer), AMGL_NONE);

        const uint32_t internal_id = conv_user_to_inernal_range(buffer);

        AM_RETURN_VALUE_IF_FIND_ELEMENT(m_context.bindings.vbo,   internal_id, AMGL_ARRAY_BUFFER);        
        AM_RETURN_VALUE_IF_FIND_ELEMENT(m_context.bindings.ebo,   internal_id, AMGL_ELEMENT_ARRAY_BUFFER);
        AM_RETURN_VALUE_IF_FIND_ELEMENT(m_context.bindings.ssbo,  internal_id, AMGL_SHADER_STORAGE_BUFFER);
        AM_RETURN_VALUE_IF_FIND_ELEMENT(m_context.bindings.ubo,   internal_id, AMGL_UNIFORM_BUFFER);
        AM_RETURN_VALUE_IF_FIND_ELEMENT(m_context.bindings.crbo,  internal_id, AMGL_COPY_READ_BUFFER);
        AM_RETURN_VALUE_IF_FIND_ELEMENT(m_context.bindings.cwbo,  internal_id, AMGL_COPY_WRITE_BUFFER);
        AM_RETURN_VALUE_IF_FIND_ELEMENT(m_context.bindings.tbo,   internal_id, AMGL_TEXTURE_BUFFER);
        AM_RETURN_VALUE_IF_FIND_ELEMENT(m_context.bindings.tfbo,  internal_id, AMGL_TRANSFORM_FEEDBACK_BUFFER);
        AM_RETURN_VALUE_IF_FIND_ELEMENT(m_context.bindings.dribo, internal_id, AMGL_DRAW_INDIRECT_BUFFER);
        AM_RETURN_VALUE_IF_FIND_ELEMENT(m_context.bindings.ppbo,  internal_id, AMGL_PIXEL_PACK_BUFFER);
        AM_RETURN_VALUE_IF_FIND_ELEMENT(m_context.bindings.pubo,  internal_id, AMGL_PIXEL_UNPACK_BUFFER);
        AM_RETURN_VALUE_IF_FIND_ELEMENT(m_context.bindings.qbo,   internal_id, AMGL_QUERY_BUFFER);
        AM_RETURN_VALUE_IF_FIND_ELEMENT(m_context.bindings.dibo,  internal_id, AMGL_DISPATCH_INDIRECT_BUFFER);
        AM_RETURN_VALUE_IF_FIND_ELEMENT(m_context.bindings.acbo,  internal_id, AMGL_ATOMIC_COUNTER_BUFFER);

        return AMGL_NONE;
    }

    uint32_t context_mng::get_binding(enum_t target, size_t binding_point) const noexcept
    {
        CHECK_BINDING_INDEX_VALIDITY(target, binding_point, AMGL_INVALID_VALUE, AM_DEFAULT_USER_ID);

        switch (target) {
            case AMGL_ARRAY_BUFFER:                 return conv_internal_to_user_range(m_context.bindings.vbo[binding_point].buffer);
            case AMGL_ELEMENT_ARRAY_BUFFER:         return conv_internal_to_user_range(m_context.bindings.ebo[binding_point].buffer);
            case AMGL_COPY_READ_BUFFER:             return conv_internal_to_user_range(m_context.bindings.crbo[binding_point].buffer);
            case AMGL_COPY_WRITE_BUFFER:            return conv_internal_to_user_range(m_context.bindings.cwbo[binding_point].buffer);
            case AMGL_SHADER_STORAGE_BUFFER:        return conv_internal_to_user_range(m_context.bindings.ssbo[binding_point].buffer);
            case AMGL_UNIFORM_BUFFER:               return conv_internal_to_user_range(m_context.bindings.ubo[binding_point].buffer);
            case AMGL_TEXTURE_BUFFER:               return conv_internal_to_user_range(m_context.bindings.tbo[binding_point].buffer);
            case AMGL_TRANSFORM_FEEDBACK_BUFFER:    return conv_internal_to_user_range(m_context.bindings.tfbo[binding_point].buffer);
            case AMGL_DRAW_INDIRECT_BUFFER:         return conv_internal_to_user_range(m_context.bindings.dribo[binding_point].buffer);
            case AMGL_PIXEL_PACK_BUFFER:            return conv_internal_to_user_range(m_context.bindings.ppbo[binding_point].buffer);
            case AMGL_PIXEL_UNPACK_BUFFER:          return conv_internal_to_user_range(m_context.bindings.pubo[binding_point].buffer);
            case AMGL_QUERY_BUFFER:                 return conv_internal_to_user_range(m_context.bindings.qbo[binding_point].buffer);
            case AMGL_DISPATCH_INDIRECT_BUFFER:     return conv_internal_to_user_range(m_context.bindings.dibo[binding_point].buffer);
            case AMGL_ATOMIC_COUNTER_BUFFER:        return conv_internal_to_user_range(m_context.bindings.acbo[binding_point].buffer);
            default:                                return AM_DEFAULT_USER_ID;
        };
    }
}