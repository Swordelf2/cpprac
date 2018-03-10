#include <stdlib.h>
#include <new>

namespace numbers {

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

}
