#pragma once
#include "amgl/amgl.hpp"

#include <cstdint>


namespace amgl
{
    #define TEXTURE_PACKED_TYPES                                                        \
        AMGL_UNSIGNED_BYTE_3_3_2,                                                       \
        AMGL_UNSIGNED_BYTE_2_3_3_REV,                                                   \
        AMGL_UNSIGNED_SHORT_5_6_5,                                                      \
        AMGL_UNSIGNED_SHORT_5_6_5_REV,                                                  \
        AMGL_UNSIGNED_SHORT_4_4_4_4,                                                    \
        AMGL_UNSIGNED_SHORT_4_4_4_4_REV,                                                \
        AMGL_UNSIGNED_SHORT_5_5_5_1,                                                    \
        AMGL_UNSIGNED_SHORT_1_5_5_5_REV,                                                \
        AMGL_UNSIGNED_INT_8_8_8_8,                                                      \
        AMGL_UNSIGNED_INT_8_8_8_8_REV,                                                  \
        AMGL_UNSIGNED_INT_10_10_10_2,                                                   \
        AMGL_UNSIGNED_INT_2_10_10_10_REV

    #define TEXTURE_PRIMITIVE_TYPES                                                     \
        AMGL_UNSIGNED_BYTE,                                                             \
        AMGL_BYTE,                                                                      \
        AMGL_UNSIGNED_SHORT,                                                            \
        AMGL_SHORT,                                                                     \
        AMGL_UNSIGNED_INT,                                                              \
        AMGL_INT,                                                                       \
        AMGL_FLOAT

    #define TEXTURE_TYPES                                                               \
        TEXTURE_PACKED_TYPES, TEXTURE_PRIMITIVE_TYPES


    /// @brief 
    /// @return Size in bytes or 0 if 'type' is invalid
    inline constexpr size_t get_type_size(enum_t type) noexcept
    {
        switch (type) {
            case AMGL_BYTE:
            case AMGL_UNSIGNED_BYTE:
            case AMGL_UNSIGNED_BYTE_3_3_2:
            case AMGL_UNSIGNED_BYTE_2_3_3_REV:
                return 1u;

            case AMGL_SHORT:
            case AMGL_UNSIGNED_SHORT:
            case AMGL_UNSIGNED_SHORT_5_6_5:
            case AMGL_UNSIGNED_SHORT_5_6_5_REV:
            case AMGL_UNSIGNED_SHORT_4_4_4_4:
            case AMGL_UNSIGNED_SHORT_4_4_4_4_REV:
            case AMGL_UNSIGNED_SHORT_5_5_5_1:
            case AMGL_UNSIGNED_SHORT_1_5_5_5_REV:
                return 2u;

            case AMGL_INT:
            case AMGL_UNSIGNED_INT:
            case AMGL_FLOAT:
            case AMGL_UNSIGNED_INT_10_10_10_2:
            case AMGL_UNSIGNED_INT_2_10_10_10_REV:
            case AMGL_UNSIGNED_INT_8_8_8_8:
            case AMGL_UNSIGNED_INT_8_8_8_8_REV:
                return 4u;

            case AMGL_DOUBLE:
                return 8u;
        }

        return 0u;
    }
}