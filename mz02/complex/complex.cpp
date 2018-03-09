#include <cstdio>
#include <cmath>
#include <iostream>

#include "complex.h"

enum
{
    BUF_SIZE = 64
};

namespace numbers {

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

complex operator+(const complex &c1, const complex &c2)
{
    double resa = c1.get_re() + c2.get_re();
    double resb = c1.get_im() + c2.get_im();
    complex res(resa, resb);
    return res;
}

complex operator-(const complex &c1, const complex &c2)
{
    return c1 + (-c2);
}

complex operator*(const complex &c1, const complex &c2)
{
    return complex(c1.a * c2.a - c1.b * c2.b, c1.a * c2.b + c2.a * c1.b);
}

complex operator/(const complex &c1, const complex &c2)
{
    double resa = (c1.a * c2.a + c1.b * c2.b) / (c2.a * c2.a + c2.b * c2.b);
    double resb = (c2.a * c1.b - c1.a * c2.b) / (c2.a * c2.a + c2.b * c2.b);
    return complex(resa, resb);
}


complex complex::operator~() const
{
    return complex(a, -b);
}

complex complex::operator-() const
{
    return complex(-a, -b);
}

std::ostream& operator<<(std::ostream &os, const complex &c)
{
    char s[BUF_SIZE];
    c.to_string(s, sizeof(s));
    os << s << std::endl;
    return os;
}

}
