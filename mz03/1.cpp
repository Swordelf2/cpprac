#include <iostream>
#include <vector>
#include <list>

using namespace std;

void process(const vector<int> &v, list<int> &l, size_t step)
{
    auto l_it = l.begin();
    auto v_it = v.begin();
    for (; v_it < v.end() && l_it != l.end(); v_it += step, ++l_it) {
        *l_it = *v_it;
    }

    for (auto l_rit = l.rbegin(); l_rit != l.rend(); ++l_rit) {
        cout << *l_rit << endl;
    }
}

int main()
{
    vector<int> v;
    list<int> l;
    int a;
    while (cin >> a) {
        v.push_back(a);
    }
    l.push_back(5);
    l.push_back(10);
    process(v, l, 3);
}
