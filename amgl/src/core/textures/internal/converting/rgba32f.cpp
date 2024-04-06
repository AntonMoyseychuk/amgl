#include "pch.hpp"
#include "rgba32f.hpp"

#include "fmt_convert.hpp"


namespace amgl
{
    namespace detail
    {
        void* get_rgba32f_convert_function(enum_t format, enum_t type) noexcept
        {
            if (format == AMGL_RGBA && type == AMGL_FLOAT) {
                return (void*)(fmt_bit_copy<fmt_rgba32f>);
            }

            switch(format) {
                case AMGL_RED:  return get_format_convert_function<fmt_rgba32f, AMGL_RED>(type);
                case AMGL_RG:   return get_format_convert_function<fmt_rgba32f, AMGL_RG>(type);
                case AMGL_RGB:  return get_format_convert_function<fmt_rgba32f, AMGL_RGB>(type);
                case AMGL_RGBA: return get_format_convert_function<fmt_rgba32f, AMGL_RGBA>(type);
            };

            return nullptr;
        }
    }
}