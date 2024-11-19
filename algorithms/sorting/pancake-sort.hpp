#pragma once
#include <vector>

inline int maxIndex(const std::vector<int> &arr, int i)
{
    int maxId = 0;
    for (int k = 1; k <= i; k++)
    {
        if (arr[k] > arr[maxId])
        {
            maxId = k;
        }
    }

    return maxId;
}

inline void flip(std::vector<int> &arr, const int i)
{
    for (int k = 0; k <= (int)((i - 1) / 2); k++)
    {
        std::swap(arr[k], arr[i - k]);
    }
}

inline void pancakeSort(std::vector<int> &arr)
{
    for (int i = arr.size() - 1; i >= 1; i--)
    {
        int maxId = maxIndex(arr, i);
        if (maxId != i)
        {
            if (maxId != 0)
            {
                flip(arr, maxId);
            }
            flip(arr, i);
        }
    }
}