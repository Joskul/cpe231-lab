#pragma once
#include <vector>

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

inline int lomutoPartition(std::vector<int> &arr, int low, int high)
{
    int pivot = arr[high];

    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
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

inline int hoarePartition(std::vector<int> &arr, int low, int high)
{
    int pivot = arr[low];
    int i = low - 1, j = high + 1;

    while (true)
    {

        // Find leftmost element greater than or
        // equal to pivot
        do
        {
            i++;
        } while (arr[i] < pivot);

        // Find rightmost element smaller than
        // or equal to pivot
        do
        {
            j--;
        } while (arr[j] > pivot);

        // If two pointers met.
        if (i >= j)
            return j;

        swap(arr[i], arr[j]);
    }
}

// Recursive QuickSort implementation
inline void quickSort(std::vector<int> &arr, int low, int high, int (*partition)(std::vector<int> &, int, int) = lomutoPartition)
{
    if (low < high)
    {
        // Partition the array and get the index of the pivot
        int pi = partition(arr, low, high);

        // Recursively sort elements before partition and after partition
        quickSort(arr, low, pi - (partition == lomutoPartition), partition);
        quickSort(arr, pi + 1, high, partition);
    }
}

// Wrapper function to handle the quicksort
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