#pragma once
#include "amgl/amgl.hpp"
#include "core/utils/id_pool.hpp"

#include <vector>


namespace amgl
{
    class images
    {
        friend class texture_mng;
    public:
        using memory_block = std::vector<uint8_t>;

    public:
        images() = default;
        images(size_t size);

        /// @brief 
        /// @return Image object in the kernel range [0, UINT32_MAX - 1]
        uint32_t create_image() noexcept;

        /// @brief 
        /// @param id Image object in the kernel range [0, UINT32_MAX - 1]
        void free_image(uint32_t id) noexcept;
        
        /// @brief 
        /// @param id Image object in the kernel range [0, UINT32_MAX - 1]
        bool is_image_exist(uint32_t id) const noexcept;

        /// @param id Image object in the kernel range [0, UINT32_MAX - 1]
        /// @param target Image object target
        /// @param width Image width
        /// @param height Image height
        /// @param depth Image depth
        /// @param internal_format Image object internal format
        /// @param format input data format
        /// @note Doesn't check params validity
        void set(uint32_t id, enum_t target, uint32_t width, uint32_t height, uint32_t depth, enum_t internal_format, enum_t format) noexcept;


    private:
        void resize(size_t size) noexcept;

    public:
        std::vector<memory_block> m_memory_blocks;
        std::vector<uint32_t> m_widths;
        std::vector<uint32_t> m_heights;
        std::vector<uint32_t> m_depths;
        std::vector<enum_t> m_internal_formats;
        
        // Needed for determine if we want to get image data as integers
        std::vector<enum_t> m_formats;
        
        // Images cannot be attached to another target if they have already been attached before. 
        // Therefore, we need to keep their original targets
        std::vector<enum_t> m_targets;

        id_pool m_id_pool;
    };
}