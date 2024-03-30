#pragma once
#include <cstdint>

using ubyte_t = uint8_t;
using enum_t = uint16_t;


enum AMGLConstant : enum_t
{
    AMGL_NONE                               = 0,

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

    /*------------------- Errors -------------------*/

    AMGL_NO_ERROR                           = 0,
    AMGL_INVALID_ENUM                       = 0x0500,
    AMGL_INVALID_VALUE                      = 0x0501,
    AMGL_INVALID_OPERATION                  = 0x0502,
    AMGL_STACK_OVERFLOW                     = 0x0503,
    AMGL_STACK_UNDERFLOW                    = 0x0504,
    AMGL_OUT_OF_MEMORY                      = 0x0505,
    AMGL_INVALID_FRAMEBUFFER_OPERATION      = 0x0506,

    /*------------------- Buffer Targets -------------------*/

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

    /*------------------- Texture Targets -------------------*/

    AMGL_TEXTURE_1D                         = 0x0DE0,
    AMGL_PROXY_TEXTURE_1D                   = 0x8063,
    AMGL_TEXTURE_2D                         = 0x0DE1,
    AMGL_PROXY_TEXTURE_2D                   = 0x8064,
    AMGL_TEXTURE_3D                         = 0x806F,
    AMGL_PROXY_TEXTURE_3D                   = 0x8070,
    AMGL_TEXTURE_1D_ARRAY                   = 0x8C18,
    AMGL_PROXY_TEXTURE_1D_ARRAY             = 0x8C19,
    AMGL_TEXTURE_2D_ARRAY                   = 0x8C1A,
    AMGL_PROXY_TEXTURE_2D_ARRAY             = 0x8C1B,
    AMGL_TEXTURE_RECTANGLE                  = 0x84F5,
    AMGL_PROXY_TEXTURE_RECTANGLE            = 0x84F7,
    AMGL_TEXTURE_CUBE_MAP                   = 0x8513,
    AMGL_PROXY_TEXTURE_CUBE_MAP             = 0x851B,
    AMGL_TEXTURE_CUBE_MAP_ARRAY             = 0x9009,
    AMGL_PROXY_TEXTURE_CUBE_MAP_ARRAY       = 0x900B,
    AMGL_TEXTURE_2D_MULTISAMPLE             = 0x9100,
    AMGL_PROXY_TEXTURE_2D_MULTISAMPLE       = 0x9101,
    AMGL_TEXTURE_2D_MULTISAMPLE_ARRAY       = 0x9102,
    AMGL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY = 0x9103,

    /*------------------- Types -------------------*/

    AMGL_BYTE                               = 0x1400,
    AMGL_UNSIGNED_BYTE                      = 0x1401,
    AMGL_SHORT                              = 0x1402,
    AMGL_UNSIGNED_SHORT                     = 0x1403,
    AMGL_INT                                = 0x1404,
    AMGL_UNSIGNED_INT                       = 0x1405,
    AMGL_FLOAT                              = 0x1406,
    AMGL_DOUBLE                             = 0x140A,

    AMGL_INT_2_10_10_10_REV                 = 0x8D9F,
    AMGL_UNSIGNED_INT_10_10_10_2            = 0x8036,
    AMGL_UNSIGNED_INT_2_10_10_10_REV        = 0x8368,
    AMGL_UNSIGNED_BYTE_3_3_2                = 0x8032,
    AMGL_UNSIGNED_BYTE_2_3_3_REV            = 0x8362,
    AMGL_UNSIGNED_SHORT_5_6_5               = 0x8363,
    AMGL_UNSIGNED_SHORT_5_6_5_REV           = 0x8364,
    AMGL_UNSIGNED_SHORT_4_4_4_4             = 0x8033,
    AMGL_UNSIGNED_SHORT_4_4_4_4_REV         = 0x8365,
    AMGL_UNSIGNED_SHORT_5_5_5_1             = 0x8034,
    AMGL_UNSIGNED_SHORT_1_5_5_5_REV         = 0x8366,
    AMGL_UNSIGNED_INT_8_8_8_8               = 0x8035,
    AMGL_UNSIGNED_INT_8_8_8_8_REV           = 0x8367,

    /*------------------- Texture Formats (Internal too) -------------------*/

    AMGL_RED                                = 0x1903,
    AMGL_RG                                 = 0x8227,
    AMGL_RGB                                = 0x1907,
    AMGL_RGBA                               = 0x1908,
    AMGL_RED_INTEGER                        = 0x8D94,
    AMGL_RG_INTEGER                         = 0x8228,
    AMGL_RGB_INTEGER                        = 0x8D98,
    AMGL_RGBA_INTEGER                       = 0x8D99,
    AMGL_BGR                                = 0x80E0,
    AMGL_BGRA                               = 0x80E1,
    AMGL_BGR_INTEGER                        = 0x8D9A,
    AMGL_BGRA_INTEGER                       = 0x8D9B,
    AMGL_STENCIL_INDEX                      = 0x1901,
    AMGL_DEPTH_COMPONENT                    = 0x1902,
    AMGL_DEPTH_STENCIL                      = 0x84F9,
    
    AMGL_SRGB                               = 0x8C40,
    AMGL_SRGB_ALPHA                         = 0x8C42,

    AMGL_DEPTH_COMPONENT16                  = 0x81A5,
    AMGL_DEPTH_COMPONENT24                  = 0x81A6,
    AMGL_DEPTH_COMPONENT32                  = 0x81A7,
    // AMGL_STENCIL_INDEX1                     = 0x8D46,
    // AMGL_STENCIL_INDEX4                     = 0x8D47,
    // AMGL_STENCIL_INDEX8                     = 0x8D48,
    // AMGL_STENCIL_INDEX16                    = 0x8D49,
    AMGL_R8                                 = 0x8229,
    AMGL_R8_SNORM                           = 0x8F94,
    AMGL_R16                                = 0x822A,
    AMGL_R16_SNORM                          = 0x8F98,
    AMGL_RG8                                = 0x822B,
    AMGL_RG8_SNORM                          = 0x8F95,
    AMGL_RG16                               = 0x822C,
    AMGL_RG16_SNORM                         = 0x8F99,
    AMGL_R3_G3_B2                           = 0x2A10,
    AMGL_RGB8                               = 0x8051,
    AMGL_RGB10                              = 0x8052,
    AMGL_RGB8_SNORM                         = 0x8F96,
    AMGL_RGB16                              = 0x8054,
    AMGL_RGB16_SNORM                        = 0x8F9A,
    AMGL_RGBA2                              = 0x8055,
    AMGL_RGBA4                              = 0x8056,
    AMGL_RGB5_A1                            = 0x8057,
    AMGL_RGBA8                              = 0x8058,
    AMGL_RGBA8_SNORM                        = 0x8F97,
    AMGL_RGB10_A2                           = 0x8059,
    AMGL_RGB10_A2UI                         = 0x906F,
    AMGL_RGBA12                             = 0x805A,
    AMGL_RGBA16                             = 0x805B,
    AMGL_SRGB8                              = 0x8C41,
    AMGL_SRGB8_ALPHA8                       = 0x8C43,
    AMGL_R16F                               = 0x822D,
    AMGL_RG16F                              = 0x822F,
    AMGL_RGB16F                             = 0x881B,
    AMGL_RGBA16F                            = 0x881A,
    AMGL_R32F                               = 0x822E,
    AMGL_RG32F                              = 0x8230,
    AMGL_RGB32F                             = 0x8815,
    AMGL_RGBA32F                            = 0x8814,
    AMGL_R11F_G11F_B10F                     = 0x8C3A,
    AMGL_R8I                                = 0x8231,
    AMGL_R8UI                               = 0x8232,
    AMGL_R16I                               = 0x8233,
    AMGL_R16UI                              = 0x8234,
    AMGL_R32I                               = 0x8235,
    AMGL_R32UI                              = 0x8236,
    AMGL_RG8I                               = 0x8237,
    AMGL_RG8UI                              = 0x8238,
    AMGL_RG16I                              = 0x8239,
    AMGL_RG16UI                             = 0x823A,
    AMGL_RG32I                              = 0x823B,
    AMGL_RG32UI                             = 0x823C,
    AMGL_RGB8I                              = 0x8D8F,
    AMGL_RGB8UI                             = 0x8D7D,
    AMGL_RGB16I                             = 0x8D89,
    AMGL_RGB16UI                            = 0x8D77,
    AMGL_RGB32I                             = 0x8D83,
    AMGL_RGB32UI                            = 0x8D71,
    AMGL_RGBA8I                             = 0x8D8E,
    AMGL_RGBA8UI                            = 0x8D7C,
    AMGL_RGBA16I                            = 0x8D88,
    AMGL_RGBA16UI                           = 0x8D76,
    AMGL_RGBA32I                            = 0x8D82,
    AMGL_RGBA32UI                           = 0x8D70,

    AMGL_VERTEX_ARRAY_BINDING               = 0x85B5,
    AMGL_MAX_TEXTURE_SIZE                   = 0x0D33,
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
bool amglIsTexture(uint32_t texture);
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