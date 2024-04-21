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

        void tex_image_2d(enum_t target, uint32_t level, enum_t internal_format, size_t width, size_t height, uint32_t border, 
            enum_t format, enum_t type, const void* data) noexcept;
        
        void generate_mipmap(enum_t target) noexcept;
        /// @brief 
        /// @param texture Texture object in the user range [1, UINT32_MAX]
        void generate_texture_mipmap(uint32_t texture) noexcept;

    private:
        texture_mng() = default;
        texture_mng(size_t preallocation_size);

        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        /// @param level LOD
        /// @param format Format of input data
        /// @param type Type of input data
        /// @param pixel_count Count of pixels
        /// @param data Input data
        /// @note Doesn't check 'texture', 'level', 'internal_format', 'format' and 'type' validity
        void reallocate_tex_memory(uint32_t texture, uint32_t level, enum_t internal_format, enum_t format, enum_t type, size_t pixel_count, const void* data);

        void resize(size_t size) noexcept;

        /// @brief Allocates texture memory that fits to PUBO
        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        /// @return Pointer to Pixel Unpack Buffer Object if it binds or nullptr
        /// @note Doesn't check params validity
        const void* get_pubo_for_unpack(uint32_t texture, uint32_t level, enum_t internal_format, enum_t format, enum_t type, size_t pixels_count) noexcept;

    public:
        textures m_textures;
    };
}