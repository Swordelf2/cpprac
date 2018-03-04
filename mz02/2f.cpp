#include <stdio.h>
#include <cmath>
#include <iostream>

namespace numbers {

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
