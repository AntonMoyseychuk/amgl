#pragma once
#include "context.hpp"


namespace amgl
{
    class context_mng
    {
    public:
        static context_mng& instance() noexcept
        {
            static context_mng manager;
            return manager;
        }

        context_mng(const context_mng&) = delete;
        context_mng& operator=(const context_mng&) = delete;
        
        const context& get_context() const noexcept { return m_context; }
        context& get_context() noexcept { return m_context; }
        
        void update_error_flag(enum_t error) const noexcept;
        enum_t get_error_flag_and_invalidate_state() const noexcept;
        enum_t get_error_flag() const noexcept;


        /*----------------------- Buffer Manager related API -----------------------*/

        /// @brief 
        /// @param array Vertex array object in the kernel range [0, UINT32_MAX - 1]
        /// @param vbo Vertex buffer object in the kernel range [0, UINT32_MAX - 1]
        /// @param ebo Vertex buffer object in the kernel range [0, UINT32_MAX - 1]
        /// @param vbo_idx 'vbo' binding point
        /// @param ebo_idx 'ebo' binding point
        /// @note Doesn't check 'array', 'vbo' and 'ebo' validity
        void bind_vertex_array(uint32_t array, uint32_t vbo, uint32_t ebo, size_t vbo_idx, size_t ebo_idx) noexcept;

        /// @brief 
        /// @param array Array object in the kernel range [0, UINT32_MAX - 1]
        /// @note Doesn't check 'array' validity
        void bind_vertex_array(uint32_t array) noexcept;
        
        /// @brief 
        /// @return Vertex array object in kernel range [0, UINT32_MAX - 1] if there is any binded vertex array, otherwise AM_DEFAULT_KERNEL_ID
        uint32_t get_binded_vertex_array() const noexcept;

        /// @brief 
        /// @param target Buffer target
        /// @param buffer Buffer object in the kernel range [0, UINT32_MAX - 1]
        /// @param index Buffer binding point
        /// @note Doesn't check 'target', and 'buffer' validity
        void bind_target_buffer(enum_t target, uint32_t buffer, size_t index) noexcept;

        /// @brief 
        /// @param target Buffer target
        /// @param index Buffer binding point
        /// @return Buffer object in kernel range [0, UINT32_MAX - 1] if there is any binding of target, otherwise AM_DEFAULT_KERNEL_ID
        uint32_t get_binded_buffer(enum_t target, size_t index) const noexcept;

        /// @brief 
        /// @param target Buffer target
        /// @param index Buffer binding point
        /// @param range Buffer range
        /// @note Doesn't check 'target', and 'buffer' validity
        void bind_target_buffer_range(enum_t target, size_t index, const buffer_range& range) noexcept;

        /// @brief 
        /// @param target Buffer target
        /// @param index Buffer binding point
        /// @note Doesn't check 'target' validity
        const buffer_range& get_binded_buffer_range(enum_t target, size_t index) const noexcept;


        /*----------------------- Texture Manager related API -----------------------*/

        /// @brief 
        /// @param target Texture target
        /// @param texture Texture object
        /// @note Doesn't check 'target', and 'texture' validity
        void bind_target_texture(enum_t target, uint32_t texture) noexcept;

        /// @brief 
        /// @param target Texture target
        /// @return Texture object in kernel range [0, UINT32_MAX - 1] if there is any binding of target, otherwise AM_DEFAULT_KERNEL_ID
        uint32_t get_binded_texture(enum_t target) const noexcept;

    private:
        context_mng() = default;

    public:
        context m_context;
    };
}