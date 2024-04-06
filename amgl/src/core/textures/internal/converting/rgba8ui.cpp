#include "pch.hpp"
#include "rgba8ui.hpp"

#include "fmt_convert.hpp"


namespace amgl
{
    namespace detail
    {
        void* get_rgba8ui_convert_function(enum_t format, enum_t type) noexcept
        {
            if (format == AMGL_RGBA && type == AMGL_UNSIGNED_BYTE) {
                return (void*)(fmt_bit_copy<fmt_rgba8ui>);
            }

            switch(format) {
                case AMGL_RED:  return get_format_convert_function<fmt_rgba8ui, AMGL_RED>(type);
                case AMGL_RG:   return get_format_convert_function<fmt_rgba8ui, AMGL_RG>(type);
                case AMGL_RGB:  return get_format_convert_function<fmt_rgba8ui, AMGL_RGB>(type);
                case AMGL_RGBA: return get_format_convert_function<fmt_rgba8ui, AMGL_RGBA>(type);
            };

            return nullptr;
        }
    }
}