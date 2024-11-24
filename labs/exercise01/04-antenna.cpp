#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

double getEfficiency(pair<int, int> pos_a, pair<int, int> pos_b)
{
    return (double)abs(pos_a.first - pos_a.second) / (double)(abs(pos_a.first) + abs(pos_a.second)) +
           (double)abs(pos_b.first - pos_b.second) / (double)(abs(pos_b.first) + abs(pos_b.second));
}

pair<int, int> getBestPos(vector<pair<int, int>> pos)
{
    pair<int, int> bestPos = pos[0];
    double bestEfficiency = INFINITY;
    for (int i = 0; i < pos.size(); i++)
    {
        double totalEfficiency = 0;
        for (int j = i + 1; j < pos.size(); j++)
        {
            double efficiency = getEfficiency(pos[i], pos[j]);
            totalEfficiency += efficiency;
        }

        // NO DIVISION NEEDED
        if (totalEfficiency < bestEfficiency)
        {
            bestEfficiency = totalEfficiency;
            bestPos = pos[i];
        }
    }
    return bestPos;
}

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> pos(n);
    for (int i = 0; i < n; i++)
    {
        cin >> pos[i].first >> pos[i].second;
    }

    cout << getBestPos(pos).first << " " << getBestPos(pos).second;
    return 0;
}