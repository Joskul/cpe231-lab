#pragma once
#include <vector>
#include <unordered_map>

inline void countingSort(std::vector<int> &arr)
{
    std::unordered_map<int, int> count(arr.size());
    std::vector<int> output(arr.size());

    for (int i = 0; i < arr.size(); i++)
    {
        count[arr[i]]++;
    }

    for (int i = 1; i < count.size(); i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = arr.size() - 1; i >= 0; i--)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < arr.size(); i++)
    {
        arr[i] = output[i];
    }
}