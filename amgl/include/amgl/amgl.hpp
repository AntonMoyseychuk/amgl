#pragma once
#include <cstdint>

using byte_t = uint8_t;
using enum_t = uint16_t;


enum AMGLConstant : enum_t
{
    AMGL_NO_ERROR                           = 0,
    AMGL_INVALID_ENUM                       = 0x0500,
    AMGL_INVALID_VALUE                      = 0x0501,
    AMGL_INVALID_OPERATION                  = 0x0502,
    AMGL_STACK_OVERFLOW                     = 0x0503,
    AMGL_STACK_UNDERFLOW                    = 0x0504,
    AMGL_OUT_OF_MEMORY                      = 0x0505,
    AMGL_INVALID_FRAMEBUFFER_OPERATION      = 0x0506,
};


using debugproc = void (*)(enum_t source, enum_t type, uint32_t id, enum_t severity, size_t length,
    const char* message, const void* user_param);


//
//  Buffer Objects
//

void amglBindBuffer(enum_t target, uint32_t buffer) noexcept;

void amglBufferData(enum_t target, size_t size, const void* data, enum_t usage) noexcept;
void amglNamedBufferData(uint32_t buffer, size_t size, const void* data, enum_t usage) noexcept;
void amglBufferSubData(enum_t target, size_t offset, size_t size, const void* data) noexcept;
void amglNamedBufferSubData(uint32_t buffer, size_t offset, size_t size, const void* data) noexcept;

void amglCopyBufferSubData(enum_t read_target, enum_t write_target, size_t read_offset, size_t write_offset, size_t size) noexcept;
void amglCopyNamedBufferSubData(uint32_t read_buffer, uint32_t write_buffer, size_t read_offset, size_t write_offset, size_t size) noexcept;

void amglDeleteBuffers(uint32_t n, const uint32_t* buffers) noexcept;

void amglEnableVertexAttribArray(uint32_t index) noexcept;
void amglEnableVertexArrayAttrib(uint32_t vaobj, uint32_t index) noexcept;

void amglDisableVertexAttribArray(uint32_t index) noexcept;
void amglDisableVertexArrayAttrib(uint32_t vaobj, uint32_t index) noexcept;

void amglGenBuffers(uint32_t n, uint32_t* buffers) noexcept;

void amglGetBufferSubData(enum_t target, size_t offset, size_t size, void* data) noexcept;
void amglGetNamedBufferSubData(uint32_t buffer, size_t offset, size_t size, void* data) noexcept;

void amglInvalidateBufferData(uint32_t buffer) noexcept;
void amglInvalidateBufferSubData(uint32_t buffer, size_t offset, size_t length) noexcept;

bool amglIsBuffer(uint32_t buffer) noexcept;

void* amglMapNamedBuffer(uint32_t buffer, enum_t access) noexcept;
void* amglMapBuffer(enum_t target, enum_t access) noexcept;

void amglUnmapBuffer(enum_t target) noexcept;
void amglUnmapNamedBuffer(uint32_t buffer) noexcept;

void amglVertexAttribPointer(uint32_t index, size_t size, enum_t type, bool normalized, size_t stride, const void* pointer) noexcept;
void amglVertexAttribIPointer(uint32_t index, size_t size, enum_t type, size_t stride, const void* pointer) noexcept;
void amglVertexAttribLPointer(uint32_t index, size_t size, enum_t type, size_t stride, const void* pointer) noexcept;


//
//  State Management
//

enum_t amglGetError() noexcept;