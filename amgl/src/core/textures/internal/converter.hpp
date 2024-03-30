#pragma once
#include "amgl/amgl.hpp"


namespace amgl
{
    class texture_data_converter
    {
        using converting_func_ptr = void (*)(void* dst, const void* src, size_t pixel_count);

    public:
        texture_data_converter(enum_t internal_format, enum_t format, enum_t type);

        void operator()(void* dst, const void* src, size_t pixel_count) const noexcept;
        
        bool is_valid() const noexcept { return convert != nullptr; }

    private:
        static converting_func_ptr get_converting_func(enum_t internal_format, enum_t format, enum_t type) noexcept;

    private:
        converting_func_ptr convert = nullptr;
    };
}