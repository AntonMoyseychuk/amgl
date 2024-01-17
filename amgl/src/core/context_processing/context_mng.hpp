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

        void update_error_flag(enum_t error) noexcept;
        enum_t get_error_flag_and_invalidate_state() noexcept;
        enum_t get_error_flag() const noexcept;

        // Takes 'buffer' in the user range [1, UINT32_MAX]
        // Doesn't check 'target' and 'buffer' validity
        void bind_target_buffer_unsafe(enum_t target, uint32_t buffer) noexcept;

        // Takes 'binding' in the user range [1, UINT32_MAX]
        // Returns AMGL_NONE if buffer is not binded to any target or it's default buffer
        enum_t get_binding_target(uint32_t binding) const noexcept;

        // Returns id in user range [1, UINT32_MAX] if there is any binding of target, otherwise AM_DEFAULT_USER_ID
        uint32_t get_binding(enum_t target) const noexcept;

    private:
        context_mng() = default;

    private:
        context m_context;
    };
}