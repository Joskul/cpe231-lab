#include <iostream>
#include <vector>

using namespace std;

class HashTable
{
private:
    int buckets;
    vector<string> table;

    int hash(string key)
    {
        int val = 0;
        for (const auto &c : key)
        {
            val += c - 'A' + 1;
        }

        return val % buckets;
    }

public:
    HashTable(int size) : buckets(size), table(size, "NULL") {};

    void insert(string key)
    {
        int hashVal = hash(key);
        while (table[hashVal] != "NULL")
        {
            hashVal = (hashVal + 1) % buckets;
        }

        table[hashVal] = key;
    }

    void print()
    {
        for (const string &str : table)
        {
            cout << str << " ";
        }
    }
};

int main()
{
    int z, n;
    cin >> z >> n;
    HashTable table(z);

    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        table.insert(s);
    }

    table.print();
}