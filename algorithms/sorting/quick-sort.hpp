#pragma once
#include <vector>
// #include <algorithm> // For std::swap

template <typename T>
void swap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
}

// Lomuto partition scheme
inline std::size_t lomutoPartition(std::vector<int> &arr, std::size_t low, std::size_t high)
{
    int pivot = arr[high];
    std::size_t i = low - 1;

    for (std::size_t j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Hoare partition scheme
inline std::size_t hoarePartition(std::vector<int> &arr, std::size_t low, std::size_t high)
{
    int pivot = arr[low];
    std::size_t i = low - 1, j = high + 1;

    while (true)
    {
        do
        {
            i++;
        } while (arr[i] < pivot && i < high); // Ensure i does not exceed high

        do
        {
            j--;
        } while (arr[j] > pivot && j > low); // Ensure j does not go below low

        if (i >= j)
            return j;

        std::swap(arr[i], arr[j]);
    }
}

// Recursive QuickSort implementation
inline void quickSort(std::vector<int> &arr, std::size_t low, std::size_t high, std::size_t (*partition)(std::vector<int> &, std::size_t, std::size_t) = lomutoPartition)
{
    if (low < high)
    {
        std::size_t pi = partition(arr, low, high);

        // Adjust recursion bounds based on partition scheme
        if (partition == lomutoPartition)
        {
            quickSort(arr, low, pi - 1, partition);
            quickSort(arr, pi + 1, high, partition);
        }
        else
        { // hoarePartition
            quickSort(arr, low, pi, partition);
            quickSort(arr, pi + 1, high, partition);
        }
    }
}

// Wrapper functions
inline void quickSortLomuto(std::vector<int> &arr)
{
    if (!arr.empty())
    {
        quickSort(arr, 0, arr.size() - 1, lomutoPartition);
    }
}

inline void quickSortHoare(std::vector<int> &arr)
{
    if (!arr.empty())
    {
        quickSort(arr, 0, arr.size() - 1, hoarePartition);
    }
}
