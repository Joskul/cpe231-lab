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

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &x : arr)
    {
        cin >> x;
    }

    quickSort(arr.data(), arr.data() + n);

    for (const int &x : arr)
    {
        cout << x << " ";
    }
    cout << endl;
}
