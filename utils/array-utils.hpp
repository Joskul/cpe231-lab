#pragma once
#include "debug.hpp"

#include <vector>
#include <random>
#include <iostream>

template <typename T>
inline void printArray(const std::vector<T> &arr)
{
    for (const auto &x : arr)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

inline std::vector<int> range(int start, int end, int step = 1)
{
    std::vector<int> arr;
    for (int i = start; i < end; i += step)
    {
        arr.push_back(i);
    }
    return arr;
}

#include <vector>
#include <random>

// Generates a sorted array of given size
inline std::vector<int> generateSortedArray(std::size_t size)
{
    std::vector<int> arr(size);
    for (std::size_t i = 0; i < size; ++i)
    {
        arr[i] = static_cast<int>(i); // Cast to int for array values
    }
    return arr;
}

// Generates a reverse-sorted array of given size
inline std::vector<int> generateReverseSortedArray(std::size_t size)
{
    std::vector<int> arr(size);
    for (std::size_t i = 0; i < size; ++i)
    {
        arr[i] = static_cast<int>(size - i - 1); // Cast to int for array values
    }
    return arr;
}

// Generates a random array of given size
inline std::vector<int> generateRandomArray(std::size_t size, int rMul = 10)
{
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 eng(rd());
    long long range = static_cast<long long>(size) * rMul; // Ensure no overflow
    std::uniform_int_distribution<> distr(0, range > INT_MAX ? INT_MAX : static_cast<int>(range));

    for (std::size_t i = 0; i < size; ++i)
    {
        arr[i] = distr(eng); // Fill array with random numbers
    }
    return arr;
}

template <typename T>
T slice(const T &arr, int begin, int end)
{
    T slice(end - begin);
    for (int i = begin; i < end; i++)
    {
        slice[i - begin] = arr[i];
    }
    return slice;
}

inline std::vector<int>::const_iterator maxIt(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end)
{
    if (end - begin <= 1)
    {
        return begin;
    }

    const auto temp1 = maxIt(begin, begin + (end - begin) / 2);
    const auto temp2 = maxIt(begin + (end - begin) / 2, end);

    return *temp1 > *temp2 ? temp1 : temp2;
}