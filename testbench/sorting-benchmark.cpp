#define DEBUG

#include "../utils/debug.hpp"

#include <vector>

#include "../utils/sorting-benchmark.hpp"

#include "../algorithms/sorting/merge-sort.hpp"
#include "../algorithms/sorting/heap-sort.hpp"
#include "../algorithms/sorting/quick-sort.hpp"
#include "../algorithms/sorting/pancake-sort.hpp"
#include "../algorithms/sorting/insertion-sort.hpp"
#include "../algorithms/sorting/counting-sort.hpp"
#include "../algorithms/sorting/bubble-sort.hpp"

using namespace std;

void stdSortWrapper(vector<int> &arr) { sort(arr.begin(), arr.end()); }

int main()
{
    vector<pair<string, void (*)(vector<int> &)>> sortingAlgorithms = {
        {"Merge Sort", mergeSortWrapper},
        {"Heap Sort", heapSort},
        {"Quick Sort (Lomuto)", quickSortLomuto},
        {"Quick Sort (Hoare)", quickSortHoare},
        {"Pancake Sort", pancakeSort},
        {"Insertion Sort", insertionSort},
        {"Counting Sort", countingSort},
        {"Bubble Sort", bubbleSort},
        {"Standard Sort", stdSortWrapper}};

    vector<int> inputSizes;
    for (int i = 0; i <= 18; i++)
    {
        inputSizes.push_back(pow(2, i));
    }

    benchmarkSortingAlgorithms(sortingAlgorithms, inputSizes, "results.csv", 3);
};