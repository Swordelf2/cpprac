#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

void process(const vector<int> &v, list<int> &lst)
{
    vector<int> my_v(v);
    sort(my_v.begin(), my_v.end());
    auto new_end = unique(my_v.begin(), my_v.end());

    auto it = my_v.begin();
    for (; it != new_end && *it <= 0; ++it) {}
    if (it == new_end) {
        return;
    }

    auto l_it = lst.begin();
    int pos = 1;
    for (; l_it != lst.end(); ++pos) {
        if (pos == *it) {
            l_it = lst.erase(l_it);
            ++it;
            if (it == new_end) {
                break;
            }
        } else {
            ++l_it;
        }
    }

    cout << endl;
}

int main()
{
    int a;
    vector<int> v;
    list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    while (cin >> a) {
        v.push_back(a);
    }

    process(v, l);
    for (auto it = l.begin(); it != l.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;
}
