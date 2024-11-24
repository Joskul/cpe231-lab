#include <iostream>
#include <vector>

using namespace std;

// Comparison functions
bool larger(int a, int b)
{
    return a > b;
}
bool smaller(int a, int b)
{
    return a < b;
}

// smaller -> max heap
// larger -> min heap
void heapify(vector<int> &arr, bool (*comp)(int, int) = larger, int root = 0, int end = -1)
{
    if (end == -1)
    {
        end = arr.size(); // Default value if no end is passed
    }

    for (int i = (end - 1) / 2; i >= root; i--)
    {
        int k = i;      // Start at parent node
        int v = arr[k]; // Value of the node
        bool heap = false;

        while (!heap && 2 * k + 1 < end)
        {
            int j = 2 * k + 1;
            if (j + 1 < end && comp(arr[j], arr[j + 1]))
            {
                j++;
            }

            if (!comp(v, arr[j]))
            {
                heap = true;
            }
            else
            {
                arr[k] = arr[j];
                k = j;
            }
        }
        arr[k] = v;
    }
}

// HeapSort function
void heapSort(vector<int> &arr)
{
    int n = arr.size();

    heapify(arr, larger);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);

        heapify(arr, larger, 0, i);
    }
}

int main()
{
    int n; // Number of elements
    cin >> n;

    vector<int> arr(n);
    for (auto &x : arr)
    {
        cin >> x;
    }

    // Build a min heap
    heapify(arr, larger);

    for (const auto &x : arr)
    {
        cout << x << " ";
    }
    cout << endl;

    heapSort(arr);
    for (const auto &x : arr)
    {
        cout << x << " ";
    }

    return 0;
}
