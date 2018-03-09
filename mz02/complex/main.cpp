#include <iostream>
#include "complex.h"
#include "complex_stack.h"

using namespace std;
using namespace numbers;

int main()
{
    double a, b;
    cin >> a >> b;
    numbers::complex c1(a, b);
    cin >> a >> b;
    numbers::complex c2(a, b);

    complex_stack stack, stack2;
    stack = stack << c1 << c2;
    stack2 = stack;
    stack2 = ~stack2;
    cout << stack[0] << endl;
    cout << +stack << endl;
    cout << +stack2 << endl;
}
