#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ALT

// using DFS approach

// visited product bitmasking
#ifndef ALT
double maxCost(const vector<vector<double>> &costs, int visitedProd = 0, int state = 0)
{
    if (state == costs.size())
    {
        return 0;
    }

    double maxVal = 0;

    for (int productID = 0; productID < costs.size(); productID++)
    {
        if (!(visitedProd & (1 << productID)))
        {
            double currentVal = costs[state][productID] + maxCost(costs, visitedProd | (1 << productID), state + 1);
            maxVal = maxVal > currentVal ? maxVal : currentVal;
        }
    }
    return maxVal;
}
#else
vector<int> range(int start, int end, int step = 1)
{
    vector<int> arr;
    for (int i = start; i <= end; i += step)
    {
        arr.push_back(i);
    }
    return arr;
}

double maxCost(const vector<vector<double>> &costs)
{
    vector<int> goods = range(0, costs.size() - 1);
    double maxCost = 0;

    do
    {
        double cost = 0;
        for (int i = 0; i < goods.size(); i++)
        {
            cost += costs[i][goods[i]];
        }
        maxCost = maxCost > cost ? maxCost : cost;
    } while (next_permutation(goods.begin(), goods.end()));

    return maxCost;
}
#endif

int main()
{
    int n; // number of products
    cin >> n;

    vector<vector<double>> costs(n, vector<double>(n)); // cost of products for each state
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> costs[i][j];
        }
    }

    cout << maxCost(costs) << endl;
    return 0;
}