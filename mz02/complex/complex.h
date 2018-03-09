#ifndef _COMPLEX_H
#define _COMPLEX_H

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

    friend std::ostream& operator<<(std::ostream &os, const complex &c);


    complex operator~() const;
    complex operator-() const;

    private:
    double a;
    double b;
};

}
#endif
