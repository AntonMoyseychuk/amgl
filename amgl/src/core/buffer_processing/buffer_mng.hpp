#pragma once
#include "buffers.hpp"
#include "vertex_arrays.hpp"

namespace amgl
{
    class buffer_mng
    {
    public:
        static buffer_mng& instance() noexcept
        {
            #ifdef AMGL_CFG_PREALLOCATION_SIZE
                static buffer_mng manager(AMGL_CFG_PREALLOCATION_SIZE);
            #else
                static buffer_mng manager;
            #endif
            return manager;
        }

        buffer_mng(const buffer_mng&) = delete;
        buffer_mng& operator=(const buffer_mng&) = delete;

    private:
        buffer_mng() = default;
        buffer_mng(size_t preallocation_size);

    private:
        buffers m_buffers;
        vertex_arrays m_vertex_arrays;
    };
}