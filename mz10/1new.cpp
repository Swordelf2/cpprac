#include <iostream>

using namespace std;

size_t k;

string s;

void f(size_t pos, bool moved)
{
    if (pos == k) {
        cout << s << endl;
    } else {
        s[pos] = '1';
        f(pos + 1, true);
        s[pos] = '2';
        f(pos + 1, true);
        if (!moved) {
            s[pos] = '3';
            f(pos + 1, false);
            s[pos] = '4';
            f(pos + 1, false);
        }
    }
}


int main()
{
    cin >> k;
    s.resize(k);
    f(0, false);
}
