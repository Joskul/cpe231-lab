#include <iostream>
#include <string>

using namespace std;

int main()
{
    // Get user input
    string str;
    cin >> str;

    char start, end;
    cin >> start >> end;

    int minLen;
    cin >> minLen;

    int cNum = 0;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != start)
        {
            continue;
        }
        for (int j = i + minLen - 1; j < str.length(); j++)
        {
            if (str[j] == end)
            {
                // cout << str.substr(i, j - i + 1) << endl;
                cNum++;
            }
        }
    }
    cout << cNum;
}
