#pragma once
#include "core/math/common.hpp"

namespace amgl
{
    namespace detail
    {   
        inline constexpr bool are_memory_regions_overlap(const void* region0, size_t size0, const void* region1, size_t size1) noexcept
        {
            return math::is_in_range(uintptr_t(region0), uintptr_t(region1), uintptr_t(region1) + size1) ||
                math::is_in_range(uintptr_t(region1), uintptr_t(region0), uintptr_t(region0) + size0);
        }
    }
}