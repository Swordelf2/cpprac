#include <iostream>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <new>

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

enum
{
    STACK_INIT_SIZE = 16,
    STACK_EXTEND_MUL = 2
};

class complex_stack
{
    public:
    complex_stack(size_t init_size = 0);
    complex_stack(const complex_stack &other);
    complex_stack(complex_stack &&other);
    ~complex_stack();

    complex_stack& operator=(const complex_stack &other);
    complex_stack& operator=(complex_stack &&other);
    complex& operator[](int i) const;
    friend complex_stack operator<<(const complex_stack &stack, const complex &c);
    friend complex_stack operator<<(complex_stack &&stack, const complex &c);
    complex& operator+() const;
    friend complex_stack operator~(const complex_stack &stack);
    friend complex_stack operator~(complex_stack &&stack);

    size_t size() const;

    friend void swap(complex_stack &stack1, complex_stack &stack2);

    private:
    complex *arr;
    size_t cur_size;
    size_t max_size;

    void extend();
};

complex eval(char **args, const complex &z);

void PerformBinOp(complex_stack &stack, char op);
void PerformUnaryOp(complex_stack &stack, char op);

/* ## Definitions ## */


enum
{
    BUF_SIZE = 64
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


/* Main constructor */
complex_stack::complex_stack(size_t init_size)
    : cur_size(0), max_size(init_size)
{
    if (init_size > 0) {
        arr = (complex *) malloc(init_size * sizeof(*arr));
    } else {
        arr = nullptr;
    }
}

/* Copy constructor */
complex_stack::complex_stack(const complex_stack &other) :
    cur_size(other.cur_size), max_size(other.max_size)
{
    if (max_size > 0) {
        arr = (complex *) malloc(max_size * sizeof(*arr));
        std::copy(other.arr, other.arr + other.cur_size, arr);
    } else {
        arr = nullptr;
    }
}

/* Move constructor */
complex_stack::complex_stack(complex_stack &&other)
    : complex_stack()
{
    swap(*this, other);
}

/* Destructor */
complex_stack::~complex_stack()
{
    free(arr);
}

/* Copy assignment operator */
complex_stack& complex_stack::operator=(const complex_stack &other)
{
    // Copy and swap
    complex_stack copied_stack(other);
    swap(*this, copied_stack);
    return *this;
}

/* Move assignment operator */
complex_stack& complex_stack::operator=(complex_stack &&other)
{
    // here should be an assertion for not self-assignment
    free(arr);
    arr = other.arr;
    cur_size = other.cur_size;
    max_size = other.max_size;

    other.arr = nullptr;

    return *this;
}

complex& complex_stack::operator[](int i) const
{
    return arr[i];
}

complex_stack operator<<(const complex_stack &stack, const complex &c)
{
    return complex_stack(stack) << c;
}

complex_stack operator<<(complex_stack &&stack, const complex &c)
{
    complex_stack new_stack(std::move(stack));
    if (new_stack.cur_size >= new_stack.max_size) {
        new_stack.extend();
    }
    new (new_stack.arr + new_stack.cur_size) complex(c);
    ++new_stack.cur_size;
    return new_stack;
}

complex& complex_stack::operator+() const
{
    return arr[cur_size - 1];
}

complex_stack operator~(const complex_stack &stack)
{
    return ~(complex_stack(stack));
}

complex_stack operator~(complex_stack &&stack)
{
    complex_stack new_stack(std::move(stack));
    --new_stack.cur_size;
    return new_stack;
}

size_t complex_stack::size() const
{
    return cur_size;
}

void complex_stack::extend()
{
    if (arr == nullptr) {
        max_size = STACK_INIT_SIZE;
        arr = (complex *) malloc(max_size * sizeof(*arr));
    } else {
        arr = (complex *) realloc(arr, (max_size *= STACK_EXTEND_MUL) * sizeof(*arr));
    }
}

void swap(complex_stack &stack1, complex_stack &stack2)
{
    std::swap(stack1.arr, stack2.arr);
    std::swap(stack1.cur_size, stack2.cur_size);
    std::swap(stack1.max_size, stack2.max_size);
}



complex eval(char **args, const complex &z)
{
    complex_stack stack;
    while (*args != nullptr) {
        switch (**args) {
            case '(':
                stack = std::move(stack) << complex(*args);
                break;
            case 'z':
                stack = std::move(stack) << z;
                break;
            case '+': case '-': case '*': case '/':
                PerformBinOp(stack, **args);
                break;
            default:
                PerformUnaryOp(stack, **args);
                break;
        }
        ++args;
    }
    return +stack;
}

void PerformBinOp(complex_stack &stack, char op)
{
    complex c2 = +stack;
    stack = ~std::move(stack);
    complex c1 = +stack;
    stack = ~std::move(stack);
    complex res;
    switch (op) {
        case '+':
            res = c1 + c2;
            break;
        case '-':
            res = c1 - c2;
            break;
        case '*':
            res = c1 * c2;
            break;
        case '/':
            res = c1 / c2;
            break;
    }
    stack = std::move(stack) << res;
}

void PerformUnaryOp(complex_stack &stack, char op)
{
    complex &top_elem = +stack;
    complex c;
    switch (op) {
        case '!':
            stack = std::move(stack) << top_elem;
            break;
        case ';':
            stack = ~std::move(stack);
            break;
        case '~':
            c = ~top_elem;
            stack = (~std::move(stack)) << c;
            break;
        case '#':
            c = -top_elem;
            stack = (~std::move(stack)) << c;
            break;
    }
}

}
