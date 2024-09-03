#include <iostream>
#include <vector>
#include <cmath>
#include <climits> // For INT_MAX
#include <algorithm>
#include <locale.h>

using namespace std;

vector<bool> binary(int nBit, int n)
{
    vector<bool> bin(nBit, 0);
    int i = nBit - 1;
    while (n && i >= 0)
    {
        bin[i] = n % 2;
        n /= 2;
        i--;
    }
    return bin;
}

void visualize(vector<int> space, vector<int> diff)
{
    int maxHeight = max(*max_element(space.begin(), space.end()),
                        *max_element(diff.begin(), diff.end()));

    for (int i = maxHeight; i > 0; i--)
    {
        for (int j = 0; j < space.size(); j++)
        {
            if (space[j] && diff[j] >= i)
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

int main()
{
    int Left, Mid, Right, llen;
    int rough = INT_MAX; // Initialize to maximum possible value

    setlocale(LC_ALL, "en_US.UTF-8");

    cin >> llen;
    vector<int> dirt(llen);

    for (int i = 0; i < llen; i++)
    {
        cin >> dirt[i];
    }

    cin >> Left >> Mid >> Right;

    int soillen = Right - Left + 1;

    // Generate a symmetric soil addition pattern around Mid
    vector<int> addsoil(soillen, 0);
    int midIndex = Mid - Left;
    for (int i = 0; i <= midIndex; i++)
    {
        addsoil[i] = i; // Increment up to the middle
    }
    for (int i = midIndex + 1; i < soillen; i++)
    {
        addsoil[i] = soillen - i - 1; // Decrement after the middle
    }

    int probability = (llen - soillen) + 1;
    int set = pow(2, probability);

    vector<bool> bestMinterm;
    int minterm = 0;
    vector<int> bestDirt = dirt;

    for (int i = 1; i < set; i++)
    {
        vector<bool> BinarySet = binary(probability, i);
        vector<int> tempDirt = dirt;
        int lessrough = 0; // Reset lessrough to 0 for each iteration

        // Apply binary set for different combinations
        for (int j = 0; j < probability; j++)
        {
            if (BinarySet[j] == 1)
            {
                for (int k = 0; k < soillen; k++)
                {
                    if (j + k < llen)
                    {
                        tempDirt[j + k] += addsoil[k];
                    }
                }
            }
        }

        // Calculate roughness for the current configuration
        for (int j = 0; j < llen - 1; j++)
        {
            lessrough += abs(tempDirt[j] - tempDirt[j + 1]);
        }

        // Keep the minimum roughness found
        if (lessrough < rough)
        {
            rough = lessrough;
            minterm = i;
            bestMinterm = BinarySet;
            bestDirt = tempDirt;
        }
    }

    cout << "Minimum Roughness: " << rough << endl;
    cout << "Minterm: " << minterm << endl;

    for (int i = 0; i < probability; i++)
    {
        cout << bestMinterm[i];
    }
    cout << endl;
    visualize(bestDirt, dirt);
    return 0;
}