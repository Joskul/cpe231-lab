#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Descending comparison function
bool descending(int a, int b)
{
    return a > b;
}

int main()
{
    int n;         // Number of trees
    vector<int> p; // Vector of pot heights
    vector<int> t; // Vector of tree heights

    vector<int> h;     // Vector of total heights
    int sumOfDiff = 0; // Answer

    // Get input
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x; // Pot height
        cin >> x;
        p.push_back(x);
    }
    for (int i = 0; i < n; i++)
    {
        int x; // Tree height
        cin >> x;
        t.push_back(x);
    }

    // Sort the vectors
    sort(p.begin(), p.end());             // Ascending
    sort(t.begin(), t.end(), descending); // Descending

    // Calculate the total heights
    for (int i = 0; i < n; i++)
    {
        h.push_back(p[i] + t[i]);
    }
    // Sort the heights
    sort(h.begin(), h.end());

    // Output
    for (int i = 0; i < n - 1; i++)
    {
        sumOfDiff += h[i + 1] - h[i];
    }

    cout << sumOfDiff; // Print answer

    return 0;
}

/*
h could be simplified using some kind of binary tree to reduce the sorting time.
ex. std::multiset
*/