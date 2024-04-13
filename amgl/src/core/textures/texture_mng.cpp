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
        const enum_t curr_target = m_images.m_targets[texture];                                                           \
        AM_SET_ERROR_FLAG_IF(curr_target != AMGL_NONE && curr_target != target, error_flag, gs_context_mng, __VA_ARGS__);   \
    }

    // Takes 'texture' in the kernel range [0, UINT32_MAX - 1]
    #define CHECK_TEXTURE_VALIDITY(texture, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(!m_images.is_image_exist(texture), error_flag, gs_context_mng, __VA_ARGS__)

    // Takes 'texture' in the kernel range [0, UINT32_MAX - 1]
    #define CHECK_TEXTURE_NOT_DEFAULT(texture, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(texture), error_flag, gs_context_mng, __VA_ARGS__)

    #define CHECK_TEXTURE_LOD_VALIDITY(level, max_level, error_flag, ...) \
        AM_SET_ERROR_FLAG_IF(level > max_level, error_flag, gs_context_mng, __VA_ARGS__)


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
            textures[i] = CONV_KERNEL_TO_USER_SPACE(m_images.create_image());
        }
    }

    
    void texture_mng::delete_textures(size_t n, const uint32_t *textures) noexcept
    {
        AM_RETURN_IF(!textures);

        for (uint32_t i = 0u; i < n; ++i) {
            const uint32_t kernel_id = CONV_USER_TO_KERNEL_SPACE(textures[i]);
            AM_CONTINUE_IF(AM_IS_DEFAULT_ID_KERNEL_SPACE(kernel_id) || !m_images.is_image_exist(kernel_id));
            
            m_images.free_image(kernel_id);
        }
    }

    
    void texture_mng::bind_texture(enum_t target, uint32_t texture) noexcept
    {
        CHECK_TEXTURE_TARGET_VALIDITY(target, AMGL_INVALID_ENUM);

        const uint32_t kernel_tex_id = CONV_USER_TO_KERNEL_SPACE(texture);
        CHECK_TEXTURE_VALIDITY(kernel_tex_id, AMGL_INVALID_VALUE);

        if (!AM_IS_DEFAULT_ID_KERNEL_SPACE(kernel_tex_id)) {
            CHECK_TARGET_COMPATIBILITY(target, kernel_tex_id, AMGL_INVALID_OPERATION);
            m_images.m_targets[kernel_tex_id] = target;
        }

        gs_context_mng.bind_target_texture(target, kernel_tex_id);
    }

    
    void texture_mng::get_texture_sub_image(uint32_t texture, uint32_t level, size_t xoffset, size_t yoffset, size_t zoffset, 
        size_t width, size_t height, size_t depth, enum_t format, enum_t type, size_t buf_size, void *pixels) noexcept
    {
        AM_NOT_IMPLEMENTED;
        
        // using namespace detail;
        // static context& contxt = gs_context_mng.get_context();

        // const uint32_t tex_kernel = CONV_USER_TO_KERNEL_SPACE(texture);
        // AM_SET_ERROR_FLAG_IF(!is_one_of(
        //     tex_kernel, 
        //     contxt.tex_bindings.texture1d,
        //     contxt.tex_bindings.texture1d_array,
        //     contxt.tex_bindings.texture2d,
        //     contxt.tex_bindings.texture2d_array,
        //     contxt.tex_bindings.texture3d,
        //     contxt.tex_bindings.texture_cubemap,
        //     contxt.tex_bindings.texture_cubemap_array,
        //     contxt.tex_bindings.texture_rect), AMGL_INVALID_VALUE, gs_context_mng);

        // AM_SET_ERROR_FLAG_IF(is_one_of(
        //     tex_kernel, 
        //     contxt.tex_bindings.texture_2d_multisample,
        //     contxt.tex_bindings.texture_2d_multisample_array,
        //     contxt.tex_bindings.proxy_texture_2d_multisample,
        //     contxt.tex_bindings.proxy_texture_2d_multisample_array,
        //     contxt.buf_bindings.vbo,
        //     contxt.buf_bindings.ebo,
        //     contxt.buf_bindings.ubo,
        //     contxt.buf_bindings.ssbo,
        //     contxt.buf_bindings.tbo,
        //     contxt.buf_bindings.crbo,
        //     contxt.buf_bindings.cwbo,
        //     contxt.buf_bindings.dibo,
        //     contxt.buf_bindings.dribo,
        //     contxt.buf_bindings.ppbo,
        //     contxt.buf_bindings.pubo,
        //     contxt.buf_bindings.qbo,
        //     contxt.buf_bindings.tfbo,
        //     contxt.buf_bindings.acbo), AMGL_INVALID_VALUE, gs_context_mng);

        // AM_SET_ERROR_FLAG_IF(xoffset + width > m_images.m_widths[tex_kernel] || yoffset + height > m_images.m_heights[tex_kernel]
        //     || zoffset + depth > m_images.m_depths[tex_kernel], AMGL_INVALID_VALUE, gs_context_mng);

        // AM_SET_ERROR_FLAG_IF(tex_kernel == contxt.tex_bindings.texture1d && (yoffset != 0u || height != 1u), AMGL_INVALID_VALUE, gs_context_mng);
        
        // AM_SET_ERROR_FLAG_IF(is_one_of(
        //     tex_kernel, 
        //     contxt.tex_bindings.texture1d, 
        //     contxt.tex_bindings.texture1d_array, 
        //     contxt.tex_bindings.texture2d,
        //     contxt.tex_bindings.texture_rect) && (zoffset != 0u || depth != 1u), AMGL_INVALID_VALUE, gs_context_mng);

        // AM_SET_ERROR_FLAG_IF(m_images.m_memory_blocks[tex_kernel].size() > buf_size, AMGL_INVALID_OPERATION, gs_context_mng);
    }

    
    bool texture_mng::is_texture(uint32_t texture) noexcept
    {
        AM_RETURN_IF(AM_IS_DEFAULT_ID_USER_SPACE(texture), false);

        return m_images.is_image_exist(CONV_USER_TO_KERNEL_SPACE(texture));
    }

    
    void texture_mng::tex_image_1d(enum_t target, uint32_t level, enum_t internal_format, size_t width, 
        uint32_t border, enum_t format, enum_t type, const void *data) noexcept
    {
        using namespace detail;
        static context& contxt = gs_context_mng.get_context();

        AM_RETURN_IF(!check_common_tex_params(internal_format, border, format, type));

        AM_SET_ERROR_FLAG_IF(!is_one_of(target, AMGL_TEXTURE_1D, AMGL_PROXY_TEXTURE_1D), AMGL_INVALID_ENUM, gs_context_mng);

        const uint32_t tex_kernel = gs_context_mng.get_binded_texture(target);
        const void* _data = data;

        const uint32_t binded_pubo_user_range = CONV_KERNEL_TO_USER_SPACE(contxt.buf_bindings.pubo[0].buffer);
        if (!AM_IS_DEFAULT_ID_USER_SPACE(binded_pubo_user_range)) {
            AM_SET_ERROR_FLAG_IF(gs_buffer_mng.is_buffer_mapped(binded_pubo_user_range), AMGL_INVALID_OPERATION , gs_context_mng);
            
            const size_t pubo_size = gs_buffer_mng.get_buffer_size(binded_pubo_user_range);

            reallocate_tex_memory(tex_kernel, internal_format, format, type, width, nullptr);
            const size_t texture_buffer_size = m_images.m_memory_blocks[tex_kernel].size();
            AM_SET_ERROR_FLAG_IF(pubo_size > texture_buffer_size, AMGL_INVALID_OPERATION, gs_context_mng);
            
            const uint32_t type_size_in_bytes = get_type_size(type);
            AM_SET_ERROR_FLAG_IF(pubo_size % type_size_in_bytes != 0, AMGL_INVALID_OPERATION, gs_context_mng);

            _data = gs_buffer_mng.get_buffer(binded_pubo_user_range);
        }

        if (!AM_IS_DEFAULT_ID_KERNEL_SPACE(tex_kernel)) {
            m_images.set(tex_kernel, target, width, 1u, 1u, internal_format, format);

            reallocate_tex_memory(tex_kernel, internal_format, format, type, width, _data); 
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
        const void* _data = data;

        const uint32_t binded_pubo_user_range = CONV_KERNEL_TO_USER_SPACE(contxt.buf_bindings.pubo[0].buffer);
        if (!AM_IS_DEFAULT_ID_USER_SPACE(binded_pubo_user_range)) {
            AM_SET_ERROR_FLAG_IF(gs_buffer_mng.is_buffer_mapped(binded_pubo_user_range), AMGL_INVALID_OPERATION , gs_context_mng);
            
            const size_t pubo_size = gs_buffer_mng.get_buffer_size(binded_pubo_user_range);

            reallocate_tex_memory(tex_kernel, internal_format, format, type, width * height, nullptr);
            const size_t texture_buffer_size = m_images.m_memory_blocks[tex_kernel].size();
            AM_SET_ERROR_FLAG_IF(pubo_size > texture_buffer_size, AMGL_INVALID_OPERATION, gs_context_mng);
            
            const uint32_t type_size_in_bytes = get_type_size(type);
            AM_SET_ERROR_FLAG_IF(pubo_size % type_size_in_bytes != 0, AMGL_INVALID_OPERATION, gs_context_mng);

            _data = gs_buffer_mng.get_buffer(binded_pubo_user_range);
        }

        if (!AM_IS_DEFAULT_ID_KERNEL_SPACE(tex_kernel)) {
            m_images.set(tex_kernel, target, width, height, 1u, internal_format, format);

            reallocate_tex_memory(tex_kernel, internal_format, format, type, width * height, _data); 
        }
    }

    
    texture_mng::texture_mng(size_t preallocation_size)
    {
        resize(preallocation_size);
    }


    void texture_mng::reallocate_tex_memory(
        uint32_t texture, enum_t internal_format, enum_t format, enum_t type, size_t pixel_count, const void *data)
    {
        const size_t internal_pixel_size  = get_internal_fmt_pixel_size(internal_format);

        images::memory_block& mem_block = m_images.m_memory_blocks[texture];
        mem_block.resize(pixel_count * internal_pixel_size);
        
        if (data) {
            const texture_data_converter converter(internal_format, format, type);
            converter(mem_block.data(), data, pixel_count);
        }
    }

    void texture_mng::resize(size_t size) noexcept
    {
        m_images.resize(size);
    }
}