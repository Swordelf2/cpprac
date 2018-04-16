#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    while (cin >> s) {
        auto it = s.begin();
        bool flag = true;
        if (*it != 'a') {
            flag = false;
        }
        ++it;
        int n = 0, m = 0;
        int n2 = 0, m2 = 0;
        while (it != s.end() && *it == 'a') {
            ++it;
            ++n;
        }
        while (it != s.end() && *it == '0') {
            ++it;
            ++m;
        }
        if (it == s.end() || *it != 'b') {
            flag = false;
        }
        ++n2;
        while (it != s.end() && *it == 'b') {
            ++it;
            ++n2;
        }
        while (it != s.end() && *it == '1') {
            ++it;
            ++m2;
        }
        if (it != s.end()) {
            flag = false;
        }
        if (n != n2 || m != m2) {
            flag = false;
        }
        cout << flag << endl;
    }
}
