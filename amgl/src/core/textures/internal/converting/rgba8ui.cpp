#include "pch.hpp"
#include "rgba8ui.hpp"


namespace amgl
{
    namespace detail
    {
        static void rgba8ui_convert_copy(void* dst, const void* src, size_t pixel_count) noexcept
        {
            const size_t size = pixel_count * sizeof(fmt_rgba8ui);
            memcpy_s(dst, size, src, size);
        }


        void* get_rgba8ui_convert_function(enum_t format, enum_t type) noexcept
        {
            if (format == AMGL_RGBA && type == AMGL_UNSIGNED_BYTE) {
                return (void*)rgba8ui_convert_copy;
            }

            return nullptr;
        }
    }
}