template <typename Iter>
void myreverse(Iter first, Iter last)
{
    if (first == last) {
        return;
    }
    --last;
    while (first < last) {
        auto t = *first;
        *first = *last;
        *last = t;
        ++first;
        --last;
    }
}
