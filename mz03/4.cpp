#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cstdio>

using namespace std;

constexpr double PERCENT_FIRST = 0.1;
constexpr double PERCENT_SECOND = 0.1;
constexpr int PRECISION = 10;

struct Functor
{
    double sum = 0.0;
    void operator()(const double &d)
    {
        sum += d;
    }
};

int main()
{
    double a;
    vector<double> v;
    while (cin >> a) {
        v.push_back(a);
    }

    // first and last PERCENT_FIRST %
    auto nb = v.begin() + (v.size() * PERCENT_FIRST);
    auto ne = v.end() - (v.size() * PERCENT_FIRST);

    // max and min PERCENT_SECOND %
    size_t ns = ne - nb;
    sort(nb, ne);
    nb += ns * PERCENT_SECOND;
    ne -= ns * PERCENT_SECOND;
    ns = ne - nb;

    Functor f = for_each(nb, ne, Functor());
    cout << fixed << setprecision(PRECISION) << f.sum / ns << endl;
}
