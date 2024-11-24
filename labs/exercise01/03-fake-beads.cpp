#include <iostream>
#include <vector>

using namespace std;

vector<int> distDiff(vector<int> &p)
{
    vector<int> diffs;

    int minDiff = INT_MAX;
    for (int i = 0; i < p.size() - 1; i++)
    {
        if (p[i + 1] - p[i] < minDiff)
        {
            minDiff = p[i + 1] - p[i];
        }
    }

    for (int i = 0; i < p.size(); i++)
    {
        diffs.push_back(p[i] - (p[0] + minDiff * i));
    }
    return diffs;
}

int main()
{
    int n;
    cin >> n;

    vector<int> p(n);
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }

    for (auto i : distDiff(p))
    {
        cout << i << " ";
    }
}