#include "pch.hpp"
#include "context.hpp"

namespace amgl
{
    static context& gs_context = context::instance();

    void context::update_error_flag(enum_t error) noexcept
    {
        AM_ASSERT(detail::is_one_of(error, AMGL_INVALID_ENUM, AMGL_INVALID_VALUE, AMGL_INVALID_OPERATION, 
            AMGL_STACK_OVERFLOW, AMGL_STACK_UNDERFLOW, AMGL_OUT_OF_MEMORY, AMGL_INVALID_FRAMEBUFFER_OPERATION));

        if (gs_context.error_status == AMGL_NO_ERROR) {
            gs_context.error_status = error;
        }
    }
}