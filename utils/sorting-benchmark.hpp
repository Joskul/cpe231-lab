#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "debug.hpp"
#include "benchmark.hpp"

#include "array-utils.hpp"

// Benchmark function
inline void benchmarkSortingAlgorithms(
    const std::vector<std::pair<std::string, void (*)(std::vector<int> &)>> &sortingAlgorithms,
    const std::vector<int> &inputSizes,
    const std::string &outputFileName,
    int iterations)
{
    // Open result file
    std::ofstream resultFile(outputFileName);
    if (!resultFile)
    {
        DB(std::cerr << "Failed to open " << outputFileName << " for writing." << std::endl;)
        return;
    }

    // Write headers
    resultFile << "Input Size";
    for (const auto &[name, _] : sortingAlgorithms)
    {
        resultFile << "," << name;
    }
    resultFile << std::endl;

    // Generate test cases for each input size
    std::unordered_map<int, std::vector<std::vector<int>>> testCases;
    for (int size : inputSizes)
    {
        std::vector<std::vector<int>> cases;
        for (int i = 0; i < iterations; ++i)
        {
            cases.push_back(generateReverseSortedArray(size));
        }
        testCases[size] = cases;
    }

    // Run benchmarks for each input size
    for (int size : inputSizes)
    {
        resultFile << size;
        for (const auto &[name, func] : sortingAlgorithms)
        {
            unsigned long long totalRuntime = 0;

            // Reuse the same test cases for this size
            for (const auto &testCase : testCases[size])
            {
                auto copy = testCase; // Copy to avoid modifying the original
                DB(std::cout << "Running " << name << " on " << size
                             << " elements." << std::endl;)

                totalRuntime += timeFunction(func, copy);
            }

            unsigned long long averageRuntime = totalRuntime / iterations;
            resultFile << "," << averageRuntime;
        }
        resultFile << std::endl;
    }

    resultFile.close();
    DB(std::cout << "Benchmark results written to " << outputFileName << std::endl;)
}