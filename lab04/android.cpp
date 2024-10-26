#include <iostream>
#include <vector>

using namespace std;

// factorial
int fact(int n)
{
    int res = 1;
    for (int i = 2; i <= n; i++)
    {
        res *= i;
    }
    return res;
}

int findSmaller(const string &str, int index)
{
    int count = 0;
    for (int i = index + 1; i < str.size(); i++)
    {
        count += str[i] < str[index];
    }
    return count;
}

int findRank(string str)
{
    int n = str.size();
    int rank = 1;
    int mul = fact(n);
    int count;

    for (int i = 0; i < n; i++)
    {
        mul /= (n - i);

        count = findSmaller(str, i);
        rank += count * fact(n - i - 1);
    }

    return rank;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<string> chkArr(m);
    for (auto &chk : chkArr)
    {
        cin >> chk;
    }

    for (const auto &chk : chkArr)
    {
        cout << findRank(chk) << endl;
    }
}