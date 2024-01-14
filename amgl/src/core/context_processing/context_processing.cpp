#include "pch.hpp"
#include "context.hpp"


namespace amgl
{   
    static context& gs_context = context::instance();

    enum_t amglGetError() noexcept
    {
        const enum_t error_status = gs_context.error_status;
        gs_context.error_status = AMGL_NO_ERROR;
        return error_status;
    }
}