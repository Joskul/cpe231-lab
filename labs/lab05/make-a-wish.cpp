#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int maxCrossingSum(vector<int>::iterator begin, vector<int>::iterator mid, vector<int>::iterator end)
{
    int leftSum = INT_MIN, sum = 0;
    for (auto it = mid - 1; it >= begin; --it)
    {
        sum += *it;
        if (sum > leftSum)
            leftSum = sum;
    }

    int rightSum = INT_MIN;
    sum = 0;
    for (auto it = mid; it < end; ++it)
    {
        sum += *it;
        if (sum > rightSum)
            rightSum = sum;
    }

    return leftSum + rightSum;
}

int maxConsecutiveSum(vector<int>::iterator begin, vector<int>::iterator end)
{
    if (end - begin <= 1)
        return *begin;

    auto mid = begin + (end - begin) / 2;

    return max({
        maxConsecutiveSum(begin, mid),  // Left half
        maxConsecutiveSum(mid, end),    // Right half
        maxCrossingSum(begin, mid, end) // Cross the middle
    });
}

int maxConsecutiveSum(vector<int> arr)
{
    return maxConsecutiveSum(arr.begin(), arr.end());
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

    cout << maxConsecutiveSum(arr);
}