#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    char c;
    c = cin.get();
    while (cin) {
        char b;
        int count = cin ? 1 : 0;
        while ((b = cin.get()) && cin && b == c) {
            ++count;
        }
        if (count > 4 || c == '#') {
            // rle
            cout << '#' << c << hex << count << '#';
        } else {
            for (int i = 0; i < count; ++i) {
                cout << c;
            }
        }
        c = b;
    }
}
