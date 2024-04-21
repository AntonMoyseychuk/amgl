#include "pch.hpp"
#include "texture_mng.hpp"

#include "internal/formats.hpp"
#include "internal/types.hpp"

#include "internal/converter.hpp"

#include "core/core.hpp"
#include "core/utils/util_func.hpp"

#include "core/context/context_mng.hpp"
#include "core/buffers/buffer_mng.hpp"



AM_STATIC_ASSERT_MSG(AM_INIT_TEX_COUNT > 0, "AM_INIT_TEXTURE_COUNT must be greater than 0");


namespace amgl
{
    static context_mng& gs_context_mng = context_mng::instance();
    static buffer_mng& gs_buffer_mng = buffer_mng::instance();
    

    #define TEXTURE_TARGETS                                                             \
        AMGL_TEXTURE_BUFFER,                                                            \
        AMGL_TEXTURE_1D,                                                                \
        AMGL_PROXY_TEXTURE_1D,                                                          \
        AMGL_TEXTURE_2D,                                                                \
        AMGL_PROXY_TEXTURE_2D,                                                          \
        AMGL_TEXTURE_3D,                                                                \
        AMGL_PROXY_TEXTURE_3D,                                                          \
        AMGL_TEXTURE_1D_ARRAY,                                                          \
        AMGL_PROXY_TEXTURE_1D_ARRAY,                                                    \
        AMGL_TEXTURE_2D_ARRAY,                                                          \
        AMGL_PROXY_TEXTURE_2D_ARRAY,                                                    \
        AMGL_TEXTURE_RECTANGLE,                                                         \
        AMGL_PROXY_TEXTURE_RECTANGLE,                                                   \
        AMGL_TEXTURE_CUBE_MAP,                                                          \
        AMGL_PROXY_TEXTURE_CUBE_MAP,                                                    \
        AMGL_TEXTURE_CUBE_MAP_ARRAY,                                                    \
        AMGL_PROXY_TEXTURE_CUBE_MAP_ARRAY,                                              \
        AMGL_TEXTURE_2D_MULTISAMPLE,                                                    \
        AMGL_PROXY_TEXTURE_2D_MULTISAMPLE,                                              \
        AMGL_TEXTURE_2D_MULTISAMPLE_ARRAY,                                              \
        AMGL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY


    #define CHECK_TEXTURE_TARGET_VALIDITY(target, error_flag, ...)                      \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(target, TEXTURE_TARGETS),               \
            error_flag, gs_context_mng, __VA_ARGS__)


    #define CHECK_TEXTURE_FORMAT_VALIDITY(format, error_flag, ...)                      \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(format, TEXTURE_FORMATS),               \
            error_flag, gs_context_mng, __VA_ARGS__)


    #define CHECK_TEXTURE_TYPE_VALIDITY(type, error_flag, ...)                          \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(type,                                   \
            TEXTURE_PRIMITIVE_TYPES,                                                    \
            TEXTURE_PACKED_TYPES                                                        \
        ), error_flag, gs_context_mng, __VA_ARGS__)


    #define CHECK_TEXTURE_INTERNAL_FORMAT_VALIDITY(internal_format, error_flag, ...)    \
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(internal_format,                        \
            TEXTURE_BASE_INTERNAL_FORMATS,                                              \
            TEXTURE_SIZED_INTERNAL_FORMATS                                              \
        ), error_flag, gs_context_mng, __VA_ARGS__)


    // Takes 'texture' in the kernel range [0, UINT32_MAX - 1]
    // Doesn't check 'target' validity
    #define CHECK_TARGET_COMPATIBILITY(target, texture, error_flag, ...)                                                    \
    {                                                                                                                       \
        const enum_t curr_target = m_textures.m_tex_descs.m_targets[texture];                                                        \
        AM_SET_ERROR_FLAG_IF(curr_target != AMGL_NONE && curr_target != target, error_flag, gs_context_mng, __VA_ARGS__);   \
    }

    // Takes 'texture' in the kernel range [0, UINT32_MAX - 1]
    #define CHECK_TEXTURE_VALIDITY(texture, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(!m_textures.is_texture_exist(texture), error_flag, gs_context_mng, __VA_ARGS__)

    // Takes 'texture' in the kernel range [0, UINT32_MAX - 1]
    #define CHECK_TEXTURE_NOT_DEFAULT(texture, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(texture), error_flag, gs_context_mng, __VA_ARGS__)

    #define CHECK_TEXTURE_LOD_VALIDITY(level, max_level, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(level > max_level, error_flag, gs_context_mng, __VA_ARGS__)
    
    #define IS_INTEGER_FORMAT(format) \
        detail::is_one_of(format, AMGL_RED_INTEGER, AMGL_RG_INTEGER, AMGL_RGB_INTEGER, AMGL_BGR_INTEGER, AMGL_RGBA_INTEGER, AMGL_BGRA_INTEGER)


    static bool check_common_tex_params(enum_t internal_format, uint32_t border, enum_t format, enum_t type) noexcept
    {
        using namespace detail;

        CHECK_TEXTURE_FORMAT_VALIDITY(format, AMGL_INVALID_ENUM, false);
        
        CHECK_TEXTURE_TYPE_VALIDITY(type, AMGL_INVALID_ENUM, false);
        
        CHECK_TEXTURE_INTERNAL_FORMAT_VALIDITY(internal_format, AMGL_INVALID_VALUE, false);
        
        AM_SET_ERROR_FLAG_IF(border != 0, AMGL_INVALID_VALUE, gs_context_mng, false);

        AM_SET_ERROR_FLAG_IF(is_one_of(
            type, 
            AMGL_UNSIGNED_BYTE_3_3_2, 
            AMGL_UNSIGNED_BYTE_2_3_3_REV, 
            AMGL_UNSIGNED_SHORT_5_6_5, 
            AMGL_UNSIGNED_SHORT_5_6_5_REV) && format != AMGL_RGB, AMGL_INVALID_OPERATION, gs_context_mng, false);

        AM_SET_ERROR_FLAG_IF(is_one_of(
            type, 
            AMGL_UNSIGNED_SHORT_4_4_4_4_REV,
            AMGL_UNSIGNED_SHORT_1_5_5_5_REV,
            AMGL_UNSIGNED_INT_8_8_8_8_REV,
            AMGL_UNSIGNED_INT_2_10_10_10_REV,
            AMGL_UNSIGNED_SHORT_4_4_4_4,
            AMGL_UNSIGNED_SHORT_5_5_5_1,
            AMGL_UNSIGNED_INT_8_8_8_8,
            AMGL_UNSIGNED_INT_10_10_10_2) && !is_one_of(format, AMGL_RGBA, AMGL_BGRA), AMGL_INVALID_OPERATION, gs_context_mng, false);

        AM_SET_ERROR_FLAG_IF(format == AMGL_DEPTH_COMPONENT && !is_one_of(
            internal_format, 
            AMGL_DEPTH_COMPONENT,
            AMGL_DEPTH_COMPONENT16,
            AMGL_DEPTH_COMPONENT24,
            AMGL_DEPTH_COMPONENT32), AMGL_INVALID_OPERATION , gs_context_mng, false);

        AM_SET_ERROR_FLAG_IF(is_one_of(
            internal_format, 
            AMGL_DEPTH_COMPONENT,
            AMGL_DEPTH_COMPONENT16,
            AMGL_DEPTH_COMPONENT24,
            AMGL_DEPTH_COMPONENT32) && format != AMGL_DEPTH_COMPONENT, AMGL_INVALID_OPERATION , gs_context_mng, false);

        return true;
    }


    void texture_mng::gen_textures(size_t n, uint32_t* textures) noexcept
    {
        AM_RETURN_IF(!textures);

        for (uint32_t i = 0u; i < n; ++i) {
            textures[i] = CONV_KERNEL_TO_USER_SPACE(m_textures.create_texture());
        }
    }

    
    void texture_mng::delete_textures(size_t n, const uint32_t *textures) noexcept
    {
        AM_RETURN_IF(!textures);

        for (uint32_t i = 0u; i < n; ++i) {
            const uint32_t kernel_id = CONV_USER_TO_KERNEL_SPACE(textures[i]);
            AM_CONTINUE_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(kernel_id) || !m_textures.is_texture_exist(kernel_id));
            
            m_textures.free_texture(kernel_id);
        }
    }

    
    void texture_mng::bind_texture(enum_t target, uint32_t texture) noexcept
    {
        CHECK_TEXTURE_TARGET_VALIDITY(target, AMGL_INVALID_ENUM);

        const uint32_t kernel_tex_id = CONV_USER_TO_KERNEL_SPACE(texture);
        CHECK_TEXTURE_VALIDITY(kernel_tex_id, AMGL_INVALID_VALUE);

        if (!AM_IS_DEFAULT_ID_KERNEL_SPACE(kernel_tex_id)) {
            CHECK_TARGET_COMPATIBILITY(target, kernel_tex_id, AMGL_INVALID_OPERATION);
            m_textures.set_target(kernel_tex_id, target);
        }

        gs_context_mng.bind_target_texture(target, kernel_tex_id);
    }

    
    bool texture_mng::is_texture(uint32_t texture) noexcept
    {
        AM_RETURN_IF(AM_IS_DEFAULT_ID_USER_SPACE(texture), false);

        return m_textures.is_texture_exist(CONV_USER_TO_KERNEL_SPACE(texture));
    }

    
    void texture_mng::tex_image_1d(enum_t target, uint32_t level, enum_t internal_format, size_t width, 
        uint32_t border, enum_t format, enum_t type, const void *data) noexcept
    {
        using namespace detail;
        static context& contxt = gs_context_mng.get_context();

        AM_RETURN_IF(!check_common_tex_params(internal_format, border, format, type));

        AM_SET_ERROR_FLAG_IF(!is_one_of(target, AMGL_TEXTURE_1D, AMGL_PROXY_TEXTURE_1D), AMGL_INVALID_ENUM, gs_context_mng);

        const uint32_t tex_kernel = gs_context_mng.get_binded_texture(target);

        LOD_root& lod_root = m_textures.get_LOD_root(tex_kernel);
        if (level >= lod_root.get_lods_count()) {
            return;
        }

        const void* pubo_data = get_pubo_for_unpack(tex_kernel, level, internal_format, format, type, width);

        const void* _data = pubo_data ? pubo_data : data;

        if (!AM_IS_DEFAULT_ID_KERNEL_SPACE(tex_kernel)) {
            m_textures.set_desc(tex_kernel, target, internal_format, IS_INTEGER_FORMAT(format));
            lod_root.m_images.set(level, width, 1u, 1u);

            reallocate_tex_memory(tex_kernel, level, internal_format, format, type, width, _data); 
        }
    }

    
    void texture_mng::tex_image_2d(enum_t target, uint32_t level, enum_t internal_format, size_t width, size_t height, 
        uint32_t border, enum_t format, enum_t type, const void *data) noexcept
    {
        using namespace detail;
        static context& contxt = gs_context_mng.get_context();

        AM_RETURN_IF(!check_common_tex_params(internal_format, border, format, type));

        AM_SET_ERROR_FLAG_IF(!is_one_of(
            target, 
            AMGL_TEXTURE_2D, 
            AMGL_PROXY_TEXTURE_2D, 
            AMGL_TEXTURE_1D_ARRAY, 
            AMGL_PROXY_TEXTURE_1D_ARRAY, 
            AMGL_TEXTURE_RECTANGLE, 
            AMGL_PROXY_TEXTURE_RECTANGLE, 
            AMGL_TEXTURE_CUBE_MAP_POSITIVE_X, 
            AMGL_TEXTURE_CUBE_MAP_NEGATIVE_X, 
            AMGL_TEXTURE_CUBE_MAP_POSITIVE_Y, 
            AMGL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 
            AMGL_TEXTURE_CUBE_MAP_POSITIVE_Z, 
            AMGL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 
            AMGL_PROXY_TEXTURE_CUBE_MAP), AMGL_INVALID_ENUM, gs_context_mng);

        AM_SET_ERROR_FLAG_IF(is_one_of(
            target, 
            AMGL_TEXTURE_CUBE_MAP_POSITIVE_X, 
            AMGL_TEXTURE_CUBE_MAP_NEGATIVE_X, 
            AMGL_TEXTURE_CUBE_MAP_POSITIVE_Y, 
            AMGL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 
            AMGL_TEXTURE_CUBE_MAP_POSITIVE_Z, 
            AMGL_TEXTURE_CUBE_MAP_NEGATIVE_Z) && width != height, AMGL_INVALID_ENUM, gs_context_mng);

        AM_SET_ERROR_FLAG_IF(
            !is_one_of(target, AMGL_TEXTURE_2D, AMGL_PROXY_TEXTURE_2D, AMGL_TEXTURE_RECTANGLE, AMGL_PROXY_TEXTURE_RECTANGLE) 
                && is_one_of(internal_format, AMGL_DEPTH_COMPONENT, AMGL_DEPTH_COMPONENT16, AMGL_DEPTH_COMPONENT24, AMGL_DEPTH_COMPONENT32), 
                AMGL_INVALID_OPERATION , gs_context_mng);

        AM_SET_ERROR_FLAG_IF(is_one_of(target, AMGL_TEXTURE_RECTANGLE, AMGL_PROXY_TEXTURE_RECTANGLE) 
            && level != 0, AMGL_INVALID_OPERATION , gs_context_mng);

        const uint32_t tex_kernel = gs_context_mng.get_binded_texture(target);

        LOD_root& lod_root = m_textures.get_LOD_root(tex_kernel);
        if (level >= lod_root.get_lods_count()) {
            return;
        }

        const void* pubo_data = get_pubo_for_unpack(tex_kernel, level, internal_format, format, type, width * height);

        const void* _data = pubo_data ? pubo_data : data;

        if (!AM_IS_DEFAULT_ID_KERNEL_SPACE(tex_kernel)) {
            m_textures.set_desc(tex_kernel, target, internal_format, IS_INTEGER_FORMAT(format));
            lod_root.m_images.set(level, width, height, 1u);

            reallocate_tex_memory(tex_kernel, level, internal_format, format, type, width * height, _data); 
        }
    }

    
    void texture_mng::generate_mipmap(enum_t target) noexcept
    {
        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(
            target, 
            AMGL_TEXTURE_1D, 
            AMGL_TEXTURE_2D, 
            AMGL_TEXTURE_3D, 
            AMGL_TEXTURE_1D_ARRAY, 
            AMGL_TEXTURE_2D_ARRAY, 
            AMGL_TEXTURE_CUBE_MAP, 
            AMGL_TEXTURE_CUBE_MAP_ARRAY), AMGL_INVALID_ENUM, gs_context_mng);
        
        // AM_SET_ERROR_FLAG_IF(!detail::is_one_of(
        //     target, 
        //     AMGL_TEXTURE_CUBE_MAP,
        //     AMGL_TEXTURE_CUBE_MAP_ARRAY) && texture != complete cubemap or cubemap array, AMGL_INVALID_OPERATION, gs_context_mng);

        const uint32_t kernel_tex_id = gs_context_mng.get_binded_texture(target);
        AM_RETURN_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(kernel_tex_id));

        generate_texture_mipmap(CONV_KERNEL_TO_USER_SPACE(kernel_tex_id));
    }

    
    void texture_mng::generate_texture_mipmap(uint32_t texture) noexcept
    {
        AM_NOT_IMPLEMENTED;

        // AM_RETURN_IF(!is_texture(texture));
        //
        // const uint32_t kernel_tex_id = CONV_USER_TO_KERNEL_SPACE(texture);
        // LOD_root& root = m_textures.get_LOD_root(kernel_tex_id);
        //
        // const uint32_t lod0_w = root.m_images.get_image_width(0);
        // const uint32_t lod0_h = root.m_images.get_image_height(0);
        //
        // const size_t max_lod = log2(math::max(lod0_w, lod0_h)) + 1u;
        //
        // root.resize(max_lod);
        //
        // const uint8_t* lod0_data = root.m_images.get_image_data(0);
        // AM_RETURN_IF(lod0_data == nullptr);
        //
        // const size_t pixel_size = get_internal_fmt_pixel_size(m_textures.m_tex_descs.get_internal_format(kernel_tex_id));
        //
        // uint32_t cur_lod_w = lod0_w, cur_lod_h = lod0_h;
        // for (size_t lod = 1u; lod < max_lod; ++lod) {
        //     cur_lod_w = math::max(cur_lod_w / 2u, 1u);
        //     cur_lod_h = math::max(cur_lod_h / 2u, 1u);
        //
        //     root.m_images.set(lod, cur_lod_w, cur_lod_h, 1u /* for now */);
        //     root.m_images.m_memory_blocks[lod].resize(cur_lod_w * cur_lod_h * 1u * pixel_size);
        //
        //     for (uint32_t y = 0; y < cur_lod_h; ++y) {
        //         for (uint32_t x = 0; x < cur_lod_w; ++x) {
        //             uint32_t r = 0u, g = 0u, b = 0u, a = 0u;
        //          
        //             for (uint32_t i = 0u; i < 2u; ++i) {
        //                 for (uint32_t j = 0u; j < 2u; ++j) {
        //                     const uint32_t old_x = x * 2u + i;
        //                     const uint32_t old_y = y * 2u + j;
        //          
        //                     const uint32_t old_pixel = (old_y * lod0_w + old_x) * pixel_size;
        //
        //                     r += lod0_data[old_pixel + 0u];
        //                     g += lod0_data[old_pixel + 1u];
        //                     b += lod0_data[old_pixel + 2u];
        //                     a += lod0_data[old_pixel + 3u];
        //                 }
        //             }
        //          
        //             const uint32_t cur_pixel = (y * cur_lod_w + x) * pixel_size;
        //             root.m_images.m_memory_blocks[lod][cur_pixel + 0u] = r / 4u;                    
        //             root.m_images.m_memory_blocks[lod][cur_pixel + 1u] = g / 4u;                    
        //             root.m_images.m_memory_blocks[lod][cur_pixel + 2u] = b / 4u;                    
        //             root.m_images.m_memory_blocks[lod][cur_pixel + 3u] = a / 4u;                    
        //         }
        //     }
        // } 
    }

    
    texture_mng::texture_mng(size_t preallocation_size)
    {
        resize(preallocation_size);
    }


    void texture_mng::reallocate_tex_memory(
        uint32_t texture, uint32_t level, enum_t internal_format, enum_t format, enum_t type, size_t pixel_count, const void *data)
    {
        const size_t internal_pixel_size  = get_internal_fmt_pixel_size(internal_format);

        images::memory_block& mem_block = m_textures.get_LOD_root(texture).m_images.m_memory_blocks[level];
        mem_block.resize(pixel_count * internal_pixel_size);
        
        if (data) {
            const texture_data_converter converter(internal_format, format, type);
            converter(mem_block.data(), data, pixel_count);
        }
    }

    void texture_mng::resize(size_t size) noexcept
    {
        m_textures.resize(size);
    }
    
    
    const void *texture_mng::get_pubo_for_unpack(uint32_t texture, uint32_t level, enum_t internal_format, 
        enum_t format, enum_t type, size_t pixels_count) noexcept
    {
        using namespace detail;
        static context& contxt = gs_context_mng.get_context();

        const uint32_t binded_pubo_user_range = CONV_KERNEL_TO_USER_SPACE(contxt.buf_bindings.pubo[0].buffer);
        if (!AM_IS_DEFAULT_ID_USER_SPACE(binded_pubo_user_range)) {
            AM_SET_ERROR_FLAG_IF(gs_buffer_mng.is_buffer_mapped(binded_pubo_user_range), AMGL_INVALID_OPERATION , gs_context_mng, nullptr);
            
            const size_t pubo_size = gs_buffer_mng.get_buffer_size(binded_pubo_user_range);

            reallocate_tex_memory(texture, level, internal_format, format, type, pixels_count, nullptr);
            const size_t texture_buffer_size = m_textures.get_LOD_root(texture).m_images.get_image_size(level);
            AM_SET_ERROR_FLAG_IF(pubo_size > texture_buffer_size, AMGL_INVALID_OPERATION, gs_context_mng, nullptr);
            
            const uint32_t type_size_in_bytes = get_type_size(type);
            AM_SET_ERROR_FLAG_IF(pubo_size % type_size_in_bytes != 0, AMGL_INVALID_OPERATION, gs_context_mng, nullptr);

            return gs_buffer_mng.get_buffer(binded_pubo_user_range);
        }

        return nullptr;
    }
}