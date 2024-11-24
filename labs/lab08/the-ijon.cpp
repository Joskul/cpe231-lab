#include <iostream>
#include <vector>

using namespace std;

int knapSack(int threshold, vector<int> weight, vector<int> val, int end)
{
    if (end == 0 || threshold == 0)
        return 0;
    if (weight[end - 1] > threshold)
        return knapSack(threshold, weight, val, end - 1);

    else
        return max(knapSack(threshold, weight, val, end - 1),
                   val[end - 1] + knapSack(threshold - weight[end - 1], weight, val, end - 1));
}

int main()
{
    int n;
    cin >> n;

    vector<int> val(n), weight(n);
    for (int i = 0; i < n; i++)
    {
        cin >> weight[i] >> val[i];
    }

    int p;
    cin >> p;

    cout << knapSack(p, weight, val, n);
}