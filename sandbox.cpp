#define DEBUG
#include "algorithms/knapsack.hpp"

#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<pair<int, int>> wtVal(n);
    for (int i = 0; i < n; i++)
    {
        cin >> wtVal[i].first >> wtVal[i].second;
    }

    int p;
    cin >> p;

    cout << knapSackGA(wtVal, p);
}