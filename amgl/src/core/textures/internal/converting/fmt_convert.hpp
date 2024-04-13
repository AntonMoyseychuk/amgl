#pragma once
#include "amgl/amgl.hpp"

namespace amgl
{
    namespace detail
    {
        template <typename fmt>
        inline void fmt_bit_copy(void* dst, const void* src, size_t pixel_count) noexcept
        {
            const size_t size = pixel_count * sizeof(fmt);
            memcpy_s(dst, size, src, size);
        }

        template <typename internal_fmt, typename external_fmt>
        inline void convert_integer(void* dst, const void* src, size_t pixel_count) noexcept
        {
            using namespace detail;
            using IN_T = typename external_fmt::implicit_type;
            using OUT_T = typename internal_fmt::implicit_type;

            constexpr size_t components = math::min(internal_fmt::COMPONENTS_COUNT, external_fmt::COMPONENTS_COUNT);

            internal_fmt* _dst = static_cast<internal_fmt*>(dst);
            const external_fmt* _src = static_cast<const external_fmt*>(src);

            const internal_fmt& internal_min = fmt_min_max_default<internal_fmt>::min;
            const internal_fmt& internal_max = fmt_min_max_default<internal_fmt>::max;
            const internal_fmt& internal_def = fmt_min_max_default<internal_fmt>::def;

            const external_fmt& external_min = fmt_min_max_default<external_fmt>::min;
            const external_fmt& external_max = fmt_min_max_default<external_fmt>::max;
            
            if (internal_fmt::COMPONENTS_COUNT != external_fmt::COMPONENTS_COUNT) {
                std::fill_n(_dst, pixel_count, internal_def);
            }

            for (size_t pixel = 0; pixel < pixel_count; ++pixel) {
                for (size_t component = 0; component < components; ++component) {
                    const IN_T in_min = external_min.get(component);
                    const IN_T in_max = external_max.get(component);
                    const OUT_T out_min = internal_min.get(component);
                    const OUT_T out_max = internal_max.get(component);

                    (_dst + pixel)->set(component, map<IN_T, OUT_T>(out_min, out_max, in_min, in_max, (_src + pixel)->get(component)));
                } 
            }
        }

        template <typename internal_fmt, typename external_fmt>
        inline void convert_real(void* dst, const void* src, size_t pixel_count) noexcept
        {
            using namespace detail;

            constexpr size_t components = math::min(internal_fmt::COMPONENTS_COUNT, external_fmt::COMPONENTS_COUNT);

            internal_fmt* _dst = static_cast<internal_fmt*>(dst);
            const external_fmt* _src = static_cast<const external_fmt*>(src);

            const internal_fmt& internal_min = fmt_min_max_default<internal_fmt>::min;
            const internal_fmt& internal_max = fmt_min_max_default<internal_fmt>::max;
            const internal_fmt& internal_def = fmt_min_max_default<internal_fmt>::def;
            
            if (internal_fmt::COMPONENTS_COUNT != external_fmt::COMPONENTS_COUNT) {
                std::fill_n(_dst, pixel_count, internal_def);
            }

            for (size_t pixel = 0; pixel < pixel_count; ++pixel) {
                for (size_t component = 0; component < components; ++component) {
                    const auto value = (_src + pixel)->get(component);
                    const float t = math::clamp(0.0f, 1.0f, *reinterpret_cast<const float*>(&value));

                    (_dst + pixel)->set(component, 
                        float_to_integer<typename internal_fmt::implicit_type>(internal_min.get(component), internal_max.get(component), t));
                } 
            }
        }


        template <typename internal_fmt, enum_t format>
        inline void* get_format_convert_function(enum_t type) noexcept
        {
            switch(type) {
                case AMGL_BYTE:             return (void*)(convert_integer<internal_fmt, fmt_from_enum_t<format, AMGL_BYTE>>);
                case AMGL_SHORT:            return (void*)(convert_integer<internal_fmt, fmt_from_enum_t<format, AMGL_SHORT>>);
                case AMGL_UNSIGNED_SHORT:   return (void*)(convert_integer<internal_fmt, fmt_from_enum_t<format, AMGL_UNSIGNED_SHORT>>);
                case AMGL_INT:              return (void*)(convert_integer<internal_fmt, fmt_from_enum_t<format, AMGL_INT>>);
                case AMGL_UNSIGNED_INT:     return (void*)(convert_integer<internal_fmt, fmt_from_enum_t<format, AMGL_UNSIGNED_INT>>);
                case AMGL_FLOAT:            return (void*)(convert_real<internal_fmt, fmt_from_enum_t<format, AMGL_FLOAT>>);
            };

            return nullptr;
        };
    }
}