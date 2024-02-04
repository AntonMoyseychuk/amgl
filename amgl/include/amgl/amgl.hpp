#pragma once
#include <cstdint>

using ubyte_t = uint8_t;
using enum_t = uint16_t;


enum AMGLConstant : enum_t
{
    AMGL_NONE                               = 0,

    AMGL_BYTE                               = 0x1400,
    AMGL_UNSIGNED_BYTE                      = 0x1401,
    AMGL_SHORT                              = 0x1402,
    AMGL_UNSIGNED_SHORT                     = 0x1403,
    AMGL_INT                                = 0x1404,
    AMGL_UNSIGNED_INT                       = 0x1405,
    AMGL_FLOAT                              = 0x1406,
    AMGL_DOUBLE                             = 0x140A,
    AMGL_INT_2_10_10_10_REV                 = 0x8D9F,
    AMGL_UNSIGNED_INT_2_10_10_10_REV          = 0x8368,
    AMGL_UNSIGNED_INT_10F_11F_11F_REV         = 0x8C3B,

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
//  Textures
//

void amglActiveTexture(enum_t texture);
void amglBindImageTexture(uint32_t unit, uint32_t texture, uint32_t level, bool layered, 
    uint32_t layer, enum_t access, enum_t format);
void amglBindImageTextures(uint32_t first, size_t count, const uint32_t* textures);
void amglBindTexture(enum_t target, uint32_t texture);
void amglBindTextures(uint32_t first, size_t count, const uint32_t* textures);
void amglClearTexImage(uint32_t texture, uint32_t level, enum_t format, enum_t type, const void* data);
void amglClearTexSubImage(uint32_t texture, uint32_t level, size_t xoffset, size_t yoffset, size_t zoffset, 
    size_t width, size_t height, size_t depth, enum_t format, enum_t type, const void* data);
void amglCopyImageSubData(uint32_t src_name, enum_t src_target, uint32_t src_level, 
    size_t src_x, size_t src_y, size_t src_z, uint32_t dst_name, enum_t dst_target, size_t dst_level, 
        size_t dst_x, size_t dst_y, size_t dst_z, size_t src_width, size_t src_height, size_t src_depth);
void amglCopyTexImage1D(enum_t target, uint32_t level, enum_t internal_format, size_t x, size_t y, 
    size_t width, uint32_t border);
void amglCopyTexImage2D(enum_t target, uint32_t level, enum_t internal_format, size_t x, size_t y, 
    size_t width, size_t height, uint32_t border);
void amglCopyTexSubImage1D(enum_t target, uint32_t level, size_t xoffset, size_t x, size_t y, size_t width);
void amglCopyTextureSubImage1D(uint32_t texture, uint32_t level, size_t xoffset, size_t x, size_t y, size_t width);
void amglCopyTexSubImage2D(enum_t target, uint32_t level, size_t xoffset, size_t yoffset, 
    size_t x, size_t y, size_t width, size_t height);
void amglCopyTextureSubImage2D(uint32_t texture, uint32_t level, size_t xoffset, size_t yoffset, 
    size_t x, size_t y, size_t width, size_t height);
void amglCopyTexSubImage3D(enum_t target, uint32_t level, size_t xoffset, size_t yoffset, size_t zoffset, 
    size_t x, size_t y, size_t width, size_t height);
void amglCopyTextureSubImage3D(uint32_t texture, uint32_t level, size_t xoffset, size_t yoffset, size_t zoffset, 
    size_t x, size_t y, size_t width, size_t height);
void amglDeleteTextures(size_t n, const uint32_t* textures);
void amglGenTextures(size_t n, uint32_t* textures);
void amglGenerateMipmap(enum_t target);
void amglGenerateTextureMipmap(uint32_t texture);
void amglGetTexImage(enum_t target, uint32_t level, enum_t format, enum_t type, void* pixels);
void amglGetnTexImage(enum_t target, uint32_t level, enum_t format, enum_t type, size_t bufSize, void* pixels);
void amglGetTextureImage(uint32_t texture, uint32_t level, enum_t format, enum_t type, size_t bufSize, void* pixels);
void amglGetTexLevelParameterfv(enum_t target, uint32_t level, enum_t pname, float* params);
void amglGetTexLevelParameteriv(enum_t target, uint32_t level, enum_t pname, int32_t* params);
void amglGetTextureLevelParameterfv(uint32_t texture, uint32_t level, enum_t pname, float* params);
void amglGetTextureLevelParameteriv(uint32_t texture, uint32_t level, enum_t pname, int32_t* params);
void amglGetTexParameterfv(enum_t target, enum_t pname, float* params);
void amglGetTexParameteriv(enum_t target, enum_t pname, int32_t* params);
void amglGetTexParameterIiv(enum_t target, enum_t pname, int32_t* params);
void amglGetTexParameterIuiv(enum_t target, enum_t pname, uint32_t* params);
void amglGetTextureParameterfv(uint32_t texture, enum_t pname, float* params);
void amglGetTextureParameteriv(uint32_t texture, enum_t pname, int32_t* params);
void amglGetTextureParameterIiv(uint32_t texture, enum_t pname, int32_t* params);
void amglGetTextureParameterIuiv(uint32_t texture, enum_t pname, uint32_t* params);
void amglGetTextureSubImage(uint32_t texture, uint32_t level, size_t xoffset, size_t yoffset, size_t zoffset, 
    size_t width, size_t height, size_t depth, enum_t format, enum_t type, size_t buf_size, void* pixels);
void amglInvalidateTexImage(uint32_t texture, uint32_t level);
void amglInvalidateTexSubImage(uint32_t texture, uint32_t level, size_t xoffset, size_t yoffset, size_t zoffset, 
    size_t width, size_t height, size_t depth);
void amglIsTexture(uint32_t texture);
void amglTexBuffer(enum_t target, enum_t internalFormat, uint32_t buffer);
void amglTextureBuffer(uint32_t texture, enum_t internal_format, uint32_t buffer);
void amglTexBufferRange(enum_t target, enum_t internal_format, uint32_t buffer, uintptr_t offset, size_t size);
void amglTextureBufferRange(uint32_t texture, enum_t internal_format, uint32_t buffer, uintptr_t offset, size_t size);
void amglTexImage1D(enum_t target, uint32_t level, enum_t internal_format, size_t width, uint32_t border, 
    enum_t format, enum_t type, const void* data);
void amglTexImage2D(enum_t target, uint32_t level, enum_t internal_format, size_t width, size_t height, 
    uint32_t border, enum_t format, enum_t type, const void* data);
void amglTexImage2DMultisample(enum_t target, size_t samples, enum_t internal_format, 
    size_t width, size_t height, bool fixed_sample_locations);
void amglTexImage3D(enum_t target, uint32_t level, enum_t internal_format, size_t width, size_t height, size_t depth, 
    uint32_t border, enum_t format, enum_t type, const void* data);
void amglTexImage3DMultisample(enum_t target, size_t samples, enum_t internal_format, 
    size_t width, size_t height, size_t depth, bool fixed_sample_locations);
void amglTexParameterf(enum_t target, enum_t pname, float param);
void amglTexParameteri(enum_t target, enum_t pname, int32_t param);
void amglTextureParameterf(uint32_t texture, enum_t pname, float param);
void amglTextureParameteri(uint32_t texture, enum_t pname, int32_t param);
void amglTexParameterfv(enum_t target, enum_t pname, const float* params);
void amglTexParameteriv(enum_t target, enum_t pname, const int32_t* params);
void amglTexParameterIiv(enum_t target, enum_t pname, const int32_t* params);
void amglTexParameterIuiv(enum_t target, enum_t pname, const uint32_t* params);
void amglTextureParameterfv(uint32_t texture, enum_t pname, const float* paramtexture);
void amglTextureParameteriv(uint32_t texture, enum_t pname, const int32_t* param);
void amglTextureParameterIiv(uint32_t texture, enum_t pname, const int32_t* params);
void amglTextureParameterIuiv(uint32_t texture, enum_t pname, const uint32_t* params);
void amglTexStorage1D(enum_t target, size_t levels, enum_t internal_format, size_t width);
void amglTextureStorage1D(uint32_t texture, size_t levels, enum_t internalformat, size_t width);
void amglTexStorage2D(enum_t target, size_t levels, enum_t internal_format, size_t width, size_t height);
void amglTextureStorage2D(uint32_t texture, size_t levels, enum_t internal_format, size_t width, size_t height);
void amglTexStorage2DMultisample(enum_t target, size_t samples, enum_t internal_format, 
    size_t width, size_t height, bool fixed_sample_locations);
void amglTextureStorage2DMultisample(uint32_t texture, size_t samples, enum_t internal_format, 
    size_t width, size_t height, bool fixed_sample_locations);
void amglTexStorage3D(enum_t target, size_t levels, enum_t internal_format, size_t width, size_t height, size_t depth);
void amglTextureStorage3D(uint32_t texture, size_t levels, enum_t internal_format, size_t width, size_t height, size_t depth);
void amglTexStorage3DMultisample(enum_t target, size_t samples, enum_t internal_format, 
    size_t width, size_t height, size_t depth, bool fixed_sample_locations);
void amglTextureStorage3DMultisample(uint32_t texture, size_t samples, enum_t internal_format, 
    size_t width, size_t height, size_t depth, bool fixed_sample_locations);
void amglTexSubImage1D(enum_t target, uint32_t level, size_t xoffset, size_t width, 
    enum_t format, enum_t type, const void* pixels);
void amglTextureSubImage1D(uint32_t texture, uint32_t level, size_t xoffset, size_t width, 
    enum_t format, enum_t type, const void* pixels);
void amglTexSubImage2D(enum_t target, uint32_t level, size_t xoffset, size_t yoffset, size_t width, size_t height, 
    enum_t format, enum_t type, const void* pixels);
void amglTextureSubImage2D(uint32_t texture, uint32_t level, size_t xoffset, size_t yoffset, size_t width, size_t height, 
    enum_t format, enum_t type, const void* pixels);
void amglTexSubImage3D(enum_t target, uint32_t level, size_t xoffset, size_t yoffset, size_t zoffset, 
    size_t width, size_t height, size_t depth, enum_t format, enum_t type, const void* pixels);
void amglTextureSubImage3D(uint32_t texture, uint32_t level, size_t xoffset, size_t yoffset, size_t zoffset, 
    size_t width, size_t height, size_t depth, enum_t format, enum_t type, const void* pixels);
void amglTextureView(uint32_t texture, enum_t target, uint32_t orig_texture, enum_t internal_format, 
    uint32_t min_level, uint32_t num_levels, uint32_t min_layer, uint32_t num_layers);


//
//  State Management
//

enum_t amglGetError() noexcept;