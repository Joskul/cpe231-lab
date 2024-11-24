#include <vector>

int findSpan(std::vector<int> arr)
{
    int n = arr.size();
    int minVal, maxVal;

    for (int i = 1; i <= n - 1; i++)
    {
        if (arr[i] < minVal)
        {
            minVal = arr[i];
        }
        if (arr[i] > maxVal)
        {
            maxVal = arr[i];
        }
    }

    return maxVal - minVal;

    // 2n - 2
}

int Q(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return Q(n - 1) + 2 * n - 1;
    }

    // 2n - 4
}

int main()
{
}