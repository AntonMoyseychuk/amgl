#pragma once
#include "core/textures/internal/formats.hpp"

namespace amgl
{
    namespace detail
    {
        void* get_rgba32f_convert_function(enum_t format, enum_t type) noexcept;
    }
}