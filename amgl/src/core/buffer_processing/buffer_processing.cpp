#include "amgl/amgl.hpp"

#include "buffer_mng.hpp"


static amgl::buffer_mng& gs_buffer_mng = amgl::buffer_mng::instance();


void amglBindBuffer(enum_t target, uint32_t buffer) noexcept
{
    gs_buffer_mng.bind_buffer(target, buffer);
}


void amglBufferData(enum_t target, size_t size, const void *data, enum_t usage) noexcept
{
    gs_buffer_mng.buffer_data(target, size, data, usage);
}


void amglNamedBufferData(uint32_t buffer, size_t size, const void* data, enum_t usage) noexcept
{
    gs_buffer_mng.named_buffer_data(buffer, size, data, usage);
}


void amglBufferSubData(enum_t target, size_t offset, size_t size, const void* data) noexcept
{
    gs_buffer_mng.buffer_sub_data(target, offset, size, data);
}


void amglNamedBufferSubData(uint32_t buffer, size_t offset, size_t size, const void* data) noexcept
{
    gs_buffer_mng.named_buffer_sub_data(buffer, offset, offset, data);
}


void amglCopyBufferSubData(enum_t read_target, enum_t write_target, size_t read_offset, size_t write_offset, size_t size) noexcept
{
    gs_buffer_mng.copy_buffer_sub_data(read_target, write_target, read_offset, write_offset, size);
}


void amglCopyNamedBufferSubData(uint32_t read_buffer, uint32_t write_buffer, size_t read_offset, size_t write_offset, size_t size) noexcept
{
    gs_buffer_mng.copy_named_buffer_sub_data(read_buffer, write_buffer, read_offset, write_offset, size);
}


void amglDeleteBuffers(uint32_t n, const uint32_t* buffers) noexcept
{
    gs_buffer_mng.delete_buffers(n, buffers);
}


void amglEnableVertexAttribArray(uint32_t index) noexcept
{
    gs_buffer_mng.set_vertex_attrib_array_state(index, true);
}


void amglEnableVertexArrayAttrib(uint32_t vaobj, uint32_t index) noexcept
{
    gs_buffer_mng.set_vertex_array_attrib_state(vaobj, index, true);
}


void amglDisableVertexAttribArray(uint32_t index) noexcept
{
    gs_buffer_mng.set_vertex_attrib_array_state(index, false);
}


void amglDisableVertexArrayAttrib(uint32_t vaobj, uint32_t index) noexcept
{
    gs_buffer_mng.set_vertex_array_attrib_state(vaobj, index, false);
}


void amglGenBuffers(uint32_t n, uint32_t* buffers) noexcept
{
    gs_buffer_mng.gen_buffers(n, buffers);
}


void amglGetBufferSubData(enum_t target, size_t offset, size_t size, void* data) noexcept
{
    
}


void amglGetNamedBufferSubData(uint32_t buffer, size_t offset, size_t size, void* data) noexcept
{
    
}


void amglInvalidateBufferData(uint32_t buffer) noexcept
{
    
}


void amglInvalidateBufferSubData(uint32_t buffer, size_t offset, size_t length) noexcept
{
    
}


bool amglIsBuffer(uint32_t buffer) noexcept
{
    return gs_buffer_mng.is_buffer(buffer);
}


void* amglMapNamedBuffer(uint32_t buffer, enum_t access) noexcept
{
    return nullptr;
}


void* amglMapBuffer(enum_t target, enum_t access) noexcept
{
    return nullptr;
}


void amglUnmapBuffer(enum_t target) noexcept
{
    
}


void amglUnmapNamedBuffer(uint32_t buffer) noexcept
{
    
}


void amglVertexAttribPointer(uint32_t index, size_t size, enum_t type, bool normalized, size_t stride, const void* pointer) noexcept
{
    
}


void amglVertexAttribIPointer(uint32_t index, size_t size, enum_t type, size_t stride, const void* pointer) noexcept
{
    
}


void amglVertexAttribLPointer(uint32_t index, size_t size, enum_t type, size_t stride, const void* pointer) noexcept
{
    
}