#pragma once


namespace amgl
{
    class texture_mng
    {
    public:
        static texture_mng& instance() noexcept
        {
            static texture_mng manager(AM_INIT_TEX_COUNT);
            return manager;
        }

        texture_mng(const texture_mng&) = delete;
        texture_mng& operator=(const texture_mng&) = delete;


        void gen_textures(size_t n, uint32_t *textures) noexcept;
        void delete_textures(size_t n, const uint32_t *textures) noexcept;

    private:
        texture_mng() = default;
        texture_mng(size_t preallocation_size);

        void resize(size_t size) noexcept;

    private:

    };
}