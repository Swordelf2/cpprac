#include <utility>

template <typename Iter>
void myreverse(Iter first, Iter last)
{
    int n = last - first;
    for (int i = 0; i < n / 2; ++i) {
        typename Iter::value_type temp = std::move(*(first + i));
        *(first + i) = std::move(*(last - 1 - i));
        *(last - 1 - i) = std::move(temp);
    }
}
