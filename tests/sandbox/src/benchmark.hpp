#pragma once

#include <chrono>
#include <ratio>
#include <stdio.h>

template<typename Func, typename... Args>
inline void benchmark(size_t test_count, const Func& func, const Args&... args)
{
    if(test_count == 0) {
        puts("test_count must be greater than 0\n");
        return;
    }

    using namespace std::chrono;

    puts("Benchmarking...\n");

    #if !defined(NDEBUG) || defined(_DEBUG) || defined(DEBUG)
        const char* build_type = "debug";
    #else
        const char* build_type = "release";
    #endif

    float total_time = 0.0f;
    for (size_t i = 0; i < test_count; ++i) {
        const auto start = steady_clock::now();
        func(std::forward<Args>(args)...);
        const auto end = steady_clock::now();

        const float test_duration = duration<float, std::milli>(end - start).count();

        printf_s("Benchmark %zu time (%s): %f ms\n", i, build_type, test_duration);

        total_time += test_duration;
    }

    const float average_time = total_time / test_count;

    printf_s("Average time (%s): %f ms\n", build_type, average_time);
}