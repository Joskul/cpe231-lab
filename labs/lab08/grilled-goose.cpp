#include <iostream>
#include <vector>

using namespace std;

vector<bool> possibleCombination(const vector<int> &pattern, int n)
{
    vector<bool> res(n, false);
    res[0] = true;

    for (int i = 0; i < n; i++)
    {
        if (res[i])
        {
            for (auto p : pattern)
            {
                if (i + p < n)
                {
                    res[i + p] = true;
                }
            }
        }
    }

    return res;
}

int main()
{
    int x, n;
    cin >> x >> n;

    vector<int> arr(n);
    for (auto &e : arr)
    {
        cin >> e;
    }

    vector<bool> u = possibleCombination(arr, x);

    int res = -1;
    for (int i = x - 1; i >= 0; i--)
    {
        if (!u[i])
        {
            res = i;
            break;
        }
    }

    cout << res;
}