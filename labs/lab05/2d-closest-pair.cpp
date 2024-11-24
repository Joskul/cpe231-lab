#include <cfloat>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

#define x first
#define y second
#define Vec2D pair<int, int>

double dist(Vec2D p1, Vec2D p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

bool compareX(const Vec2D &p1, const Vec2D &p2)
{
    return p1.x < p2.x;
}

bool compareY(const Vec2D &p1, const Vec2D &p2)
{
    return p1.y < p2.y;
}

double bruteForce(vector<Vec2D>::iterator begin, vector<Vec2D>::iterator end)
{
    double minD = DBL_MAX;
    for (auto p1 = begin; p1 < end; p1++)
    {
        for (auto p2 = p1 + 1; p2 < end; p2++)
        {
            minD = min(minD, dist(*p1, *p2));
        }
    }

    return minD;
}

double minStripDist(vector<Vec2D> strip, double d)
{
    double minD = d;
    sort(strip.begin(), strip.end(), compareY);

    for (auto p1 = strip.begin(); p1 < strip.end(); p1++)
    {
        for (auto p2 = p1 + 1; p2 < strip.end() && (p2->y - p1->y) < minD; p2++)
        {
            minD = min(minD, dist(*p1, *p2));
        }
    }

    return minD;
}

double minDist(vector<Vec2D>::iterator begin, vector<Vec2D>::iterator end)
{
    if (end - begin <= 3)
    {
        return bruteForce(begin, end);
    }

    auto mid = begin + ((end - begin) / 2);

    double dl = minDist(begin, mid);
    double dr = minDist(mid, end);

    double d = min(dl, dr);

    vector<Vec2D> strip;
    for (auto p1 = begin; p1 < end; p1++)
    {
        if (abs(p1->x - mid->x) < d)
        {
            strip.push_back(*p1);
        }
    }

    return min(d, minStripDist(strip, d));
}

double minDist(vector<Vec2D> &coords)
{
    sort(coords.begin(), coords.end(), compareX);
    return minDist(coords.begin(), coords.end());
}

int main()
{
    int n;
    cin >> n;

    vector<Vec2D> coords(n);
    for (auto &p : coords)
    {
        cin >> p.x >> p.y;
    }

    cout << fixed << setprecision(3) << minDist(coords);
}