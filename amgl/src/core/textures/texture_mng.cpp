#include "pch.hpp"
#include "texture_mng.hpp"
#include "texture_data_converting/texture_data_converting.hpp"

#include "core/core.hpp"
#include "core/utils/util_func.hpp"

#include "core/context/context_mng.hpp"
#include "core/buffers/buffer_mng.hpp"



static_assert(AM_INIT_TEX_COUNT > 0, "AM_INIT_TEXTURE_COUNT must be greater than 0");


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
        const enum_t curr_target = m_textures.m_targets[texture];                                                           \
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
            m_textures.m_targets[kernel_tex_id] = target;
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
        static context& contxt = gs_context_mng.get_context();

        AM_SET_ERROR_FLAG_IF(!detail::is_one_of(target, AMGL_TEXTURE_1D, AMGL_PROXY_TEXTURE_1D), AMGL_INVALID_ENUM, gs_context_mng);
        
        CHECK_TEXTURE_FORMAT_VALIDITY(format, AMGL_INVALID_ENUM);
        
        CHECK_TEXTURE_TYPE_VALIDITY(type, AMGL_INVALID_ENUM);
        
        const uint32_t max_texture_level = log2(width) + 1u;
        CHECK_TEXTURE_LOD_VALIDITY(level, max_texture_level, AMGL_INVALID_VALUE);
        
        CHECK_TEXTURE_INTERNAL_FORMAT_VALIDITY(internal_format, AMGL_INVALID_VALUE);

        AM_SET_ERROR_FLAG_IF(width > context::MAX_TEXTURE_SIZE, AMGL_INVALID_VALUE, gs_context_mng);
        
        AM_SET_ERROR_FLAG_IF(border != 0, AMGL_INVALID_VALUE, gs_context_mng);

        AM_SET_ERROR_FLAG_IF(detail::is_one_of(
            type, 
            AMGL_UNSIGNED_BYTE_3_3_2, 
            AMGL_UNSIGNED_BYTE_2_3_3_REV, 
            AMGL_UNSIGNED_SHORT_5_6_5, 
            AMGL_UNSIGNED_SHORT_5_6_5_REV) && format != AMGL_RGB, AMGL_INVALID_OPERATION, gs_context_mng);

        AM_SET_ERROR_FLAG_IF(detail::is_one_of(
            type, 
            AMGL_UNSIGNED_SHORT_4_4_4_4_REV,
            AMGL_UNSIGNED_SHORT_1_5_5_5_REV,
            AMGL_UNSIGNED_INT_8_8_8_8_REV,
            AMGL_UNSIGNED_INT_2_10_10_10_REV,
            AMGL_UNSIGNED_SHORT_4_4_4_4,
            AMGL_UNSIGNED_SHORT_5_5_5_1,
            AMGL_UNSIGNED_INT_8_8_8_8,
            AMGL_UNSIGNED_INT_10_10_10_2) && !detail::is_one_of(format, AMGL_RGBA, AMGL_BGRA), AMGL_INVALID_OPERATION, gs_context_mng);

        AM_SET_ERROR_FLAG_IF(format == AMGL_DEPTH_COMPONENT && !detail::is_one_of(
            internal_format, 
            AMGL_DEPTH_COMPONENT,
            AMGL_DEPTH_COMPONENT16,
            /*AMGL_DEPTH_COMPONENT24,*/
            AMGL_DEPTH_COMPONENT32), AMGL_INVALID_OPERATION , gs_context_mng);

        AM_SET_ERROR_FLAG_IF(detail::is_one_of(
            internal_format, 
            AMGL_DEPTH_COMPONENT,
            AMGL_DEPTH_COMPONENT16,
            /*AMGL_DEPTH_COMPONENT24,*/
            AMGL_DEPTH_COMPONENT32) && format != AMGL_DEPTH_COMPONENT, AMGL_INVALID_OPERATION , gs_context_mng);

        
        const uint32_t binded_pubo_user_range = CONV_KERNEL_TO_USER_SPACE(contxt.buf_bindings.pubo[0].buffer);
        if (!AM_IS_DEFAULT_ID_USER_SPACE(binded_pubo_user_range)) {
            AM_NOT_IMPLEMENTED;

            // AM_SET_ERROR_FLAG_IF(gs_buffer_mng.is_buffer_mapped(binded_pubo_user_range), AMGL_INVALID_OPERATION , gs_context_mng);
            //
            // const size_t pubo_size = gs_buffer_mng.get_buffer_size(binded_pubo_user_range);
            //
            // AM_SET_ERROR_FLAG_IF(pubo_size > texture_buffer_size, AMGL_INVALID_OPERATION, gs_context_mng);
            //
            // const uint32_t type_size_in_bytes = get_type_size(type);
            // AM_SET_ERROR_FLAG_IF(pubo_size % type_size_in_bytes != 0, AMGL_INVALID_OPERATION, gs_context_mng);
        } else {
            const uint32_t tex_kernel = gs_context_mng.get_binded_texture(target);
            
            if (!AM_IS_DEFAULT_ID_KERNEL_SPACE(tex_kernel)) {
                m_textures.set(tex_kernel, target, width, 1u, 1u, internal_format, format);

                initialize_memory(tex_kernel, internal_format, format, type, width, data);
            }
        }
    }

    
    texture_mng::texture_mng(size_t preallocation_size)
    {
        resize(preallocation_size);
    }

    
    void texture_mng::initialize_memory(uint32_t texture, enum_t internal_format, 
        enum_t in_format, enum_t in_type, size_t pixel_count, const void *data)
    {
        static const texture_data_converter converter;

        // const size_t type_size            = get_type_size(in_type);
        // const size_t data_component_count = get_components_count(in_format);
        // const size_t data_pixel_size      = type_size * (detail::is_one_of(in_type, TEXTURE_PACKED_TYPES) ? 1u : data_component_count);

        // const size_t internal_pixel_size  = get_bytes_per_pixel(internal_format);

        // textures::memory_block& mem_block = m_textures.m_memory_blocks[texture];
        // mem_block.resize(pixel_count * internal_pixel_size);
        
        // ubyte_t* mem_block_data_ptr = mem_block.data();
        // for (size_t i = 0u; i < pixel_count; ++i) {
        //     const void* src = (void*)((uintptr_t)data + i * data_pixel_size);
        //     void* dst = mem_block_data_ptr + i * internal_pixel_size;
        //     converter(internal_format, dst, in_format, in_type, src);
        // }
    }

    
    void texture_mng::resize(size_t size) noexcept
    {
        m_textures.resize(size);
    }
}