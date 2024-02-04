#include "amgl/amgl.hpp"

#include "texture_mng.hpp"


static amgl::texture_mng& gs_texture_mng = amgl::texture_mng::instance();


void amglDeleteTextures(size_t n, const uint32_t* textures)
{
    gs_texture_mng.delete_textures(n, textures);
}


void amglGenTextures(size_t n, uint32_t* textures) 
{
    gs_texture_mng.gen_textures(n, textures);
}