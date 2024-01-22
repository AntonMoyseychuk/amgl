#pragma once
#include "context.hpp"


namespace amgl
{
    class context_mng
    {
    public:
        static context_mng& instance() noexcept
        {
            static context_mng manager;
            return manager;
        }

        context_mng(const context_mng&) = delete;
        context_mng& operator=(const context_mng&) = delete;
        
        const context& get_context() const noexcept { return m_context; }
        context& get_context() noexcept { return m_context; }
        
        void update_error_flag(enum_t error) const noexcept;
        enum_t get_error_flag_and_invalidate_state() const noexcept;
        enum_t get_error_flag() const noexcept;

        // NOTE: Takes 'buffer' in the user range [1, UINT32_MAX]
        // NOTE: Doesn't check 'target', and 'buffer' validity
        void bind_target_buffer_unsafe(enum_t target, uint32_t buffer, size_t binding_point = 0) noexcept;

        // NOTE: Takes 'array', 'vbo' and 'ebo' in the user range [1, UINT32_MAX]
        // NOTE: Doesn't check 'array', 'vbo' and 'ebo' validity
        void bind_vertex_array_unsafe(uint32_t array, uint32_t vbo, uint32_t ebo, size_t vbo_binding_point = 0, size_t ebo_binding_point = 0) noexcept;
        
        // Returns ID in user range [1, UINT32_MAX] if there is any binded vertex array, otherwise AM_DEFAULT_USER_ID
        uint32_t get_binded_vertex_array() const noexcept;

        // NOTE: Extremely slow, try to avoid in speed-demanding code
        // NOTE: Takes 'binding' in the user range [1, UINT32_MAX]
        // RETURNS: target if any buffer is bound, otherwise AMGL_NONE
        enum_t get_binding_target(uint32_t buffer) const noexcept;

        // RETURNS: ID in user range [1, UINT32_MAX] if there is any binding of target, otherwise AM_DEFAULT_USER_ID
        uint32_t get_binding(enum_t target, size_t binding_point = 0) const noexcept;

    private:
        context_mng() = default;

    private:
        context m_context;
    };
}