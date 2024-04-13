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


void amglGetTextureSubImage(uint32_t texture, uint32_t level, size_t xoffset, size_t yoffset, size_t zoffset, 
    size_t width, size_t height, size_t depth, enum_t format, enum_t type, size_t buf_size, void* pixels)
{
    gs_texture_mng.get_texture_sub_image(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, buf_size, pixels);
}


bool amglIsTexture(uint32_t texture)
{
    return gs_texture_mng.is_texture(texture);
}


void amglTexImage1D(enum_t target, uint32_t level, enum_t internal_format, size_t width, uint32_t border, 
    enum_t format, enum_t type, const void* data)
{
    gs_texture_mng.tex_image_1d(target, level, internal_format, width, border, format, type, data);
}


void amglTexImage2D(enum_t target, uint32_t level, enum_t internal_format, size_t width, size_t height, uint32_t border, 
    enum_t format, enum_t type, const void* data)
{
    gs_texture_mng.tex_image_2d(target, level, internal_format, width, height, border, format, type, data);
}