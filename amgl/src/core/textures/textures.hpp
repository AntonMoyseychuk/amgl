#pragma once
#include "images.hpp"

namespace amgl
{
    struct texture_descs
    {
        texture_descs() = default;
        texture_descs(size_t size);

        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        /// @param target Texture object target
        /// @param internal_format Texture object internal format
        /// @param interpret_as_integer Interpret data as integer or float when sampling
        /// @note Doesn't check params validity
        void set(uint32_t texture, enum_t target, enum_t internal_format, bool interpret_as_integer) noexcept;

        /// @brief 
        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        /// @note Doesn't check 'texture' validity
        enum_t get_internal_format(uint32_t texture) const noexcept { return m_internal_formats[texture]; }

        /// @brief 
        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        /// @note Doesn't check 'texture' validity
        enum_t get_target(uint32_t texture) const noexcept { return m_targets[texture]; }

        /// @brief 
        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        /// @note Doesn't check 'texture' validity
        bool is_interpret_as_integer(uint32_t texture) const noexcept { return m_are_integers[texture]; }

        void resize(size_t size) noexcept;

        size_t get_count() const noexcept
        {
            const size_t size  = m_internal_formats.size();
            AM_ASSERT(detail::are_equal(size, m_targets.size(), m_are_integers.size()));
            return size;
        }

    public:
        // Need to determine type when sampling
        std::vector<enum_t> m_internal_formats;
        
        // Images cannot be attached to another target if they have already been attached before. 
        // Therefore, we need to keep their original targets
        std::vector<enum_t> m_targets;

        std::vector<bool> m_are_integers;
    };


    struct LOD_root
    {
        LOD_root(size_t size = 1u);

        void resize(size_t size) noexcept;

        size_t get_lods_count() const noexcept { return m_images.get_image_count(); }

    public:
        images m_images;
    };


    struct textures
    {
        textures() = default;
        textures(size_t size);

        /// @brief 
        /// @return Texture object in the kernel range [0, UINT32_MAX - 1]
        uint32_t create_texture() noexcept;

        /// @brief 
        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        void free_texture(uint32_t texture) noexcept;
        
        /// @brief 
        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        bool is_texture_exist(uint32_t texture) const noexcept;

        void resize(size_t size) noexcept;

        /// @brief 
        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        void set_target(uint32_t texture, enum_t target) noexcept { m_tex_descs.m_targets[texture] = target; }
        
        /// @brief 
        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        void set_internal_format(uint32_t texture, enum_t internal_format) noexcept 
        { 
            m_tex_descs.m_internal_formats[texture] = internal_format;
        }
        
        /// @brief 
        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        void set_interger_representation(uint32_t texture, bool interpret_as_integer) noexcept 
        { 
            m_tex_descs.m_are_integers[texture] = interpret_as_integer; 
        }

        /// @brief 
        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        void set_desc(uint32_t texture, enum_t target, enum_t internal_format, bool interpret_as_integer) noexcept 
        { 
            m_tex_descs.set(texture, target, internal_format, interpret_as_integer);
        }

        // @brief 
        /// @param texture Texture object in the kernel range [0, UINT32_MAX - 1]
        LOD_root& get_LOD_root(uint32_t texture) noexcept { return m_LOD_roots[texture]; }

        size_t get_count() const noexcept
        {
            const size_t size  = m_LOD_roots.size();
            AM_ASSERT(detail::are_equal(size, m_tex_descs.get_count()));
            return size;
        }

    public:
        std::vector<LOD_root> m_LOD_roots;
        texture_descs m_tex_descs;

        id_pool m_id_pool;
    };
}