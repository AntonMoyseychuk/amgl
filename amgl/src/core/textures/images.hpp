#pragma once
#include "amgl/amgl.hpp"
#include "core/utils/id_pool.hpp"

#include <vector>


namespace amgl
{
    struct images
    {
        images() = default;
        images(size_t size);

        /// @param width Image width
        /// @param height Image height
        /// @param depth Image depth
        /// @note Doesn't check params validity
        void set(uint32_t image, uint32_t width, uint32_t height, uint32_t depth) noexcept;

        void free_all() noexcept;
        void shrink_to_fit() noexcept;

        /// @brief 
        /// @note Doesn't check 'image' validity
        /// @return Image size in bytes
        size_t get_image_size(uint32_t image) const noexcept { return m_memory_blocks[image].size(); }

        /// @brief 
        /// @note Doesn't check 'image' validity
        const ubyte_t* get_image_data(uint32_t image) const noexcept { return m_memory_blocks[image].data(); }

        /// @brief 
        /// @note Doesn't check 'image' validity
        uint32_t get_image_width(uint32_t image) const noexcept { return m_widths[image]; }

        /// @brief 
        /// @note Doesn't check 'image' validity
        uint32_t get_image_height(uint32_t image) const noexcept { return m_heights[image]; }

        /// @brief 
        /// @note Doesn't check 'image' validity
        uint32_t get_image_depth(uint32_t image) const noexcept { return m_depths[image]; }

        void resize(size_t size) noexcept;

        size_t get_image_count() const noexcept { return m_memory_blocks.size(); }

    public:
        using memory_block = std::vector<uint8_t>;

        std::vector<memory_block> m_memory_blocks;
        std::vector<uint32_t> m_widths;
        std::vector<uint32_t> m_heights;
        std::vector<uint32_t> m_depths;
    };
}