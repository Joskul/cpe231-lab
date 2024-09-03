#include <iostream>
#include <vector>

// #define DEBUG

using namespace std;

struct Node
{
    string id;
    int score;
};

void selectionSort(vector<Node> &seats)
{
    for (int i = 0; i < seats.size(); i++)
    {
        for (int j = i + 1; j < seats.size(); j++)
        {
            if (seats[i].score < seats[j].score)
            {
                seats.insert(seats.begin() + i, seats[j]);
                seats.erase(seats.begin() + j + 1);
            }
        }
    }
}

int main()
{
    int n; // number of seats
    cin >> n;

    vector<Node> seats(n);

    for (int i = 0; i < n; i++)
    {
        cin >> seats[i].id >> seats[i].score;
    }

    selectionSort(seats);

    for (int i = 0; i < n; i++)
    {
        cout << seats[i].id << endl;
    }
    return 0;
}