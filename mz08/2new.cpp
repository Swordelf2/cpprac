#include <iostream>
#include <ctype.h>

using namespace std;

int main()
{
    char c;
    cin.get(c);
    // word cycle
    while (cin) {
        int c0 = 0, c1 = 0;
        while (cin && c == '0') {
            ++c0;
            cin.get(c);
        }
        while (cin && c == '1') {
            ++c1;
            cin.get(c);
        }
        bool flag = false;
        if (c0 > 0 && c1 > 0) {
            flag = true;
            // 01 seq cycle
            while (flag) {
                if (!cin || isspace(c)) {
                    // all good
                    break;
                }
                
                for (int i = 0; i < c0; ++i) {

                    if (!(cin && c == '0')) {
                        flag = false;
                        break;
                    }
                    cin.get(c);
                }
                for (int i = 0; i < c1; ++i) {
                    if (!(cin && c == '1')) {
                        flag = false;
                        break;
                    }
                    cin.get(c);
                }
            }
        }
        cout << flag << endl;
        // skip until spaces
        while (cin && !isspace(c)) {
            cin.get(c);
        }
        // skip spaces
        while (cin && isspace(c)) {
            cin.get(c);
        }
    }
}
