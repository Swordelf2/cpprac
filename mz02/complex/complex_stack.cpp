#include "complex_stack.h"
#include <stdlib.h>

namespace numbers {

/* Main constructor */
complex_stack::complex_stack(size_t init_size) : cur_size(0), max_size(init_size)
{
    arr = (complex *) malloc(init_size * sizeof(complex));
}

/* Copy constructor */
complex_stack::complex_stack(const complex_stack &other) :
    cur_size(other.cur_size), max_size(other.max_size)
{
    arr = (complex *) malloc(max_size * sizeof(complex));
    for (size_t i = 0; i < cur_size; ++i) {
        arr[i] = other.arr[i];
    }
}

/* Destructor */
complex_stack::~complex_stack()
{
    free(arr);
}

/* Assignment operator */
complex_stack& complex_stack::operator=(const complex_stack &other)
{
    if (this != &other) {
        free(arr);
        cur_size = other.cur_size;
        max_size = other.max_size;
        arr = (complex *) malloc(max_size * sizeof(complex));
        for (size_t i = 0; i < cur_size; ++i) {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

complex& complex_stack::operator[](int i) const
{
    return arr[i];
}

complex_stack operator<<(complex_stack stack, const complex &c)
{
    if (stack.cur_size >= stack.max_size) {
        stack.extend();
    }
    new (stack.arr + stack.cur_size) complex(c);
    ++stack.cur_size;
    return stack;
}

complex& complex_stack::operator+() const
{
    return arr[cur_size - 1];
}

complex_stack operator~(complex_stack stack)
{
    --stack.cur_size;
    return stack;
}

size_t complex_stack::size() const
{
    return cur_size;
}

void complex_stack::extend()
{
    arr = (complex *) realloc(arr, (max_size *= STACK_EXTEND_MUL) * sizeof(complex));
}

}
