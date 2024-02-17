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

        /// @brief 
        /// @param n Texture count
        /// @param textures Texture objects in the user range [1, UINT32_MAX]
        void delete_textures(size_t n, const uint32_t *textures) noexcept;

        /// @brief 
        /// @param target Texture target
        /// @param texture Texture object in the user range [1, UINT32_MAX]
        void bind_texture(enum_t target, uint32_t texture) noexcept;

        /// @brief 
        /// @param texture Texture object in the user range [1, UINT32_MAX]
        bool is_texture(uint32_t texture) noexcept;

        void tex_image_1d(enum_t target, uint32_t level, enum_t internal_format, size_t width, uint32_t border, 
            enum_t format, enum_t type, const void* data) noexcept;
        

    private:
        texture_mng() = default;
        texture_mng(size_t preallocation_size);

        /// @brief Allocates memory based on passed params
        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        /// @param internal_format Format of internal texture storage
        /// @param in_format Format of input data
        /// @param in_type Type of input data
        /// @param in_size Count of pixels
        /// @param data Input buffer
        /// @note Doesn't check 'texture', 'internal_format', 'in_format' and 'in_type' validity
        /// @note Copy 'data' in allocted buffer if it is not nullptr
        void initialize_memory(uint32_t texture, enum_t internal_format, enum_t in_format, enum_t in_type, size_t pixel_count, const void* data);

        void resize(size_t size) noexcept;

    private:
        textures m_textures;
    };
}