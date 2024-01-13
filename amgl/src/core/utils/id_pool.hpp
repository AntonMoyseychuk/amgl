#pragma once
#include <cstdint>
#include <unordered_set>

namespace amgl
{
    class id_pool
    {
    public:
        static inline constexpr bool is_default_id(uint32_t id) noexcept { return id == DEFAULT_ID; }

    public:
        uint32_t generate_id() noexcept;
        void free_id(uint32_t id) noexcept;

        bool is_busy(uint32_t id) const noexcept;
        bool is_full() const noexcept;

    private:
        static constexpr uint32_t DEFAULT_ID = UINT32_MAX;

    private:
        std::unordered_set<uint32_t> m_freed_ids;
        uint32_t m_max_provided_id = 0u;
    };

    // User has IDs in range [1, UINT32_MAX], but id_pool stores IDs in range [0, UINT32_MAX - 1]
    inline constexpr uint32_t conv_internal_to_user_range(uint32_t id) noexcept { return id + 1; }
    inline constexpr uint32_t conv_user_to_inernal_range(uint32_t id) noexcept { return id - 1; }
}