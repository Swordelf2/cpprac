#include <iostream>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <limits>

using namespace std;

constexpr size_t char_cnt = numeric_limits<unsigned char>::max();

inline int& add_to_map(map<string, int> &state_map, string &&s, int &state_cnt)
{
    auto insert_res = state_map.insert(move(make_pair(move(s), state_cnt)));
    if (insert_res.second)
    {
        // the insertion took place
        ++state_cnt;
    }
    return insert_res.first->second;
}

int main()
{
    int state_cnt = 0;
    map<string, int> state_map; // a mapping of states to integers - [0, state_cnt)

    vector<vector<int>> rules; // this is a matrix [state x char] -> [array of states]
    // set of final states
    set<int> final_states;

    // Read rules one by one, if new state is found, add it to the map
    // each rule is inserted into the rules matrix

    string s1, s2;
    string c;
    while ((cin >> s1) && (s1 != "END")) {
        cin >> c >> s2;
        const int &state1 = add_to_map(state_map, move(s1), state_cnt);
        const int &state2 = add_to_map(state_map, move(s2), state_cnt);
        unsigned char uc;
        if (c == "eps") {
            uc = 0;
        } else {
            uc = static_cast<unsigned char>(c[0]);
        }
        rules.resize(state_cnt * char_cnt);
        rules[state1 * char_cnt + uc].push_back(state2);
    }

    while ((cin >> s1) && (s1 != "END")) {
        final_states.insert(state_map[s1]);
    }

    /*** breadth first search ***/

    auto used = make_unique<bool[]>(state_cnt); 
    auto used_next = make_unique<bool[]>(state_cnt);
    queue<int> q;
    queue<int> q_next;

    for (int i = 0; i < state_cnt; ++i) {
        used[i] = used_next[i] = false;
    }

    cin >> s1;
    const int &state = state_map[s1];

    q.push(state);

    string input;
    cin >> input;

    auto it = input.begin();
    bool good = true;
    for (; it != input.end(); ++it) {
        while (!q.empty()) {
            int from = q.front();
            q.pop();
            if (!used[from]) {
                q_next.push(from);
                used[from] = true;
            }
            // epsilon rules
            for (const int &to : rules[from * char_cnt]) {
                if (!used[to]) {
                    q.push(to);
                    q_next.push(to);
                    used[to] = true;
                }
            }
        }

        unsigned char uc = static_cast<unsigned char>(*it);
        while (!q_next.empty()) {
            int from = q_next.front();
            q_next.pop();
            for (const int &to : rules[from * char_cnt + uc]) {
                if (!used_next[to]) {
                    q.push(to);
                    used_next[to] = true;
                }
            }
        }
        if (q.empty()) {
            good = false;
            break;
        }
        // refresh arrays
        for (int i = 0; i < state_cnt; ++i) {
            used[i] = used_next[i] = false;
        }
    }

    if (good) {
        good = false;
        while (!q.empty()) {
            int st = q.front();
            q.pop();
            used[st] = true;
            if (final_states.find(st) != final_states.end()) {
                good = true;
                break;
            }
            // epsilon rules
            for (const int &to : rules[st * char_cnt]) {
                if (!used[to]) {
                    q.push(to);
                    used[to] = true;
                }
            }
        }
    }
    
    cout << good << endl << (it - input.begin()) << endl;
}
