#include <functional>

template <typename Iter, typename F>
void sort(Iter first, Iter last, F f = std::less<typename Iter::value_type>)
{
    int n = last - first;
    for (int i = 0; i < n - 1; ++i) {
        min_ind = i;
        for (int j = i + 1; j < n; ++j) {
            if (f(*(first + ) {
                min_ind = j;
            }
        }
        std::swap(*(first + i), *(first + min_ind));
    }
}
