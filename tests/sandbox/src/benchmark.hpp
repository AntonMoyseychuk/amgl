#pragma once

#include <chrono>
#include <ratio>
#include <stdio.h>

#include <cassert>

#define CLOCK_NOW() std::chrono::steady_clock::now()
#define DURATION(begin, end) std::chrono::duration<float, std::milli>((end) - (begin)).count()


template<typename Func, typename... Args>
inline void benchmark(size_t test_count, const Func& func, const Args&... args)
{
    assert(test_count > 0 && "test_count must be greater than 0");

    #if !defined(NDEBUG) || defined(_DEBUG) || defined(DEBUG)
        const char* build_type = "debug";
    #else
        const char* build_type = "release";
    #endif

    float total_time = 0.0f;
    for (size_t i = 0; i < test_count; ++i) {
        const auto start = CLOCK_NOW();
        func(std::forward<Args>(args)...);
        const auto end = CLOCK_NOW();

        const float test_duration = DURATION(start, end);

        printf_s("Benchmark %u time (%s): %f ms\n", i, build_type, test_duration);

        total_time += test_duration;
    }

    const float average_time = total_time / test_count;

    printf_s("Average time (%s): %f ms\n", build_type, average_time);
}