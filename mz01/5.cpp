#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

// b is the denominator
class Rational
{
    public:
    Rational();
    Rational(int _a);
    Rational(int _a, int _b);
    
    Rational &Add(Rational r2);
    Rational &Substract(Rational r2);
    Rational &Multiply(Rational r2);
    Rational &Divide(Rational r2);

    bool EqualTo(Rational r2) const;
    int CompareTo(Rational r2) const;
    bool IsInteger() const;
    string ToString() const;


    private:
    int a, b;
    void Reduce();
};

Rational::Rational()
{
    a = 0;
    b = 1;
}

Rational::Rational(int _a)
{
    a = _a;
    b = 1;
}

Rational::Rational(int _a, int _b)
{
    if (_b < 0) {
        _a = -_a;
        _b = -_b;
    }
    a = _a;
    b = _b;
    Reduce();
}

void Rational::Reduce()
{
    int preva = a;
    int prevb = b;

    // Euclid
    if (a < 0) {
        a = -a;
    }
    if (a < b) {
        int t = a;
        a = b;
        b = t;
    }
    while (b)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    // now a is the largest common divisor
    int lcd = a;
    a = preva / lcd;
    b = prevb / lcd;
}

Rational &Rational::Add(Rational r2)
{
    int prevb = b;
    b = b * r2.b;
    a = a * r2.b + r2.a * prevb;
    Reduce();
    return *this;
}
    
Rational &Rational::Substract(Rational r2)
{
    r2.a = -r2.a;
    return Add(r2);
}

Rational &Rational::Multiply(Rational r2)
{
    a = a * r2.a;
    b = b * r2.b;
    Reduce();
    return *this;
}

Rational &Rational::Divide(Rational r2)
{
    a = a * r2.b;
    b = b * r2.a;
    if (b < 0) {
        a = -a;
        b = -b;
    }
    Reduce();
    return *this;
}

bool Rational::EqualTo(Rational r2) const
{
    return (a == r2.a) && (b == r2.b);
}

int Rational::CompareTo(Rational r2) const
{
    return a * r2.b - b * r2.a;
}

bool Rational::IsInteger() const
{
    return b == 1;
}

string Rational::ToString() const
{
    char s[100];
    snprintf(s, sizeof(s), "%d:%d", a, b);
    string str = s;
    return str;
}
