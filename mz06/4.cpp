#include <iostream>
#include <utility>

using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    int a1, b1, a2, b2;
    while (cin >> a1 >> b1 >> a2 >> b2) {
        int diff1 = abs(a2 - a1);
        int diff2 = abs(b2 - b1);
        int one = min(diff1, -diff1 + m);
        int two = min(diff2, -diff2 + n);
        cout << one + two << endl;
    }
}
