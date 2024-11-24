#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    for (; i < n1 && j < n2; k++)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
    }

    while (i < n1)
    {
        arr[k++] = L[i++];
    }
    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

void bottomUpMergeSort(vector<int> &arr)
{
    int n = arr.size();
    if (n < 2)
    {
        return;
    }
    for (int i = 1; i < n; i *= 2)
    {
        for (int j = 0; j < n - i; j += 2 * i)
        {
            if (n < j + (2 * i))
            {
                merge(arr, j, j + i - 1, n - 1);
            }
            else
            {
                merge(arr, j, j + i - 1, j + (2 * i) - 1);
            }
        }
    }
}

int main()
{
    int n; // number of elements in the array
    cin >> n;

    vector<int> arr(n);
    for (auto &x : arr)
    {
        cin >> x;
    }

    bottomUpMergeSort(arr);

    for (const auto &x : arr)
    {
        cout << x << " ";
    }
}