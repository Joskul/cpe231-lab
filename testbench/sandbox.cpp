// #define DEBUG

#include "../utils/debug.hpp"

#include <iostream>
#include <vector>
#include "../utils/array-utils.hpp"

#include "../utils/benchmark.hpp"

#include "../algorithms/sorting/bubble-sort.hpp"
#include "../algorithms/sorting/insertion-sort.hpp"
#include "../algorithms/sorting/merge-sort.hpp"
#include "../algorithms/sorting/quick-sort.hpp"
#include "../algorithms/sorting/heap-sort.hpp"

using namespace std;

int riddle(vector<int> A)
{
    printArray(A);
    if (A.size() == 1)
    {
        return A[0];
    }
    else
    {
        int n = A.size();
        int temp = riddle(slice(A, 0, n - 1));
        if (temp <= A[n - 1])
        {
            return temp;
        }
        else
        {
            return A[n - 1];
        }
    }
}

void stdSortWrapper(vector<int> &arr) { sort(arr.begin(), arr.end()); }

int main()
{
    vector<pair<string, void (*)(vector<int> &)>> sortingAlgorithms;
    // sortingAlgorithms.push_back(make_pair("Bubble Sort", bubbleSort));
    // sortingAlgorithms.push_back(make_pair("Insertion Sort", insertionSort));
    sortingAlgorithms.push_back(make_pair("Merge Sort", mergeSortWrapper));
    sortingAlgorithms.push_back(make_pair("Quick Sort (Lomuto)", quickSortLomuto));
    sortingAlgorithms.push_back(make_pair("Quick Sort (Hoare)", quickSortHoare));
    sortingAlgorithms.push_back(make_pair("Heap Sort", heapSort));
    sortingAlgorithms.push_back(make_pair("Standard Sort", stdSortWrapper));

    vector<pair<string, long long>>
        benchmarkResults;

    vector<int> testSizes = {
        100, 1000, 10000, 100000, 1000000};

    for (const auto &size : testSizes)
    {
        vector<int> testArr(generateSortedArray(size));

        for (const auto &algorithm : sortingAlgorithms)
        {
            vector<int> copy = testArr;
            benchmarkResults.push_back(make_pair(algorithm.first, timeFunction(algorithm.second, copy)));
        }
    }

    for (const auto &result : benchmarkResults)
    {
        cout << result.first << ": " << result.second << endl;
    }
}