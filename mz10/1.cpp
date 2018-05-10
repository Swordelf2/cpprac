#include <iostream>

using namespace std;

size_t k;

void f(size_t pos, bool moved, string &s)
{
    if (pos == k) {
        cout << s << endl;
    } else {
        s[pos] = '1';
        f(pos + 1, true, s);
        s[pos] = '2';
        f(pos + 1, true, s);
        if (!moved) {
            s[pos] = '3';
            f(pos + 1, false, s);
            s[pos] = '4';
            f(pos + 1, false, s);
        }
    }
}


int main()
{
    string s;
    cin >> k;
    s.resize(k);
    f(0, false, s);
}

