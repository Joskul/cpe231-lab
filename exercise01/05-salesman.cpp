#include <algorithm>
#include <iostream>
#include <vector>

// #define DEBUG

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

class Graph
{
    int n;                   // number of vertices
    vector<vector<int>> adj; // adjacency matrix

    vector<string> names; // map from country name to index

public:
    Graph(int n) : n(n), adj(n, vector<int>(n, INT_MIN)) {}

    void addEdge(string src, string dst, int w)
    {
        if (find(names.begin(), names.end(), src) == names.end())
        {
            names.push_back(src);
        }
        if (find(names.begin(), names.end(), dst) == names.end())
        {
            names.push_back(dst);
        }

        int i = find(names.begin(), names.end(), src) - names.begin(),
            j = find(names.begin(), names.end(), dst) - names.begin();
        adj[i][j] = w;
        adj[j][i] = w;
    }

    int calculateCost(vector<int> &circuit)
    {
        int cost = 0;
        for (int i = 0; i < circuit.size() - 1; i++)
        {
            cost += adj[circuit[i]][circuit[i + 1]];
        }
        return cost;
    }

    vector<string> longestCircuit(int &cost)
    {
        cost = INT_MIN;
        vector<int> longestCircuit;
        vector<int> circuit = range(1, n - 1);

        do
        {
            circuit.insert(circuit.begin(), 0);
            circuit.push_back(0);

            int currentCost = calculateCost(circuit);
#ifdef DEBUG
            cout << "Circuit: ";
            visualizeCircuit(circuit);
            cout << "Cost: " << currentCost << endl;
#endif
            if (currentCost > cost)
            {
                cost = currentCost;
                longestCircuit = circuit;
            }

            circuit.pop_back();
            circuit.erase(circuit.begin());
        } while (next_permutation(circuit.begin(), circuit.end()));

        vector<string> circuitString;
        for (int i = 0; i < longestCircuit.size(); i++)
        {
            circuitString.push_back(names[longestCircuit[i]]);
        }

        return circuitString;
    }

#ifdef DEBUG
    void showEntries()
    {
        for (auto it = index.begin(); it != index.end(); it++)
        {
            cout << it->first << " " << it->second << endl;
        }
    }

    void showWeights()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << getKey(index, i) << " " << getKey(index, j) << " " << adj[i][j] << " ";
            }
            cout << endl;
        }
    }

    void visualizeCircuit(const vector<int> &circuit)
    {
        for (int i = 0; i < circuit.size(); i++)
        {
            cout << getKey(index, circuit[i]) << " ";
        }
        cout << endl;
    }
#endif
};

int main()
{
    int n, p; // number of countries and flights
    cin >> n >> p;

    Graph g(n + 1); // create a graph with n vertices

    for (int i = 0; i < p; i++)
    {
        string u, v;
        int w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int cost;

    for (string c : g.longestCircuit(cost))
    {
        cout << c << " ";
    }
    cout << endl
         << cost;
    return 0;
}