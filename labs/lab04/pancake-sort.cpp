#include <iostream>
#include <vector>

using namespace std;

int maxIndex(const vector<int> &arr, int i)
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

void flip(vector<int> &arr, const int i)
{
    for (int k = 0; k <= (int)((i - 1) / 2); k++)
    {
        swap(arr[k], arr[i - k]);
    }
}

void pancakeSort(vector<int> &arr)
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

int main()
{
    int n; // number of elements
    cin >> n;

    vector<int> arr(n);
    for (auto &i : arr)
    {
        cin >> i;
    }

    pancakeSort(arr);

    for (const auto &i : arr)
    {
        cout << i << " ";
    }
}
