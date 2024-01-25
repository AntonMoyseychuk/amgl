#include "amgl/amgl.hpp"

#include "buffer_mng.hpp"


static amgl::buffer_mng& gs_buffer_mng = amgl::buffer_mng::instance();


void amglBindBuffer(enum_t target, uint32_t buffer) noexcept
{
    gs_buffer_mng.bind_buffer(target, buffer);
}


void amglBindBufferBase(enum_t target, uint32_t index, uint32_t buffer) noexcept
{
    gs_buffer_mng.bind_buffer_base(target, index, buffer);
}


void amglBindBuffersBase(enum_t target, uint32_t first, size_t count, const uint32_t* buffers) noexcept
{
    gs_buffer_mng.bind_buffers_base(target, first, count, buffers);
}


void amglBindBufferRange(enum_t target, uint32_t index, uint32_t buffer, size_t offset, size_t size) noexcept
{
    gs_buffer_mng.bind_buffer_range(target, index, buffer, &offset, &size);
}


void amglBindBuffersRange(enum_t target, uint32_t first, size_t count, const uint32_t *buffers, const size_t *offsets, const size_t *sizes) noexcept
{
    gs_buffer_mng.bind_buffers_range(target, first, count, buffers, offsets, sizes);
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
    gs_buffer_mng.get_buffer_sub_data(target, offset, size, data);
}


void amglGetNamedBufferSubData(uint32_t buffer, size_t offset, size_t size, void* data) noexcept
{
    gs_buffer_mng.get_named_buffer_sub_data(buffer, offset, size, data);
}


void amglInvalidateBufferData(uint32_t buffer) noexcept
{
    gs_buffer_mng.invalidate_buffer_data(buffer);
}


bool amglIsBuffer(uint32_t buffer) noexcept
{
    return gs_buffer_mng.is_buffer(buffer);
}


void* amglMapBuffer(enum_t target, enum_t access) noexcept
{
    return gs_buffer_mng.map_buffer(target, access);
}


void* amglMapNamedBuffer(uint32_t buffer, enum_t access) noexcept
{
    return gs_buffer_mng.map_named_buffer(buffer, access);
}


void amglUnmapBuffer(enum_t target) noexcept
{
    gs_buffer_mng.unmap_buffer(target);
}


void amglUnmapNamedBuffer(uint32_t buffer) noexcept
{
    gs_buffer_mng.unmap_named_buffer(buffer);
}


void amglVertexAttribPointer(uint32_t index, size_t size, enum_t type, bool normalized, size_t stride, const void* pointer) noexcept
{
    gs_buffer_mng.vertex_attrib_pointer(index, size, type, normalized, stride, pointer);
}


void amglVertexAttribIPointer(uint32_t index, size_t size, enum_t type, size_t stride, const void* pointer) noexcept
{
    gs_buffer_mng.vertex_attrib_I_pointer(index, size, type, stride, pointer);
}


void amglVertexAttribLPointer(uint32_t index, size_t size, enum_t type, size_t stride, const void* pointer) noexcept
{
    gs_buffer_mng.vertex_attrib_L_pointer(index, size, type, stride, pointer);
}


void amglBindVertexArray(uint32_t array) noexcept
{
    gs_buffer_mng.bind_vertex_array(array);
}


void amglDeleteVertexArrays(size_t n, const uint32_t* arrays) noexcept
{
    gs_buffer_mng.delete_vertex_arrays(n, arrays);
}


void amglGenVertexArrays(size_t n, uint32_t* arrays) noexcept
{
    gs_buffer_mng.gen_vertex_arrays(n, arrays);
}


bool amglIsVertexArray(uint32_t array) noexcept
{
    return gs_buffer_mng.is_vertex_array(array);
}