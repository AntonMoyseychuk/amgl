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

    private:
        context_mng() = default;

    private:
        context m_context;
    };
}