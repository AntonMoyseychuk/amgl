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


        /*----------------------- Buffer Manager related API -----------------------*/

        // NOTE: Takes 'array', 'vbo' and 'ebo' in the user range [1, UINT32_MAX - 1]
        // NOTE: Doesn't check 'array', 'vbo' and 'ebo' validity
        void bind_vertex_array(uint32_t array, uint32_t vbo, uint32_t ebo, size_t vbo_idx, size_t ebo_idx) noexcept;
        // NOTE: Takes 'array' in the user range [1, UINT32_MAX - 1]
        // NOTE: Doesn't check 'array' validity
        void bind_vertex_array(uint32_t array) noexcept;
        
        // Returns ID in user range [1, UINT32_MAX - 1] if there is any binded vertex array, otherwise AM_DEFAULT_USER_ID
        uint32_t get_binded_vertex_array() const noexcept;

        // NOTE: Takes 'buffer' in the user range [1, UINT32_MAX - 1]
        // NOTE: Doesn't check 'target', and 'buffer' validity
        void bind_target_buffer(enum_t target, uint32_t buffer, size_t index) noexcept;

        // RETURNS: ID in user range [1, UINT32_MAX - 1] if there is any binding of target, otherwise AM_DEFAULT_USER_ID
        uint32_t get_binded_buffer(enum_t target, size_t index) const noexcept;

    private:
        context_mng() = default;

    private:
        context m_context;
    };
}