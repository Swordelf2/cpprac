#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string s;
    while (cin >> s) {
        int max = 1;
        for (size_t len = s.length(); len >= 2; --len) {
            string cpy(s, 0, len);
            reverse(cpy.begin(), cpy.end());
            if (string(s, 0, len) == cpy) {
                max = len;
                break;
            }
        }
        cout << string(s, 0, max) << endl;
    }
}
