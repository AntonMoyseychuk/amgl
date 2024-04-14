#include "pch.hpp"
#include "id_pool.hpp"

namespace amgl
{
    id_pool::id_pool(size_t capacity)
    {
        m_freed_ids.reserve(capacity);
        m_max_provided_id = 0u;
    }


    uint32_t id_pool::generate_id() noexcept
    {
        if (!m_freed_ids.empty()) {
            const uint32_t id = *m_freed_ids.cbegin();
            m_freed_ids.erase(id);
            return id;
        }

        return m_max_provided_id++;
    }


    void id_pool::free_id(uint32_t id) noexcept
    {
        if (is_busy(id)) {
            m_freed_ids.insert(id);
        }
    }

    
    void id_pool::reserve(size_t new_capacity) noexcept
    {
        m_freed_ids.reserve(new_capacity);
    }

    
    bool id_pool::is_busy(uint32_t id) const noexcept
    {
        return id < m_max_provided_id && m_freed_ids.find(id) == m_freed_ids.end();
    }
    

    bool id_pool::is_full() const noexcept
    {
        return m_max_provided_id == UINT32_MAX && m_freed_ids.empty();
    }
    
    
    size_t id_pool::get_busy_count() const noexcept
    {
        return m_max_provided_id - m_freed_ids.size();
    }
}