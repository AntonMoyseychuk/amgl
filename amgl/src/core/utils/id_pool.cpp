#include "pch.hpp"
#include "id_pool.hpp"

namespace amgl
{
    uint32_t id_pool::generate_id() noexcept
    {
        if (!m_freed_ids.empty()) {
            const uint32_t id = *m_freed_ids.cbegin();
            m_freed_ids.erase(id);
            return id;
        }

        AM_ASSERT_MSG(m_max_provided_id != DEFAULT_ID, "ID overflow");
        return m_max_provided_id++;
    }

    void id_pool::free_id(uint32_t id) noexcept
    {
        if (is_busy()) {
            m_freed_ids.insert(id);
        }
    }
    
    bool id_pool::is_busy(uint32_t id) const noexcept
    {
        return id < m_max_provided_id && m_freed_ids.find(id) == m_freed_ids.end();
    }
    
    bool id_pool::is_full() const noexcept
    {
        return m_max_provided_id == DEFAULT_ID && m_freed_ids.empty();
    }
}