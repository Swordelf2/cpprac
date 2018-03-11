#include <iostream>
#include <cstdio>
#include <cmath>
#include <iostream>
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

    friend std::ostream& operator<<(std::ostream &os, const complex &c);


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

std::ostream& operator<<(std::ostream &os, const complex &c)
{
    char s[BUF_SIZE];
    c.to_string(s, sizeof(s));
    os << s << std::endl;
    return os;
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


using numbers::complex;
using numbers::eval;

enum Args
{
    ARG_CENTER = 1,
    ARG_RADIUS = 2,
    ARG_N = 3,
    ARG_FUNC = 4
};

enum
{
    OUTPUT_BUF_SIZE = 128
};

inline complex GetPoint(const complex &center, double R, double angle);

int main(int argc, char **argv)
{
    complex center(argv[ARG_CENTER]);
    double R = strtod(argv[ARG_RADIUS], NULL);
    unsigned long N = strtol(argv[ARG_N], NULL, 0);

    char **expr = argv + ARG_FUNC;

    complex I = 0;
    complex prev_p = GetPoint(center, R, 0);
    double prev_angle = 0;
    for (unsigned long i = 1; i <= N; ++i) {
        double angle = 2.0 * M_PI * i / N;
        complex p = GetPoint(center, R, angle);
        complex val = eval(expr, GetPoint(center, R, (angle + prev_angle) * 0.5));
        I = I + val * (p - prev_p);
        prev_p = p;
        prev_angle = angle;
    }

    char buf[OUTPUT_BUF_SIZE];
    I.to_string(buf, sizeof(buf));
    std::cout << buf << std::endl;
}

complex GetPoint(const complex &center, double R, double angle)
{
    double cosine = cos(angle);
    double sine;
    if (angle <= M_PI) {
        sine = sqrt(1 - cosine * cosine);
    } else {
        sine = -sqrt(1 - cosine * cosine);
    }
    return center + complex(R * cosine, R * sine);
}
