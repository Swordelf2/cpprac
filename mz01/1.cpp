#include <iostream>

using namespace std;

class A
{
    public:
        A(char z = 'x') { cout << 1 << endl; };
        A(int a, double b = 1.0) { cout << 2 << endl; };
        A(double z, int a = 2, int c = 3) { cout << 3 << endl;};
};

int
main()
{
    A v1;
    unsigned char z1 = 'y';
    A v2(z1);
    float z2 = 0.1f;
    A v3(z2);
    A v4 = A();
    A v5(z2, 1.0, 1.0);
    A v6(z1, z2);
}
