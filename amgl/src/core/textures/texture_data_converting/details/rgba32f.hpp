#pragma once
#include "amgl/amgl.hpp"

namespace amgl
{
    namespace detail
    {
        void format_type_to_rgba32f(void* dst, enum_t format, enum_t type, const void* src) noexcept;
    }
}