#ifndef CSTACK_H
#define CSTACK_H

#include "complex.h" 


namespace numbers {

enum
{
    STACK_INIT_SIZE = 16,
    STACK_EXTEND_MUL = 2
};

class complex_stack
{
    public:
    complex_stack(size_t init_size = 16);
    complex_stack(const complex_stack &other);
    ~complex_stack();

    complex_stack& operator=(const complex_stack &other);
    complex& operator[](int i) const;
    friend complex_stack operator<<(complex_stack stack, const complex &c);
    complex& operator+() const;
    friend complex_stack operator~(complex_stack stack);

    size_t size() const;

    private:
    complex *arr;
    size_t cur_size;
    size_t max_size;

    void extend();
};

}

#endif
