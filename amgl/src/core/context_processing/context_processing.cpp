#include "pch.hpp"
#include "context_mng.hpp"

#include "amgl/amgl.hpp"


namespace amgl
{   
    static context_mng& gs_context_mng = context_mng::instance();

    enum_t amglGetError() noexcept
    {
        return gs_context_mng.get_error_flag_and_invalidate_state();
    }
}