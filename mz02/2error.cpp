#include <stdio.h>
#include <cmath>
#include <iostream>

namespace numbers {
class complex
{
    public:
    complex();
    complex(const double &a, double _b = 0.0);
    explicit complex(const char *str);
    double get_re() const;
    double get_im() const;
    double abs2() const;
    double abs() const;
    void to_string(char *buf, size_t size) const;
    friend const complex operator+(complex c1, complex c2);
    const complex operator-(complex other) const;
    const complex operator*(complex other) const;
    const complex operator/(complex other) const;

    friend const complex operator+(double d, complex c);
    friend const complex operator-(double d, complex c);
    friend const complex operator*(double d, complex c);
    friend const complex operator/(double d, complex c);

    const complex operator~() const;
    const complex operator-() const;

    private:
    double a;
    double b;
};

complex::complex()
{
    a = b = 0.0;
}

complex::complex(const double &_a, double _b)
{
    a = _a;
    b = _b;
}

complex::complex(const char *str)
{
    sscanf(str, "(%lf, %lf)", &a, &b);
}

double complex::get_re() const
{
    return a;
}

double complex::get_im() const
{
    return b;
}

double complex::abs2() const
{
    return a * a + b * b;
}

double complex::abs() const
{
    return sqrt(abs2());
}

void complex::to_string(char *buf, size_t size) const
{
    snprintf(buf, size, "(%.10g,%.10g)", a, b);
}

const complex operator+(complex c1, complex c2)
{
    double resa = c1.get_re() + c2.get_re();
    double resb = c1.get_im() + c2.get_im();
    complex res(resa, resb);
    return res;
}

const complex complex::operator-(complex other) const
{
    double resa = a - other.get_re();
    double resb = b - other.get_im();
    complex res(resa, resb);
    return res;
}

const complex complex::operator*(complex other) const
{
    double resa = a * other.get_re() - b * other.get_im();
    double resb = a * other.get_im() + b * other.get_re();
    complex res(resa, resb);
    return res;
}

const complex complex::operator/(complex other) const
{
    double a1, a2, b1, b2;
    a1 = a;
    a2 = other.a;
    b1 = b;
    b2 = other.b;
    double resa = (a1 * a2 + b1 * b2) / (a2 * a2 + b2 * b2);
    double resb = (a2 * b1 - a1 * b2) / (a2 * a2 + b2 * b2);
    complex res(resa, resb);
    return res;
}


const complex operator+(double d, complex c)
{
    return c + d;
}

const complex operator-(double d, complex c)
{
    return -(c - d);
}

const complex operator*(double d, complex c)
{
    return c * d;
}

const complex operator/(double d, complex c)
{
    complex c0(d, 0);
    return c0 / c;
}

const complex complex::operator~() const
{
    double resa = a;
    double resb = -b;
    complex res(resa, resb);
    return res;
}

const complex complex::operator-() const
{
    double resa = -a;
    double resb = -b;
    complex res(resa, resb);
    return res;
}

class complex_stack
{
    public:
    complex_stack(size_t s = 0);
    complex_stack(const complex_stack &other);
    ~complex_stack();
    size_t size() const;
    complex &operator[](size_t i) const;
    complex_stack operator<<(const complex &c) const;
    complex operator+() const;
    complex_stack operator~() const;

    void add(complex c);
    void del();

    private:
    complex *elem;
    size_t max_size;
    size_t cur_size;
};


complex_stack::complex_stack(size_t s)
{
    if (s != 0) {
        max_size = s;
    } else {
        max_size = 16;
    }
    cur_size = 0;
    elem = new complex[16];
}

complex_stack::complex_stack(const complex_stack &other)
{
    max_size = other.max_size;
    cur_size = other.cur_size;
    elem = new complex [max_size];
    for (size_t i = 0; i < cur_size; ++i) {
        elem[i] = other.elem[i];
    }
}

complex_stack::~complex_stack()
{
    delete elem;
}

size_t complex_stack::size() const
{
    return cur_size;
}

complex &complex_stack::operator[](size_t i) const
{
    return elem[i];
}

complex_stack complex_stack::operator<<(const complex &c) const
{
    complex_stack new_stack = *this;
    new_stack.add(c);
    return new_stack;
}

complex complex_stack::operator+() const
{
    return elem[cur_size - 1];
}

complex_stack complex_stack::operator~() const
{
    complex_stack new_stack = *this;
    new_stack.del();
    return new_stack;
}

void complex_stack::add(complex c)
{
    if (cur_size >= max_size) {
        max_size *= 2;
        complex *new_mem = new complex [max_size];
        for (size_t i = 0; i < cur_size; ++i) {
            new_mem[i] = elem[i];
        }
        delete elem;
        elem = new_mem;
    }
    elem[cur_size++] = c;
}

void complex_stack::del()
{
    --cur_size;
}

}

using namespace numbers;
using namespace std;

int main()
{
    complex_stack stack;
    stack = stack << complex(3, 5);
    stack = stack << complex(2, 4);
    complex a = +stack;
    cout << a.get_re() << ' ' << a.get_im() << endl;
    stack = ~stack;
    a = +stack;
    cout << a.get_re() << ' ' << a.get_im() << endl;
}
