#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cstdio>

using namespace std;

struct Functor
{
    Functor() { sum = 0.0; };
    double sum;
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

    // first and last 10%
    auto nb = v.begin() + (size_t) (v.size() * 0.1f);
    auto ne = v.end() - (size_t) (v.size() * 0.1f);

    // max and min 10%
    size_t ns = ne - nb;
    sort(nb, ne);
    nb += (size_t) ns * 0.1f;
    ne -= (size_t) ns * 0.1f;
    
    Functor f = for_each(nb, ne, Functor());
    printf("%.10f\n", f.sum / ns);
}
