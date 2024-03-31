#include "pch.hpp"

#include "primitive.hpp"
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

        template <typename in_fmt>
        static void rgba8ui_convert_integer(void* dst, const void* src, size_t pixel_count) noexcept
        {
            using namespace detail;

            fmt_rgba8ui* _dst = static_cast<fmt_rgba8ui*>(dst);
            const in_fmt* _src = static_cast<const in_fmt*>(src);

            std::fill_n(_dst, pixel_count, fmt_rgba8ui(0, 0, 0, 255));

            constexpr size_t components = math::min(fmt_rgba8ui::COMPONENTS_COUNT, in_fmt::COMPONENTS_COUNT);

            using T = typename in_fmt::imlicit_type;
            constexpr T in_min = std::numeric_limits<T>::lowest();
            constexpr T in_max = std::numeric_limits<T>::max();

            for (size_t pixel = 0; pixel < pixel_count; ++pixel) {
                for (size_t component = 0; component < components; ++component) {
                    (_dst + pixel)->set(component, 
                        map<T, uint8_t>((uint8_t)0, (uint8_t)255, in_min, in_max, (_src + pixel)->get(component)));
                } 
            }
        }

        template <typename in_fmt>
        static void rgba8ui_convert_real(void* dst, const void* src, size_t pixel_count) noexcept
        {
            using namespace detail;

            fmt_rgba8ui* _dst = static_cast<fmt_rgba8ui*>(dst);
            const in_fmt* _src = static_cast<const in_fmt*>(src);

            std::fill_n(_dst, pixel_count, fmt_rgba8ui(0, 0, 0, 255));

            constexpr size_t components = math::min(fmt_rgba8ui::COMPONENTS_COUNT, in_fmt::COMPONENTS_COUNT);

            for (size_t pixel = 0; pixel < pixel_count; ++pixel) {
                for (size_t component = 0; component < components; ++component) {
                    const auto value = (_src + pixel)->get(component);

                    (_dst + pixel)->set(component, float_to_integer<uint8_t>(math::clamp(0.0f, 1.0f, *reinterpret_cast<const float*>(&value))));
                } 
            }
        }


        template <enum_t format>
        void* get_rgba8ui_format_convert_function(enum_t type) noexcept
        {
            switch(type) {
                case AMGL_BYTE:             return (void*)(rgba8ui_convert_integer<fmt_from_enum_t<format, AMGL_BYTE>>);
                case AMGL_SHORT:            return (void*)(rgba8ui_convert_integer<fmt_from_enum_t<format, AMGL_SHORT>>);
                case AMGL_UNSIGNED_SHORT:   return (void*)(rgba8ui_convert_integer<fmt_from_enum_t<format, AMGL_UNSIGNED_SHORT>>);
                case AMGL_INT:              return (void*)(rgba8ui_convert_integer<fmt_from_enum_t<format, AMGL_INT>>);
                case AMGL_UNSIGNED_INT:     return (void*)(rgba8ui_convert_integer<fmt_from_enum_t<format, AMGL_UNSIGNED_INT>>);
                case AMGL_FLOAT:            return (void*)(rgba8ui_convert_real<fmt_from_enum_t<format, AMGL_FLOAT>>);
            };

            return nullptr;
        };


        void* get_rgba8ui_convert_function(enum_t format, enum_t type) noexcept
        {
            if (format == AMGL_RGBA && type == AMGL_UNSIGNED_BYTE) {
                return (void*)rgba8ui_convert_copy;
            }

            switch(format) {
                case AMGL_RED:  return get_rgba8ui_format_convert_function<AMGL_RED>(type);
                case AMGL_RG:   return get_rgba8ui_format_convert_function<AMGL_RG>(type);
                case AMGL_RGB:  return get_rgba8ui_format_convert_function<AMGL_RGB>(type);
                case AMGL_RGBA: return get_rgba8ui_format_convert_function<AMGL_RGBA>(type);
            };

            return nullptr;
        }
    }
}