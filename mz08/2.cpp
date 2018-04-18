#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    while (cin >> s) {
        auto it = s.begin();
        int c0 = 0, c1 = 0;
        while (it != s.end() && *it == '0') {
            ++it;
            ++c0;
        }
        while (it != s.end() && *it == '1') {
            ++it;
            ++c1;
        }
        bool flag = false;
        if (c0 > 0 && c1 > 0) {
            string u = s.substr(0, it - s.begin());
            size_t len = u.length();
            flag = true;
            while (it != s.end()) {
                auto new_pos = s.find(u, it - s.begin());
                if (new_pos == s.npos || new_pos != (size_t) (it - s.begin())) {
                    flag = false;
                    break;
                }
                if (it + len <= s.end()) {
                    it += len;
                } else {
                    flag = false;
                    break;
                }
            }
        }
        cout << flag << endl;
    }
}
