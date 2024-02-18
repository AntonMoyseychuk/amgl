#pragma once
#include "amgl/amgl.hpp"
#include "core/utils/id_pool.hpp"

#include <vector>


namespace amgl
{
    class textures
    {
        friend class texture_mng;

    public:
        using memory_block = std::vector<uint8_t>;

    public:
        textures() = default;
        textures(size_t size);

        /// @brief 
        /// @return Texture object in the kernel range [0, UINT32_MAX - 1]
        uint32_t create_texture() noexcept;

        /// @brief 
        /// @param id Texture object in the kernel range [0, UINT32_MAX - 1]
        void free_texture(uint32_t id) noexcept;
        
        /// @brief 
        /// @param id Texture object in the kernel range [0, UINT32_MAX - 1]
        bool is_texture_exist(uint32_t id) const noexcept;

        /// @param id Texture object in the kernel range [0, UINT32_MAX - 1]
        /// @param target Texture object target
        /// @param width Texture width
        /// @param height Texture height
        /// @param depth Texture depth
        /// @param internal_format Texture object internal format
        /// @note Doesn't check params validity
        void set(uint32_t id, enum_t target, uint32_t width, uint32_t height, uint32_t depth, enum_t internal_format) noexcept;


    private:
        void resize(size_t size) noexcept;

    private:
        std::vector<memory_block> m_memory_blocks;
        std::vector<uint32_t> m_widths;
        std::vector<uint32_t> m_heights;
        std::vector<uint32_t> m_depths;
        std::vector<enum_t> m_internal_formats;
        
        // Textures cannot be attached to another target if they have already been attached before. 
        // Therefore, we need to keep their original targets
        std::vector<enum_t> m_targets;

        id_pool m_id_pool;
    };
}