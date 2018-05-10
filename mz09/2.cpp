#include <string>
#include <iostream>

using namespace std;

enum State
{
    Q000 = 0x0, Q001, Q010, Q011,
    Q100, Q101, Q110, Q111,
};

bool automatic(const string &s)
{
    enum State state = Q000;
    for (const char &c : s) {
        if (c == '0') {
            switch (state) {
            case Q000:
            case Q100:
                state = Q000;
                break;
            case Q001:
            case Q101:
                state = Q010;
                break;
            case Q010:
            case Q110:
                state = Q100;
                break;
            case Q011:
            case Q111:
                state = Q110;
                break;
            default:
                ;
            }
        } else if (c == '1') {
            switch (state) {
            case Q000:
            case Q100:
                state = Q001;
                break;
            case Q001:
            case Q101:
                state = Q011;
                break;
            case Q010:
            case Q110:
                state = Q101;
                break;
            case Q011:
            case Q111:
                state = Q111;
                break;
            default:
                ;
            }
        } else {
            return false;
        }
    }

    if (state == Q100 || state == Q101 ||
            state == Q110 || state == Q111) {
        return true;
    } else {
        return false;
    }
}

int main()
{
    string s;
    while (cin >> s) {
        cout << automatic(s) << endl;
    }
}
