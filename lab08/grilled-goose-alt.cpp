#include <iostream>
#include <vector>

using namespace std;

vector<int> knapsack(const vector<int> &costs, const vector<int> &values, int maxVal)
{
    vector<int> dp(maxVal + 1, 0);
    for (int item = 0; item < costs.size(); ++item)
    {
        for (int capacity = maxVal; capacity >= costs[item]; --capacity)
        {
            dp[capacity] = max(dp[capacity], dp[capacity - costs[item]] + values[item]);
        }
    }
    return dp;
}
int findMaxValue(const vector<int> &dp)
{
    int res = 0;
    for (int i = 1; i < dp.size(); i++)
    {
        res = max(dp[i], dp[i - 1]);
    }
    return res;
}

int main()
{
    int x, n;
    cin >> x;
    cin >> n;

    vector<int> cost(n);

    for (int i = 0; i < n; i++)
    {
        cin >> cost[i];
    }

    vector<int> dp = knapsack(cost, value, x);
    int result = findMaxValue(dp);

    cout << result;
    return 0;
}
