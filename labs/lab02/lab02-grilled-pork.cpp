#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int comp_counter = 0; // Comparison counter
int mul_counter = 0;  // Multiplication counter
int add_counter = 0;  // Addition counter

int main()
{
    vector<int> p; // Vector of package sizes
    for (int i = 0; i < 4; i++)
    {
        int val;
        cin >> val;
        p.push_back(val);
    }

    int n;
    cin >> n;

    // pd[i] = {0,1,2,...n/p[i]}
    vector<vector<int>> pd(4); // Initialize pd with the same size as p
    for (int i = 0; i < 4; i++)
    {
        int val = n / p[i];
        for (int j = 0; j <= val; j++)
        {
            pd[i].push_back(j);
        }
    }

    vector<int> universe; // Universe vector of {0,1,2,...n}
    for (int i = 0; i <= n; i++)
    {
        universe.push_back(i);
    }

    // Nested loops to iterate over all possible combinations
    for (auto a : pd[0])
    {
        for (auto b : pd[1])
        {
            for (auto c : pd[2])
            {
                for (auto d : pd[3])
                {
                    int val = a * p[0] + b * p[1] + c * p[2] + d * p[3];
                    add_counter += 3;
                    mul_counter += 4;
                    comp_counter += 1;
                    if (val <= n)
                    {
                        auto it = find(universe.begin(), universe.end(), val);
                        if (it != universe.end()) // Ensure the value exists before erasing
                        {
                            universe.erase(it);
                        }
                    }
                }
            }
        }
    }

    // universe is now a vector of impossible combinations

    cout << *max_element(universe.begin(), universe.end()) << endl;

    cout << "Number of additions: " << add_counter << endl;
    cout << "Number of multiplications: " << mul_counter << endl;
    cout << "Number of comparisons: " << comp_counter << endl;

    return 0;
}
