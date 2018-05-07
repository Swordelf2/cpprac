#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    string s;
    map<string, int> labels;
    vector<string> input;
    int cnt = 1;
    while (cin >> s) {
        if (s[s.length() - 1] == ':') {
            labels[s.substr(0, s.length() - 1)] = cnt;
        } else {
            input.push_back(s);
            ++cnt;
        }
    }
    for (const string &el : input) {
        auto f = labels.find(el);
        if (f == labels.end()) {
            cout << el << endl;
        } else {
            cout << f->second << endl;
        }
    }
}
