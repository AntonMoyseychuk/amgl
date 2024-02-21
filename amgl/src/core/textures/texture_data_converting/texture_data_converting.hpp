#pragma once
#include "amgl/amgl.hpp"

#include "texture_formats.hpp"
#include "texture_types.hpp"

namespace amgl
{
    struct texture_data_converter
    {
        /// @brief Copy data from 'src' to 'dst' based on 'internal_format', 'format' and 'type'
        /// @note Doesn't check params validity 
        void operator()(enum_t internal_format, void* dst, enum_t format, enum_t type, const void* src) const noexcept;
    };
}