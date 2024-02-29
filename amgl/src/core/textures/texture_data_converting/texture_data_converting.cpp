#include "pch.hpp"
#include "texture_data_converting.hpp"

#include "details/rgba8.hpp"
#include "details/rgba32f.hpp"

#include "core/core.hpp"

namespace amgl
{
    void texture_data_converter::operator()(enum_t internal_format, void *dst, enum_t format, enum_t type, const void *src) const noexcept
    {
        switch(internal_format) {
            case AMGL_RED:                  AM_NOT_IMPLEMENTED; break;
            case AMGL_RG:                   AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB:                  AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA:                 AM_NOT_IMPLEMENTED; break;
            case AMGL_RED_INTEGER:          AM_NOT_IMPLEMENTED; break;
            case AMGL_RG_INTEGER:           AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB_INTEGER:          AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA_INTEGER:         AM_NOT_IMPLEMENTED; break;
            case AMGL_BGR:                  AM_NOT_IMPLEMENTED; break;
            case AMGL_BGRA:                 AM_NOT_IMPLEMENTED; break;
            case AMGL_BGR_INTEGER:          AM_NOT_IMPLEMENTED; break;
            case AMGL_BGRA_INTEGER:         AM_NOT_IMPLEMENTED; break;
            case AMGL_STENCIL_INDEX:        AM_NOT_IMPLEMENTED; break;
            case AMGL_DEPTH_COMPONENT:      AM_NOT_IMPLEMENTED; break;
            case AMGL_DEPTH_STENCIL:        AM_NOT_IMPLEMENTED; break;
            case AMGL_SRGB:                 AM_NOT_IMPLEMENTED; break;
            case AMGL_SRGB_ALPHA:           AM_NOT_IMPLEMENTED; break;
            case AMGL_DEPTH_COMPONENT16:    AM_NOT_IMPLEMENTED; break;
            // case AMGL_DEPTH_COMPONENT24:    AM_NOT_IMPLEMENTED; break;
            case AMGL_DEPTH_COMPONENT32:    AM_NOT_IMPLEMENTED; break;
            case AMGL_R8:                   AM_NOT_IMPLEMENTED; break;
            case AMGL_R8_SNORM:             AM_NOT_IMPLEMENTED; break;
            case AMGL_R16:                  AM_NOT_IMPLEMENTED; break;
            case AMGL_R16_SNORM:            AM_NOT_IMPLEMENTED; break;
            case AMGL_RG8:                  AM_NOT_IMPLEMENTED; break;
            case AMGL_RG8_SNORM:            AM_NOT_IMPLEMENTED; break;
            case AMGL_RG16:                 AM_NOT_IMPLEMENTED; break;
            case AMGL_RG16_SNORM:           AM_NOT_IMPLEMENTED; break;
            case AMGL_R3_G3_B2:             AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB8:                 AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB10:                AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB8_SNORM:           AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB16:                AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB16_SNORM:          AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA2:                AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA4:                AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB5_A1:              AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA8:                AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA8_SNORM:          AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB10_A2:             AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB10_A2UI:           AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA12:               AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA16:               AM_NOT_IMPLEMENTED; break;
            case AMGL_SRGB8:                AM_NOT_IMPLEMENTED; break;
            case AMGL_SRGB8_ALPHA8:         AM_NOT_IMPLEMENTED; break;
            case AMGL_R16F:                 AM_NOT_IMPLEMENTED; break;
            case AMGL_RG16F:                AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB16F:               AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA16F:              AM_NOT_IMPLEMENTED; break;
            case AMGL_R32F:                 AM_NOT_IMPLEMENTED; break;
            case AMGL_RG32F:                AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB32F:               AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA32F:              AM_NOT_IMPLEMENTED; break;
            case AMGL_R11F_G11F_B10F:       AM_NOT_IMPLEMENTED; break;
            case AMGL_R8I:                  AM_NOT_IMPLEMENTED; break;
            case AMGL_R8UI:                 AM_NOT_IMPLEMENTED; break;
            case AMGL_R16I:                 AM_NOT_IMPLEMENTED; break;
            case AMGL_R16UI:                AM_NOT_IMPLEMENTED; break;
            case AMGL_R32I:                 AM_NOT_IMPLEMENTED; break;
            case AMGL_R32UI:                AM_NOT_IMPLEMENTED; break;
            case AMGL_RG8I:                 AM_NOT_IMPLEMENTED; break;
            case AMGL_RG8UI:                AM_NOT_IMPLEMENTED; break;
            case AMGL_RG16I:                AM_NOT_IMPLEMENTED; break;
            case AMGL_RG16UI:               AM_NOT_IMPLEMENTED; break;
            case AMGL_RG32I:                AM_NOT_IMPLEMENTED; break;
            case AMGL_RG32UI:               AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB8I:                AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB8UI:               AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB16I:               AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB16UI:              AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB32I:               AM_NOT_IMPLEMENTED; break;
            case AMGL_RGB32UI:              AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA8I:               AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA8UI:              AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA16I:              AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA16UI:             AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA32I:              AM_NOT_IMPLEMENTED; break;
            case AMGL_RGBA32UI:             AM_NOT_IMPLEMENTED; break;
        }
    }
}