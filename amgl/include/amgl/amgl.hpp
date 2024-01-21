#pragma once
#include <cstdint>

using byte_t = uint8_t;
using enum_t = uint16_t;


enum AMGLConstant : enum_t
{
    AMGL_NONE                               = 0,

    AMGL_NO_ERROR                           = 0,
    AMGL_INVALID_ENUM                       = 0x0500,
    AMGL_INVALID_VALUE                      = 0x0501,
    AMGL_INVALID_OPERATION                  = 0x0502,
    AMGL_STACK_OVERFLOW                     = 0x0503,
    AMGL_STACK_UNDERFLOW                    = 0x0504,
    AMGL_OUT_OF_MEMORY                      = 0x0505,
    AMGL_INVALID_FRAMEBUFFER_OPERATION      = 0x0506,

    AMGL_ARRAY_BUFFER                       = 0x8892,
    AMGL_ATOMIC_COUNTER_BUFFER              = 0x92C0,
    AMGL_COPY_READ_BUFFER                   = 0x8F36,
    AMGL_COPY_WRITE_BUFFER                  = 0x8F37,
    AMGL_DISPATCH_INDIRECT_BUFFER           = 0x90EE,
    AMGL_DRAW_INDIRECT_BUFFER               = 0x8F3F,
    AMGL_ELEMENT_ARRAY_BUFFER               = 0x8893,
    AMGL_PIXEL_PACK_BUFFER                  = 0x88EB,
    AMGL_PIXEL_UNPACK_BUFFER                = 0x88EC,
    AMGL_QUERY_BUFFER                       = 0x9192,
    AMGL_SHADER_STORAGE_BUFFER              = 0x90D2,
    AMGL_TEXTURE_BUFFER                     = 0x8C2A,
    AMGL_TRANSFORM_FEEDBACK_BUFFER          = 0x8C8E,
    AMGL_UNIFORM_BUFFER                     = 0x8A11,

    AMGL_STREAM_DRAW                        = 0x88E0,
    AMGL_STREAM_READ                        = 0x88E1,
    AMGL_STREAM_COPY                        = 0x88E2,
    AMGL_STATIC_DRAW                        = 0x88E4,
    AMGL_STATIC_READ                        = 0x88E5,
    AMGL_STATIC_COPY                        = 0x88E6,
    AMGL_DYNAMIC_DRAW                       = 0x88E8,
    AMGL_DYNAMIC_READ                       = 0x88E9,
    AMGL_DYNAMIC_COPY                       = 0x88EA,

    AMGL_READ_ONLY                          = 0x88B8,
    AMGL_WRITE_ONLY                         = 0x88B9,
    AMGL_READ_WRITE                         = 0x88BA,

    AMGL_VERTEX_ARRAY_BINDING               = 0x85B5,
};


using debugproc = void (*)(enum_t source, enum_t type, uint32_t id, enum_t severity, size_t length,
    const char* message, const void* user_param);


//
//  Buffer Objects
//

void amglBindBuffer(enum_t target, uint32_t buffer) noexcept;

void amglBindBufferBase(enum_t target, uint32_t index, uint32_t buffer) noexcept;
void amglBindBuffersBase(enum_t target, uint32_t first, size_t count, const uint32_t* buffers) noexcept;

void amglBindBufferRange(enum_t target, uint32_t index, uint32_t buffer, size_t offset, size_t size) noexcept;
void amglBindBuffersRange(enum_t target, uint32_t first, size_t count, const uint32_t *buffers, const size_t *offsets, const size_t *sizes) noexcept;

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

bool amglIsBuffer(uint32_t buffer) noexcept;

void* amglMapBuffer(enum_t target, enum_t access) noexcept;
void* amglMapNamedBuffer(uint32_t buffer, enum_t access) noexcept;
void amglUnmapBuffer(enum_t target) noexcept;
void amglUnmapNamedBuffer(uint32_t buffer) noexcept;

void amglVertexAttribPointer(uint32_t index, size_t size, enum_t type, bool normalized, size_t stride, const void* pointer) noexcept;
void amglVertexAttribIPointer(uint32_t index, size_t size, enum_t type, size_t stride, const void* pointer) noexcept;
void amglVertexAttribLPointer(uint32_t index, size_t size, enum_t type, size_t stride, const void* pointer) noexcept;


//
//  Vertex Array Objects
//

void amglBindVertexArray(uint32_t array) noexcept;
void amglDeleteVertexArrays(size_t n, const uint32_t* arrays) noexcept;
void amglGenVertexArrays(size_t n, uint32_t* arrays) noexcept;
bool amglIsVertexArray(uint32_t array) noexcept;


//
//  State Management
//

enum_t amglGetError() noexcept;