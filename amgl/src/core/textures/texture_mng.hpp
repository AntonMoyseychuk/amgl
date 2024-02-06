#pragma once
#include "textures.hpp"


namespace amgl
{
    class texture_mng
    {
    public:
        static texture_mng& instance() noexcept
        {
            static texture_mng manager(AM_INIT_TEX_COUNT);
            return manager;
        }

        texture_mng(const texture_mng&) = delete;
        texture_mng& operator=(const texture_mng&) = delete;


        void gen_textures(size_t n, uint32_t *textures) noexcept;
        // Clears memory allocated for 'textures' and textures ids
        // NOTE: Takes 'textures' in the user range [1, UINT32_MAX]
        void delete_textures(size_t n, const uint32_t *textures) noexcept;

        // NOTE: Takes 'texture' in the user range [1, UINT32_MAX]
        void bind_texture(enum_t target, uint32_t texture) noexcept;
        

    private:
        texture_mng() = default;
        texture_mng(size_t preallocation_size);

        void resize(size_t size) noexcept;

    private:
        textures m_textures;
    };
}