#include <functional>

template <typename Iter, typename F = std::less<typename Iter::value_type>>
void selection_sort(Iter first, Iter last, F f = F())
{
    int n = last - first;
    for (int i = 0; i < n - 1; ++i) {
        int min_ind = i;
        for (int j = i + 1; j < n; ++j) {
            if (f(*(first + j), *(first + min_ind))) {
                min_ind = j;
            }
        }
        if (min_ind != i) {
            std::swap(*(first + i), *(first + min_ind));
        }
    }
}
