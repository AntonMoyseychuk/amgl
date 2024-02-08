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


    void context_mng::bind_vertex_array(uint32_t array, uint32_t vbo, uint32_t ebo, size_t vbo_idx, size_t ebo_idx) noexcept
    {
        CHECK_BINDING_INDEX_VALIDITY(AMGL_ARRAY_BUFFER, vbo_idx, AMGL_INVALID_VALUE);
        CHECK_BINDING_INDEX_VALIDITY(AMGL_ELEMENT_ARRAY_BUFFER, ebo_idx, AMGL_INVALID_VALUE);

        m_context.buf_bindings.vao          = array;
        m_context.buf_bindings.vbo[vbo_idx].buffer = vbo;
        m_context.buf_bindings.ebo[ebo_idx].buffer = ebo;
    }

    
    void context_mng::bind_vertex_array(uint32_t array) noexcept
    {
        m_context.buf_bindings.vao = array;
    }


    uint32_t context_mng::get_binded_vertex_array() const noexcept
    {
        return m_context.buf_bindings.vao;
    }

    
    void context_mng::bind_target_buffer(enum_t target, uint32_t buffer, size_t index) noexcept
    {
        CHECK_BINDING_INDEX_VALIDITY(target, index, AMGL_INVALID_VALUE);

        switch (target) {
            case AMGL_ARRAY_BUFFER:                 m_context.buf_bindings.vbo[index].buffer   = buffer; break;
            case AMGL_ATOMIC_COUNTER_BUFFER:        m_context.buf_bindings.acbo[index].buffer  = buffer; break;
            case AMGL_COPY_READ_BUFFER:             m_context.buf_bindings.crbo[index].buffer  = buffer; break;
            case AMGL_COPY_WRITE_BUFFER:            m_context.buf_bindings.cwbo[index].buffer  = buffer; break;
            case AMGL_DISPATCH_INDIRECT_BUFFER:     m_context.buf_bindings.dibo[index].buffer  = buffer; break;
            case AMGL_DRAW_INDIRECT_BUFFER:         m_context.buf_bindings.dribo[index].buffer = buffer; break;
            case AMGL_ELEMENT_ARRAY_BUFFER:         m_context.buf_bindings.ebo[index].buffer   = buffer; break;
            case AMGL_PIXEL_PACK_BUFFER:            m_context.buf_bindings.ppbo[index].buffer  = buffer; break;
            case AMGL_PIXEL_UNPACK_BUFFER:          m_context.buf_bindings.pubo[index].buffer  = buffer; break;
            case AMGL_QUERY_BUFFER:                 m_context.buf_bindings.qbo[index].buffer   = buffer; break;
            case AMGL_SHADER_STORAGE_BUFFER:        m_context.buf_bindings.ssbo[index].buffer  = buffer; break;
            case AMGL_TEXTURE_BUFFER:               m_context.buf_bindings.tbo[index].buffer   = buffer; break;
            case AMGL_TRANSFORM_FEEDBACK_BUFFER:    m_context.buf_bindings.tfbo[index].buffer  = buffer; break;
            case AMGL_UNIFORM_BUFFER:               m_context.buf_bindings.ubo[index].buffer   = buffer; break;
        };
    }


    uint32_t context_mng::get_binded_buffer(enum_t target, size_t index) const noexcept
    {
        CHECK_BINDING_INDEX_VALIDITY(target, index, AMGL_INVALID_VALUE, AM_DEFAULT_KERNEL_ID);

        switch (target) {
            case AMGL_ARRAY_BUFFER:                 return m_context.buf_bindings.vbo[index].buffer;
            case AMGL_ELEMENT_ARRAY_BUFFER:         return m_context.buf_bindings.ebo[index].buffer;
            case AMGL_COPY_READ_BUFFER:             return m_context.buf_bindings.crbo[index].buffer;
            case AMGL_COPY_WRITE_BUFFER:            return m_context.buf_bindings.cwbo[index].buffer;
            case AMGL_SHADER_STORAGE_BUFFER:        return m_context.buf_bindings.ssbo[index].buffer;
            case AMGL_UNIFORM_BUFFER:               return m_context.buf_bindings.ubo[index].buffer;
            case AMGL_TEXTURE_BUFFER:               return m_context.buf_bindings.tbo[index].buffer;
            case AMGL_TRANSFORM_FEEDBACK_BUFFER:    return m_context.buf_bindings.tfbo[index].buffer;
            case AMGL_DRAW_INDIRECT_BUFFER:         return m_context.buf_bindings.dribo[index].buffer;
            case AMGL_PIXEL_PACK_BUFFER:            return m_context.buf_bindings.ppbo[index].buffer;
            case AMGL_PIXEL_UNPACK_BUFFER:          return m_context.buf_bindings.pubo[index].buffer;
            case AMGL_QUERY_BUFFER:                 return m_context.buf_bindings.qbo[index].buffer;
            case AMGL_DISPATCH_INDIRECT_BUFFER:     return m_context.buf_bindings.dibo[index].buffer;
            case AMGL_ATOMIC_COUNTER_BUFFER:        return m_context.buf_bindings.acbo[index].buffer;
            default:                                return AM_DEFAULT_KERNEL_ID;
        };
    }
    
    
    void context_mng::bind_target_buffer_range(enum_t target, size_t index, const buffer_range& range) noexcept
    {
        CHECK_BINDING_INDEX_VALIDITY(target, index, AMGL_INVALID_VALUE);

        switch (target) {
            case AMGL_ATOMIC_COUNTER_BUFFER:        m_context.buf_bindings.acbo_ranges[index] = range; break;
            case AMGL_SHADER_STORAGE_BUFFER:        m_context.buf_bindings.ssbo_ranges[index] = range; break;
            case AMGL_TRANSFORM_FEEDBACK_BUFFER:    m_context.buf_bindings.tfbo_ranges[index] = range; break;
            case AMGL_UNIFORM_BUFFER:               m_context.buf_bindings.ubo_ranges[index]  = range; break;
        };
    }
    
    
    const buffer_range& context_mng::get_binded_buffer_range(enum_t target, size_t index) const noexcept
    {
        const static buffer_range default_range;

        CHECK_BINDING_INDEX_VALIDITY(target, index, AMGL_INVALID_VALUE, default_range);

        switch (target) {
            case AMGL_ATOMIC_COUNTER_BUFFER:        return m_context.buf_bindings.acbo_ranges[index];
            case AMGL_SHADER_STORAGE_BUFFER:        return m_context.buf_bindings.ssbo_ranges[index];
            case AMGL_TRANSFORM_FEEDBACK_BUFFER:    return m_context.buf_bindings.tfbo_ranges[index];
            case AMGL_UNIFORM_BUFFER:               return m_context.buf_bindings.ubo_ranges[index];
            default:                                return default_range;
        };
    }

    
    void context_mng::bind_target_texture(enum_t target, uint32_t texture) noexcept
    {
        switch (target) {
            case AMGL_TEXTURE_1D:                         m_context.tex_bindings.texture1d                          = texture; break;
            case AMGL_PROXY_TEXTURE_1D:                   m_context.tex_bindings.proxy_texture1d                    = texture; break;
            case AMGL_TEXTURE_2D:                         m_context.tex_bindings.texture2d                          = texture; break;
            case AMGL_PROXY_TEXTURE_2D:                   m_context.tex_bindings.proxy_texture2d                    = texture; break;
            case AMGL_TEXTURE_3D:                         m_context.tex_bindings.texture3d                          = texture; break;
            case AMGL_PROXY_TEXTURE_3D:                   m_context.tex_bindings.proxy_texture3d                    = texture; break;
            case AMGL_TEXTURE_RECTANGLE:                  m_context.tex_bindings.texture_rect                       = texture; break;
            case AMGL_PROXY_TEXTURE_RECTANGLE:            m_context.tex_bindings.proxy_texture_rect                 = texture; break;
            case AMGL_TEXTURE_1D_ARRAY:                   m_context.tex_bindings.texture1d_array                    = texture; break;
            case AMGL_PROXY_TEXTURE_1D_ARRAY:             m_context.tex_bindings.proxy_texture1d_array              = texture; break;
            case AMGL_TEXTURE_2D_ARRAY:                   m_context.tex_bindings.texture2d_array                    = texture; break;
            case AMGL_PROXY_TEXTURE_2D_ARRAY:             m_context.tex_bindings.proxy_texture2d_array              = texture; break;
            case AMGL_TEXTURE_CUBE_MAP:                   m_context.tex_bindings.texture_cubemap                    = texture; break;
            case AMGL_PROXY_TEXTURE_CUBE_MAP:             m_context.tex_bindings.proxy_texture_cubemap              = texture; break;
            case AMGL_TEXTURE_CUBE_MAP_ARRAY:             m_context.tex_bindings.texture_cubemap_array              = texture; break;
            case AMGL_PROXY_TEXTURE_CUBE_MAP_ARRAY:       m_context.tex_bindings.proxy_texture_cubemap_array        = texture; break;
            case AMGL_TEXTURE_2D_MULTISAMPLE:             m_context.tex_bindings.texture_2d_multisample             = texture; break;
            case AMGL_PROXY_TEXTURE_2D_MULTISAMPLE:       m_context.tex_bindings.proxy_texture_2d_multisample       = texture; break;
            case AMGL_TEXTURE_2D_MULTISAMPLE_ARRAY:       m_context.tex_bindings.texture_2d_multisample_array       = texture; break;
            case AMGL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY: m_context.tex_bindings.proxy_texture_2d_multisample_array = texture; break;
            case AMGL_TEXTURE_BUFFER:                     m_context.tex_bindings.texture_buffer                     = texture; break;
        };
    }
    
    
    uint32_t context_mng::get_binded_texture(enum_t target) const noexcept
    {
        switch (target) {
            case AMGL_TEXTURE_1D:                           return m_context.tex_bindings.texture1d;
            case AMGL_PROXY_TEXTURE_1D:                     return m_context.tex_bindings.proxy_texture1d;
            case AMGL_TEXTURE_2D:                           return m_context.tex_bindings.texture2d;
            case AMGL_PROXY_TEXTURE_2D:                     return m_context.tex_bindings.proxy_texture2d;
            case AMGL_TEXTURE_3D:                           return m_context.tex_bindings.texture3d;
            case AMGL_PROXY_TEXTURE_3D:                     return m_context.tex_bindings.proxy_texture3d;
            case AMGL_TEXTURE_RECTANGLE:                    return m_context.tex_bindings.texture_rect;
            case AMGL_PROXY_TEXTURE_RECTANGLE:              return m_context.tex_bindings.proxy_texture_rect;
            case AMGL_TEXTURE_1D_ARRAY:                     return m_context.tex_bindings.texture1d_array;
            case AMGL_PROXY_TEXTURE_1D_ARRAY:               return m_context.tex_bindings.proxy_texture1d_array;
            case AMGL_TEXTURE_2D_ARRAY:                     return m_context.tex_bindings.texture2d_array;
            case AMGL_PROXY_TEXTURE_2D_ARRAY:               return m_context.tex_bindings.proxy_texture2d_array;
            case AMGL_TEXTURE_CUBE_MAP:                     return m_context.tex_bindings.texture_cubemap;
            case AMGL_PROXY_TEXTURE_CUBE_MAP:               return m_context.tex_bindings.proxy_texture_cubemap;
            case AMGL_TEXTURE_CUBE_MAP_ARRAY:               return m_context.tex_bindings.texture_cubemap_array;
            case AMGL_PROXY_TEXTURE_CUBE_MAP_ARRAY:         return m_context.tex_bindings.proxy_texture_cubemap_array;
            case AMGL_TEXTURE_2D_MULTISAMPLE:               return m_context.tex_bindings.texture_2d_multisample;
            case AMGL_PROXY_TEXTURE_2D_MULTISAMPLE:         return m_context.tex_bindings.proxy_texture_2d_multisample;
            case AMGL_TEXTURE_2D_MULTISAMPLE_ARRAY:         return m_context.tex_bindings.texture_2d_multisample_array;
            case AMGL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY:   return m_context.tex_bindings.proxy_texture_2d_multisample_array;
            case AMGL_TEXTURE_BUFFER:                       return m_context.tex_bindings.texture_buffer;
            default:                                        return AM_DEFAULT_KERNEL_ID;
        };
    }
}