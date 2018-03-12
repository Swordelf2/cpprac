#include <utility>

template <typename Iter>
void myreverse(Iter first, Iter last)
{
    int n = last - first;
    for (int i = 0; i < n / 2; ++i) {
        std::swap(*(first + i), *(last - 1 - i));
    }
}
