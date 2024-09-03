#include <iostream>
#include <vector>
#include <math.h>

#define DEBUG // debug mode

#ifdef DEBUG
#include <algorithm>
#include <bitset>
#include <locale.h>
#endif

// #define DIFF // use alternative method

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

class Chunk
{
public:
    Chunk(int l, int m, int r)
        : l(l), m(m), r(r)
    {
        for (int i = l; i < m; i++)
        {
            heights.push_back(i);
        }
        for (int i = m; i >= r; i--)
        {
            heights.push_back(i);
        }
    };
    Chunk(const Chunk &c)
        : l(c.l), m(c.m), r(c.r), heights(c.heights) {};
    Chunk() = default;
    int l, m, r;
    vector<int> heights;

    const int size()
    {
        return heights.size();
    }
};
#ifndef DIFF
class Landfill
{
public:
    Landfill(const vector<int> &heights, Chunk chunk)
        : space(heights.begin(), heights.end()),
          chunk(chunk) {}
    Landfill(const Landfill &L)
        : space(L.space), chunk(L.chunk) {}
    Landfill operator=(const Landfill &L)
    {
        space = L.space;
        chunk = L.chunk;
        return *this;
    }

    vector<int> space;
    Chunk chunk;

    const int
    roughness()
    {
        int roughness = 0;
        for (vector<int>::iterator i = space.begin(); i != space.end() - 1; i++)
        {
            roughness += abs(*i - *(i + 1));
        }
        return roughness;
    }

    void fill(int pos)
    {
        if (pos < 0 || pos > space.size() - chunk.size())
        {
            return;
        }

        for (int h : chunk.heights)
        {
            space[pos++] += h;
        }
    }

#ifdef DEBUG
    void visualize(const Landfill &diff) const
    {
        int maxHeight = max(*max_element(space.begin(), space.end()),
                            *max_element(diff.space.begin(), diff.space.end()));

        for (int i = maxHeight; i > 0; i--)
        {
            for (int j = 0; j < space.size(); j++)
            {
                if (space[j] >= i && diff.space[j] >= i)
                {
                    // Overlap
                    cout << "■";
                }
                else if (space[j] >= i)
                {
                    // Changes
                    cout << "\033[34m■\033[0m"; // Blue for changes
                }
                else
                {
                    cout << " ";
                }
                cout << " ";
            }
            cout << endl;
        }
    }
#endif

private:
};

int minRoughness(Landfill &L)
{
    int possibleSpace = L.space.size() - L.chunk.size() + 1;
    int k = pow(2, possibleSpace);
    int minRoughness = INT_MAX;

#ifdef DEBUG
    Landfill minRough(L);
    int bestMinterm = 0;
    cout << "k: " << k << endl;
#endif

    for (int i = 0; i < k; i++)
    {
        int minterm = i;
        int pos = 0;

        Landfill copy(L);
        do
        {
            copy.fill(minterm & 1 ? pos : -1);
            minterm >>= 1;
            pos++;
        } while (minterm > 0);

        int currentRoughness = copy.roughness();

        if (currentRoughness < minRoughness)
        {
            minRoughness = currentRoughness;
        }
#ifdef DEBUG
        if (currentRoughness == minRoughness)
        {
            minRough = copy;
            bestMinterm = i;
        }
        std::bitset<32> binary(i);
        std::string binaryString = binary.to_string();
        std::string result = binaryString.substr(32 - possibleSpace, possibleSpace);

        cout << "Minterm: " << result << endl;
        copy.visualize(L);
        cout << "Roughness: " << currentRoughness << endl
             << endl;
#endif
    }

#ifdef DEBUG
    cout << "Min Roughness: " << minRoughness << endl
         << "Minterm: " << bestMinterm << endl;
    minRough.visualize(L);
#endif

    return minRoughness;
}
#else

// Alternative Approach
// For the data storage we could use the difference between heights to save space and calculations
// Example:
// heights = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
// chunk = [3, 4, 5, 6, 7]
// could be stored as
// heightsDiff = [1, 1, 1, 1, 1, 1, 1, 1, 1]
// chunkDiff = [1, 1, 1, 1]
// we could then calculate roughness as
// roughness = sum(abs(x) for x in heightsDiff)
// and fill the space as
// for (int i = 0; i < chunkDiff.size(); i++)
// {
//     space[i] += chunkDiff[i];
// }

class LandfillDiff
{
public:
    LandfillDiff(const vector<int> &heights, const Chunk &chunk)
    {
        for (size_t i = 1; i < heights.size(); ++i)
        {
            diffs.push_back(heights[i] - heights[i - 1]);
        }
        for (size_t i = 1; i < chunk.heights.size(); ++i)
        {
            chunkDiffs.push_back(chunk.heights[i] - chunk.heights[i - 1]);
        }
    }

    LandfillDiff(const LandfillDiff &L)
        : diffs(L.diffs), chunkDiffs(L.chunkDiffs) {}
    LandfillDiff operator=(const LandfillDiff &L)
    {
        diffs = L.diffs;
        chunkDiffs = L.chunkDiffs;
        return *this;
    }

    vector<int> diffs;
    vector<int> chunkDiffs;

    int roughness() const
    {
        int roughness = 0;
        for (int diff : diffs)
        {
            roughness += abs(diff);
        }
        return roughness;
    }

    void applyChunk(int pos)
    {
        for (size_t i = 0; i < chunkDiffs.size(); ++i)
        {
            diffs[pos + i] += chunkDiffs[i];
        }
    }

#ifdef DEBUG
    void visualize(const LandfillDiff &diff) const
    {
        vector<int> heights = {0}; // Assume the first height is 0
        for (int d : diffs)
        {
            heights.push_back(heights.back() + d);
        }

        vector<int> diffHeights = {0};
        for (int d : diff.diffs)
        {
            diffHeights.push_back(diffHeights.back() + d);
        }

        int maxHeight = max(*max_element(heights.begin(), heights.end()),
                            *max_element(diffHeights.begin(), diffHeights.end()));

        for (int i = maxHeight; i > 0; i--)
        {
            for (size_t j = 0; j < heights.size(); j++)
            {
                if (heights[j] >= i && diffHeights[j] >= i)
                {
                    // Overlap
                    cout << "■";
                }
                else if (heights[j] >= i)
                {
                    // Changes
                    cout << "\033[34m■\033[0m"; // Blue for changes
                }
                else
                {
                    cout << " ";
                }
                cout << " ";
            }
            cout << endl;
        }
    }
#endif
};

int minRoughness(LandfillDiff &L)
{
    int possibleSpace = L.diffs.size() - L.chunkDiffs.size() + 1;
    int k = pow(2, possibleSpace);
    int minRoughness = INT_MAX;

#ifdef DEBUG
    LandfillDiff minRough(L);
    int bestMinterm = 0;
    cout << "k: " << k << endl;
#endif

    for (int i = 0; i < k; i++)
    {
        int minterm = i;
        int pos = 0;

        LandfillDiff copy(L);
        do
        {
            copy.applyChunk(minterm & 1 ? pos : -1);
            minterm >>= 1;
            pos++;
        } while (minterm > 0);

        int currentRoughness = copy.roughness();

        if (currentRoughness < minRoughness)
        {
            minRoughness = currentRoughness;
        }
#ifdef DEBUG
        if (currentRoughness == minRoughness)
        {
            minRough = copy;
            bestMinterm = i;
        }
        std::bitset<32> binary(i);
        std::string binaryString = binary.to_string();
        std::string result = binaryString.substr(32 - possibleSpace, possibleSpace);

        cout << "Minterm: " << result << endl;
        cout << "Roughness: " << currentRoughness << endl
             << endl;
#endif
    }

#ifdef DEBUG
    cout << "Min Roughness: " << minRoughness << endl
         << "Minterm: " << bestMinterm << endl;
    minRough.visualize(L);
#endif

    return minRoughness;
}
#endif

int main()
{
#ifdef DEBUG
    setlocale(LC_ALL, "en_US.UTF-8");
#endif
    int n;         // Area length
    int l, m, r;   // left, middle, right height of a chunk
    vector<int> h; // Vector of heights

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        h.push_back(x);
    }

    cin >> l >> m >> r;

    Landfill L = {
        h, Chunk(l, m, r)};

    // cout << minRoughness(L);

    // minterm testing
    int minterm;
    while (cin >> minterm)
    {
        int pos = 0;
        Landfill copy(L);
        do
        {
            copy.fill(minterm & 1 ? pos : -1);
            minterm >>= 1;
            pos++;
        } while (minterm > 0);
        copy.visualize(L);
        cout << "Roughness: " << copy.roughness() << endl;
    }

    // fill testing
    // int pos = 0;
    // Landfill fillCopy(L);
    // while (cin >> pos)
    // {
    //     fillCopy.fill(pos);
    //     fillCopy.visualize(L);
    //     cout << "Roughness: " << fillCopy.roughness() << endl;
    // }
}
