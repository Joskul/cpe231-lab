#pragma once
#include <vector>

inline void insertionSort(std::vector<int> &arr)
{
    for (auto it = arr.begin() + 1; it < arr.end(); it++)
    {
        int key = *it;
        auto j = it - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= arr.begin() && *j > key)
        {
            *(j + 1) = *j;
            j = j - 1;
        }
        *(j + 1) = key;
    }
}