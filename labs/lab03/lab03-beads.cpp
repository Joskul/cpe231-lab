#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>

// #define DEBUG

using namespace std;

vector<bool> binary(int nBit, int n)
{
    vector<bool> bin(nBit, 0);
    int i = nBit - 1;
    while (n >= 0 && i >= 0)
    {
        bin[i] = n % 2;
        n /= 2;
        i--;
    }

    return bin;
}

string slice(string str, vector<bool> bin)
{
    string slice;
    for (int i = 0; i < bin.size(); i++)
    {
        if (bin[i])
        {
            slice.append(str.substr(i, 1));
        }
    }
    return slice;
}

bool isPalindrome(string str)
{
    if (str.length() <= 1)
    {
        return false;
    }
    bool isPal = true;

    for (int i = 0; i < str.length() / 2; i++)
    {
        if (str[i] != str[str.length() - 1 - i])
        {
            isPal = false;
            break;
        }
    }

#ifdef DEBUG
    if (isPal)
    {
        cout << str << endl;
    }
#endif
    return isPal;
}

int hashFunction(string str)
{
    int k = pow(2, str.length());

    vector<string> pList;

    for (int i = 0; i < k; i++)
    {
        vector<bool> bin = binary(str.length(), i);
        string s = slice(str, bin);
        if (isPalindrome(s) && find(pList.begin(), pList.end(), s) == pList.end())
        {
            pList.push_back(s);
        }
    }

    return pList.size();
}

int main()
{
    string str;
    cin >> str;

    cout << hashFunction(str);

    return 0;
}