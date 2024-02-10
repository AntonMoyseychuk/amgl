#include "SDL.h"

#include "amgl/amgl.hpp"

#include "benchmark.hpp"

#include <stdio.h>

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

float ssbo_data[1024u];

void test() noexcept
{
    constexpr float ssbo_sub_data[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    for (size_t i = 0; i < 1'000'000; ++i) {
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
        amglBindTexture(AMGL_TEXTURE_1D, texture);
        amglTexImage1D(AMGL_TEXTURE_1D, 0, AMGL_RGBA, 100, 0, AMGL_RGBA, AMGL_FLOAT, nullptr);
        amglBindTexture(AMGL_TEXTURE_1D, 0);

        const bool is_texture = amglIsTexture(texture);

        amglDeleteTextures(1, &texture);
        amglDeleteBuffers(1, &ssbo);
        amglDeleteBuffers(1, &ebo);
        amglDeleteBuffers(1, &vbo);
        amglDeleteVertexArrays(1, &vao);
    }
}


int main(int argc, char* argv[]) 
{
    for (size_t i = 0; i < sizeof(ssbo_data) / sizeof(ssbo_data[0]); ++i) {
        ssbo_data[i] = (float)i;
    }

    #if !defined(NDEBUG) || defined(_DEBUG) || defined(DEBUG)
        constexpr size_t test_count = 1u;
    #else
        constexpr size_t test_count = 30u;
    #endif

    benchmark(test_count, test);

    // if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    //     puts(SDL_GetError());
    //     return -1;
    // }
    //
    // SDL_Window* window = SDL_CreateWindow("AMGL Sandbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    // if (window == nullptr) {
    //     puts(SDL_GetError());
    //     return -1;
    // }
    //
    // bool running = true;
    // while (running) {
    //     SDL_Event event;
    //     while (SDL_PollEvent(&event)) {
    //         switch (event.type)  {
    //         case SDL_QUIT:
    //             running = false;
    //             break;
    //         }
    //     }
    // }
    //
    // SDL_DestroyWindow(window);
    // SDL_Quit();

    return 0;
}