#pragma once
#include "amgl/amgl.hpp"
#include "core/utils/id_pool.hpp"

#include <vector>


namespace amgl
{
    class texture_descs
    {
        friend class texture_mng;
    public:
        texture_descs() = default;
        texture_descs(size_t size);

        /// @param image Image object in the kernel range [0, UINT32_MAX - 1]
        /// @param target Image object target
        /// @param internal_format Image object internal format
        /// @param interpret_as_integer Interpret data as integer or float when sampling
        /// @note Doesn't check params validity
        void set(uint32_t image, enum_t target, enum_t internal_format, bool interpret_as_integer) noexcept;

        /// @brief 
        /// @param image Image object in the kernel range [0, UINT32_MAX - 1]
        /// @note Doesn't check 'image' validity
        enum_t get_internal_format(uint32_t image) const noexcept { return m_internal_formats[image]; }

        /// @brief 
        /// @param image Image object in the kernel range [0, UINT32_MAX - 1]
        /// @note Doesn't check 'image' validity
        enum_t get_target(uint32_t image) const noexcept { return m_targets[image]; }

        /// @brief 
        /// @param image Image object in the kernel range [0, UINT32_MAX - 1]
        /// @note Doesn't check 'image' validity
        bool is_interpret_as_integer(uint32_t image) const noexcept { return m_are_integers[image]; }

    private:
        void resize(size_t size) noexcept;

    public:
        // Need to determine type when sampling
        std::vector<enum_t> m_internal_formats;
        
        // Images cannot be attached to another target if they have already been attached before. 
        // Therefore, we need to keep their original targets
        std::vector<enum_t> m_targets;

        std::vector<bool> m_are_integers;
    };


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
        /// @param image Image object in the kernel range [0, UINT32_MAX - 1]
        void free_image(uint32_t image) noexcept;
        
        /// @brief 
        /// @param image Image object in the kernel range [0, UINT32_MAX - 1]
        bool is_image_exist(uint32_t image) const noexcept;

        /// @param image Image object in the kernel range [0, UINT32_MAX - 1]
        /// @param width Image width
        /// @param height Image height
        /// @param depth Image depth
        /// @note Doesn't check params validity
        void set(uint32_t image, uint32_t width, uint32_t height, uint32_t depth) noexcept;

        /// @brief 
        /// @param image Image object in the kernel range [0, UINT32_MAX - 1]
        /// @note Doesn't check 'image' validity
        /// @return Image size in bytes
        size_t get_image_size(uint32_t image) const noexcept { return m_memory_blocks[image].size(); }

        /// @brief 
        /// @param image Image object in the kernel range [0, UINT32_MAX - 1]
        /// @note Doesn't check 'image' validity
        const ubyte_t* get_image_data(uint32_t image) const noexcept { return m_memory_blocks[image].data(); }

        /// @brief 
        /// @param image Image object in the kernel range [0, UINT32_MAX - 1]
        /// @note Doesn't check 'image' validity
        uint32_t get_image_width(uint32_t image) const noexcept { return m_widths[image]; }

        /// @brief 
        /// @param image Image object in the kernel range [0, UINT32_MAX - 1]
        /// @note Doesn't check 'image' validity
        uint32_t get_image_height(uint32_t image) const noexcept { return m_heights[image]; }

        /// @brief 
        /// @param image Image object in the kernel range [0, UINT32_MAX - 1]
        /// @note Doesn't check 'image' validity
        uint32_t get_image_depth(uint32_t image) const noexcept { return m_depths[image]; }

    private:
        void resize(size_t size) noexcept;

    public:
        std::vector<memory_block> m_memory_blocks;
        std::vector<uint32_t> m_widths;
        std::vector<uint32_t> m_heights;
        std::vector<uint32_t> m_depths;

        id_pool m_id_pool;
    };
}