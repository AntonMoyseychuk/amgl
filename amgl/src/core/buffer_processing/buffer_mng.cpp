#include "pch.hpp"
#include "buffer_mng.hpp"

namespace amgl
{
    #ifdef AMGL_CFG_KEEP_MEMORY_ALLOCATED
        #define CLEAR_ASSOCIATED_MEMORY_BUFFER(id) m_buffers.invalidate_memory_block((id))
    #else
        #define CLEAR_ASSOCIATED_MEMORY_BUFFER(id) m_buffers.deallocate_memory_block((id))
    #endif

    buffer_mng::buffer_mng(size_t preallocation_size)
        : m_buffers(preallocation_size), m_vertex_arrays(preallocation_size)
    {
    }

    void buffer_mng::gen_buffers(uint32_t n, uint32_t *buffers) noexcept
    {
        RETURN_IF(!buffers);

        for (uint32_t i = 0u; i < n; ++i) {
            buffers[i] = m_buffers.create_id();
        }
    }
    
    void buffer_mng::delete_buffers(uint32_t n, const uint32_t *buffers) noexcept
    {
        RETURN_IF(!buffers);

        for (uint32_t i = 0u; i < n; ++i) {
            CLEAR_ASSOCIATED_MEMORY_BUFFER(buffers[i]);
            m_buffers.free_id(buffers[i]);
        }
    }
}