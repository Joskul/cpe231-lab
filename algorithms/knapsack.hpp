#include <vector>

// Knapsack Algorithm : Dynamic Programming Approach
inline std::vector<int> knapsackDP(const std::vector<int> &costs, const std::vector<int> &values, int maxVal)
{
    std::vector<int> dp(maxVal + 1, 0);
    for (int item = 0; item < costs.size(); ++item)
    {
        for (int capacity = maxVal; capacity >= costs[item]; --capacity)
        {
            dp[capacity] = std::max(dp[capacity], dp[capacity - costs[item]] + values[item]);
        }
    }
    return dp;
}