#include "pch.hpp"
#include "texture_mng.hpp"

static_assert(AM_INIT_TEX_COUNT > 0, "AM_INIT_TEXTURE_COUNT must be greater than 0");


namespace amgl
{
    texture_mng::texture_mng(size_t preallocation_size)
    {
    }


    void texture_mng::gen_textures(size_t n, uint32_t *textures) noexcept
    {
    }
    
    
    void texture_mng::delete_textures(size_t n, const uint32_t *textures) noexcept
    {
    }
}