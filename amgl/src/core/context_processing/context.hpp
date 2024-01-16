#pragma once
#include "amgl/amgl.hpp"

namespace amgl
{
    class context
    {
    public:
        // struct depth_range_t
        // {
        //     float near  = 0.0f;
        //     float far   = 1.0f;
        // };

        // struct color_mask_t
        // {
        //     bool red    = true;
        //     bool green  = true;
        //     bool blue   = true;
        //     bool alpha  = true;
        // };

        // struct rect_t
        // {
        //     int32_t x       = 0;
        //     int32_t y       = 0;
        //     uint32_t width  = 0u;
        //     uint32_t height = 0u;
        // };

        // struct color_t
        // {
        //     float red   = 0.0f;
        //     float green = 0.0f;
        //     float blue  = 0.0f;
        //     float alpha = 0.0f;
        // };

        struct bindings
        {
            uint32_t vao    = DEFAULT_INTERNAL_ID;   // vertex array object
            
            uint32_t vbo    = DEFAULT_INTERNAL_ID;   // vertex buffer object
            uint32_t acbo   = DEFAULT_INTERNAL_ID;   // atomic counter buffer object
            uint32_t crbo   = DEFAULT_INTERNAL_ID;   // copy read buffer object
            uint32_t cwbo   = DEFAULT_INTERNAL_ID;   // copy write buffer object
            uint32_t dibo   = DEFAULT_INTERNAL_ID;   // dispatch indirect buffer object
            uint32_t dribo  = DEFAULT_INTERNAL_ID;   // draw indirect buffer object
            uint32_t ebo    = DEFAULT_INTERNAL_ID;   // element buffer object
            uint32_t ppbo   = DEFAULT_INTERNAL_ID;   // pixel pack buffer object
            uint32_t pubo   = DEFAULT_INTERNAL_ID;   // pixel unpack buffer object
            uint32_t qbo    = DEFAULT_INTERNAL_ID;   // query buffer object
            uint32_t ssbo   = DEFAULT_INTERNAL_ID;   // shader storage buffer object
            uint32_t tbo    = DEFAULT_INTERNAL_ID;   // texture buffer object
            uint32_t tfbo   = DEFAULT_INTERNAL_ID;   // transform feedback buffer object
            uint32_t ubo    = DEFAULT_INTERNAL_ID;   // uniform buffer object
        };

    public:
        static constexpr uint32_t MAX_VERTEX_ATTRIBS_COUNT = 16u;


    public:
        bindings bindings;
        enum_t error_status = AMGL_NO_ERROR;

        // enum_t active_texture_unit = AMGL_TEXTURE0;

        // color_t blend_color;

        // enum_t blend_equation_rgb = AMGL_FUNC_ADD;
        // enum_t blend_equation_alpha = AMGL_FUNC_ADD;

        // enum_t blend_src_rgb = AMGL_ONE;
        // enum_t blend_src_alpha = AMGL_ONE;
        // enum_t blend_dst_rgb = AMGL_ZERO;
        // enum_t blend_dst_alpha = AMGL_ZERO;

        // color_t clear_color;
        // color_mask_t color_mask;

        // debugproc debug_callback = {};
        // void* debug_user_param = nullptr;

        // depth_range_t depth_range;
        // float depth_clear_value = 1.0f;
        // enum_t depth_func = AMGL_LESS;

        // enum_t face_culling_mode = AMGL_BACK;
        // enum_t front_face_orientation_mode = AMGL_CCW;

        // float line_width = 1.0f;

        // enum_t logic_op_mode = AMGL_COPY;
            
        // enum_t last_error = AMGL_NO_ERROR;

        // enum_t polygon_mode = AMGL_FILL;
            
        // float point_size = 1.0f;

        // rect_t scissor_rect;

        // id_t shader_program = 0;

        // state_flags_t state_flags;

        // rect_t viewport_rect;
    };
}
