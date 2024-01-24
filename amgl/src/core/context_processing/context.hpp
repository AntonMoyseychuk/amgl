#pragma once
#include "amgl/amgl.hpp"

namespace amgl
{
    class context
    {
    public:
        static constexpr size_t MAX_VERTEX_ATTRIB_BINDINGS                  = 16u;
        
        static constexpr size_t MAX_VERTEX_BUFFER_BINDINGS                  = 1u;
        static constexpr size_t MAX_ELEMENT_BUFFER_BINDINGS                 = 1u;
        static constexpr size_t MAX_COPY_READ_BUFFER_BINDINGS               = 1u;
        static constexpr size_t MAX_COPY_WRITE_BUFFER_BINDINGS              = 1u;
        static constexpr size_t MAX_DISPATCH_INDIRECT_BUFFER_BINDINGS       = 1u;
        static constexpr size_t MAX_DRAW_INDIRECT_BUFFER_BINDINGS           = 1u;
        static constexpr size_t MAX_PIXEL_PACK_BUFFER_BINDINGS              = 1u;
        static constexpr size_t MAX_PIXEL_UNPACK_BUFFER_BINDINGS            = 1u;
        static constexpr size_t MAX_QUERY_BUFFER_BINDINGS                   = 1u;
        static constexpr size_t MAX_TEXTURE_BUFFER_BINDINGS                 = 1u;
        static constexpr size_t MAX_UNIFORM_BUFFER_BINDINGS                 = 36u;
        static constexpr size_t MAX_SHADER_STORAGE_BUFFER_BINDINGS          = 8u;
        static constexpr size_t MAX_ATOMIC_COUNTER_BUFFER_BINDINGS          = 1u;
        static constexpr size_t MAX_TRANSFORM_FEEDBACK_BUFFER_BINDINGS      = 4u;
        
        static constexpr size_t MAX_UNIFORM_LOCATIONS                       = 1024u;
        static constexpr size_t MAX_TEXTURE_IMAGE_UNITS                     = 16u;

    private:
        // struct depth_range_t
        // {
        //     float near  = 0.0f;
        //     float far   = 1.0f;
        // };
        //
        // struct color_mask_t
        // {
        //     bool red    = true;
        //     bool green  = true;
        //     bool blue   = true;
        //     bool alpha  = true;
        // };
        //
        // struct rect_t
        // {
        //     int32_t x       = 0;
        //     int32_t y       = 0;
        //     uint32_t width  = 0u;
        //     uint32_t height = 0u;
        // };
        //
        // struct color_t
        // {
        //     float red   = 0.0f;
        //     float green = 0.0f;
        //     float blue  = 0.0f;
        //     float alpha = 0.0f;
        // };

        struct binding_point
        {
            operator uint32_t() const noexcept { return buffer; }

            uint32_t buffer = AM_DEFAULT_INTERNAL_ID;
        };

        struct binding_point_range
        {
            size_t offset = 0u;
            size_t size   = 0u;
        };

        struct bindings
        {
            template<size_t SIZE>
            using binding_points = std::array<binding_point, SIZE>;
            template<size_t SIZE>
            using bp_ranges = std::array<binding_point_range, SIZE>;

            bp_ranges<MAX_VERTEX_BUFFER_BINDINGS>                   vbo_ranges;    // vertex buffer object binding point ranges
            bp_ranges<MAX_ELEMENT_BUFFER_BINDINGS>                  ebo_ranges;    // element buffer object binding point ranges
            bp_ranges<MAX_UNIFORM_BUFFER_BINDINGS>                  ubo_ranges;    // uniform buffer object binding point ranges   
            bp_ranges<MAX_SHADER_STORAGE_BUFFER_BINDINGS>          ssbo_ranges;    // shader storage buffer object binding point ranges  
            bp_ranges<MAX_TEXTURE_BUFFER_BINDINGS>                  tbo_ranges;    // texture buffer object binding point ranges
            bp_ranges<MAX_COPY_READ_BUFFER_BINDINGS>               crbo_ranges;    // copy read buffer object binding point ranges
            bp_ranges<MAX_COPY_WRITE_BUFFER_BINDINGS>              cwbo_ranges;    // copy write buffer object binding point ranges
            bp_ranges<MAX_DISPATCH_INDIRECT_BUFFER_BINDINGS>       dibo_ranges;    // dispatch indirect buffer object binding point ranges
            bp_ranges<MAX_DRAW_INDIRECT_BUFFER_BINDINGS>          dribo_ranges;    // draw indirect buffer object binding point ranges
            bp_ranges<MAX_PIXEL_PACK_BUFFER_BINDINGS>              ppbo_ranges;    // pixel pack buffer object binding point ranges
            bp_ranges<MAX_PIXEL_UNPACK_BUFFER_BINDINGS>            pubo_ranges;    // pixel unpack buffer object binding point ranges
            bp_ranges<MAX_QUERY_BUFFER_BINDINGS>                    qbo_ranges;    // query buffer object binding point ranges
            bp_ranges<MAX_TRANSFORM_FEEDBACK_BUFFER_BINDINGS>      tfbo_ranges;    // transform feedback buffer object binding point ranges   
            bp_ranges<MAX_ATOMIC_COUNTER_BUFFER_BINDINGS>          acbo_ranges;    // atomic counter buffer object binding point ranges
            binding_points<MAX_VERTEX_BUFFER_BINDINGS>                     vbo;    // vertex buffer object binding points
            binding_points<MAX_ELEMENT_BUFFER_BINDINGS>                    ebo;    // element buffer object binding points
            binding_points<MAX_UNIFORM_BUFFER_BINDINGS>                    ubo;    // uniform buffer object binding points   
            binding_points<MAX_SHADER_STORAGE_BUFFER_BINDINGS>            ssbo;    // shader storage buffer object binding points   
            binding_points<MAX_TEXTURE_BUFFER_BINDINGS>                    tbo;    // texture buffer object binding points
            binding_points<MAX_COPY_READ_BUFFER_BINDINGS>                 crbo;    // copy read buffer object binding points
            binding_points<MAX_COPY_WRITE_BUFFER_BINDINGS>                cwbo;    // copy write buffer object binding points
            binding_points<MAX_DISPATCH_INDIRECT_BUFFER_BINDINGS>         dibo;    // dispatch indirect buffer object binding points
            binding_points<MAX_DRAW_INDIRECT_BUFFER_BINDINGS>            dribo;    // draw indirect buffer object binding points
            binding_points<MAX_PIXEL_PACK_BUFFER_BINDINGS>                ppbo;    // pixel pack buffer object binding points
            binding_points<MAX_PIXEL_UNPACK_BUFFER_BINDINGS>              pubo;    // pixel unpack buffer object binding points
            binding_points<MAX_QUERY_BUFFER_BINDINGS>                      qbo;    // query buffer object binding points
            binding_points<MAX_TRANSFORM_FEEDBACK_BUFFER_BINDINGS>        tfbo;    // transform feedback buffer object binding points   
            binding_points<MAX_ATOMIC_COUNTER_BUFFER_BINDINGS>            acbo;    // atomic counter buffer object binding points
            
            uint32_t vao                              = AM_DEFAULT_INTERNAL_ID;    // vertex array object
        };
        

    public:
        bindings bindings;
        
        mutable enum_t error_status = AMGL_NO_ERROR;

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
