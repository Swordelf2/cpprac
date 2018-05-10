#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

using namespace std;

int main()
{
    map<string, map<char, string>> rules;
    string s1, s2;
    char c;
    while ((cin >> s1) && (s1 != "END")) {
        cin >> c >> s2;
        rules[move(s1)][c] = move(s2);
    }

    set<string> final_states;
    while ((cin >> s1) && (s1 != "END")) {
        final_states.insert(move(s1));
    }

    string state;
    cin >> state;
    
    string input;
    cin >> input;

    bool good = true;
    auto it = input.begin();
    for (; it != input.end(); ++it) {
        auto iter = rules.find(state);
        if (iter == rules.end()) {
            good = false;
        } else {
            auto &char_map = iter->second;
            auto iter2 = char_map.find(*it);
            if (iter2 == char_map.end()) {
                good = false;
            } else {
                state = iter2->second;
            }
        }
        if (!good) {
            break;
        }
    }

    if (final_states.find(state) == final_states.end()) {
        good = false;
    }

    if (good) {
        cout << '1' << endl <<
                input.length() << endl <<
                state << endl;
    } else {
        cout << '0' << endl <<
                (it - input.begin()) << endl <<
                state << endl;
    }
}
