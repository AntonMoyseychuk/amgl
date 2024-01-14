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

    namespace detail 
    {
        // Converts id from internal [0, UINT32_MAX - 1] to user [1, UINT32_MAX] range
        inline constexpr uint32_t conv_internal_to_user_range(uint32_t id) noexcept { return id + 1; }
        // Converts id from user [1, UINT32_MAX] to internal [0, UINT32_MAX - 1] range
        inline constexpr uint32_t conv_user_to_inernal_range(uint32_t id) noexcept { return id - 1; }
        
        inline constexpr bool is_default_id_user_range(uint32_t id) noexcept { return id == 0; }
        inline constexpr bool is_default_id_internal_range(uint32_t id) noexcept { return id == UINT32_MAX; }
    }
}