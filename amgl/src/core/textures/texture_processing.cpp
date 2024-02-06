#include "amgl/amgl.hpp"

#include "texture_mng.hpp"


static amgl::texture_mng& gs_texture_mng = amgl::texture_mng::instance();


void amglBindTexture(enum_t target, uint32_t texture)
{
    gs_texture_mng.bind_texture(target, texture);
}


void amglDeleteTextures(size_t n, const uint32_t* textures)
{
    gs_texture_mng.delete_textures(n, textures);
}


void amglGenTextures(size_t n, uint32_t* textures) 
{
    gs_texture_mng.gen_textures(n, textures);
}