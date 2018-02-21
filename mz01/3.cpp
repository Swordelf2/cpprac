#include <iostream>

using namespace std;

class Sum
{
    public:
        int result;
    Sum(int a, int b) { result = a + b; };
    int get() { return result; };
};
