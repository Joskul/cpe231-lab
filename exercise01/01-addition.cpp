#include <iostream>
#include <vector>
#define DEBUG

using namespace std;

vector<int> range(int start, int end, int step = 1)
{
    vector<int> arr;
    for (int i = start; i <= end; i += step)
    {
        arr.push_back(i);
    }
    return arr;
}

bool isOdd(int x)
{
    return x % 2;
}

int sum(const vector<int> &arr)
{
    int sum = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    return sum;
}

int countSubarrays(int start, int end, int target, vector<int> &sol, vector<vector<int>> &ans)
{
#ifdef DEBUG
    for (auto i : sol)
    {
        cout << i << " + ";
    }
    cout << "\b \b\b \b= " << sum(sol) << endl;
#endif
    int count = 0;
    if (sum(sol) == target) // Solution found
    {
        ans.push_back(sol);
        return 1;
    }

    for (int i = start; i <= end; i++)
    {
        sol.push_back(i);
        count += countSubarrays(i + 1, min(target - sum(sol), end), target, sol, ans);
        sol.pop_back();
    }

    return count;
}

int main()
{
    int x, y;
    cin >> x >> y;

    vector<vector<int>> subArrays;
    vector<int> temp;

    int oddCount = 0, evenCount = 0;

    countSubarrays(1, x, y, temp, subArrays);

    for (auto i : subArrays)
    {
        for (auto j : i)
        {
            oddCount += isOdd(j);
            evenCount += !isOdd(j);
        }
    }
    cout << oddCount << endl
         << evenCount << endl;

    return 0;
}
