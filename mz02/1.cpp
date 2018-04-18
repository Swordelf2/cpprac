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
    double a = 0.0;
    double b = 0.0;
};

complex::complex() {}

complex::complex(const double &_a, double _b) : a(_a), b(_b) {}

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

}
