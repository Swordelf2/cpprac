template <typename Iter, typename F>
int myfilter(Iter first, Iter last, F f,
        typename Iter::value_type  val = {})
{
    int count = 0;
    for (auto it = first; it != last; ++it) {
        if (f(*it)) {
            *it = val;
            ++count;
        }
    }
    return count;
}
