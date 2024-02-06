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

        // RETURNS: ID in the kernel range [0, UINT32_MAX - 1]
        uint32_t create_texture() noexcept;
        // NOTE: Takes 'id' in the kernel range [0, UINT32_MAX - 1]
        void free_texture(uint32_t id) noexcept;

        // NOTE: Takes 'id' in the kernel range [0, UINT32_MAX - 1]
        bool is_texture_exist(uint32_t id) const noexcept;


    private:
        void resize(size_t size) noexcept;

    private:
        struct tex_target
        {
            enum_t target = AMGL_NONE;
        };

        std::vector<memory_block> m_memory_blocks;
        std::vector<uint32_t> m_widths;
        std::vector<uint32_t> m_heights;
        std::vector<uint32_t> m_depths;
        
        // Textures cannot be attached to another target if they have already been attached before. 
        // Therefore, we need to keep their original targets
        std::vector<tex_target> m_targets;

        id_pool m_id_pool;
    };
}