#include <iostream>
#include <string>

using namespace std;

string s;

void f(int pos, int step)
{
    if (pos >= s.length()) {
        return;
    }
    if (s[pos] == '1' && s[pos - step - 1] == '0') {
        cout << '1';
        f(pos + 1, step + 1);
        cout << '0';
    } else {
        cout << '1';
        f(pos + 1, step + 1);
    }
}

int main()
{
    string s;
    while (cin >> s) {
        f(s.length() / 2, 0);
        cout << endl;
    }
}
