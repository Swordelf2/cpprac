#include <iostream>

using namespace std;

class A
{
public:
    virtual void a() { cout << 1 << endl; }
    virtual void b() { cout << 2 << endl; }
    virtual void c() { cout << 3 << endl; }
    virtual void d() { cout << 4 << endl; }
    ~A() {}
};

class B : public A
{
public:
    virtual void a() { cout << 5 << endl; }
    virtual void b() { cout << 6 << endl; }
    ~B() {}
};

class C : public A
{
public:
    virtual void b() { cout << 7 << endl; }
    virtual void c() { cout << 8 << endl; }
    virtual void d() { cout << 9 << endl; }
    ~C() {}
};

class D: public B, public C
{
public:
    virtual void e() { cout << 10 << endl; }
    virtual void f() { cout << 11 << endl; }
    ~D() {}
};

class E : public D
{
public:
    virtual void a() { cout << 12 << endl; }
    virtual void d() { cout << 13 << endl; }
    virtual void f() { cout << 14 << endl; }
    ~E() {}
};

int main(void)
{
    A* pa1 = new B;
    B* pb1 = new E;
    C* pc1 = new D;
    B* pb2 = static_cast<B*>(new A);

    pa1->a(); // 1
    pa1->b(); // 2
    pb1->a(); // 3
    pb1->b(); // 4
    pb1->c(); // 5
    pb1->d(); // 6
    pc1->b(); // 7
    pc1->c(); // 8
    pc1->d(); // 9
    pb2->a(); // 10
    pb2->d(); // 11

    return 0;
}


/* Result 
1) 5
2) 2
3) 12
4) 6
5) 3
6) 4
7) 7
8) 8
9) 9
10) 1
11) 4
*/
