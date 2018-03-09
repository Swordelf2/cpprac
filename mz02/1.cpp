#include <cstdio>
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

    friend complex operator+(const complex &c1, const complex &c2);
    friend complex operator-(const complex &c1, const complex &c2);
    friend complex operator*(const complex &c1, const complex &c2);
    friend complex operator/(const complex &c1, const complex &c2);

    complex operator~() const;
    complex operator-() const;

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

complex operator+(const complex &c1, const complex &c2)
{
    double resa = c1.get_re() + c2.get_re();
    double resb = c1.get_im() + c2.get_im();
    complex res(resa, resb);
    return res;
}

complex operator*(const complex &c1, const complex &c2) const
{
    return complex(c1.a * c2a - c1.b * c2.b, c1.a * c2.b + c2.a * c1.b);
}

const complex complex::operator/(complex other) const
{
    double resa = (c1.a * c2.a + c1.b * c2.b) / (c2.a * c2.a + c2.b * c2.b);
    double resb = (c2.a * c1.b - c1.a * c2.b) / (c2.a * c2.a + c2.b * c2.b);
    return complex(resa, resb);
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
