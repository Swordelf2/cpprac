template <typename T>
typename T::value_type process(const T& t, int del_count = 3)
{
    typename T::value_type sum {};
    int i = 0;
    for (auto it = t.rbegin(); it != t.rend() && i < del_count; ++it) {
        sum = sum + *it;
        ++i;
    }
    return sum;
}
