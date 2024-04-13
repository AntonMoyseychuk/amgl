#include "window/window.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "amgl/amgl.hpp"

#include "benchmark.hpp"

#include <filesystem>
#include <algorithm>
#include <numeric>
#include <stdio.h>

#if !defined(NDEBUG) || defined(_DEBUG) || defined(DEBUG)
    static const char* build_type = "debug";
#else
    static const char* build_type = "release";
#endif

struct vec2
{
    float x, y;
};

struct vec3
{
    float x, y, z;
};

struct vertex
{
    vec3 position;
    vec3 normal;
    vec2 texcoord;
};

vertex vbo_data[] = {
    {
        { -1.0f, -1.0f, 0.0f },
        {  0.0f,  0.0f, 1.0f },
        {  0.0f,  0.0f },
    },

    {
        { -1.0f,  1.0f, 0.0f },
        {  0.0f,  0.0f, 1.0f },
        {  0.0f,  1.0f },
    },

    {
        {  1.0f,  1.0f, 0.0f },
        {  0.0f,  0.0f, 1.0f },
        {  1.0f,  1.0f },
    },

    {
        {  1.0f, -1.0f, 0.0f },
        {  0.0f,  0.0f, 1.0f },
        {  1.0f,  0.0f },
    }
};

uint32_t ebo_data[] = {
    0, 2, 1, 0, 3, 2
};

static float ssbo_data[1024u];

struct texture_t
{
    uint8_t* data;
    uint32_t width;
    uint32_t height;
    uint32_t channels;
};

static texture_t tex_obj;


void test() noexcept
{
    static constexpr float ssbo_sub_data[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    uint32_t vao;
    amglGenVertexArrays(1, &vao);
    const bool is_vao = amglIsVertexArray(vao);
    amglBindVertexArray(vao);

    uint32_t vbo;
    amglGenBuffers(1, &vbo);
    const bool is_vbo = amglIsBuffer(vbo);
    amglBindBuffer(AMGL_ARRAY_BUFFER, vbo);
    amglBufferData(AMGL_ARRAY_BUFFER, sizeof(vbo_data), vbo_data, AMGL_STATIC_DRAW);

    amglVertexAttribPointer(0, AMGL_BGRA, AMGL_UNSIGNED_BYTE, true, sizeof(vertex), (void*)offsetof(vertex, position));
    amglEnableVertexAttribArray(0);

    amglVertexAttribPointer(1, 3, AMGL_FLOAT, false, sizeof(vertex), (void*)offsetof(vertex, normal));
    amglEnableVertexAttribArray(1);

    amglVertexAttribPointer(2, 2, AMGL_FLOAT, false, sizeof(vertex), (void*)offsetof(vertex, texcoord));
    amglEnableVertexAttribArray(2);

    uint32_t ebo;
    amglGenBuffers(1, &ebo);
    const bool is_ibo = amglIsBuffer(ebo);
    amglBindBuffer(AMGL_ELEMENT_ARRAY_BUFFER, ebo);
    amglBufferData(AMGL_ELEMENT_ARRAY_BUFFER, sizeof(ebo_data), ebo_data, AMGL_STATIC_DRAW);

    uint32_t ssbo;
    amglGenBuffers(1, &ssbo);
    const bool is_ssbo = amglIsBuffer(ssbo);
    amglBindBuffer(AMGL_SHADER_STORAGE_BUFFER, ssbo);
    amglBufferData(AMGL_SHADER_STORAGE_BUFFER, sizeof(ssbo_data), ssbo_data, AMGL_STATIC_DRAW);
    amglBufferSubData(AMGL_SHADER_STORAGE_BUFFER, 0, sizeof(ssbo_sub_data), ssbo_sub_data);
    amglBindBufferBase(AMGL_SHADER_STORAGE_BUFFER, 2, ssbo);
    amglBindBufferRange(AMGL_SHADER_STORAGE_BUFFER, 2, ssbo, 0, sizeof(ssbo_sub_data));

    const float* buffer_data = (const float*)amglMapBuffer(AMGL_SHADER_STORAGE_BUFFER, AMGL_READ_WRITE);
    amglUnmapBuffer(AMGL_SHADER_STORAGE_BUFFER);

    uint32_t texture;
    amglGenTextures(1, &texture);
    amglBindTexture(AMGL_TEXTURE_2D, texture);
    amglTexImage2D(AMGL_TEXTURE_2D, 0, AMGL_RGBA8UI, tex_obj.width, tex_obj.height, 0, AMGL_RGB, AMGL_UNSIGNED_BYTE, tex_obj.data);
    amglBindTexture(AMGL_TEXTURE_2D, 0);

    const bool is_texture = amglIsTexture(texture);

    amglDeleteTextures(1, &texture);
    amglDeleteBuffers(1, &ssbo);
    amglDeleteBuffers(1, &ebo);
    amglDeleteBuffers(1, &vbo);
    amglDeleteVertexArrays(1, &vao);
}


int main(int argc, char* argv[]) 
{
    // constexpr size_t test_count = 10'000u;
    constexpr size_t test_count = 1u;
    
    std::iota(std::begin(ssbo_data), std::end(ssbo_data), 0.0f);

    const char* texture_data_path = SANDBOX_ASSET_DIR "textures/debug_texture.jpg";
    tex_obj.data = stbi_load(texture_data_path, (int*)&tex_obj.width, (int*)&tex_obj.height, (int*)&tex_obj.channels, 0);
    if (tex_obj.data == nullptr) {
        printf_s("Failed to load texture: %s\n", texture_data_path);
        return -1;
    }

    puts("Benchmarking...\n");
    const float average_time = benchmark(test_count, test);
    printf_s(
        "Total test count: %u\n"
        "Average time (%s): %f ms\n", test_count, build_type, average_time);

    win_framewrk::Window* window = win_framewrk::Window::Get();
    window->Init("Sandbox", tex_obj.width, tex_obj.height);

    const size_t width = std::min(tex_obj.width, window->GetWidth());
    const size_t height = std::min(tex_obj.width, window->GetHeight());

    const uint8_t* data = tex_obj.data;

    while (window->IsOpen()) {
        window->PollEvent();

        for (size_t y = 0; y < height; ++y) {
            for (size_t x = 0; x < width; ++x) {
                const uint8_t* pixel = data + (y * tex_obj.width + x) * 3u;
                window->SetPixelColor(x, y, *(pixel + 0), *(pixel + 1), *(pixel + 2), 255);
            }
        }

        window->PresentPixelBuffer();
        window->FillPixelBuffer(255, 255, 255, 255);
    }

    stbi_image_free(tex_obj.data);

    return 0;
}