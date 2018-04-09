#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    while (cin >> s) {
        auto it = s.begin();
        while (it != s.end() && (*it == '3' || *it == '4')) {
            ++it;
        }
        while (it != s.end() && (*it == '1' || *it == '2')) {
            ++it;
        }
        if (it == s.end()) {
            cout << '1' << endl;
        } else {
            cout << '0' << endl;
        }
    }
}
