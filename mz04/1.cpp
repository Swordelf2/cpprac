#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

struct Cmp
{
    bool operator() (const pair<string, int> &a, const pair<string, int> &b)
    {
        return a.second == b.second ? a.first < b.first : a.second > b.second;
    }
};

int percent(int a, int b)
{
    int half = (b - 1) / 2 + 1;
    return (a * 100 + half) / b;
}

int main()
{
    int n;
    map<string, int> m = {
        pair<string, int>("napoleon", 0),
        pair<string, int>("loshad", 0),
        pair<string, int>("balyk", 0),
        pair<string, int>("zhir", 0),
        pair<string, int>("grusha", 0) };
    cin >> n;
    string s;
    int ov_count = 0;
    int bad = 0;
    while (cin >> s) {
        auto it = m.find(s);
        if (it != m.end()) {
            ++(*it).second;
        } else {
            ++bad;
        }
        ++ov_count;
    }


    vector<pair<string, int>> v(m.size());
    copy(m.begin(), m.end(), v.begin());
    for (auto it = v.begin(); it != v.end(); ++it) {
        it->second = percent(it->second, ov_count);
    }
    sort(v.begin(), v.end(), Cmp());
    
    cout << percent(ov_count, n) << endl;
    cout << percent(bad, ov_count) << endl;
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << it->first << ' ' << it->second << endl;
    }
}
