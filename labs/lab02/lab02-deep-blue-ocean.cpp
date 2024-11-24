#include <iostream>

using namespace std;

int mul_counter = 0;

int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        mul_counter++;
        return n * factorial(n - 1);
    }
}

int main()
{
    int n, v; // Number of students and professors
    cin >> n >> v;

    int s[n]; // Vector of students
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

    int p; // Number of students with mental problems :(
    cin >> p;

    int e[p]; // Vector of students
    for (int i = 0; i < p; i++)
    {
        cin >> e[i];
    }

    cout << factorial(n - 1) * (n - p) << endl; // Perform the calculation and output
    mul_counter++;

    cout << "Number of multiplications: " << mul_counter;
}