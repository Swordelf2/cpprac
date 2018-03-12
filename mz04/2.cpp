template <typename T>
typename T::value_type process(const T& t)
{
    typename T::value_type sum {};
    int i = 0;
    for (auto it = t.rbegin(); it != t.rend() && i < 3; ++it) {
        sum = sum + *it;
        ++i;
    }
    return sum;
}
