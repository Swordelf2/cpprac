#include <iostream>
#include <string>

using namespace std;

// Grammar (type 1)
/*
S -> AB
A -> aAb | ab
B -> CB1 | C1
bC -> Cb
aC -> a0
0C -> 00
*/

int main()
{
    string s;
    while (cin >> s) {
        auto it = s.begin();
        bool flag = true;
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
        if (n == 0 || m == 0 || n != n2 || m != m2) {
            flag = false;
        }
        cout << flag << endl;
    }
}
