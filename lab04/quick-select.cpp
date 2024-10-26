#include <iostream>
#include <vector>

using namespace std;

vector<int>::iterator lomutoPartition(vector<int>::iterator begin, vector<int>::iterator end)
{
    auto p = *begin;
    auto s = begin;
    for (auto i = begin + 1; i < end; i++)
    {
        if (*i < p)
        {
            s++;
            swap(*s, *i);
        }
    }
    swap(*begin, *s);
    return s;
}

// Returns the value of the kth smallest element
int quickSelect(vector<int>::iterator begin, vector<int>::iterator end, size_t k)
{
    auto s = lomutoPartition(begin, end);
    size_t p = s - begin;
    if (p == k - 1)
    {
        return *s;
    }
    else if (p > k - 1)
    {
        return quickSelect(begin, s, k);
    }
    else
    {
        return quickSelect(s + 1, end, k - 1 - p);
    }
}

int quickSelect(vector<int> arr, size_t k)
{
    return quickSelect(arr.begin(), arr.end(), k);
}

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (auto &i : arr)
    {
        cin >> i;
    }

    int k;
    cin >> k;

    cout << quickSelect(arr, k);
}