#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

unordered_map<char, int> shiftTable(string str)
{
    unordered_map<char, int> res;
    for (const auto &c : str)
    {
        res[c]++;
    }

    int m = str.length();
    int size = res.bucket_count();

    for (int i = 0; i < res.bucket_count(); i++)
    {
        res[i] = m;
        for (int j = 0; j < m - 1; j++)
        {
            res[str[j]] = m - 1 - j;
        }
    }

    return res;
}

int findMatch(string str, string word, int &moveCount)
{
    int m = word.length();
    int n = str.length();

    auto shift_table = shiftTable(word);
    int i = m - 1;

    while (i <= n - 1)
    {
        int k = 0; // number of matched characters
        while (k <= m - 1 && word[m - 1 - k] == str[i - k])
        {
            k++;
        }

        if (k == m)
        {
            return i - m + 1;
        }
        else
        {
            i += shift_table.find(str[i]) != shift_table.end() ? shift_table[str[i]] : m;
            moveCount++;
        }
    }
    return -1;
}

int main()
{
    int m, n;
    cin >> m >> n;

    string ticket;
    string match;
    cin >> ticket >> match;

    int moveCount = 0;

    int matchIndex = findMatch(ticket, match, moveCount);
    cout << ((matchIndex == -1) ? "NO " : "YES ") << moveCount << " " << matchIndex << endl;
}