#pragma once
#include "images.hpp"


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

        /// @brief Retrieve a sub-region of a texture image from a texture object
        /// @param texture The name of the source texture object 
        /// @param level The level-of-detail
        /// @param xoffset Texel offset in the x direction within the texture array
        /// @param yoffset Texel offset in the y direction within the texture array
        /// @param zoffset Texel offset in the z direction within the texture array
        /// @param width Width of the texture subimage
        /// @param height Height of the texture subimage
        /// @param depth Depth of the texture subimage
        /// @param format Format of the pixel data
        /// @param type Data type of the pixel data
        /// @param buf_size Size of the buffer to receive the retrieved pixel data
        /// @param pixels Pointer to an array of the type specified by type
        void get_texture_sub_image(uint32_t texture, uint32_t level, size_t xoffset, size_t yoffset, size_t zoffset, 
            size_t width, size_t height, size_t depth, enum_t format, enum_t type, size_t buf_size, void* pixels) noexcept;

        /// @brief 
        /// @param texture Texture object in the user range [1, UINT32_MAX]
        bool is_texture(uint32_t texture) noexcept;

        void tex_image_1d(enum_t target, uint32_t level, enum_t internal_format, size_t width, uint32_t border, 
            enum_t format, enum_t type, const void* data) noexcept;

        void tex_image_2d(enum_t target, uint32_t level, enum_t internal_format, size_t width, size_t height, uint32_t border, 
            enum_t format, enum_t type, const void* data) noexcept;
        

    private:
        texture_mng() = default;
        texture_mng(size_t preallocation_size);

        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        /// @param internal_format Format of internal texture storage
        /// @param format Format of input data
        /// @param type Type of input data
        /// @param pixel_count Count of pixels
        /// @param data Input data
        /// @note Doesn't check 'texture', 'internal_format', 'format' and 'type' validity
        void reallocate_tex_memory(uint32_t texture, enum_t internal_format, enum_t format, enum_t type, size_t pixel_count, const void* data);

        void resize(size_t size) noexcept;

    public:
        images m_images;
    };
}