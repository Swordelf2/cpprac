#include <utility>
#include <functional>

template <typename Iter, typename F = std::less<typename Iter::value_type>>
void selection_sort(Iter first, Iter last, F f = F())
{
    if (first == last) {
        return;
    }
    for (Iter it = first; it < last - 1; ++it) {
        Iter min_it = it;
        for (Iter it_inner = it + 1; it_inner != last; ++it_inner) {
            if (f(*it_inner, *min_it)) {
                min_it = it_inner;
            }
        }
        if (min_it != it) {
            // swap values of min_it and it
            std::swap(*min_it, *it);
        }
    }
}
