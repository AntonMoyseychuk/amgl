#pragma once
#include <cstdint>

using byte_t = uint8_t;
using enum_t = uint16_t;

enum AMGLConstant : enum_t
{

};

//
//  Buffer Objects
//
void amglBindBuffer(enum_t target, uint32_t buffer) noexcept;