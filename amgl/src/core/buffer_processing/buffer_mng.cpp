#include "pch.hpp"
#include "buffer_mng.hpp"

namespace amgl
{
    buffer_mng::buffer_mng(size_t preallocation_size)
        : m_buffers(preallocation_size), m_vertex_arrays(preallocation_size)
    {
    }
}