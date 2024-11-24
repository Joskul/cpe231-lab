#include <iostream>
#include <vector>

using namespace std;

int *hoarePartition(int *begin, int *end)
{
    int pivot = *begin;
    int *lPtr = begin - 1;
    int *rPtr = end;

    while (true)
    {
        do
        {
            lPtr++;
        } while (*lPtr < pivot);

        do
        {
            rPtr--;
        } while (*rPtr > pivot);

        if (lPtr >= rPtr)
            return rPtr;

        swap(*lPtr, *rPtr);
    }
}

void quickSort(int *begin, int *end)
{
    if (begin < end - 1)
    {
        int *split = hoarePartition(begin, end);
        quickSort(begin, split + 1);
        quickSort(split + 1, end);
    }
}

bool printUnique(vector<int> arr)
{
    bool res = true;
    quickSort(arr.data(), arr.data() + arr.size());
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] != arr[i + 1])
        {
            cout << arr[i] << " ";
        }
    }
    return true;
}

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &x : arr)
    {
        cin >> x;
    }

    printUnique(arr);
}
