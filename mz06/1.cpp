#include <iostream>

class A
{
public:
    int a;
    A(int b = 0) { a = b; };
    ~A() { std::cout << a << std::endl; };
};

void f(void)
{
    int b;
    if (!(std::cin >> b)) {
        throw 0;
    }
    A a(b);

    f();
}

int main()
{
    try
    {
        f();
    }
    catch (int)
    {
        ;
    }
}
