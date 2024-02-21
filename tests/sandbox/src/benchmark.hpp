#pragma once

#include <chrono>
#include <ratio>

/// @brief 
/// @tparam Func Function type
/// @tparam ...Args Function arg types
/// @param test_count Count of tests
/// @param func Function for benchmarking
/// @param ...args Function args
/// @return average time in milliseconds
template<typename Func, typename... Args>
inline float benchmark(size_t test_count, const Func& func, const Args&... args)
{
    if(test_count == 0) {
        puts("test_count must be greater than 0\n");
        return -1.0f;
    }

    float total_time = 0.0f;
    for (size_t i = 0; i < test_count; ++i) {
        const auto start = std::chrono::steady_clock::now();
        func(std::forward<Args>(args)...);
        const auto end = std::chrono::steady_clock::now();

        total_time += std::chrono::duration<float, std::milli>(end - start).count();
    }

    return total_time / test_count;
}