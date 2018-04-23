#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <cctype>

using namespace std;

int main()
{
    vector<pair<unsigned char, string>> rules;
    char c;
    while (cin >> c) {
        string s;
        cin >> s;
        rules.push_back({c, s});
    }

    set<unsigned char> reachable = {'S'};
    bool added = true;
    while (added) {
        added = false;
        vector<unsigned char> to_insert;
        for (auto &N : reachable) {
            if (isupper(N)) {
                for (auto &rule : rules) {
                    if (rule.first == N) {
                        string &s = rule.second;
                        for (auto &c : s) {
                            if (reachable.find(c) == reachable.end()) {
                                added = true;
                                to_insert.push_back(c);
                            }
                        }
                    }
                }
            }
        }
        for (auto &c : to_insert) {
            reachable.insert(c);
        }
        to_insert.clear();

    }

    for (auto &rule : rules) {
        // check if all chars are in the set
        bool good = true;
        if (reachable.find(rule.first) != reachable.end()) {
            for (auto &c : rule.second) {
                if (reachable.find(c) == reachable.end()) {
                    good = false;
                    break;
                }
            }
        } else {
            good = false;
        }

        if (good) {
            cout << rule.first << ' ' << rule.second << endl;
        }
    }
}
