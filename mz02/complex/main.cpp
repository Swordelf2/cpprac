#include <stdio.h>
#include <iostream>
#include <string>
#include "complex.h"
#include "complex_stack.h"
#include "eval.h"

using namespace std;
using namespace numbers;

int main(int argc, char *argv[])
{
    double a, b;
    cin >> a >> b;
    cout << eval(argv + 1, complex(a, b));
}
