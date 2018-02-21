#include <iostream>

using std::cout;
using std::endl;

void f(int a, int b = 1)
{
    cout << 2 << endl;
}

void f(int a, const char *s)
{
    cout << 2 << endl;
}
