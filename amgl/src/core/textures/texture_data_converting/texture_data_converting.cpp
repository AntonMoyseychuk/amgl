#include "pch.hpp"
#include "texture_data_converting.hpp"

#include "core/core.hpp"

#include "internal/red.hpp"

namespace amgl
{
    void texture_data_converter::operator()(enum_t internal_format, void *dst, enum_t format, enum_t type, const void *src) const noexcept
    {
        switch(internal_format) {
            case AMGL_RED:                      detail::format_type_to_red(dst, format, type, src);
            // case AMGL_RG:
            // case AMGL_RGB:
            // case AMGL_RGBA:
            // case AMGL_RED_INTEGER:
            // case AMGL_RG_INTEGER:
            // case AMGL_RGB_INTEGER:
            // case AMGL_RGBA_INTEGER:
            // case AMGL_BGR:
            // case AMGL_BGRA:
            // case AMGL_BGR_INTEGER:
            // case AMGL_BGRA_INTEGER:
            // case AMGL_STENCIL_INDEX:
            // case AMGL_DEPTH_COMPONENT:
            // case AMGL_DEPTH_STENCIL:
            // case AMGL_SRGB:
            // case AMGL_SRGB_ALPHA:
            // case AMGL_DEPTH_COMPONENT16:
            // case AMGL_DEPTH_COMPONENT24:
            // case AMGL_DEPTH_COMPONENT32:
            // case AMGL_R8:
            // case AMGL_R8_SNORM:
            // case AMGL_R16:
            // case AMGL_R16_SNORM:
            // case AMGL_RG8:
            // case AMGL_RG8_SNORM:
            // case AMGL_RG16:
            // case AMGL_RG16_SNORM:
            // case AMGL_R3_G3_B2:
            // case AMGL_RGB8:
            // case AMGL_RGB10:
            // case AMGL_RGB8_SNORM:
            // case AMGL_RGB16:
            // case AMGL_RGB16_SNORM:
            // case AMGL_RGBA2:
            // case AMGL_RGBA4:
            // case AMGL_RGB5_A1:
            // case AMGL_RGBA8:
            // case AMGL_RGBA8_SNORM:
            // case AMGL_RGB10_A2:
            // case AMGL_RGB10_A2UI:
            // case AMGL_RGBA12:
            // case AMGL_RGBA16:
            // case AMGL_SRGB8:
            // case AMGL_SRGB8_ALPHA8:
            // case AMGL_R16F:
            // case AMGL_RG16F:
            // case AMGL_RGB16F:
            // case AMGL_RGBA16F:
            // case AMGL_R32F:
            // case AMGL_RG32F:
            // case AMGL_RGB32F:
            // case AMGL_RGBA32F:
            // case AMGL_R11F_G11F_B10F:
            // case AMGL_R8I:
            // case AMGL_R8UI:
            // case AMGL_R16I:
            // case AMGL_R16UI:
            // case AMGL_R32I:
            // case AMGL_R32UI:
            // case AMGL_RG8I:
            // case AMGL_RG8UI:
            // case AMGL_RG16I:
            // case AMGL_RG16UI:
            // case AMGL_RG32I:
            // case AMGL_RG32UI:
            // case AMGL_RGB8I:
            // case AMGL_RGB8UI:
            // case AMGL_RGB16I:
            // case AMGL_RGB16UI:
            // case AMGL_RGB32I:
            // case AMGL_RGB32UI:
            // case AMGL_RGBA8I:
            // case AMGL_RGBA8UI:
            // case AMGL_RGBA16I:
            // case AMGL_RGBA16UI:
            // case AMGL_RGBA32I:
            // case AMGL_RGBA32UI:
        }
    }
}