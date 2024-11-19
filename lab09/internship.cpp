#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int findRank(const vector<vector<int>> &preferences, int woman, int currentMan, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (preferences[currentMan][i] == woman)
            return i;
    }
    return -1;
}

vector<int> stableMarriage(const vector<vector<int>> &womanRank, const vector<vector<int>> &manRank)
{
    int n = womanRank.size();
    queue<int> freeMen;                // Queue of free men
    vector<int> currentPartner(n, -1); // Current partner for each woman
    vector<int> currentIndex(n, 0);    // Track which woman each man has proposed to

    // Initialize the queue with all men
    for (int i = 0; i < n; i++)
    {
        freeMen.push(i);
    }

    // Main loop to process proposals
    while (!freeMen.empty())
    {
        int man = freeMen.front(); // Get the next free man
        freeMen.pop();

        int preferredWoman = manRank[man][currentIndex[man]]; // Get the next woman to propose to

        if (currentPartner[preferredWoman] == -1)
        {                                         // If woman is free
            currentPartner[preferredWoman] = man; // Engage them
        }
        else
        {                                                                                          // Woman is already engaged
            int rankCur = findRank(womanRank, man, preferredWoman, n);                             // Rank of current man
            int rankPrev = findRank(womanRank, currentPartner[preferredWoman], preferredWoman, n); // Rank of previous man

            if (rankCur < rankPrev)
            {                                                 // If current man is preferred over previous
                freeMen.push(currentPartner[preferredWoman]); // Previous man becomes free
                currentPartner[preferredWoman] = man;         // Engage new pair
            }
            else
            {
                currentIndex[man]++; // Move to next choice for this man
                freeMen.push(man);   // Reinsert this man into the queue for future proposals
            }
        }
    }

    return currentPartner; // Return the final matches
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> internRank(n, vector<int>(n)); // Intern ranking each company gave
    for (auto &pref : internRank)
    {
        for (auto &rank : pref)
        {
            cin >> rank;
        }
    }

    vector<vector<int>> companyRank(n, vector<int>(n)); // Company ranking each intern gave
    for (auto &pref : companyRank)
    {
        for (auto &rank : pref)
        {
            cin >> rank;
        }
    }

    auto res = stableMarriage(companyRank, internRank); // Find stable matches

    for (int i = 0; i < res.size(); i++)
    {
        cout << i << " " << res[i] << endl; // Output results
    }

    return 0;
}