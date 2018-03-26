#include <iostream>
#include <utility>

using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    int a1, b1, a2, b2;
    while (cin >> a1 >> b1 >> a2 >> b2) {
        if (a2 < a1) {
            swap(a1, a2);
        }
        if (b2 < b1) {
            swap(b1, b2);
        }
        int one = min(a2 - a1, a1 - a2 + m);
        int two = min(b2 - b1, b1 - b2 + n);
        cout << one + two << endl;
    }
}
