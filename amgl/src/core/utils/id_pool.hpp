#pragma once
#include <cstdint>
#include <unordered_set>

namespace amgl
{
    class id_pool
    {
    public:
        uint32_t generate_id() noexcept;
        void free_id(uint32_t id) noexcept;

        bool is_busy(uint32_t id) const noexcept;
        bool is_full() const noexcept;

    private:
        std::unordered_set<uint32_t> m_freed_ids;
        uint32_t m_max_provided_id = 0u;
    };
}