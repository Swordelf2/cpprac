#include <memory>
#include <cstring>
#include <algorithm>

#include <iostream>

class String
{
    class Impl;
    std::unique_ptr<Impl> pImpl;
public:
    String();
    String(const String &other);
    String(const char *str);

    char& operator[](int i);
};

/* Implementation class */
class String::Impl
{
    char *buf = nullptr;
    size_t size = 0;
    size_t max_size = 0;
public:
    Impl();
    Impl(const Impl &other);
    Impl(const char *str);
    ~Impl();
};

/* String definitions */

String::String() : pImpl(std::make_unique<Impl>()) {}

String::String(const String &other) : pImpl(std::make_unique<Impl>(*other.pImpl)) {}

String::String(const char *str) : pImpl(std::make_unique<Impl>(str)) {}




/* String::Impl definitions */

String::Impl::Impl() {}

String::Impl::Impl(const Impl &other)
{
    std::cout << "copied ?? " << std::endl;
}

String::Impl::Impl(const char *str)
{
    max_size = size = std::strlen(str);
    buf = new char [max_size];
    std::copy(str, str + size, buf);
}

String::Impl::~Impl()
{
    // TODO: perform Copy on all phantoms of this string
    delete [] buf;
}

int main()
{
    String a;
    String b = a;
}
