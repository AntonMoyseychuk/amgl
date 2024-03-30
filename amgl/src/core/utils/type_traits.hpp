#pragma once
#include <type_traits>

_STD_BEGIN

template<size_t bits>
using min_uint_t = std::conditional_t<bits <= 8u, uint8_t,
                        std::conditional_t<bits <= 16u, uint16_t,
                        std::conditional_t<bits <= 32u, uint32_t,
                        std::conditional_t<bits <= 64u, uint64_t,
                        void>>>>;

_STD_END
