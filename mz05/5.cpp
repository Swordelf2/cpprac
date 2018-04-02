#include <cmath>
#include <string>

class Circle : public Figure
{
    double r = 0.0;
public:
    static Circle *make(const std::string &s)
    {
        Circle *c = new Circle();
        c->r = std::stod(s, nullptr);
        return c;
    }
    double get_square() const override
    {
        return M_PI * r * r;
    }
};

class Square : public Figure
{
    double a = 0.0;
public:
    static Square *make(const std::string &s)
    {
        Square *c = new Square();
        c->a = std::stod(s, nullptr);
        return c;
    }
    double get_square() const override
    {
        return a * a;
    }
};

class Rectangle : public Figure
{
    double a = 0.0;
    double b = 0.0;
public:
    static Rectangle *make(const std::string &s)
    {
        Rectangle *c = new Rectangle();
        size_t pos;
        c->a = std::stod(s, &pos);
        c->b = std::stod(s.substr(pos), nullptr);
        return c;
    }
    double get_square() const override
    {
        return a * b;
    }
};
