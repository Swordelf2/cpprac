#include <iostream>

using namespace std;

/* Grammar:
S -> aSd | aAd
A -> bAc | bc
*/

void f(int k, int n);
void S(int k, int n);
void A(int m);

void f(int k, int n)
{
    S(k, n);
    cout << endl;
    if (n > 1) {
        f(k, n - 1);
    }
}

void S(int k, int n)
{
    cout << 'a';
    if (n > 1) {
        S(k - 2, n - 1);
    } else {
        A(k / 2 - n);
    }
    cout << 'd';
}

void A(int m)
{
    cout << 'b';
    if (m > 1) {
        A(m - 1);
    }
    cout << 'c';
}

int main()
{
    int k;
    cin >> k;
    if (k % 2 == 0 && k >= 4) {
        f(k, k / 2 - 1);
    }
}
