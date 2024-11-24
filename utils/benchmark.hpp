#pragma once

#include <chrono>
#include <functional>

// Benchmark function, returns execution time in ms
template <typename Func, typename... Args>
long long timeFunction(Func &&func, Args &&...args)
{
    auto start = std::chrono::high_resolution_clock::now();

    // Invoke the function with provided arguments
    std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return duration;
}