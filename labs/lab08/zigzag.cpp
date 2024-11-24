#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> initializeDP(int size)
{
    return vector<pair<int, int>>(size, {1, 1});
}

void computeZigzagDP(const vector<int> &arr, vector<pair<int, int>> &dp)
{
    int total = arr.size();
    for (int i = 1; i < total; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] < arr[i])
            {
                dp[i].first = max(dp[i].first, dp[j].second + 1);
            }
            if (arr[j] > arr[i])
            {
                dp[i].second = max(dp[i].second, dp[j].first + 1);
            }
        }
    }
}

int main()
{
    int total;
    cin >> total;

    vector<int> arr(total);
    for (int &x : arr)
    {
        cin >> x;
    }

    vector<pair<int, int>> dp = initializeDP(total);

    computeZigzagDP(arr, dp);
    for (const auto &p : dp)
    {
        cout << p.first << " ";
    }
    cout << '\n';
    for (const auto &p : dp)
    {
        cout << p.second << " ";
    }
}
