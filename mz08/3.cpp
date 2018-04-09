#include <string>
#include <iostream>
#include <ctype.h>

using namespace std;

int main()
{
    string s1, s2;
    bool empty = true;
    bool isgram = true;
    bool S = false;
    bool cf = true;
    bool lesslen = true;
    while (cin >> s1) {
        cin >> s2;
        empty = false;
        bool thisGood = false;
        for (auto it = s1.begin(); it != s1.end(); ++it) {
            if (!(islower(*it) || isdigit(*it))) {
                thisGood = true;
            }
        }
        if (!thisGood) {
            isgram = false;
        }
        if (s1 == "S") {
            S = true;
        }
        if (s2.length() < s1.length()) {
            lesslen = false;
        }
        if (!((s1.length() == 1) && ((isupper(s1[0])) || s1[0] == '_'))) {
            cf = false;
        }
    }
    if (empty || !S) {
        isgram = false;
    }

    if (!isgram) {
        cout << -1 << endl;
    } else if (cf) {
        cout << 2;
        if (lesslen) {
            cout << 3;
        }
        cout << endl;
    } else {
        cout << 10;
    }
}
